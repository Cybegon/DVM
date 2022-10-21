#ifndef VIRTUALDRAGON_VCPUCLASS_H
#define VIRTUALDRAGON_VCPUCLASS_H

#include "datatypes.h"

#include "dvm.h"

typedef struct DVM_GUID DVM_GUID;

struct DVM_GUID
{
    duint32 data1;      // 32bit low time
    duint16 data2;      // 16bit middle time
    duint16 data3;      // 4bit version and 12 high bits of the time
    // 1 to 3-bit "variant" in the most significant bits,
    // followed by the 13 to 15-bit clock sequence
    duint16 data4;
    struct {
        duint16 node_h;
        duint32 node_l;
    } node;
};

struct VCPU
{
    DVM_GUID guid;
    duint8 vendorID[16];

    struct {
        DVM_LOAD    init;
        DVM_ENTRY   pipeline;
        DVM_UNLOAD  unload;
    } main, debug, jit;
};

#endif // VIRTUALDRAGON_VCPUCLASS_H
