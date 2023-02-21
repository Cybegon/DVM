#include "format-l.h"

#include "dvmstate.h"
#include "dvmdef.h"
#include "vcpu.h"
#include "dvmflags.h"

#define CAR_FORMAT_I
#include "opcodes.h"

#define CAR_64
#define DVM_ENABLE_JUMP32
#include "auxiliary.h"

#define ITERATE_REGISTERS(c, o)             \
    for (duint16 i = REGISTER_COUNT; c; o)

#define IF_BIT_ENABLED(var, pos, bits)      \
    if ((var << i) & (1u << (bits - 1u)))

VOID DVM_FASTCALL format_l64(DVM* state, duint64 instruction)
{
    vmdispatch(GET_OPCODE8(instruction)) {
        vmcase(OP_PUSH) {
            if (GET_A(instruction)) {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
            } else {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { PUSH(REGISTER, R(i));         }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { PUSH(REGISTER, R(i + 1));     }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { PUSH(REGISTER, R(i + 2));     }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { PUSH(REGISTER, R(i + 3));     }
                }
            }
            vmbreak;
        }
        vmcase(OP_POP) {
            if (GET_A(instruction)) {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
            } else {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)      = POP(REGISTER); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1)  = POP(REGISTER); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2)  = POP(REGISTER); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3)  = POP(REGISTER); }
                }
            }
            vmbreak;
        }
        vmcase(OP_SWP) {
            if (GET_A(instruction)) {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
            } else {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { DVM_BSWAP64( R(i) );      }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { DVM_BSWAP64( R(i + 1) );  }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { DVM_BSWAP64( R(i + 2) );  }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { DVM_BSWAP64( R(i + 3) );  }
                }
            }
            vmbreak;
        }
        vmcase(OP_ADD) {
            if (GET_A(instruction)) {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) += R(i);       }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) += R(i + 1);   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) += R(i + 2);   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) += R(i + 3);   }
                }
            } else {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)     += R(GET_R0(instruction));   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1) += R(GET_R0(instruction));   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2) += R(GET_R0(instruction));   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3) += R(GET_R0(instruction));   }
                }
            }
            vmbreak;
        }
        vmcase(OP_SUB) {
            if (GET_A(instruction)) {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) -= R(i);       }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) -= R(i + 1);   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) -= R(i + 2);   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) -= R(i + 3);   }
                }
            } else {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)     -= R(GET_R0(instruction));   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1) -= R(GET_R0(instruction));   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2) -= R(GET_R0(instruction));   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3) -= R(GET_R0(instruction));   }
                }
            }
            vmbreak;
        }
        vmcase(OP_INC) {
            if (GET_A(instruction)) {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
            } else {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { ++R(i);       }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { ++R(i + 1);   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { ++R(i + 2);   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { ++R(i + 3);   }
                }
            }
            vmbreak;
        }
        vmcase(OP_DEC) {
            if (GET_A(instruction)) {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
            } else {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { --R(i);       }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { --R(i + 1);   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { --R(i + 2);   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { --R(i + 3);   }
                }
            }
            vmbreak;
        }
        vmcase(OP_MUL) {
            if (GET_A(instruction)) {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) *= R(i);       }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) *= R(i + 1);   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) *= R(i + 2);   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) *= R(i + 3);   }
                }
            } else {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)     *= R(GET_R0(instruction));   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1) *= R(GET_R0(instruction));   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2) *= R(GET_R0(instruction));   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3) *= R(GET_R0(instruction));   }
                }
            }
            vmbreak;
        }
        vmcase(OP_DIV) {
            if (GET_A(instruction)) {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) /= R(i);       }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) /= R(i + 1);   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) /= R(i + 2);   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) /= R(i + 3);   }
                }
            } else {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)     /= R(GET_R0(instruction));   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1) /= R(GET_R0(instruction));   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2) /= R(GET_R0(instruction));   }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3) /= R(GET_R0(instruction));   }
                }
            }
            vmbreak;
        }
        vmcase(OP_IMUL) {
            if (GET_A(instruction)) {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)R(i) );     }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)R(i + 1) ); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)R(i + 2) ); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)R(i + 3) ); }
                }
            } else {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)      = ( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)R(i) );     }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1)  = ( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)R(i + 1) ); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2)  = ( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)R(i + 2) ); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3)  = ( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)R(i + 3) ); }
                }
            }
            vmbreak;
        }
        vmcase(OP_IDIV) {
            if (GET_A(instruction)) {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)R(i) );     }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)R(i + 1) ); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)R(i + 2) ); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)R(i + 3) ); }
                }
            } else {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)      = ( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)R(i) );     }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1)  = ( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)R(i + 1) ); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2)  = ( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)R(i + 2) ); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3)  = ( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)R(i + 3) ); }
                }
            }
            vmbreak;
        }
        vmcase(OP_MOD) {
            if (GET_A(instruction)) {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
            } else {
                ITERATE_REGISTERS(i > 0, i -= 4) {
                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)      = ( (IREGISTER)R(GET_R0(instruction)) ) % ( (IREGISTER)R(i) );     }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1)  = ( (IREGISTER)R(GET_R0(instruction)) ) % ( (IREGISTER)R(i + 1) ); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2)  = ( (IREGISTER)R(GET_R0(instruction)) ) % ( (IREGISTER)R(i + 2) ); }
                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3)  = ( (IREGISTER)R(GET_R0(instruction)) ) % ( (IREGISTER)R(i + 3) ); }
                }
            }
            vmbreak;
        }
        vmcase(OP_SHL) {
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)     <<= R(GET_R0(instruction));   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1) <<= R(GET_R0(instruction));   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2) <<= R(GET_R0(instruction));   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3) <<= R(GET_R0(instruction));   }
            }
            vmbreak;
        }
        vmcase(OP_SHR) {
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)     >>= R(GET_R0(instruction));   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1) >>= R(GET_R0(instruction));   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2) >>= R(GET_R0(instruction));   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3) >>= R(GET_R0(instruction));   }
            }
            vmbreak;
        }
        vmcase(OP_ROL) {

            vmbreak;
        }
        vmcase(OP_ROR) {

            vmbreak;
        }
    }
}
