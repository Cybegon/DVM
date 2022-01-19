#include "virtualdragon.h"

#include "dvm.h"
#include "flags.h"

#include "vcpu.h"

#include "dvm-32_64/dvm-32_64.h"

DVM* dvm_newState(DVM_CLASS* dvmClass)
{
    // DVM Messages
    if ( dvmClass->msgCallback == NULL )
        return NULL;
//
//    // Memory access
//    if ( dvmClass->memExec.memoryAccess == NULL )
//        dvmClass->msgCallback( DVM_MSG_ERROR, "Code access is not assigned to DVM_CLASS.\n" );
//    if ( dvmClass->memExec.memoryAccessBlockSize < 4 )
//        dvmClass->msgCallback( DVM_MSG_ERROR, "Code access block size must be at least 4 bytes.\n" );
//
//    // Stack
//    if ( dvmClass->stackSize < KB( 1 ) )
//        dvmClass->msgCallback( DVM_MSG_ERROR, "Stack size must be at least 1 kilobytes.\n" );
//
//    if (dvmClass->callGlobalTable == NULL)
//        dvmClass->msgCallback( DVM_MSG_ERROR, "Global table is not defined.");

    // New state
    DVM* state = dvmClass->alloc( sizeof( DVM ) );
    for (int i = 0; i < sizeof( DVM ); ++i) // !!!improve later
    {
        ( ( duint8* )state )[i] = 0;
    }

    DESCRIPTOR stackDesc = dvmClass->createMemoryMap(NULL, dvmClass->stackSize, // address, size
                                                     DVM_MEM_READWRITE          // protection start
                                                     | DVM_MEM_STACK
                                                     | DVM_MEM_PRIVATE,         // protection end
                                                     0);                        // flags
    state->dvmClass     = dvmClass;
    state->text         = dvmClass->viewMemoryMap(dvmClass->programDescriptor, IP, dvmClass->codeChunkSize);
    state->stack        = dvmClass->viewMemoryMap(stackDesc, 0, dvmClass->stackSize);

    state->flags        = 0;

    state->processorID = 0;
    state->extensionID = 1;

    state->vcpus = (const VCPU **) dvmClass->alloc(sizeof(VCPU *) * 2);
    state->vcpus[0] = dvm_32_64_getVCPU(state);
    state->vcpus[1] = NULL;


    return state;
}

DVM_CLASS* dvm_getClass(DVM* state)
{
    return state->dvmClass;
}

vm_code dvm_execute(DVM* state)
{
    cpu_init(state);
    cpu_attach(state);
    cpu_unload(state);
    return 0;
}

vm_code dvm_exit(DVM* state, dint exitCode)
{
    cpu_unload(state);

    return DVM_EXIT;
}