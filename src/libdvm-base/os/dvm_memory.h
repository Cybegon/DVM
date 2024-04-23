#ifndef VIRTUALDRAGON_DVM_MEMORY_H
#define VIRTUALDRAGON_DVM_MEMORY_H

#include "datatypes.h"
#include "dvmclass.h"

#define DVM_PROT_READ       (0x00000100)
#define DVM_PROT_READWRITE  (0x00000200)
#define DVM_PROT_WRITECPY   (0x00000400) // experimental
#define DVM_PROT_EXEC       (0x00001000)

MEMORY  DVM_CALLBACK dvm_malloc     (dsize size);
MEMORY  DVM_CALLBACK dvm_realloc    (MEMORY address, dsize size);
VOID    DVM_CALLBACK dvm_free       (MEMORY address);

duint32 DVM_CALLBACK dvm_getPageSize();
duint32 DVM_CALLBACK dvm_getGranularity();

MEMORY  DVM_CALLBACK dvm_vAlloc (ADDRESS base, dsize size, duint32 protection);
dint    DVM_CALLBACK dvm_vProt  (ADDRESS chunk, dsize size, duint32 protection);
void    DVM_CALLBACK dvm_vFree  (ADDRESS address, dsize size, dint32 freeType);

#if defined(CYBEGON_PLATFORM_UNIX)
#   include "os/unix/dvm_memory.c"
#elif defined(CYBEGON_PLATFORM_WINDOWS)
#   include "os/win32/dvm_memory.c"
#else
#   error "[libdvm-base] Please write your own implementation of dvm_memory.c"
#endif

#endif //VIRTUALDRAGON_DVM_MEMORY_H
