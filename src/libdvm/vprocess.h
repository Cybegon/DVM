//
// Created by Limaaron on 03.12.2021.
//

#ifndef VIRTUALDRAGON_VPROCESS_H
#define VIRTUALDRAGON_VPROCESS_H

#include "datatypes.h"

#include "dvmdef.h"
#include "vmutills.h"

// feature
typedef struct VPROCESS VPROCESS;

struct VPROCESS {
    // 32 general purpose registers.
    REGISTER    rn[ REGISTER_COUNT ]; // real number registers.
    // 32 floating point registers.
    FREGISTER   fp[ REGISTER_COUNT ]; // float point registers.
    REGISTER    flags;      // flags.

    MEMORY      text;       // program memory space.
    MEMORY      data;       // data memory space.
    MEMORY      stack;      // machine stack.
};

#endif //VIRTUALDRAGON_VPROCESS_H
