#ifndef VIRTUALDRAGON_DVM_H
#define VIRTUALDRAGON_DVM_H

#include "datatypes.h"
#include "virtualdragon.h"

#define REGISTER_COUNT 32

#define vmdispatch(o)	switch(o)
#define vmswitch(o)     switch(o)
#define vmcase(l)	    case l:
#define vmbreak		    break
#define vmdefault       default:
#define vmrelease       return

typedef struct DVM DVM;

typedef duint8      REGISTER8;
typedef duint16     REGISTER16;
typedef duint32     REGISTER32;
typedef duint64     REGISTER64;
typedef REGISTER64  REGISTER;

typedef double      FREGISTER;

struct DVM
{
    DVM_CLASS*  dvmClass;   // dvm base functions.

    // 32 general purpose registers.
    REGISTER    rn[ REGISTER_COUNT ]; // real number registers.
    // 32 floating point registers.
    FREGISTER   fp[ REGISTER_COUNT ]; // float point registers.
    REGISTER    flags;      // flags.
    MEMORY      memory;     // a program memory space.
    MEMORY      stack;      // machine stack.
};

#endif // VIRTUALDRAGON_DVM_H
