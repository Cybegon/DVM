#include "dvmbase.h"
#include "dvmbase_p.h"

#include <windows.h>


MEMORY DVM_CALLBACK dvm_malloc(dsize size)
{
    MEMORY block =
            HeapAlloc(GetProcessHeap(), 0, size);

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

duint32 DVM_CALLBACK dvm_getGranularity()
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);

    return (duint32)systemInfo.dwAllocationGranularity;
}

duint32 DVM_CALLBACK dvm_getPageSize()
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);

    return (duint32)systemInfo.dwPageSize;
}

// !~MM Memory mapping
MEMORY DVM_CALLBACK dvm_vAlloc(ADDRESS base, dsize size, duint32 flags, duint32 protection)
{
    duint32 localFlags      = 0;
    duint32 localProtection = 0;
    duint32 granularity     = dvm_getGranularity();

    if (flags == 0 || protection == 0)
        return NULL;

    if (flags & DVM_MEM_COMMIT)
        localFlags |= MEM_COMMIT;
    if (flags & DVM_MEM_RESERVE)
        localFlags |= MEM_RESERVE;

    if (protection & DVM_PROT_EXEC) {
        if (protection & DVM_PROT_READ)
            localProtection |= PAGE_EXECUTE_READ;
        if (protection & DVM_PROT_READWRITE)
            localProtection |= PAGE_EXECUTE_READWRITE;
        if (protection & DVM_PROT_WRITECPY)
            localProtection |= PAGE_EXECUTE_WRITECOPY;
    } else {
        if (protection & DVM_PROT_READ)
            localProtection |= PAGE_READONLY;
        if (protection & DVM_PROT_READWRITE)
            localProtection |= PAGE_READWRITE;
        if (protection & DVM_PROT_WRITECPY)
            localProtection |= PAGE_WRITECOPY;
    }

    size = ALIGN_SIZE(size, granularity);
    MEMORY mem = VirtualAlloc((LPVOID)base, (SIZE_T)size,
                              (DWORD)localFlags, (DWORD)localProtection);

    if (flags & DVM_MEM_NULL) {
        // !!make later
    }



    return mem;
}

dint dvm_vProt(ADDRESS chunk, dsize size, duint32 protection)
{
    duint32 oldProtection   = 0;
    duint32 localProtection = 0;
    duint32 pageSize        = dvm_getPageSize();

    if (protection & DVM_PROT_EXEC) {
        if (protection & DVM_PROT_READ)
            localProtection |= PAGE_EXECUTE_READ;
        if (protection & DVM_PROT_READWRITE)
            localProtection |= PAGE_EXECUTE_READWRITE;
        if (protection & DVM_PROT_WRITECPY)
            localProtection |= PAGE_EXECUTE_WRITECOPY;
    } else {
        if (protection & DVM_PROT_READ)
            localProtection |= PAGE_READONLY;
        if (protection & DVM_PROT_READWRITE)
            localProtection |= PAGE_READWRITE;
        if (protection & DVM_PROT_WRITECPY)
            localProtection |= PAGE_WRITECOPY;
    }

    size = ALIGN_SIZE(size, pageSize);
    dint status = VirtualProtect(chunk, size,
                                 localProtection, (PDWORD)&oldProtection);

    if (status)
        return TRUE;
    else
        return FALSE;
}

void dvm_vFree(ADDRESS address, dsize size, dint32 freeType)
{
    duint32 localFreeType = 0;

    if (freeType & DVM_MEM_DECOMMIT)
        localFreeType |= MEM_DECOMMIT;
    if (freeType & DVM_MEM_RELEASE)
        localFreeType |= MEM_RELEASE;

    VirtualFree(address, size, localFreeType);
}
