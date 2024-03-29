#ifndef VIRTUALDRAGON_DVM_H
#define VIRTUALDRAGON_DVM_H

#include "datatypes.h"

#include "dvmclass.h"

typedef struct DVM DVM;
typedef struct VCPU VCPU;
typedef dint32 vm_code;

typedef union INSTRUCTION64 INSTRUCTION64;
typedef union INSTRUCTION32 INSTRUCTION32;

typedef INSTRUCTION64 INSTRUCTION;

typedef duint64         REGISTER;
typedef dint64          IREGISTER;
typedef double          FREGISTER;

typedef duint64         REGISTER64;
typedef duint32         REGISTER32;
typedef duint16         REGISTER16;

typedef dint64          IREGISTER64;
typedef dint32          IREGISTER32;
typedef dint16          IREGISTER16;

typedef struct FLREGISTER FLREGISTER;

typedef vm_code (*DVM_INT)          ( DVM* state );
typedef vm_code (*DVM_LOAD)         ( DVM* state );
typedef vm_code (*DVM_STEP)         ( DVM* state, INSTRUCTION* instruction );
typedef vm_code (*DVM_ENTRY)        ( DVM* state );
typedef vm_code (*DVM_UNLOAD)       ( DVM* state );

vm_code     dvm_validateClass       ( DVM_CLASS* dvmClass );

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

vm_code     dvm_setVCPU             (DVM* state, const VCPU* vcpu );
vm_code     dvm_setSWI              (DVM* state, DVM_INT* vector);
vm_code     dvm_setEndian           (DVM* state, duint8 endian);

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
