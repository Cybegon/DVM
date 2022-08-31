#ifndef VIRTUALDRAGON_DVMDEF_H
#define VIRTUALDRAGON_DVMDEF_H

#include "datatypes.h"

#define DVM_DEFAULT_PAGE_SIZE   512u
#define DVM_DEFAULT_PAGE_SHIFT  3u

#define DVM_ENDIAN_BIG      1u
#define DVM_ENDIAN_LITTLE   0u

#define DVM_EXIT                (0u)
#define DVM_SUCCESS             (1u)
#define DVM_FAIL                (2u)
#define DVM_UNDEFINED_VMCODE    (3u)

#define DVM_LOAD_PAGE           (8u) // get next block to cache // Hello transition delay ;)
#define DVM_TRANSFER_CONTROL    (65535u)

#define DVM_R(n) n

// Special registers
#define DVM_IP DVM_R(0u) // Instruction pointer
#define DVM_FR DVM_R(7u) // Flag register

// Registers
#define DVM_RA DVM_R(0u)     // Accumulator

#define DVM_TP DVM_R(29u)    // This pointer
#define DVM_BP DVM_R(30u)    // Base pointer
#define DVM_SP DVM_R(31u)    // Stack pointer

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
