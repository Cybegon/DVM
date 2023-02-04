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
    if ((var << i) & (1u << (bits - 1)))

VOID DVM_FASTCALL format_l64(DVM* state, duint64 instruction)
{
    vmdispatch(GET_OPCODE8(instruction)) {
        vmcase(OP_PUSH) {
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { PUSH(REGISTER, R(i));         }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { PUSH(REGISTER, R(i + 1));     }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { PUSH(REGISTER, R(i + 2));     }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { PUSH(REGISTER, R(i + 3));     }
            }
            vmbreak;
        }
        vmcase(OP_POP) {
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)      = POP(REGISTER); }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1)  = POP(REGISTER); }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2)  = POP(REGISTER); }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3)  = POP(REGISTER); }
            }
            vmbreak;
        }
        vmcase(OP_SWP) {
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { DVM_BSWAP64( R(i) );      }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { DVM_BSWAP64( R(i + 1) );  }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { DVM_BSWAP64( R(i + 2) );  }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { DVM_BSWAP64( R(i + 3) );  }
            }
            vmbreak;
        }
        vmcase(OP_ADD) {
// TODO: сделать еще один вариант, и ILLEGAL_OPCODE для OP_MOD
//            if (r bit enabled) {
//                ITERATE_REGISTERS(i > 0, i -= 4) {
//                    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i);     += R(GET_R0(instruction))   }
//                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1); += R(GET_R0(instruction))   }
//                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2); += R(GET_R0(instruction))   }
//                    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3); += R(GET_R0(instruction))   }
//                }
//            }
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) += R(i);       }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) += R(i + 1);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) += R(i + 2);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) += R(i + 3);   }
            }
            vmbreak;
        }
        vmcase(OP_SUB) {
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) -= R(i);       }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) -= R(i + 1);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) -= R(i + 2);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) -= R(i + 3);   }
            }
            vmbreak;
        }
        vmcase(OP_INC) {
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { ++R(i);       }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { ++R(i + 1);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { ++R(i + 2);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { ++R(i + 3);   }
            }
            vmbreak;
        }
        vmcase(OP_DEC) {
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { --R(i);       }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { --R(i + 1);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { --R(i + 2);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { --R(i + 3);   }
            }
            vmbreak;
        }
        vmcase(OP_MUL) {
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) *= R(i);       }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) *= R(i + 1);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) *= R(i + 2);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) *= R(i + 3);   }
            }
            vmbreak;
        }
        vmcase(OP_DIV) {
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) /= R(i);       }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) /= R(i + 1);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) /= R(i + 2);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) /= R(i + 3);   }
            }
            vmbreak;
        }
        vmcase(OP_IMUL) {
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)R(i) );     }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)R(i + 1) ); }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)R(i + 2) ); }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)R(i + 3) ); }
            }
            vmbreak;
        }
        vmcase(OP_IDIV) {
            ITERATE_REGISTERS(i > 0, i -= 4) {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)R(i) );     }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)R(i + 1) ); }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)R(i + 2) ); }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) = ( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)R(i + 3) ); }
            }
            vmbreak;
        }
        vmcase(OP_MOD) {

            vmbreak;
        }
        vmcase(OP_SHL) {

            vmbreak;
        }
        vmcase(OP_SHR) {

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
