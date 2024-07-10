#ifndef VIRTUALDRAGON_DVMBASE_H
#define VIRTUALDRAGON_DVMBASE_H

#include "datatypes.h"
#include "dvmclass.h"

#define DVM_BASE_STACK_SIZE MB(1)
#define DVM_BASE_CHUNK_SIZE MB(4)

typedef struct DVMOptions DVMOptions;
typedef struct DVM_FS_CONTEXT   DVM_FS_CONTEXT;

DVM_CLASS*  dvm_initClass(DVM_CLASS* dvmClass);

//void        dvm_fastAllInit         ( DVM_CLASS* dvmClass, DVMOptions* options, DVM* state );
dint32      dvm_createVMImage( DVM_CLASS* dvmClass, DVMOptions* options, DVM_FS_CONTEXT* ctx);

// memory
MEMORY  DVM_CALLBACK dvm_malloc     (dsize size);
MEMORY  DVM_CALLBACK dvm_realloc    (MEMORY address, dsize size);
VOID    DVM_CALLBACK dvm_free       (MEMORY address);

#endif //VIRTUALDRAGON_DVMBASE_H
