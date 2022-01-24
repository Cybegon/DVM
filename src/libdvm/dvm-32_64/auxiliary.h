#ifndef VIRTUALDRAGON_AUXILIARY_H
#define VIRTUALDRAGON_AUXILIARY_H

#define IF_EQ() if ( (FR & EQ) )        // EQual
#define IF_NE() if (!(FR & EQ) )        // Not Equal
#define IF_LT() if ( (FR & LT) )        // Less Than
#define IF_GT() if (!(FR & LT) )        // Greater Than
#define IF_LE() if ( (FR & (LT|EQ)) )   // Less than or Equal
#define IF_GE() if (!(FR & (LT|EQ)) )   // Greater than or Equal

#if defined(DVM_ENABLE_JUMP)
#   define JUMP() IP = DVM_GET_IMM24(instruction)
#endif

#endif //VIRTUALDRAGON_AUXILIARY_H
