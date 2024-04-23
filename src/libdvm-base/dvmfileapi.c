#include "dvmfileapi.h"

#include "dvmfsapi.h"
#include "dvmfs_p.h"

typedef struct DVM_FS_DESCRIPTOR_WRAPPER DVM_FS_DESCRIPTOR_WRAPPER;

struct DVM_FS_DESCRIPTOR_WRAPPER
{
    const   DVM_CLASS*  dvmClass;
    const   DVM_FIO*    fIO;
            DESCRIPTOR  descriptor;
};

DESCRIPTOR dvm_fileOpen(POINTER path, dint flags, DVM_FS_CONTEXT* fsContext)
{
    DVM_CLASS* dvmClass = fsContext->dvmClass;
    const DVM_FIO* fIO  = dvm_getFIOByPath( path, fsContext );

    DVM_FS_DESCRIPTOR_WRAPPER* wrapper = NULL;

    if ( fIO == NULL )
        return NULL;

    wrapper = dvmClass->malloc( sizeof( DVM_FS_DESCRIPTOR_WRAPPER ) );
    wrapper->dvmClass   = dvmClass;
    wrapper->fIO        = fIO;
    wrapper->descriptor = fIO->open(dvm_getPath( path ), flags, fIO->deviceDescriptor );

    return (DESCRIPTOR)wrapper;
}

void dvm_fileClose(DESCRIPTOR file)
{
    DVM_FS_DESCRIPTOR_WRAPPER* wrapper  = (DVM_FS_DESCRIPTOR_WRAPPER*)file;
    const DVM_CLASS* dvmClass           = wrapper->dvmClass;

    wrapper->fIO->close( wrapper->descriptor,
                             wrapper->fIO->deviceDescriptor );
    dvmClass->free( wrapper );
}

dint64 dvm_fileRead(DESCRIPTOR file, MEMORY buffer, dint64 size)
{
    DVM_FS_DESCRIPTOR_WRAPPER* wrapper  = (DVM_FS_DESCRIPTOR_WRAPPER*)file;

    return wrapper->fIO->read( wrapper->descriptor, buffer, size,
                               wrapper->fIO->deviceDescriptor );
}

dint64 dvm_fileWrite(DESCRIPTOR file, MEMORY buffer, dint64 size)
{
    DVM_FS_DESCRIPTOR_WRAPPER* wrapper  = (DVM_FS_DESCRIPTOR_WRAPPER*)file;

    return wrapper->fIO->write( wrapper->descriptor, buffer, size,
                                wrapper->fIO->deviceDescriptor );
}

dint32 dvm_fileIsOpen(DESCRIPTOR file)
{
    DVM_FS_DESCRIPTOR_WRAPPER* wrapper  = (DVM_FS_DESCRIPTOR_WRAPPER*)file;

    if ( wrapper->fIO->flags & FS_UNSUPPORTED_IS_OPEN )
        return -1;

    return wrapper->fIO->isOpen( wrapper->descriptor,
                                 wrapper->fIO->deviceDescriptor );
}

dint32 dvm_fileFStat(DESCRIPTOR file, DVM_FSTAT* info)
{
    DVM_FS_DESCRIPTOR_WRAPPER* wrapper  = (DVM_FS_DESCRIPTOR_WRAPPER*)file;

    return wrapper->fIO->fstat( file, info,
                                wrapper->fIO->deviceDescriptor );
}
