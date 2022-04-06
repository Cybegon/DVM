#include <stdlib.h>
#include <stdio.h>

#define DT_DISABLE_GUID
#include "libdvm/dvm.h"
#include "libdvm/dvmdef.h"

#include "memory.h"

static DVM* state;

VOID DVM_CALLBACK msgVM (Msg_t type, const char* message)
{
    if (type)
#ifdef CYBEGON_COMPILER_CLANG
        printf("%s R0 = %lu | R1 = %lu\n", message, dvm_getRegisterValue(state, 0),
            dvm_getRegisterValue(state, 1));
#else
        printf("%s R0 = %llu | R1 = %llu | R3 = %llu\n", message, dvm_getRegisterValue(state, 0),
               dvm_getRegisterValue(state, 1), dvm_getRegisterValue(state, 3));
#endif
    else
        printf("%s\n", message);
}

static DVM_INT swiVector[256] = { 0 };

vm_code dvmExit(DVM* dvmState) {
    printf("Interrupt exit\n");

    dint32 exitCode = (dint32)dvm_popQuad(state);
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

    HANDLE hFile = CreateFile("G:/dvm_code.dex", GENERIC_READ, 0, NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, NULL);

    HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY,
                                        0, 0, NULL);
    
    // mov  r0, 255
    // mov  r1, 127
    // add  r1, 128
    // mov  r1, 0
    // push r0
    // int  0 ; exit
//    const unsigned char code[32] = {
//        0xFF, 0x00, 0x00, 0x10, // mov  r0, 255
//        0x7F, 0x00, 0x01, 0x10, // mov  r1, 127
//        0x80, 0x00, 0x01, 0x12, // add  r1, 128
//        0x00, 0x00, 0x01, 0x10, // mov  r1, 0
//        0x00, 0x00, 0x21, 0x10, // push r0
//        0x00, 0x00, 0x01, 0x70, // 64bit
//        0xFF, 0xFF, 0xFF, 0xFF, // 64bit
//        0x00, 0x00, 0x60, 0x11, // int  0 ; exit
//        };

    DVM_CLASS dvmClass;
    dvmClass.msgCallback        = msgVM;

    dvmClass.alloc              = allocVM;
    dvmClass.realloc            = reallocVM;
    dvmClass.free               = freeVM;

    dvmClass.createMemoryMap    = mmapVM;
    dvmClass.viewMemoryMap      = viewMmapVM;
    dvmClass.unmapMemoryMap     = freeMmapVM;

    dvmClass.stackSize          = MB(1);
    dvmClass.imageDescriptor    = hMapping;
    dvmClass.codeChunkSize      = 32;

    state = dvm_newState(&dvmClass);

    dvm_setSWI(state, swiVector);
    dvm_execute(state);

    printf("END PROGRAM\n");
    return 0;
}
