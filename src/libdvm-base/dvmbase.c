#include "dvmbase.h"

#include "dvm.h"

#include "dvm_memory.h"
#include "dvmfsapi.h"
#include "dvmfileapi.h"
#include "dvmoptions.h"

#include "geff.h"

#define DESC_ROFS (1 << 0)

MEMORY dvm_getChunk(DESCRIPTOR VMImage, dsize offset, dsize size)
{
    return ((MEMORY)((char*)VMImage + offset));
}

DVM_CLASS* dvm_initClass(DVM_CLASS* dvmClass)
{
    dvmClass->malloc            = dvm_malloc;
    dvmClass->realloc           = dvm_realloc;
    dvmClass->free              = dvm_free;

    dvmClass->stackSize         = DVM_BASE_STACK_SIZE;
    dvmClass->imageDescriptor   = NULL;
    dvmClass->chunkSize         = DVM_BASE_CHUNK_SIZE;
    dvmClass->getChunk          = dvm_getChunk;

    return dvmClass;
}

void dvm_fastAllInit( DVM_CLASS* dvmClass, DVMOptions* options, DVM* state )
{
    dvm_initClass( dvmClass );


}

DVM_CLASS* dvm_setVMImage(DVM_CLASS* dvmClass)
{
    return dvmClass;
}



//duint dvm_loadSectionIntoMemory(DVMFileImage* image, MEMORY VMImage, struct GEFF_HEADER* header, duint16 sectionId)
//{
//    MEMORY mem = NULL;
//
//    duint32 localProtection = 0;
//
//    struct zip_t* zip = (struct zip_t*)dvmExecutableFile;
//    struct GEFF_SECTION* section = geff_getSectionById(header, sectionId);
//
//    if (section == NULL)
//        return -1; // section not found
//
//    if (section->flags & GEFF_FLAG_READ)
//        localProtection |= DVM_PROT_READ;
//    if (section->flags & GEFF_FLAG_WRITE)
//        localProtection |= DVM_PROT_READWRITE;
//    if (section->flags & GEFF_FLAG_EXECUTE)
//        localProtection |= DVM_PROT_EXEC;
//
//    mem = VMImage;
//    dvm_vProt((ADDRESS)((duint64)VMImage + (duint64)section->va),
//              section->sectionSize, DVM_PROT_READWRITE);
//
//    dvm_vProt(mem, section->sectionSize, localProtection);
//
//    return 0;
//}
//
//MEMORY dvm_createVMImage(DVM_CLASS* dvmClass, DVMFileImage* image)
//{
//    MEMORY VMImage = NULL;
//
//    // Parse header
//    struct GEFF_HEADER* header = (struct GEFF_HEADER*)data;
//    if (geff_validateGEFFHeader(header))
//        return NULL;
//
//    duint size = geff_calculateAllSectionSize(header);
//
//    VMImage = dvm_vAlloc(NULL, size, DVM_PROT_READ);
//    if (VMImage == NULL)
//        return NULL; // can't create image
//
//    for (duint16 i = 0; i < header->sectionNumber; ++i)
//        dvm_loadSectionIntoMemory(VMImage, dvmExecutableFile, header, i);
//
//    return (DESCRIPTOR)VMImage;
//}
