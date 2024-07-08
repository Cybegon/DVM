#include "common/zipfs/zipfs.h"

#include <mz.h>
#include <mz_zip.h>
#include <mz_strm_os.h>

#include "dvmfileapi.h"

DESCRIPTOR  zipfs_open     (POINTER path, dint flags, DESCRIPTOR deviceDescriptor);
void        zipfs_close    (DESCRIPTOR file, DESCRIPTOR deviceDescriptor);
dint64      zipfs_readFile (DESCRIPTOR file, MEMORY buf, duint32 size, DESCRIPTOR deviceDescriptor);
dint32      zipfs_fileStat (DESCRIPTOR file, DVM_FSTAT* info, DESCRIPTOR deviceDescriptor);

DESCRIPTOR zipFileOpen(POINTER path, dint flags)
{
    void* stream    = mz_stream_os_create();
    void* zip       = mz_zip_create();

    if ( !stream )
        return NULL;

    if ( mz_stream_os_open( stream, path, MZ_OPEN_MODE_READ ) != MZ_OK )
        goto CLEANUP;
    if ( mz_zip_open( zip, stream, MZ_OPEN_MODE_READ ) != MZ_OK )
        goto CLEANUP;

    return zip;

CLEANUP:
    mz_zip_delete( &zip );
    mz_stream_os_delete( &stream );

    return NULL;
}

void zipCloseIfOpen(DESCRIPTOR deviceDescriptor)
{
    if ( mz_zip_entry_is_open( deviceDescriptor ) == MZ_OK )
        mz_zip_entry_close(deviceDescriptor );
}

DVM_FIO* zipfs_createFs(POINTER space, POINTER path, DVM_CLASS* dvmClass)
{
    DVM_FIO* fIO = dvmClass->malloc( sizeof( DVM_FIO ) );

    fIO->space              = space;
    fIO->deviceDescriptor   = zipFileOpen( path, 0 );

    fIO->open               = zipfs_open;
    fIO->close              = zipfs_close;

    fIO->read               = zipfs_readFile;
    fIO->write              = NULL;

    fIO->isOpen             = NULL;
    fIO->fstat              = zipfs_fileStat;

    fIO->flags              = FS_CAN_READ | FS_CAN_COMPRESS |
                                FS_UNSUPPORTED_IS_OPEN;

    return fIO;
}

void zipfs_destroyFs(DVM_FIO *fIO, DVM_CLASS* dvmClass)
{
    void* stream = NULL;
    mz_zip_get_stream(fIO->deviceDescriptor, &stream);

    zipCloseIfOpen( fIO->deviceDescriptor );

    mz_zip_close( fIO->deviceDescriptor );
    mz_zip_delete((void **)&fIO->deviceDescriptor);

    mz_stream_os_close( stream );
    mz_stream_os_delete( &stream );

    dvmClass->free( fIO );
}

DESCRIPTOR zipfs_open(POINTER path, dint flags, DESCRIPTOR deviceDescriptor)
{
    if ( mz_zip_locate_entry( deviceDescriptor, path, 0 ) != MZ_OK )
        return NULL;
    return POINTER_CAST( DESCRIPTOR, mz_zip_get_entry( deviceDescriptor ) );
}

void zipfs_close(DESCRIPTOR file, DESCRIPTOR deviceDescriptor)
{
    zipCloseIfOpen( deviceDescriptor );
}

dint64 zipfs_readFile(DESCRIPTOR file, MEMORY buf, duint32 size, DESCRIPTOR deviceDescriptor)
{
    zipCloseIfOpen( deviceDescriptor );

    mz_zip_goto_entry( deviceDescriptor, (dint64)file );
    mz_zip_entry_read_open( deviceDescriptor, 0, NULL );

    return mz_zip_entry_read( deviceDescriptor, buf, (dint32)size ); // TODO: read using a loop
}

dint32 zipfs_fileStat(DESCRIPTOR file, DVM_FSTAT* info, DESCRIPTOR deviceDescriptor)
{
    zipCloseIfOpen( deviceDescriptor );

    mz_zip_file *file_info = NULL;

    mz_zip_goto_entry( deviceDescriptor, (dint64)file );
    mz_zip_entry_get_info( deviceDescriptor, &file_info );

    info->crc32             = file_info->crc;
    info->fileID            = (dint64)file;
    info->compressedSize    = file_info->compressed_size;
    info->uncompressedSize  = file_info->uncompressed_size;

    return 0;
}