#ifndef VIRTUALDRAGON_DVMCLASS_H
#define VIRTUALDRAGON_DVMCLASS_H

#include "datatypes.h"

#define DVM_CALLBACK __cdecl
#ifndef CYBEGON_LACKS_FASTCALL
#define DVM_FASTCALL __fastcall
#else
#define DVM_FASTCALL
#endif

// Memory map allocator
// Protection
#define DVM_MEM_NONE    ( 0x01u )
#define DVM_MEM_EXEC    ( 0x02u )
#define DVM_MEM_STACK   ( 0x04u )    // top down
#define DVM_MEM_READ    ( 0x08u )
#define DVM_MEM_WRITE   ( 0x10u )

#define DVM_MEM_READWRITE ( DVM_MEM_READ | DVM_MEM_WRITE )

#define DVM_MEM_FIXED   ( 0x01u )
#define DVM_MEM_PRIVATE ( 0x02u )
#define DVM_MEM_SHARED  ( 0x04u )

// VM Msg_t
#define DVM_MSG_INFO    0
#define DVM_MSG_ERROR   1
#define DVM_MSG_WARNING 2

typedef duint32 Msg_t;

typedef struct DVM_CLASS DVM_CLASS;

// DVM_CLASS functions
// Memory allocator
typedef MEMORY     (DVM_CALLBACK *MemAllocator)        (dsize size);
typedef MEMORY     (DVM_CALLBACK *MemReAllocator)      (MEMORY address, dsize size);
typedef VOID       (DVM_CALLBACK *MemFree)             (MEMORY address);
// Memory map
typedef DESCRIPTOR (DVM_CALLBACK *CreateMemMapFunc)    (MEMORY address, dsize size, duint32 protection, duint32 flags);
typedef MEMORY     (DVM_CALLBACK *MemMapAccessFunc)    (DESCRIPTOR handle, duint64 offset, duint64 length);
typedef VOID       (DVM_CALLBACK *UnmapMemFunc)        (DESCRIPTOR handle);
// Callback funcs
typedef VOID       (DVM_CALLBACK *MsgCallbackFunc)     (Msg_t type, const char* message);
typedef ADDRESS    (DVM_CALLBACK *FGT)                 (const char* importName);

//  DVM MetaClass
struct DVM_CLASS
{
    // Memory management
    MemAllocator        alloc;
    MemReAllocator      realloc;
    MemFree             free;

    CreateMemMapFunc    createMemoryMap; // return programDescriptor
    // accepts an DESCRIPTOR
    // return data with programCacheSize
    MemMapAccessFunc    viewMemoryMap;
    UnmapMemFunc        unmapMemoryMap;

    DESCRIPTOR          programDescriptor;  // Must contain the program file image
    // dsize codeChunkSize & dataChunkSize
    // Prefetch N bytes from the programDescriptor,
    // Size can affect performance
    dsize               codeChunkSize;
    dsize               dataChunkSize;
    dsize               stackSize;

    // Contains native machine code
    // For current processor architecture
    dsize               reservedCodeCacheSize;
    dsize               maxHeapSize;

    MsgCallbackFunc     msgCallback;        // for example: stdout

    // Calling bridge
    FGT                 funcGlobalTable;
};

#endif // VIRTUALDRAGON_DVMCLASS_H
