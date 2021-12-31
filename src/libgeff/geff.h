#ifndef VIRTUALDRAGON_GEFF_H
#define VIRTUALDRAGON_GEFF_H

#include "datatypes.h"

struct GEFF
{
    duint64 signature;
    // System arch (COFF compatible).
    duint16 machine;
    // Entry for dvm.
    duint64 entry;
    // Extra header size.
    duint16 sizeOfOptionalHeader;
    // Compile date.
    duint64 timeDateStamp;
    duint64
};

#endif // !VIRTUALDRAGON_GEFF_H