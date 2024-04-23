#include "dvm_memory.h"
#include "dvmbase.h"

#include <stdlib.h>
#include <unistd.h>

#include <sys/mman.h>

#define DVM_CVT_PROT_FLAGS(prot, localProt)           \
    if (prot & DVM_PROT_EXEC)                         \
        localProt |= PROT_EXEC;                       \
    if (prot & DVM_PROT_READ)                         \
        localProt |= PROT_READ;                       \
    if (prot & DVM_PROT_READWRITE)                    \
        localProt |= PROT_READ | PROT_WRITE;

MEMORY DVM_CALLBACK dvm_malloc(dsize size) {
    return (MEMORY)malloc(size);
}

MEMORY DVM_CALLBACK dvm_realloc(MEMORY address, dsize size)
{
    if (address == NULL)
        return dvm_malloc(size);

    return (MEMORY)realloc(address, size);
}

VOID DVM_CALLBACK dvm_free(MEMORY address)
{
    if (address == NULL)
        return;

    free(address);
}

duint32 DVM_CALLBACK dvm_getPageSize()
{
    return (duint32)sysconf(_SC_PAGESIZE);
}

duint32 DVM_CALLBACK dvm_getGranularity()
{
    return dvm_getPageSize();
}

// !~MM Memory mapping
MEMORY DVM_CALLBACK dvm_vAlloc(ADDRESS base, dsize size, duint32 protection)
{
    dint32 localProtection  = 0;

    if (protection == 0)
        return NULL;

    DVM_CVT_PROT_FLAGS(protection, localProtection)

    size = ALIGN_SIZE(size, dvm_getPageSize());
    MEMORY mem = mmap(base, size, localProtection, MAP_PRIVATE | MAP_ANON, -1, 0);

    return (mem != MAP_FAILED) ? mem : NULL;
}

dint DVM_CALLBACK dvm_vProt(ADDRESS chunk, dsize size, duint32 protection)
{
    dint32 localProtection  = 0;
    duint32 pageSize        = dvm_getPageSize();

    DVM_CVT_PROT_FLAGS(protection, localProtection)

    size = ALIGN_SIZE(size, pageSize);
    dint status = mprotect(chunk, size, localProtection);

    return (status == 0) ? TRUE : FALSE;
}

void DVM_CALLBACK dvm_vFree(ADDRESS address, dsize size, dint32 freeType)
{
    munmap(address, size);
}
