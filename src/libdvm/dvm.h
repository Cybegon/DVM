#ifndef VIRTUALDRAGON_DVM_H
#define VIRTUALDRAGON_DVM_H

#include "datatypes.h"

#include "dvmid.h"
#include "dvmdef.h"
#include "virtualdragon.h"
#include "vmutills.h"

#include "vcpuclass.h"

struct DVM
{
    DVM_CLASS*  dvmClass;   // dvm base functions.
    DVM_ID      dvmID;

    // 32 general purpose registers.
    REGISTER    rn[ REGISTER_COUNT ]; // real number registers.
    // 8 special registers.
    REGISTER    sr[ SPECIAL_REGISTER_COUNT ]; // flags, ip, etc..
    // 32 floating point registers.
    FREGISTER   fp[ REGISTER_COUNT ]; // float point registers.

    MEMORY      text;       // program memory space.
    MEMORY      data;       // data memory space.
    MEMORY      stack;      // machine stack.

    DVM_INT*    HVI;        // pointer to hardware vector interrupt
    DVM_INT*    SVI;        // pointer to software vector interrupt

    const VCPU** vcpus;
    duint32 processorID; // default: 0
    duint32 extensionID; // default: 1
};

//struct DVM_Thread {
//    duint32  id;
//};

#endif // VIRTUALDRAGON_DVM_H
