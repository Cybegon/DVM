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

#if defined(DVM_ENABLE_JUMP)
#   define JUMP() IP = DVM_GET_IMM24(instruction)
#endif

#endif //VIRTUALDRAGON_AUXILIARY_H
