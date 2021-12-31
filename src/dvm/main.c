
#include <stdlib.h>
#include <stdio.h>

#include "libdvm/virtualdragon.h"
#include "libdvm/vmutills.h"

static DVM* state;

MEMORY DVM_CALLBACK allocVM (dsize size)
{
    return (MEMORY)malloc(size);
}

MEMORY DVM_CALLBACK reallocVM (MEMORY address, dsize size)
{
    return (MEMORY) realloc(address, size);
}

VOID  DVM_CALLBACK freeVM (MEMORY address)
{
    free(address);
}

DESCRIPTOR  DVM_CALLBACK mmapVM(MEMORY address, dsize size, duint32 protection, duint32 flags)
{
    MEMORY address1 = NULL;
    if (address == NULL)
        address1 = malloc(size);
    else
        address1 = realloc(address, size);

    if (protection & DVM_MEM_STACK)
    {
        duint8* tmp = (duint8*)address1;
        tmp += size;
        address1 = tmp;
    }

    return address1;
}

MEMORY DVM_CALLBACK viewMmapVM (DESCRIPTOR handle, duint64 offset, duint64 length)
{
    return handle;
}

VOID DVM_CALLBACK freeMmapVM(DESCRIPTOR handle)
{
    free(handle);
}

VOID DVM_CALLBACK msgVM (Msg_t type, const char* message)
{
    if (type)
        printf("%s R0 = %llu | R1 = %llu\n", message, dvm_getRegisterValue(state, 0),
            dvm_getRegisterValue(state, 1));
    else
        printf("%s\n", message);
}

static DVM_INT swiVector[256] = { 0 };

vm_code dvmExit(DVM* dvmState) {
    printf("Interrupt exit\n");

    duint64 exitCode = dvm_popQuad(state);
    dvm_exit(state, exitCode);
    exit(exitCode);
}

vm_code emptyInterrupt(DVM* dvmState) {
    return DVM_SUCCESS;
}

int main(int argc, char* argv[])
{

    swiVector[0] = dvmExit;
    for (int i = 1; i < 0xFF; ++i) {
        swiVector[i] = emptyInterrupt;
    }
    
    // mov  r0, 255
    // mov  r1, 127
    // add  r1, 128
    // mov  r1, 0
    // push r0
    // int  0 ; exit
    const unsigned char code[24] = {
        0xFF, 0x00, 0x00, 0x10, // mov  r0, 255
        0x7F, 0x00, 0x01, 0x10, // mov  r1, 127
        0x80, 0x00, 0x01, 0x12, // add  r1, 128
        0x00, 0x00, 0x01, 0x10, // mov  r1, 0
        0x00, 0x00, 0x21, 0x10, // push r0
        0x00, 0x00, 0x60, 0x11, // int  0 ; exit
        };

    DVM_CLASS dvmClass;
    dvmClass.msgCallback        = msgVM;

    dvmClass.alloc              = allocVM;
    dvmClass.realloc            = reallocVM;
    dvmClass.free               = freeVM;

    dvmClass.createMemoryMap    = mmapVM;
    dvmClass.viewMemoryMap      = viewMmapVM;
    dvmClass.unmapMemoryMap     = freeMmapVM;

    dvmClass.stackSize          = MB(1);
    dvmClass.programDescriptor  = (DESCRIPTOR)&code;
    dvmClass.codeChunkSize      = MB(4);

    state = dvm_newState(&dvmClass);

    dvm_setSWI(state, swiVector);
    dvm_execute(state);

    printf("END PROGRAM\n");
    return 0;
}