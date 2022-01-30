#ifndef VIRTUALDRAGON_AUXILIARY_H
#define VIRTUALDRAGON_AUXILIARY_H

#define IF_EQ() if ( (FR & EQ) )        // EQual
#define IF_NE() if (!(FR & EQ) )        // Not Equal

// Unsigned
#define IF_LO() if ( (FR & LO) )      // LOwer
#define IF_HI() if (!(FR & LO) )      // HIgher
#define IF_LS() if ( (FR & (LO|EQ)) ) // Lower or Same
#define IF_HS() if (!(FR & (LO|EQ)) ) // Higher or Same

// Signed
#define IF_LT() if ( (FR & LT) )        // Less Than
#define IF_GT() if (!(FR & LT) )        // Greater Than
#define IF_LE() if ( (FR & (LT|EQ)) )   // Less than or Equal
#define IF_GE() if (!(FR & (LT|EQ)) )   // Greater than or Equal

#if defined(DVM_ENABLE_JUMP)
#   define JUMP() IP = DVM_GET_IMM24(instruction)
#endif

#endif //VIRTUALDRAGON_AUXILIARY_H
