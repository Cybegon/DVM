#ifndef VIRTUALDRAGON_VIRTUALDRAGON_H
#define VIRTUALDRAGON_VIRTUALDRAGON_H

#include "datatypes.h"
#include "dvmclass.h"

#define DVM_EXIT                (0)
#define DVM_SUCCESS             (1)
#define DVM_FAIL                (2)
#define DVM_UNDEFINED_VMCODE    (3)

#define DVM_LOAD_PAGE           (8) // get next block to cache
#define DVM_TRANSFER_CONTROL    (65535)

typedef struct DVM DVM;
typedef dint32 vm_code;

DVM*        dvm_newState            (DVM_CLASS* dvmClass);
vm_code     dvm_execute             (DVM* state);
vm_code     dvm_exit                (DVM* state, dint exitCode);

DVM_CLASS*  dvm_getClass            (DVM* state);

#endif // VIRTUALDRAGON_VIRTUALDRAGON_H
