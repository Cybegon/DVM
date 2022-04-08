#ifndef VIRTUALDRAGON_DVM_H
#define VIRTUALDRAGON_DVM_H

#include "datatypes.h"
#include "dvmclass.h"
#include "dvmdef.h"

DVM*        dvm_newState            ( DVM_CLASS* dvmClass );
vm_code     dvm_execute             ( DVM* state );
vm_code     dvm_reset               ( DVM* state );
vm_code     dvm_exit                ( DVM* state, dint exitCode );

DVM_CLASS*  dvm_getClass            ( DVM* state );

// Call hardware interrupt
vm_code     dvm_callHVI             ( DVM* state, duint8 interruptNumber );
vm_code     dvm_call                ( DVM* state, REGISTER address );

REGISTER    dvm_getRegisterValue    (DVM* state, duint8 nReg);
REGISTER*   dvm_getRegisterRef      (DVM* state, duint8 nReg);
vm_code     dvm_setSWI              (DVM* state, DVM_INT* vector);

VOID dvm_pushByte   (DVM* state, duint16  _byte);
VOID dvm_pushShort  (DVM* state, duint16 _short);
VOID dvm_pushLong   (DVM* state, duint32 _long);
VOID dvm_pushQuad   (DVM* state, duint64 _quad);

duint16 dvm_popByte     (DVM* state);
duint16 dvm_popShort    (DVM* state);
duint32 dvm_popLong     (DVM* state);
duint64 dvm_popQuad     (DVM* state);

duint8 dvm_getByteOrder ();

#endif // VIRTUALDRAGON_DVM_H
