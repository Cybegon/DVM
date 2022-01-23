#ifndef VIRTUALDRAGON_VCPUCLASS_H
#define VIRTUALDRAGON_VCPUCLASS_H

typedef struct VCPU VCPU;

struct VCPU
{
    DVM_GUID guid;
    duint8 vendorID[16];

    enum {
        BASIC_SET   = 0x00,
        EXTENSION   = 0x01
    } vcpuOpcodeBitType; // 0xxxxxxx or 1xxxxxxx opcode

    struct {
        DVM_LOAD    init;
        DVM_ENTRY   pipeline;
        DVM_UNLOAD  unload;
    } main, debug, jit;
};

#endif // VIRTUALDRAGON_VCPUCLASS_H
