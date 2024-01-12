#include "libgeff/geff.h"

#include "datatypes.h"

dint geff_validateGEFFHeader(struct GEFF_HEADER* header)
{
    if (header->signature != GEFF_SIGNATURE_SECTION)
        return FALSE;
    if (header->geffVersion != GEFF_VERSION)
        return FALSE;

    return TRUE;
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
