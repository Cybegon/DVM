#ifndef VIRTUALDRAGON_DVMBASE_H
#define VIRTUALDRAGON_DVMBASE_H

#include "datatypes.h"
#include "dvmclass.h"

#define DVM_BASE_STACK_SIZE MB(1)

// memory
MEMORY  DVM_CALLBACK dvm_malloc     (dsize size, duint32 flags, duint32 protection);
MEMORY  DVM_CALLBACK dvm_realloc    (MEMORY address, dsize size);
VOID    DVM_CALLBACK dvm_free       (MEMORY address);

// Memory mapping
DESCRIPTOR  DVM_CALLBACK dvm_mmap     (DESCRIPTOR file, dsize size, duint32 flags, duint32 protection);
MEMORY      DVM_CALLBACK dvm_viewMmap (DESCRIPTOR handle, duint64 offset, duint64 length);
VOID        DVM_CALLBACK dvm_freeMmap (DESCRIPTOR handle);

DESCRIPTOR  DVM_CALLBACK dvm_fileOpen   (const char* fileName, duint32 flags);
VOID        DVM_CALLBACK dvm_fileRead   (MEMORY buffer, duint64 size, DESCRIPTOR file);
VOID        DVM_CALLBACK dvm_fileWrite  (MEMORY buffer, duint64 size, DESCRIPTOR file);

#endif //VIRTUALDRAGON_DVMBASE_H
