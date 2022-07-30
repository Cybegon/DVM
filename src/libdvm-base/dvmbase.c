#include "dvmbase.h"

#if defined(CYBEGON_PLATFORM_UNIX)
#   include "os/unix/dvm_memory.c"
#else
#   include "os/win32/dvm_memory.c"
#endif

#include "zip.h"

#include "libgeff/geff.h"

DESCRIPTOR dvm_openExecutableFile(const char* fileName)
{
    return (DESCRIPTOR)zip_open(fileName, ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
}

duint dvm_loadSectionIntoMemory(MEMORY VMImage, DESCRIPTOR dvmExecutableFile, struct GEFF_HEADER* header, duint16 sectionId)
{
    MEMORY mem = NULL;

    duint32 localProtection = 0;

    struct zip_t* zip = (struct zip_t*)dvmExecutableFile;
    struct GEFF_SECTION* section = geff_getSectionById(header, sectionId);

    if (section == NULL)
        return -1; // section not found

    if (section->flags & GEFF_FLAG_READ)
        localProtection |= DVM_PROT_READ;
    if (section->flags & GEFF_FLAG_WRITE)
        localProtection |= DVM_PROT_READWRITE;
    if (section->flags & GEFF_FLAG_EXECUTE)
        localProtection |= DVM_PROT_EXEC;

    mem = VMImage;
    dvm_vProt((ADDRESS)((duint64)VMImage + (duint64)section->virtualAddress),
              section->sectionSize, DVM_PROT_READWRITE);

    zip_entry_open(zip, section->name);
    {
        zip_entry_noallocread(zip, mem, section->sectionSize);
    }
    zip_entry_close(zip);

    dvm_vProt(mem, section->sectionSize, localProtection);

    return 0;
}

MEMORY dvm_createVMImage(DESCRIPTOR dvmExecutableFile, duint16 fileType)
{
    MEMORY VMImage = NULL;

    int err = 0;
    void* data = NULL;
    dsize dataSize = 0;

    struct zip_t* zip = (struct zip_t*)dvmExecutableFile;
    err = zip_entry_open(zip, ".header");
    {
        switch (err) {
            case ZIP_ENOINIT:
                return NULL; // invalid descriptor
            case ZIP_EINVENTNAME:
            case ZIP_ENOENT:
                return NULL; // can't find .header section
            default:
                break;
        }

        zip_entry_read(zip, &data, &dataSize);
    }
    zip_entry_close(zip);

    // Parse header
    struct GEFF_HEADER* header = (struct GEFF_HEADER*)data;
    if (header->signature != GEFF_SIGNATURE_HEADER)
        return NULL; // signatire undefined

    duint size = geff_calculateAllSectionSize(header);

    VMImage = dvm_vAlloc(NULL, size, DVM_PROT_READ);
    if (VMImage == NULL)
        return NULL; // can't create image

    for (duint16 i = 0; i < header->sectionNumber; ++i)
        dvm_loadSectionIntoMemory(VMImage, dvmExecutableFile, header, i);

    return (DESCRIPTOR)VMImage;
}

MEMORY dvm_getChunk(DESCRIPTOR VMImage, dsize offset, dsize size)
{
    return ((MEMORY)((char*)VMImage + offset));
}

DVM_CLASS* dvm_initClass(DVM_CLASS* dvmClass, DESCRIPTOR VMImage)
{
    dvmClass->malloc             = dvm_malloc;
    dvmClass->realloc            = dvm_realloc;
    dvmClass->free               = dvm_free;

    dvmClass->stackSize          = DVM_BASE_STACK_SIZE;
    dvmClass->imageDescriptor    = VMImage;
    dvmClass->chunkSize          = DVM_BASE_CHUNK_SIZE;
    dvmClass->getChunk           = dvm_getChunk;

    return dvmClass;
}

