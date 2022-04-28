#include "memory.h"

#include "stdio.h"

MEMORY DVM_CALLBACK allocVM(dsize size, duint32 flags, duint32 protection)
{
    duint32 localFlags      = 0;
    duint32 localProtection = 0;

    localFlags |= MEM_COMMIT;

//    if (protection & DVM_MEM_READ)
//        localProtection |= PAGE_READONLY;
    if (protection & DVM_MEM_WRITE || protection & DVM_MEM_READWRITE)
        localProtection |= PAGE_READWRITE;

    MEMORY address1 = NULL;
    address1 = VirtualAlloc(address1, size, localFlags, localProtection);

    if (flags & DVM_MEM_STACK)
    {
        //address1 = ((MEMORY)(((duint8*)address1) + size));
    }

    return address1;
}

MEMORY DVM_CALLBACK reallocVM(MEMORY address, dsize size)
{
    return (MEMORY) realloc(address, size);
}

VOID DVM_CALLBACK freeVM(MEMORY address)
{
    VirtualFree(address, 0, MEM_RELEASE);
}

DESCRIPTOR DVM_CALLBACK mmapVM(MEMORY address, dsize size, duint32 flags, duint32 protection)
{

    HANDLE hMapping = CreateFileMapping(address, NULL, PAGE_READONLY,
                                        0, 0, NULL);
//    if (address == NULL)
//        address1 = malloc(size);
//    else
//        address1 = realloc(address, size);
//
//    if (flags & DVM_MEM_STACK)
//    {
//        duint8* tmp = (duint8*)address1;
//        tmp += size;
//        address1 = (MEMORY) tmp;
//    }

    return (DESCRIPTOR)hMapping;
}

MEMORY DVM_CALLBACK viewMmapVM (DESCRIPTOR handle, duint64 offset, duint64 length)
{
//    SYSTEM_INFO sysinfo = {0};
//    GetSystemInfo(&sysinfo);
//    DWORD cbView = sysinfo.dwAllocationGranularity;
//
//    duint32 offsetHigh  = ((offset >> 32u) & 0xFFFFFFFFu);
//    duint32 offsetLow   = (offset & 0xFFFFFFFFu);

    MEMORY dataPtr = (MEMORY)MapViewOfFile(handle,
            FILE_MAP_READ,
            0,
                          0,
                          0);
//
//    FILE* f = fopen("G:/dump.dex", "w");
//
//    fwrite(dataPtr, 32, 1, f);
//    fclose(f);

    return dataPtr;
}

VOID DVM_CALLBACK freeMmapVM(DESCRIPTOR handle)
{
    free(handle);
}