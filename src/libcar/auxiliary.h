#ifndef VIRTUALDRAGON_AUXILIARY_H
#define VIRTUALDRAGON_AUXILIARY_H

#include "dvmdef.h"
#include "interrupts.h"

#define C4146_FIX(o, m) (REGISTER)(o(IREGISTER)m)

#define IF_EQ() if ( (cvtR2FR(FR)->vm_status & EQ) )        // EQual
#define IF_NE() if (!(cvtR2FR(FR)->vm_status & EQ) )        // Not Equal

// Signed
#define IF_LE() if ( (cvtR2FR(FR)->vm_status & (LT|EQ)) )   // Less than or Equal
#define IF_GE() if (!(cvtR2FR(FR)->vm_status & LT) )        // Greater than or Equal
#define IF_LT() if ( (cvtR2FR(FR)->vm_status & LT) )        // Less Than
#define IF_GT() if (!(cvtR2FR(FR)->vm_status & (LT|EQ)) )   // Greater Than

// Unsigned
#define IF_LS() if ( (cvtR2FR(FR)->vm_status & (LO|EQ)) )   // Lower or Same
#define IF_HS() if (!(cvtR2FR(FR)->vm_status & LO) )        // Higher or Same
#define IF_LO() if ( (cvtR2FR(FR)->vm_status & LO) )        // LOwer
#define IF_HI() if (!(cvtR2FR(FR)->vm_status & (LO|EQ)) )   // HIgher

#if defined(CAR_32)
#   define GET_OPCODE7(i)  ( (i & 0x0FE00000u) >> 21u )     // 7    bit
#   define GET_OPCODE4(i)  ( (i & 0x0F000000u) >> 24u )     // 4    bit
#   define GET_R0(i)       ( (i & 0x001F0000u) >> 16u )     // 5    bit
#   define GET_R1(i)       ( (i & 0x0000F800u) >> 11u )     // 5    bit
#   define GET_R2(i)       ( (i & 0x000007C0u) >> 6u )      // 5    bit
#   define GET_R3(i)       ( (i & 0x0000003Eu) >> 1u )      // 5    bit
#elif defined(CAR_64)
#   define GET_OPCODE8(i)  ( (i & 0x00FF000000000000ull) >> 48u )   // 8    bit
#   define GET_R0(i)       ( (i & 0x0000F80000000000ull) >> 43u )   // 5    bit
#   define GET_R1(i)       ( (i & 0x000007C000000000ull) >> 38u )   // 5    bit
#   define GET_R2(i)       ( (i & 0x0000003E00000000ull) >> 33u )   // 5    bit
#   define GET_A(i)        ( (i & 0x0000000100000000ull) >> 32u )   // Alternative
#endif

#define GET_IMM8(i)     ( i & 0x000000FFu )             // 8    bit
#define GET_IMM16(i)    ( i & 0x0000FFFFu )             // 16   bit
#define GET_IMM24(i)    ( i & 0x00FFFFFFu )             // 24   bit
#define GET_IMM32(i)    ( i & 0x00000000FFFFFFFFull )   // 32   bit
#define GET_IMM48(i)    ( i & 0x0000FFFFFFFFFFFFull )   // 48   bit

#if defined(DVM_ENABLE_JUMPR)
#   define JUMPR(r) IP = (r)
#endif

#if defined(DVM_ENABLE_RJUMP48)
#   define RJUMP48() IP += ( (IREGISTER)GET_IMM48(instruction) )
#endif

#if defined(DVM_ENABLE_JUMP48)
#   define JUMP48() IP = ( (REGISTER)GET_IMM48(instruction) )
#endif

#if defined(DVM_ENABLE_JUMP32)
#   define JUMP32() IP += ( (IREGISTER)GET_IMM32(instruction) )
#endif

#if defined(DVM_ENABLE_JUMP24)
#   define JUMP24() IP += DVM_SIGN_EXTEND((REGISTER)GET_IMM24(instruction), 24)
#endif

#if defined(DVM_ENABLE_JUMP16)
#   define JUMP16() IP += DVM_SIGN_EXTEND((REGISTER)GET_IMM16(instruction), 16)
#endif

#if defined(DVM_ENABLE_JUMP8)
#   define JUMP8() IP += ( (IREGISTER)GET_IMM8(instruction) )
#endif

#define STUB return

#endif //VIRTUALDRAGON_AUXILIARY_H
