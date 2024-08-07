#include "dvm.h"

#include "dvmstate.h"
#include "dvmdef.h"
#include "dvmflags.h"

#include "vcpu.h"

#define IMAGE_BASE_ADDRESS 0

vm_code dvm_validateClass( DVM_CLASS* dvmClass )
{
#if defined(DVM_NO_MESSAGE) || defined(DVM_LIGHTWEIGHT) // make later
    if (dvmClass->codeChunkSize < sizeof(INSTRUCTION))
        dvmClass->msgCallback(DVM_MSG_ERROR, "Code chunk is smaller less then 8 bytes");
    if (dvmClass->imageDescriptor == NULL)
        dvmClass->msgCallback(DVM_MSG_ERROR, "Image descriptor cannot be NULL");
    if (dvmClass->stackSize < 256)
        dvmClass->msgCallback(DVM_MSG_ERROR, "Minimum stack size 256 bytes");
    if (dvmClass->stackSize < KB(1))
        dvmClass->msgCallback(DVM_MSG_WARNING, "Minimum desired stack size 1kb");
#endif

    if (dvmClass->chunkSize < sizeof(INSTRUCTION))
        return DVM_FAIL;
    if (dvmClass->imageDescriptor == NULL)
        return DVM_FAIL;
    if (dvmClass->stackSize < 256)
        return DVM_FAIL;

    return DVM_SUCCESS;
}

DVM* dvm_newState( DVM_CLASS* dvmClass )
{
    // New state
    DVM* state = dvmClass->malloc( sizeof( DVM ) );
    for (int i = 0; i < sizeof( DVM ); ++i) // !!!improve later
    {
        ( ( duint8* )state )[i] = 0;
    }

    // Setting up registers
    BL = IMAGE_BASE_ADDRESS;
    BH = dvmClass->chunkSize;
    SP = dvmClass->stackSize - sizeof( INSTRUCTION );

    state->dvmClass     = dvmClass;
    state->text         = dvmClass->getChunk( dvmClass->imageDescriptor, BL, BH );
    state->data         = dvmClass->getChunk( dvmClass->imageDescriptor, BL, BH );
    state->stack        = dvmClass->malloc( dvmClass->stackSize );

    dvm_setEndian( state, dvm_getByteOrder() );

    return state;
}

DVM_CLASS* dvm_getClass( DVM* state )
{
    return state->dvmClass;
}

vm_code dvm_setVCPU( DVM* state, const VCPU* vcpu )
{
    state->vcpu = vcpu;

    return DVM_SUCCESS;
}

vm_code dvm_execute( DVM* state )
{
    cpu_init    ( state );
    cpu_attach  ( state );
    cpu_unload  ( state );

    return DVM_SUCCESS; // TODO: replace
}

vm_code dvm_reset( DVM* state )
{
    DVM_CLASS* dvmClass = state->dvmClass;

    for (duint i = 0; i < REGISTER_COUNT; ++i) {
        state->rn[i] = 0;
        state->fp[i] = 0.0f;
    }
    for (duint i = 0; i < SPECIAL_REGISTER_COUNT; ++i) {
        state->sr[i] = 0;
    }

    // Setting up registers
    BL = IMAGE_BASE_ADDRESS;
    BH = dvmClass->chunkSize;
    SP = dvmClass->stackSize - sizeof( INSTRUCTION );

    state->text = dvmClass->getChunk( dvmClass->imageDescriptor, BL, BH );
    state->data = dvmClass->getChunk( dvmClass->imageDescriptor, BL, BH );

    return DVM_SUCCESS; // TODO: replace
}

vm_code dvm_exit( DVM* state, dint exitCode )
{
    cpu_unload( state );

    return DVM_EXIT; // TODO: replace
}

vm_code dvm_call( DVM* state, REGISTER address ) // TODO: replace
{
    IP = address;
    cpu_stateHandler( state, DVM_LOAD_PAGE );

    return DVM_SUCCESS; // TODO: replace
}

REGISTER dvm_getRegisterValue( DVM* state, duint8 nReg )
{
    return R( nReg );
}

REGISTER* dvm_getRegisterRef( DVM* state, duint8 nReg )
{
    return &R( nReg );
}

vm_code dvm_setSWI( DVM* state, DVM_INT* vector )
{
    if ( vector == NULL )
        return DVM_FAIL;

    state->SVI = vector;

    return DVM_SUCCESS;
}

vm_code dvm_setEndian( DVM* state, duint8 endian ) {
    ( endian >= 1 )
    ? _BIT_SET( cvtR2FR(FR)->vm_control, 7u )
    : _BIT_CLEAR( cvtR2FR(FR)->vm_control, 7u );

    return DVM_SUCCESS;
}

VOID dvm_pushByte(DVM* state, duint16 _byte)
{
    PUSH( duint16, _byte ); // aligned 16 bytes
}

VOID dvm_pushShort(DVM* state, duint16 _short)
{
    PUSH( duint16, _short ); // aligned 16 bytes
}

VOID dvm_pushLong(DVM* state, duint32 _long)
{
    PUSH( duint32, _long ); // aligned 16 bytes
}

VOID dvm_pushQuad(DVM* state, duint64 _quad)
{
    PUSH( duint64, _quad ); // aligned 16 bytes
}

duint16 dvm_popByte(DVM* state)
{
    duint16 retVal = POP( duint16 );
    return retVal; // aligned 16 bytes
}

duint16 dvm_popShort(DVM* state)
{
    duint16 retVal = POP( duint16 );
    return retVal; // aligned 16 bytes
}

duint32 dvm_popLong(DVM* state)
{
    duint32 retVal = POP( duint32 );
    return retVal; // aligned 16 bytes
}

duint64 dvm_popQuad(DVM* state)
{
    duint64 retVal = POP( duint64 );
    return retVal; // aligned 16 bytes
}

duint8 dvm_getByteOrder()
{
    duint16 x = 0x0001;

    return ( *( (duint8*)&x ) ? DVM_ENDIAN_BIG : DVM_ENDIAN_LITTLE );
}
