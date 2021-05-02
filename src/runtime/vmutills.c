#include "vmutills.h"

#include "dvm.h"
#include "dvmdef.h"

////////////////////////////////////////////////////
VOID dvm_sendMessage(DVM* state, const char* message)
{

}
////////////////////////////////////////////////////

//
// 0x1F Allows no more than 32 (REGISTER COUNT),
// 0x1F have five bits included. 0x00011111b
//
REGISTER dvm_getRegisterValue(DVM* state, duint8 nReg)
{
    return state->rn[ ( nReg & 0x1Fu ) ];
}

REGISTER* dvm_getRegisterRef(DVM* state, duint8 nReg)
{
    return &( state->rn[ ( nReg & 0x1Fu ) ] );
}

VOID dvm_pushByte(DVM* state, duint8 _byte)
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
    PUSH( duint32, _quad ); // aligned 16 bytes
}

duint8 dvm_popByte(DVM* state)
{
    return POP( duint16 ); // aligned 16 bytes
}

duint16 dvm_popShort(DVM* state)
{
    return POP( duint16 ); // aligned 16 bytes
}

duint32 dvm_popLong(DVM* state)
{
    return POP( duint32 ); // aligned 16 bytes
}

duint64 dvm_popQuad(DVM* state)
{
    return POP( duint64 ); // aligned 16 bytes
}
