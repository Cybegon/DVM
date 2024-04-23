#ifndef VIRTUALDRAGON_DVMCLASS_H
#define VIRTUALDRAGON_DVMCLASS_H

#include "datatypes.h"

#if defined(CYBEGON_COMPILER_GCC)
#   define DVM_CALLBACK __attribute__((__cdecl__))
#   define DVM_FASTCALL __attribute__((__fastcall__))
#elif defined(CYBEGON_COMPILER_MSVC)
#   define DVM_CALLBACK __cdecl
#   define DVM_FASTCALL __fastcall
#else
#   define DVM_CALLBACK
#   define DVM_FASTCALL
#endif

#if defined(CYBEGON_LACKS_FASTCALL)
#   undef DVM_FASTCALL
#   define DVM_FASTCALL
#endif

// VM Msg_t
#define DVM_MSG_INFO    0
#define DVM_MSG_ERROR   1
#define DVM_MSG_WARNING 2

typedef duint32 Msg_t;

typedef struct DVM_CLASS DVM_CLASS;

// DVM_CLASS functions
// Memory allocator
typedef MEMORY      (DVM_CALLBACK *MemAllocator)        (dsize size);
typedef MEMORY      (DVM_CALLBACK *MemReAllocator)      (MEMORY address, dsize size);
typedef VOID        (DVM_CALLBACK *MemFree)             (MEMORY address);

// Memory map
//typedef DESCRIPTOR  (DVM_CALLBACK *CreateMemMapFunc)    (MEMORY address, dsize size, duint32 flags, duint32 protection);
//typedef MEMORY      (DVM_CALLBACK *MemMapAccessFunc)    (DESCRIPTOR handle, duint64 offset, duint64 length);
//typedef void        (DVM_CALLBACK *UnmapMemFunc)        (DESCRIPTOR handle);

typedef MEMORY      (DVM_CALLBACK *GetChunk)            (DESCRIPTOR image, dsize offset, dsize size);

//  DVM MetaClass
struct DVM_CLASS
{
    // Memory management
    MemAllocator        malloc;
    MemReAllocator      realloc;
    MemFree             free;

    GetChunk            getChunk;

//    CreateMemMapFunc    createMemoryMap; // return programDescriptor
//    // accepts an DESCRIPTOR
//    // return data with programCacheSize
//    MemMapAccessFunc    viewMemoryMap;
//    UnmapMemFunc        unmapMemoryMap;

    DESCRIPTOR          imageDescriptor;  // Must contain the program file image
    // dsize chunkSize Prefetch N bytes
    // from the programDescriptor,
    // Size can affect performance
    dsize               chunkSize;
    dsize               stackSize;

    // Contains native machine code
    // For current processor architecture
    dsize               reservedCodeCacheSize;
    dsize               maxHeapSize;

    duint32             flags;
};

#endif // VIRTUALDRAGON_DVMCLASS_H
