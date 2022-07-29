#include "libgeff/geff.h"

#include "datatypes.h"

dint geff_validateGEFFHeader(struct GEFF_HEADER* header)
{
    return (header->signature == GEFF_SIGNATURE_SECTION) ? TRUE : FALSE;
}

dsize geff_calculateAllSectionSize(struct GEFF_HEADER* header)
{
    dsize size = 0;
    struct GEFF_SECTION* section = (struct GEFF_SECTION*)((char*)header + header->sectionTablePointer);

    for (duint16 i = 0; i < header->sectionNumber; ++i)
        size += geff_getSectionById(header, i)->sectionSize;

    return size;
}

struct GEFF_SECTION* geff_getSectionById(struct GEFF_HEADER* header, duint16 sectionId)
{
    if (sectionId > header->sectionNumber)
        return NULL;
    struct GEFF_SECTION* section = (struct GEFF_SECTION*)((char*)header + header->sectionTablePointer);

    return &section[sectionId];
}
