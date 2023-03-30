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

// TODO: Make the code more readable

#define ITERATE_REGISTERS4                          \
    for (duint16 i = REGISTER_COUNT; i > 0; i -= 4)

#define ITERATE_REGISTERS                   \
    ITERATE_REGISTERS4

#define IF_BIT_ENABLED(var, pos, bits)      \
    if (( (var) << (pos) ) & ( 1u << ((bits) - 1u) ))

#define ARITH_REG2LIST4(i, op, type)                                                                                                            \
    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(GET_R0(instruction)) = ( (type)R(i) )     op ( (type)R(GET_R0(instruction)) ); }    \
    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(GET_R0(instruction)) = ( (type)R(i + 1) ) op ( (type)R(GET_R0(instruction)) ); }    \
    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(GET_R0(instruction)) = ( (type)R(i + 2) ) op ( (type)R(GET_R0(instruction)) ); }    \
    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(GET_R0(instruction)) = ( (type)R(i + 3) ) op ( (type)R(GET_R0(instruction)) ); }

#define ARITH_LIST2REG4(i, op, type)                                                                                            \
    IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)      = ( (type)R(i) )     op ( (type)R(GET_R0(instruction)) ); } \
    IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1)  = ( (type)R(i + 1) ) op ( (type)R(GET_R0(instruction)) ); } \
    IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2)  = ( (type)R(i + 2) ) op ( (type)R(GET_R0(instruction)) ); } \
    IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3)  = ( (type)R(i + 3) ) op ( (type)R(GET_R0(instruction)) ); }



#define IF_ALT() if (GET_A(instruction))

VOID DVM_FASTCALL format_l64(DVM* state, duint64 instruction)
{
    vmdispatch(GET_OPCODE8(instruction)) {
        vmcase(OP_PUSH) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { PUSH(REGISTER, R(i));         }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { PUSH(REGISTER, R(i + 1));     }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { PUSH(REGISTER, R(i + 2));     }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { PUSH(REGISTER, R(i + 3));     }
            }
            vmbreak;
        }
        vmcase(OP_POP) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)      = POP(REGISTER); }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1)  = POP(REGISTER); }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2)  = POP(REGISTER); }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3)  = POP(REGISTER); }
            }
            vmbreak;
        }
        vmcase(OP_SWP) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { DVM_BSWAP64( R(i) );      }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { DVM_BSWAP64( R(i + 1) );  }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { DVM_BSWAP64( R(i + 2) );  }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { DVM_BSWAP64( R(i + 3) );  }
            }
            vmbreak;
        }

        // !~IA - Integer arithmetic
        vmcase(OP_ADD) {
            IF_ALT() {
                ITERATE_REGISTERS {
                    ARITH_REG2LIST4(i, +, REGISTER)
                }
                vmbreak;
            }

           ITERATE_REGISTERS {
               ARITH_LIST2REG4(i, +, REGISTER)
           }
           vmbreak;
        }
        vmcase(OP_SUB) {
            IF_ALT() {
                ITERATE_REGISTERS {
                    ARITH_REG2LIST4(i, -, REGISTER)
                }
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, -, REGISTER)
            }
            vmbreak;
        }
        vmcase(OP_INC) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { ++R(i);       }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { ++R(i + 1);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { ++R(i + 2);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { ++R(i + 3);   }
            }
            vmbreak;
        }
        vmcase(OP_DEC) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { --R(i);       }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { --R(i + 1);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { --R(i + 2);   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { --R(i + 3);   }
            }
            vmbreak;
        }
        vmcase(OP_MUL) {
            IF_ALT() {
                ITERATE_REGISTERS {
                    ARITH_REG2LIST4(i, *, REGISTER)
                }
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, *, REGISTER)
            }
            vmbreak;
        }
        vmcase(OP_DIV) {
            IF_ALT() {
                ITERATE_REGISTERS {
                    ARITH_REG2LIST4(i, /, REGISTER)
                }
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, /, REGISTER)
            }
            vmbreak;
        }
        vmcase(OP_IMUL) {
            IF_ALT() {
                ITERATE_REGISTERS {
                    ARITH_REG2LIST4(i, *, IREGISTER)
                }
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, *, IREGISTER)
            }
            vmbreak;
        }
        vmcase(OP_IDIV) {
            IF_ALT() {
                ITERATE_REGISTERS {
                    ARITH_REG2LIST4(i, /, IREGISTER)
                }
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, /, IREGISTER)
            }
            vmbreak;
        }
        vmcase(OP_MOD) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, %, REGISTER)
            }
            vmbreak;
        }
        vmcase(OP_SHL) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, <<, REGISTER)
            }
            vmbreak;
        }
        vmcase(OP_SHR) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, >>, REGISTER)
            }
            vmbreak;
        }
        vmcase(OP_ASHL) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, <<, IREGISTER)
            }
            vmbreak;
        }
        vmcase(OP_ASHR) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, >>, IREGISTER)
            }
            vmbreak;
        }
        vmcase(OP_ROL) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                ROL(R(i),     R(i),       R(GET_R0(instruction)))
                ROL(R(i + 1), R(i + 1),   R(GET_R0(instruction)))
                ROL(R(i + 2), R(i + 2),   R(GET_R0(instruction)))
                ROL(R(i + 3), R(i + 3),   R(GET_R0(instruction)))
            }
            vmbreak;
        }
        vmcase(OP_ROR) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                ROR(R(i),     R(i),       R(GET_R0(instruction)))
                ROR(R(i + 1), R(i + 1),   R(GET_R0(instruction)))
                ROR(R(i + 2), R(i + 2),   R(GET_R0(instruction)))
                ROR(R(i + 3), R(i + 3),   R(GET_R0(instruction)))
            }
            vmbreak;
        }

        // !~L - Logic
        vmcase(OP_AND) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, &, IREGISTER)
            }
            vmbreak;
        }
        vmcase(OP_NAND) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, & ~, IREGISTER)
            }
            vmbreak;
        }
        vmcase(OP_OR) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, |, IREGISTER)
            }
            vmbreak;
        }
        vmcase(OP_NOR) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, | ~, IREGISTER)
            }
            vmbreak;
        }
        vmcase(OP_XOR) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                ARITH_LIST2REG4(i, ^, IREGISTER)
            }
            vmbreak;
        }
        vmcase(OP_NOT) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)      = ~R(i);        }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1)  = ~R(i + 1);    }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2)  = ~R(i + 2);    }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3)  = ~R(i + 3);    }
            }
            vmbreak;
        }
        vmcase(OP_NEG) {
            IF_ALT() {
                state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
                vmbreak;
            }

            ITERATE_REGISTERS {
                IF_BIT_ENABLED(GET_IMM32(instruction), i    , 32)   { R(i)      = C4146_FIX(-, R(i));       }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 1, 32)   { R(i + 1)  = C4146_FIX(-, R(i + 1));   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 2, 32)   { R(i + 2)  = C4146_FIX(-, R(i + 2));   }
                IF_BIT_ENABLED(GET_IMM32(instruction), i + 3, 32)   { R(i + 3)  = C4146_FIX(-, R(i + 3));   }
            }
            vmbreak;
        }
    }
}
