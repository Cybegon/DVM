#ifndef VIRTUALDRAGON_DVM_H
#define VIRTUALDRAGON_DVM_H

#include "datatypes.h"
#include "dvmdef.h"
#include "virtualdragon.h"
#include "vmutills.h"

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
