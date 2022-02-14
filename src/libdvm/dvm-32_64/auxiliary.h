#ifndef VIRTUALDRAGON_AUXILIARY_H
#define VIRTUALDRAGON_AUXILIARY_H

#define IF_EQ() if ( (FR & EQ) )        // EQual
#define IF_NE() if (!(FR & EQ) )        // Not Equal

// Signed
#define IF_LE() if ( (FR & (LT|EQ)) )   // Less than or Equal
#define IF_GE() if (!(FR & LT) )        // Greater than or Equal
#define IF_LT() if ( (FR & LT) )        // Less Than
#define IF_GT() if (!(FR & (LT|EQ)) )   // Greater Than

// Unsigned
#define IF_LS() if ( (FR & (LO|EQ)) )   // Lower or Same
#define IF_HS() if (!(FR & LO) )        // Higher or Same
#define IF_LO() if ( (FR & LO) )        // LOwer
#define IF_HI() if (!(FR & (LO|EQ)) )   // HIgher

#if defined(DVM_ENABLE_JUMP)
#   define JUMP() IP = DVM_GET_IMM24(instruction)
#endif

#endif //VIRTUALDRAGON_AUXILIARY_H
