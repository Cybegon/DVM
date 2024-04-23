#include "dvm_memory.h"
#include "dvmbase.h"

#include <windows.h>

#define DVM_CVT_PROT_FLAGS(prot, localProt)               \
            if (prot & DVM_PROT_READ)                     \
                localProt |= PAGE_READONLY;               \
            if (prot & DVM_PROT_READWRITE)                \
                localProt |= PAGE_READWRITE;              \
            if (prot & DVM_PROT_WRITECPY)                 \
                localProt |= PAGE_WRITECOPY;

//#define DVM_CVT_PROT_FLAGS(prot, localProt)               \
//        if (prot & DVM_PROT_EXEC) {                       \
//            if (prot & DVM_PROT_READ)                     \
//                localProt |= PAGE_EXECUTE_READ;           \
//            if (prot & DVM_PROT_READWRITE)                \
//                localProt |= PAGE_EXECUTE_READWRITE;      \
//            if (prot & DVM_PROT_WRITECPY)                 \
//                localProt |= PAGE_EXECUTE_WRITECOPY;      \
//        } else {                                          \
//            if (prot & DVM_PROT_READ)                     \
//                localProt |= PAGE_READONLY;               \
//            if (prot & DVM_PROT_READWRITE)                \
//                localProt |= PAGE_READWRITE;              \
//            if (prot & DVM_PROT_WRITECPY)                 \
//                localProt |= PAGE_WRITECOPY;              \
//        }

MEMORY DVM_CALLBACK dvm_malloc(dsize size)
{
    MEMORY block =
            (MEMORY)HeapAlloc(GetProcessHeap(), 0, size);

    if (block)
        return block;

    return NULL;
}

MEMORY DVM_CALLBACK dvm_realloc(MEMORY address, dsize size)
{
    if (address == NULL)
        return dvm_malloc(size);

    MEMORY block =
            (MEMORY)HeapReAlloc(GetProcessHeap(), 0, (LPVOID)address, (DWORD)size);

    if (block)
        return block;

    return NULL;
}

VOID DVM_CALLBACK dvm_free(MEMORY address)
{
    if (address == NULL)
        return;

    HeapFree(GetProcessHeap(), 0, address);
}

duint32 DVM_CALLBACK dvm_getPageSize()
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);

    return (duint32)systemInfo.dwPageSize;
}

duint32 DVM_CALLBACK dvm_getGranularity()
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);

    return (duint32)systemInfo.dwAllocationGranularity;
}

// !~MM Memory mapping
MEMORY DVM_CALLBACK dvm_vAlloc(ADDRESS base, dsize size, duint32 protection)
{
    duint32 localProtection = 0;
    duint32 granularity     = dvm_getGranularity();

    if (protection == 0)
        return NULL;

    DVM_CVT_PROT_FLAGS(protection, localProtection)

    size = ALIGN_SIZE(size, granularity);
    MEMORY mem = VirtualAlloc((LPVOID)base, (SIZE_T)size,
                              MEM_COMMIT, (DWORD)localProtection);

    return mem;
}

dint DVM_CALLBACK dvm_vProt(ADDRESS chunk, dsize size, duint32 protection)
{
    duint32 oldProtection   = 0;
    duint32 localProtection = 0;
    duint32 pageSize        = dvm_getPageSize();

    DVM_CVT_PROT_FLAGS(protection, localProtection)

    size = ALIGN_SIZE(size, pageSize);
    dint status = VirtualProtect(chunk, size,
                                 localProtection, (PDWORD)&oldProtection);

    return (status != 0) ?  TRUE : FALSE;
}

void DVM_CALLBACK dvm_vFree(ADDRESS address, dsize size, dint32 freeType)
{
    VirtualFree(address, size, MEM_RELEASE);
}
