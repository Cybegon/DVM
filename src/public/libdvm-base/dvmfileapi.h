#ifndef VIRTUALDRAGON_DVMFILEAPI_H
#define VIRTUALDRAGON_DVMFILEAPI_H

#include "datatypes.h"
#include "dvmbase.h"

enum DVMFileFlags
{
    DVM_F
};

typedef struct DVM_FS_CONTEXT   DVM_FS_CONTEXT;
typedef struct DVM_FSTAT        DVM_FSTAT;

struct DVM_FSTAT
{
    duint32         crc32;

    duint64         fileID;
    const char*     space;

    duint64         compressedSize;
    duint64         uncompressedSize;

    duint32         flags;
};

DESCRIPTOR      dvm_fileOpen    (POINTER path, dint flags, DVM_FS_CONTEXT* fsContext);
void            dvm_fileClose   (DESCRIPTOR file);

dint64          dvm_fileRead    (DESCRIPTOR file, MEMORY buffer, duint32 size);
dint64          dvm_fileWrite   (DESCRIPTOR file, MEMORY buffer, duint32 size);

dint32          dvm_fileIsOpen  (DESCRIPTOR file);
dint32          dvm_fileFStat   (DESCRIPTOR file, DVM_FSTAT* info);

#endif //VIRTUALDRAGON_DVMFILEAPI_H
