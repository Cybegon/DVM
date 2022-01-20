#include "vmutills.h"

#include "dvm.h"

////////////////////////////////////////////////////
VOID dvm_sendMessage(DVM* state, const char* message)
{

}
////////////////////////////////////////////////////

REGISTER dvm_getRegisterValue(DVM* state, duint8 nReg)
{
    return R(nReg);
}

REGISTER* dvm_getRegisterRef(DVM* state, duint8 nReg)
{
    return &R(nReg);
}

vm_code dvm_setSWI(DVM* state, DVM_INT* vector)
{
    if (vector == NULL)
        return DVM_FAIL;

    state->SVI = vector;

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

    return ( *( (duint8*)&x ) ? 0 : 1 );
}