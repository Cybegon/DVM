#ifndef VIRTUALDRAGON_VIRTUALDRAGON_H
#define VIRTUALDRAGON_VIRTUALDRAGON_H

#include "datatypes.h"

#define DVM_CALLBACK __cdecl
#define DVM_FASTCALL __fastcall

// VM func code
#define DVM_OK          0
#define DVM_WARNING     1
#define DVM_ERROR       2

// VM Msg_t
#define MSG_INFO    0
#define MSG_ERROR   1
#define MSG_WARNING 2

typedef struct DVM DVM;
typedef duchar Msg_t;

typedef MEMORY  DVM_CALLBACK (*AllocFunc)           (dsize size);
typedef MEMORY  DVM_CALLBACK (*ReallocFunc)         (MEMORY mem, dsize size);
typedef VOID    DVM_CALLBACK (*FreeFunc)            (MEMORY mem);

typedef VOID    DVM_CALLBACK (*MsgCallbackFunc)     (Msg_t type, const char* message);
typedef MEMORY  DVM_CALLBACK (*MemoryAccessFunc)    (duint64 offset, duint64 length);

typedef ADDRESS DVM_CALLBACK (*CALL_DICTIONARY)     (const char* moduleName, const char* importName);

//  DVM MetaClass
typedef struct DVM_CLASS
{
    // Memory management
    AllocFunc           malloc;
    ReallocFunc         realloc;
    FreeFunc            free;

    dsize               stackSize;
    dsize               memoryAccessBlockSize;
    MemoryAccessFunc    memoryAccess;
    MsgCallbackFunc     msgCallback;

    // Calling bridge
    CALL_DICTIONARY     callDictionary;
} DVM_CLASS;

DVM*        dvm_newState            (DVM_CLASS* dvmClass);
int         dvm_execute             (DVM* state);

DVM_CLASS*  dvm_getClass            (DVM* state);

#endif // VIRTUALDRAGON_VIRTUALDRAGON_H
