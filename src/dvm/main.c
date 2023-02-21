#include <stdlib.h>
#include <stdio.h>

#include "dvm.h"
#include "dvmdef.h"

#include "dvmbase.h"

#include "car.h"

static DVM* state;

VOID DVM_CALLBACK msgVM (Msg_t type, const char* message)
{
    if (type)
#if defined(CYBEGON_COMPILER_CLANG) && defined(CYBEGON_PLATFORM_APPLE)
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
    DESCRIPTOR fileImage = dvm_openExecutableFile("VM.dex");
    fileImage = dvm_createVMImage(fileImage, 0);

    for (int i = 0; i < 0xFF; ++i) {
        swiVector[i] = emptyInterrupt;
    }
    swiVector[0] = dvmExit;

    DVM_CLASS dvmClass;
    dvm_initClass(&dvmClass, fileImage);

    state = dvm_newState(&dvmClass);

    dvm_setVCPU( state, car_getVCPU(state) );
    dvm_setSWI(state, swiVector);
    dvm_execute(state);

    printf("END PROGRAM\n");
    return 0;
}
