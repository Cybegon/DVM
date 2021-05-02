#ifndef VIRTUALDRAGON_VMUTILLS_H
#define VIRTUALDRAGON_VMUTILLS_H

#include "datatypes.h"
#include "virtualdragon.h"

typedef duint8      REGISTER8;
typedef duint16     REGISTER16;
typedef duint32     REGISTER32;
typedef duint64     REGISTER64;
typedef REGISTER64  REGISTER;

typedef double      FREGISTER;

////////////////////////////////////////////////////
VOID dvm_sendMessage(DVM* state, const char* message);
////////////////////////////////////////////////////

REGISTER    dvm_getRegisterValue    (DVM* state, duint8 nReg);
REGISTER*   dvm_getRegisterRef      (DVM* state, duint8 nReg);

VOID dvm_pushByte   (DVM* state, duint8  _byte);
VOID dvm_pushShort  (DVM* state, duint16 _short);
VOID dvm_pushLong   (DVM* state, duint32 _long);
VOID dvm_pushQuad   (DVM* state, duint64 _quad);

duint8  dvm_popByte     (DVM* state);
duint16 dvm_popShort    (DVM* state);
duint32 dvm_popLong     (DVM* state);
duint64 dvm_popQuad     (DVM* state);

#endif // VIRTUALDRAGON_VMUTILLS_H
