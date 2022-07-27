#ifndef VIRTUALDRAGON_DVMBASE_H
#define VIRTUALDRAGON_DVMBASE_H

#include "datatypes.h"
#include "libdvm/dvmclass.h"

#define DVM_BASE_STACK_SIZE MB(1)
#define DVM_BASE_CHUNK_SIZE MB(4)

#define FILE_TYPE_RAW 0
#define FILE_TYPE_VEX 1

DESCRIPTOR  dvm_openExecutableFile(const char* fileName);
MEMORY      dvm_createVMImage(DESCRIPTOR dvmExecutableFile, duint16 fileType);
DVM_CLASS*  dvm_initClass(DVM_CLASS* dvmClass, MEMORY VMImage);

// memory
MEMORY  DVM_CALLBACK dvm_malloc     (dsize size);
MEMORY  DVM_CALLBACK dvm_realloc    (MEMORY address, dsize size);
VOID    DVM_CALLBACK dvm_free       (MEMORY address);

#endif //VIRTUALDRAGON_DVMBASE_H
