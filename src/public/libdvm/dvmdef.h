#ifndef VIRTUALDRAGON_DVMDEF_H
#define VIRTUALDRAGON_DVMDEF_H

#include "datatypes.h"

#define DEFAULT_PAGE_SIZE   512
#define DEFAULT_PAGE_SHIFT  3

#define DVM_EXIT                (0)
#define DVM_SUCCESS             (1)
#define DVM_FAIL                (2)
#define DVM_UNDEFINED_VMCODE    (3)

#define DVM_LOAD_PAGE           (8) // get next block to cache
#define DVM_TRANSFER_CONTROL    (65535)

typedef struct DVM DVM;
typedef dint32 vm_code;

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


/////////////////////////// DANGER ///////////////////////////
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

VOID dvm_sendMessage(DVM* state, const char* message);

//ADDRESS dvm_getLabel(const char* labelName);
//vm_code dvm_precompileFromLabel(ADDRESS functionAddress);
/////////////////////////// DANGER ///////////////////////////

#endif // VIRTUALDRAGON_DVMDEF_H
