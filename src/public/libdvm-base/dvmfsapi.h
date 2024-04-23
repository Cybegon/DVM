#ifndef VIRTUALDRAGON_DVMFSAPI_H
#define VIRTUALDRAGON_DVMFSAPI_H

#include "datatypes.h"
#include "dvmbase.h"

typedef struct DVM_FS_CONTEXT   DVM_FS_CONTEXT;
typedef struct DVM_FIO          DVM_FIO;
typedef struct DVM_FSTAT        DVM_FSTAT;

typedef DESCRIPTOR  (*DVM_IO_OPEN)      (POINTER path, dint flags, DESCRIPTOR deviceDescriptor);
typedef void        (*DVM_IO_CLOSE)     (DESCRIPTOR file, DESCRIPTOR deviceDescriptor);

typedef dint64      (*DVM_IO_READ)      (DESCRIPTOR file, MEMORY buf, dsize size, DESCRIPTOR deviceDescriptor);
typedef dint64      (*DVM_IO_WRITE)     (DESCRIPTOR file, MEMORY buf, dsize size, DESCRIPTOR deviceDescriptor);

typedef dint32      (*DVM_IO_IS_OPEN)   (DESCRIPTOR file, DESCRIPTOR deviceDescriptor);
typedef dint32      (*DVM_IO_FSTAT)     (DESCRIPTOR file, DVM_FSTAT* info, DESCRIPTOR deviceDescriptor);

enum FSIOFlags
{
    FS_CAN_READ             = ( 1 << 0 ),
    FS_CAN_WRITE            = ( 1 << 1 ),
    FS_CAN_COMPRESS         = ( 1 << 2 ),
    FS_CAN_DECOMPRESS       = ( 1 << 3 ),

    FS_CAN_READWRITE        = ( FS_CAN_READ | FS_CAN_WRITE ),

    FS_UNSUPPORTED_IS_OPEN  = ( 1 << 10 ),
    FS_UNSUPPORTED_FSTAT    = ( 1 << 11 )
};

enum FOpenFlags
{
    F_OPEN      = ( 1 << 0 ),
    F_WRITE     = ( 1 << 1 ),

    F_READWRITE = ( F_OPEN | F_WRITE ),

    F_APPEND    = ( 1 << 2 ),
    F_CREATE    = ( 1 << 3 ),

    F_EXISTING  = ( 1 << 4 ),

    F_COMPRESSION_METHOD_STORE  = ( 1 << 10 ),
    F_COMPRESSION_METHOD_ZLIB   = ( 1 << 11 ),
};

struct DVM_FIO
{
    const char*     space;
    DESCRIPTOR      deviceDescriptor; // optional

    // File IO
    DVM_IO_OPEN     open;
    DVM_IO_CLOSE    close;

    DVM_IO_READ     read;
    DVM_IO_WRITE    write;

    DVM_IO_IS_OPEN  isOpen;

    DVM_IO_FSTAT    fstat;

    duint32         flags;
};

DVM_FS_CONTEXT* dvm_fsInit      (DVM_CLASS* dvmClass);

dint32          dvm_registerFs      (DVM_FIO* fIO, DVM_FS_CONTEXT* fsContext);
const DVM_FIO*  dvm_getFIOByPath    (const char* path, DVM_FS_CONTEXT* fsContext);
char*           dvm_getFileExtension(const char* path);
char*           dvm_getPath         (const char* path);

#endif //VIRTUALDRAGON_DVMFSAPI_H
