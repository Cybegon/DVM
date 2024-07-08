#include "common/osfs/osfs.h"

#include "dvmfileapi.h"

#include <mz.h>
#include <mz_strm.h>
#include <mz_strm_os.h>

DESCRIPTOR  osfs_open       (POINTER path, dint flags, DESCRIPTOR deviceDescriptor);
void        osfs_close      (DESCRIPTOR file, DESCRIPTOR deviceDescriptor);

dint64      osfs_readFile   (DESCRIPTOR file, MEMORY buf, duint32 size, DESCRIPTOR deviceDescriptor);
dint64      osfs_writeFile  (DESCRIPTOR file, MEMORY buf, duint32 size, DESCRIPTOR deviceDescriptor);

dint32      osfs_isOpen     (DESCRIPTOR file, DESCRIPTOR deviceDescriptor);
dint32      osfs_fileStat   (DESCRIPTOR file, DVM_FSTAT* info, DESCRIPTOR deviceDescriptor);

DVM_FIO* osfs_createFs(POINTER space, POINTER path, DVM_CLASS* dvmClass)
{
    DVM_FIO* fIO = POINTER_CAST( DVM_FIO*, dvmClass->malloc( sizeof( DVM_FIO ) ) );

    fIO->space              = space;
    fIO->deviceDescriptor   = path;

    fIO->open               = osfs_open;
    fIO->close              = osfs_close;

    fIO->read               = osfs_readFile;
    fIO->write              = osfs_writeFile;

    fIO->isOpen             = osfs_isOpen;
    fIO->fstat              = osfs_fileStat;

    fIO->flags              = FS_CAN_READWRITE;

    return fIO;
}

DESCRIPTOR osfs_open(POINTER path, dint flags, DESCRIPTOR deviceDescriptor)
{
    void* stream = mz_stream_os_create();
    mz_stream_os_open(stream, path, MZ_OPEN_MODE_READ);

    return POINTER_CAST( DESCRIPTOR, stream );
}

void osfs_close(DESCRIPTOR file, DESCRIPTOR deviceDescriptor)
{
    mz_stream_os_close( file );
    mz_stream_os_delete(POINTER_CAST( void**, &file ) );
}

dint64 osfs_readFile(DESCRIPTOR file, MEMORY buf, duint32 size, DESCRIPTOR deviceDescriptor)
{
    return mz_stream_os_read( file, buf, size );
}

dint64 osfs_writeFile(DESCRIPTOR file, MEMORY buf, duint32 size, DESCRIPTOR deviceDescriptor)
{
    return mz_stream_os_write( file, buf, size );
}

dint32 osfs_isOpen(DESCRIPTOR file, DESCRIPTOR deviceDescriptor)
{
    return mz_stream_os_is_open( file );
}

dint32 osfs_fileStat(DESCRIPTOR file, DVM_FSTAT* info, DESCRIPTOR deviceDescriptor)
{
    dint64 position = mz_stream_tell( file );
    dint64 size;

    mz_stream_os_seek( file, 0, MZ_SEEK_END );
    size = mz_stream_os_tell( file );
    mz_stream_os_seek( file, position, MZ_SEEK_SET );

    info->crc32             = 0;
    info->fileID            = (dint64)file;
    info->compressedSize    = 0;
    info->uncompressedSize  = size;

    return 0;
}
