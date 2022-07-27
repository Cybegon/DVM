#include "dvmbase.h"

#include "os/win32/dvm_memory.c"
#include "zip.h"

#include "libgeff/geff.h"

#include "stdio.h"

static size_t on_extract(void *arg, unsigned long long offset, const void *data, size_t size) {
//    printf("%llu, %llu\n\n", offset, size);

    return size;
}

DESCRIPTOR dvm_openExecutableFile(const char* fileName)
{
    return (DESCRIPTOR)zip_open(fileName, ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
}

void dvm_loadSectionIntoMemory(MEMORY imageBase, DESCRIPTOR dvmExecutableFile, struct GEFF_HEADER* header, duint16 sectionId)
{
    MEMORY mem = NULL;

    duint32 localProtection = 0;

    struct zip_t* zip = (struct zip_t*)dvmExecutableFile;
    struct GEFF_SECTION* section = (struct GEFF_SECTION*)header->sectionTablePointer;

    if (section[sectionId].flags & GEFF_FLAG_READ)
        localProtection |= DVM_PROT_READ;
    if (section[sectionId].flags & GEFF_FLAG_WRITE)
        localProtection |= DVM_PROT_READWRITE;
    if (section[sectionId].flags & GEFF_FLAG_EXECUTE)
        localProtection |= DVM_PROT_EXEC;

    mem = dvm_vAlloc((ADDRESS)((duint64)imageBase + (duint64)section[sectionId].virtualAddress),
               section[sectionId].sectionSize,
               DVM_MEM_COMMIT,
               localProtection);

    zip_entry_open(zip, section[sectionId].name);
    {
        zip_entry_noallocread(zip, mem, section[sectionId].sectionSize);
    }
    zip_entry_close(zip);
}

MEMORY dvm_createVMImage(DESCRIPTOR dvmExecutableFile, duint16 fileType)
{
    MEMORY image = NULL;

    int err = 0;
    void* data = NULL;
    dsize dataSize = 0;

    struct zip_t* zip = (struct zip_t*)dvmExecutableFile;
    err = zip_entry_open(zip, ".header");

    switch (err) {
        case ZIP_ENOINIT:
            return NULL; // invalid descriptor
        case ZIP_EINVENTNAME:
        case ZIP_ENOENT:
            return NULL; // can't find .header section
    }
    zip_entry_read(zip, &data, &dataSize);

    // Parse header
    struct GEFF_HEADER* header = (struct GEFF_HEADER*)data;
    if (header->signature != GEFF_SIGNATURE)
    {
        return NULL; // signatire undefined
    }

    duint size = geff_calculateAllSectionSize(header);

    image = dvm_vAlloc(NULL, size, DVM_MEM_RESERVE, DVM_PROT_READ);

}

MEMORY dvm_getChunk(MEMORY VMImage, dsize offset, dsize size)
{

}

DVM_CLASS* dvm_initClass(DVM_CLASS* dvmClass, DESCRIPTOR fileImage)
{
    dvmClass->malloc             = dvm_malloc;
    dvmClass->realloc            = dvm_realloc;
    dvmClass->free               = dvm_free;

    dvmClass->stackSize          = DVM_BASE_STACK_SIZE;
    dvmClass->imageDescriptor    = fileImage;
    dvmClass->chunkSize          = DVM_BASE_CHUNK_SIZE;

    return dvmClass;
}

