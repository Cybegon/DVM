#ifndef VIRTUALDRAGON_VMUTILLS_H
#define VIRTUALDRAGON_VMUTILLS_H

#include "datatypes.h"
#include "virtualdragon.h"

#define DEFAULT_PAGE_SIZE   512
#define DEFAULT_PAGE_SHIFT  3

typedef duint64         REGISTER;
typedef dint64          IREGISTER;
typedef double          FREGISTER;

typedef duint64         REGISTER64;
typedef duint32         REGISTER32;
typedef duint16         REGISTER16;

typedef dint64          IREGISTER64;
typedef dint32          IREGISTER32;
typedef dint16          IREGISTER16;

typedef vm_code (*DVM_INT)          (DVM* state);
typedef vm_code (*DVM_LOAD)         (DVM* state);
typedef vm_code (*DVM_ENTRY)        (DVM* state);
typedef vm_code (*DVM_UNLOAD)       (DVM* state);

//union REGISTER
//{
//    // machine word deps on the architecture
//    dsize word;
//
//    REGISTER64  T64;
//    REGISTER32  T32;
//    REGISTER16  T16;
//    REGISTER8   T8;
//};

////////////////////////////////////////////////////
VOID dvm_sendMessage(DVM* state, const char* message);
////////////////////////////////////////////////////

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

//ADDRESS dvm_getLabel(const char* labelName);
//vm_code dvm_precompileFromLabel(ADDRESS functionAddress);

#endif // VIRTUALDRAGON_VMUTILLS_H
