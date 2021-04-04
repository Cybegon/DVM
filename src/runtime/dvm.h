#ifndef VIRTUALDRAGON_DVM_H
#define VIRTUALDRAGON_DVM_H

#include "datatypes.h"
#include "virtualdragon.h"
#include "vmutills.h"

#define REGISTER_COUNT 32

#define vmdispatch(o)	switch(o)
#define vmswitch(o)     switch(o)
#define vmcase(l)	    case l:
#define vmbreak		    break
#define vmdefault       default:
#define vmrelease       return

typedef struct DVM DVM;

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
