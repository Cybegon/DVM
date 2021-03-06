#ifndef VIRTUALDRAGON_AUXILIARY_H
#define VIRTUALDRAGON_AUXILIARY_H

#include "dvmdef_p.h"

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

#define DVM_GET_IMM8(i)     ( i & 0x000000FFu )             // 8    bit
#define DVM_GET_IMM16(i)    ( i & 0x0000FFFFu )             // 16   bit
#define DVM_GET_IMM24(i)    ( i & 0x00FFFFFFu )             // 24   bit
#define DVM_GET_IMM32(i)    ( i & 0x00000000FFFFFFFFull)    // 32   bit

#if defined(DVM_ENABLE_JUMP24)
#   define JUMP24() IP = CP + DVM_GET_IMM24(instruction)
#endif

#if defined(DVM_ENABLE_JUMP16)
#   define JUMP16() IP = CP + DVM_GET_IMM16(instruction)
#endif

#define SVI_EXIT            0x00
#define SVI_RESET           0x01
#define SVI_TRACE           0x02
#define SVI_BREAKPOINT      0x03
#define SVI_IO              0x04
#define SVI_ILLEGAL_OPCODE  0x05

#define SVI_INVOKE          0x0F

#define SVI_CPU_SPECIFIC    0x20
#define SVI_FREE            0x40

#endif //VIRTUALDRAGON_AUXILIARY_H
