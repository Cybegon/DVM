//
// Created by Limaaron on 26.01.2024.
//

#include "dvmfsapi.h"
#include "dvmfs_p.h"

#include "dvmbase.h"
#include "dvmutils.h"

#include "hashmap.h"

#define FS_DELIM "://"

DVM_FS_CONTEXT* dvm_fsInit(DVM_CLASS* dvmClass)
{
    DVM_FS_CONTEXT* fsContext = dvmClass->malloc( sizeof(DVM_FS_CONTEXT) );

    fsContext->dvmClass = dvmClass;
    fsContext->mounts   = dvmClass->malloc( sizeof(hashmap_t) );

    if ( hashmap_create( 8, fsContext->mounts ) != 0 )
        return NULL;

    return fsContext;
}

dint32 dvm_registerFs(DVM_FIO* fIO, DVM_FS_CONTEXT* fsContext)
{
    if (!fIO->space
            || !fIO->open
            || !fIO->close
            || !fIO->read)
        return 0;

    if ( !(fIO->flags & FS_CAN_WRITE) )
        if ( !fIO->write )
            return 0;
    if ( !(fIO->flags & FS_UNSUPPORTED_IS_OPEN) )
        if ( !fIO->isOpen )
            return 0;
    if ( !(fIO->flags & FS_UNSUPPORTED_FSTAT) )
        if ( !fIO->fstat )
            return 0;

    dsize size = dvm_strlen( fIO->space );
    if (!size)
        return hashmap_put( fsContext->mounts, "null", sizeof("null"), fIO );

    return hashmap_put( fsContext->mounts, fIO->space, size, fIO );
}

const DVM_FIO* dvm_getFIOByPath(const char* path, DVM_FS_CONTEXT* fsContext)
{
    dsize size = ( ( (duint8*)strstr( path, FS_DELIM ) ) - ( (duint8*)path ) );

    if (!size)
        return (const DVM_FIO*)hashmap_get(fsContext->mounts, "null", sizeof("null"));

    return (const DVM_FIO*)hashmap_get(fsContext->mounts, path, size);
}

char* dvm_getFileExtension(const char* path)
{
    return strrchr( path, '.') + 1;
}

char* dvm_getPath(const char* path)
{
    dsize size = (
            ( ((duint8*)strstr( path, FS_DELIM )) - ((duint8*)path) )
            + (sizeof(FS_DELIM) - 1)
            );

    return ( (char*)( ((dsize)path) + ((dsize)size) ) );
}
