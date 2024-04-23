#ifndef VIRTUALDRAGON_DVMBASE_H
#define VIRTUALDRAGON_DVMBASE_H

#include "datatypes.h"
#include "dvmclass.h"

#define DVM_BASE_STACK_SIZE MB(1)
#define DVM_BASE_CHUNK_SIZE MB(4)

#define FILE_TYPE_RAW 0
#define FILE_TYPE_VEX 1

typedef struct DVMFileImage DVMFileImage;

DVM_CLASS*  dvm_initClass(DVM_CLASS* dvmClass);

DVMFileImage*   dvm_openExecutableFile  (DVM_CLASS* dvmClass, const char* path);
MEMORY          dvm_createVMImage       (DVM_CLASS* dvmClass, DVMFileImage* fileImage);

// memory
MEMORY  DVM_CALLBACK dvm_malloc     (dsize size);
MEMORY  DVM_CALLBACK dvm_realloc    (MEMORY address, dsize size);
VOID    DVM_CALLBACK dvm_free       (MEMORY address);

#endif //VIRTUALDRAGON_DVMBASE_H
