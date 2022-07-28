#include "dvmbase.h"
#include "dvmbase_p.h"

#include <stdlib.h>
#include <unistd.h>

#include <sys/mman.h>

MEMORY DVM_CALLBACK dvm_malloc(dsize size) {
    return (MEMORY)(malloc(size));
}

MEMORY DVM_CALLBACK dvm_realloc(MEMORY address, dsize size) {
    if (address == NULL)
        return dvm_malloc(size);

    return (MEMORY)(realloc(address, size));
}

VOID DVM_CALLBACK dvm_free(MEMORY address) {
    if (address == NULL)
        return;

    free(address);
}

duint32 DVM_CALLBACK dvm_getPageSize() {
    return (duint32)(sysconf(_SC_PAGESIZE));
}


#define DVM_SET_CONVERT_PROTECTION_FLAGS(protection, localProtection) \
{ \
    if (protection & DVM_PROT_EXEC) \
        localProtection |= PROT_EXEC; \
    if (protection & DVM_PROT_READ) \
        localProtection |= PROT_READ; \
    if (protection & DVM_PROT_READWRITE) \
        localProtection |= (PROT_READ | PROT_WRITE); \
}

#define DVM_SET_CONVERT_PROTECTION_FLAGS_WCPY(protection, localProtection, localFlags) \
{ \
    DVM_SET_CONVERT_PROTECTION_FLAGS(protection, localProtection) \
    if (protection & DVM_PROT_WRITECPY) \
        localFlags |= MAP_PRIVATE; \
}

// !~MM Memory mapping
MEMORY DVM_CALLBACK dvm_vAlloc(ADDRESS base, dsize size, duint32 flags, duint32 protection) {
    dint32 localFlags = MAP_PRIVATE | MAP_ANON;
    dint32 localProtection = 0;

    if (flags == 0 || protection == 0)
        return NULL;

    //if (flags & DVM_MEM_COMMIT)
    //    localFlags |= MEM_COMMIT;
    if (flags & DVM_MEM_RESERVE)
        localProtection = PROT_NONE;

    DVM_SET_CONVERT_PROTECTION_FLAGS_WCPY(protection, localProtection, localFlags);

    size = ALIGN_SIZE(size, dvm_getPageSize());
    MEMORY mem = mmap(base, size, localProtection, localFlags, -1, 0);
    if (mem == MAP_FAILED)
        return NULL;
    
    //MEMORY mem = VirtualAlloc((LPVOID)base, (SIZE_T)size,
    //                          (DWORD)localFlags, (DWORD)localProtection);

    if (flags & DVM_MEM_NULL) {
        // !!make later
    }



    return mem;
}

dint dvm_vProt(ADDRESS chunk, dsize size, duint32 protection)
{
    dint32 localProtection = 0;
    duint32 pageSize = dvm_getPageSize();

    DVM_SET_CONVERT_PROTECTION_FLAGS(protection, localProtection);

    size = ALIGN_SIZE(size, pageSize);
    dint status = mprotect(chunk, size, localProtection);

    return status;
}

void dvm_vFree(ADDRESS address, dsize size, dint32 freeType)
{
    if (freeType & DVM_MEM_DECOMMIT)
        mprotect(address, size, PROT_NONE);
    else
        munmap(address, size);
}
