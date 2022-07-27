#include <stdlib.h>
#include <stdio.h>

#define DT_DISABLE_GUID
#include "libdvm/dvm.h"
#include "libdvm/dvmdef.h"

#include "libdvm-base/dvmbase.h"

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
    DESCRIPTOR fileImage = dvm_openExecutableFile("G:/app.zip");
    dvm_createVMImage(fileImage);

//    for (int i = 0; i < 0xFF; ++i) {
//        swiVector[i] = emptyInterrupt;
//    }
//    swiVector[0] = dvmExit;
//
//    DVM_CLASS dvmClass;
//    dvm_initClass(&dvmClass, dFile);
//
//    state = dvm_newState(&dvmClass);
//
//    dvm_setSWI(state, swiVector);
//    dvm_execute(state);
//
//    printf("END PROGRAM\n");
    return 0;
}
