#ifndef VIRTUALDRAGON_AUXILIARY_H
#define VIRTUALDRAGON_AUXILIARY_H

#include "dvmdef.h"

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

#define GET_OPCODE(i)   ( (i & 0x0FE00000u) >> 21u )    // 7    bit
#define GET_OPCODE4(i)  ( (i & 0x0F000000u) >> 24u )    // 4    bit
#define GET_R0(i)       ( (i & 0x001F0000u) >> 16u )    // 5    bit
#define GET_R1(i)       ( (i & 0x0000F800u) >> 11u )    // 5    bit
#define GET_R2(i)       ( (i & 0x000007C0u) >> 6u )     // 5    bit
#define GET_R3(i)       ( (i & 0x0000003Eu) >> 1u )     // 5    bit

#define GET_IMM8(i)     ( i & 0x000000FFu )             // 8    bit
#define GET_IMM16(i)    ( i & 0x0000FFFFu )             // 16   bit
#define GET_IMM24(i)    ( i & 0x00FFFFFFu )             // 24   bit
#define GET_IMM32(i)    ( i & 0x00000000FFFFFFFFull)    // 32   bit

#if defined(DVM_ENABLE_JUMPR)
#   define JUMPR(r) IP = (r)
#endif

#if defined(DVM_ENABLE_JUMP24)
#   define JUMP24() IP = CP + GET_IMM24(instruction)
#endif

#if defined(DVM_ENABLE_JUMP16)
#   define JUMP16() IP = CP + GET_IMM16(instruction)
#endif

#if defined(DVM_ENABLE_JUMP8)
#   define JUMP8() IP = CP + GET_IMM8(instruction)
#endif

#define SVI_EXIT            ( 0x00 )
#define SVI_RESET           ( 0x01 )
#define SVI_TRACE           ( 0x02 )
#define SVI_BREAKPOINT      ( 0x03 )
#define SVI_IO              ( 0x04 )
#define SVI_ILLEGAL_OPCODE  ( 0x05 )

#define SVI_INVOKE          ( 0x0F )

#define SVI_CPU_SPECIFIC    ( 0x20 )
#define SVI_FREE            ( 0x40 )

#define STUB return

#endif //VIRTUALDRAGON_AUXILIARY_H
