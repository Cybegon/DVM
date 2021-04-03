#include "virtualdragon.h"

#include "dvm.h"

DVM* dvm_newState(DVM_CLASS* dvmClass)
{
    // DVM Messages
    if ( dvmClass->msgCallback == NULL )
        return NULL;

    // Memory access
    if ( dvmClass->memoryAccess == NULL )
        dvmClass->msgCallback( MSG_ERROR, "Code access is not assigned to DVM_CLASS.\n" );
    if ( dvmClass->memoryAccessBlockSize < 4 )
        dvmClass->msgCallback( MSG_ERROR, "Code access block size must be at least 4 bytes.\n" );

    // Malloc functions
    if ( dvmClass->malloc == NULL )
        dvmClass->msgCallback( MSG_ERROR, "Malloc function is not defined in the DVM_CLASS.\n" );

    if ( dvmClass->realloc == NULL )
        dvmClass->msgCallback( MSG_ERROR, "Realloc function is not defined in the DVM_CLASS.\n" );
    if ( dvmClass->free == NULL )
        dvmClass->msgCallback( MSG_ERROR, "Free function is not defined in the DVM_CLASS.\n" );

    // Stack
    if ( dvmClass->stackSize < KB( 1 ) )
        dvmClass->msgCallback( MSG_ERROR, "Stack size must be at least 1 kilobytes.\n" );

    // New state
    DVM* dvm = dvmClass->malloc( sizeof( DVM ) );

    for (int i = 0; i < REGISTER_COUNT; ++i)
    {
        dvm->rn[i] = 0;
        dvm->fp[i] = 0.0f;
    }

    dvm->flags      = 0;
    dvm->dvmClass   = dvmClass;
    dvm->stack      = dvmClass->malloc( dvmClass->stackSize );
    dvm->memory     = dvmClass->memoryAccess( 0, dvmClass->memoryAccessBlockSize );

    return dvm;
}

DVM_CLASS* dvm_getClass(DVM* state)
{
    return state->dvmClass;
}

int dvm_execute(DVM* state)
{

}