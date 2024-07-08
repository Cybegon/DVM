#ifndef VIRTUALDRAGON_DVMFS_P_H
#define VIRTUALDRAGON_DVMFS_P_H

#include "datatypes.h"
#include "dvmclass.h"

#include "hashmap/hashmap.h"

struct DVM_FS_CONTEXT
{
    DVM_CLASS*  dvmClass;
    hashmap_t*  mounts;
};

struct DVMFileImage
{
    void*   file;
    void*   manifest;
    void*   header;
    void*   cachedData;
    duint32 flags;
};

#endif //VIRTUALDRAGON_DVMFS_P_H
