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

#include "dvmfsapi.h"
#include "dvmfileapi.h"
#include "dvmoptions.h"

#include "common/zipfs/zipfs.h"
#include "common/osfs/osfs.h"

int main(int argc, char* argv[])
{
    DVM_CLASS dvmClass;
    dvm_initClass(&dvmClass);

    DVM_FS_CONTEXT* ctx = dvm_fsInit(&dvmClass);

    DVM_FIO* dvxFIO     = zipfs_createFs("dvx", "G:/appledragon.zip", &dvmClass);
    DVM_FIO* osfsFIO    = osfs_createFs("osfs", NULL, &dvmClass);

    if (dvm_registerFs(dvxFIO, ctx) != 0)
        printf("dvx not loaded");
    if (dvm_registerFs(osfsFIO, ctx) != 0)
        printf("osfs not loaded");

    DESCRIPTOR file = dvm_fileOpen( "dvx://manifest.json", 0, ctx );

    DVMOptions* options = dvm_createOptions( &dvmClass );
    dvm_loadOptionsFile( options, file );

    dvm_optionsAdd( options, "dvm.launch.executable.file.path", argv[1] );
    // TODO: Make format.
    //  As example dvm_optionsAdd( options,
    //              "dvm.launch.executable.file.path",
    //              "{interpreter.handler.instruction.set.name}"
    //              );
    dvm_optionsAdd( options, "dvm.launch.executable.file.path", dvm_optionsGet( options, "interpreter.handler.instruction.set.name" ) );

    dvm_fileClose( file );

    printf("%s\n", dvm_optionsGet( options, "interpreter.handler.name" ) );
    printf("%s\n", dvm_optionsGet( options, "interpreter.handler.instruction.set.name" ) );
    printf("%s\n", dvm_optionsGet( options, "app.entries.game::main.displayName" ) );
    printf("%s\n", dvm_optionsGet( options, "app.author" ) );
    printf("%s\n", dvm_optionsGet( options, "app.version" ) );
    printf("%s\n", dvm_optionsGet( options, "app.license" ) );

    dvm_optionsDelete( options, &dvmClass );

    dvm_createVMImage( &dvmClass, options, ctx );

//    DESCRIPTOR fileImage = dvm_openExecutableFile(&dvmClass, argv[1]);
//    fileImage = dvm_createVMImage(fileImage, 0);
//
//    for (int i = 0; i < 0xFF; ++i) {
//        swiVector[i] = emptyInterrupt;
//    }
//    swiVector[0] = dvmExit;
//
//    state = dvm_newState(&dvmClass);
//
//    dvm_setVCPU( state, car_getVCPU(state) );
//    dvm_setSWI(state, swiVector);
//    dvm_execute(state);
//
//    printf("END PROGRAM\n");
    return 0;
}
