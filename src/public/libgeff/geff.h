#ifndef VIRTUALDRAGON_GEFF_H
#define VIRTUALDRAGON_GEFF_H

#include "datatypes.h"

#define GEFF_SIGNATURE_HEADER   (0x4745464601010000)
#define GEFF_SIGNATURE_SECTION  (0x4745464601020000)

#define GEFF_TYPE_NON   (0x0000)
#define GEFF_TYPE_KER   (0x0001)
#define GEFF_TYPE_SYS   (0x0002)
#define GEFF_TYPE_EXE   (0x0010)
#define GEFF_TYPE_SRV   (0x0020)
#define GEFF_TYPE_DYN   (0x0030)
#define GEFF_TYPE_OBJ   (0xDF2D)

#define GEFF_FLAG_READ      (0x00000100)
#define GEFF_FLAG_WRITE     (0x00000200)
#define GEFF_FLAG_EXECUTE   (0x00001000)

//#define GEFF_LOCATOR_TYPE_NONE (0x00000000)
//#define GEFF_LOCATOR_TYPE_NONE (0x00000000)

PACKED_BEGIN

struct GEFF_HEADER
{
    duint64 signature;
    // File type.
    duint16 type;
    // Compile date.
    duint64 timeDateStamp;
    // Extra header size.
    duint16 sizeOptionalHeader;
    // Number of sections.
    duint16 sectionNumber;
    duint64 sectionTablePointer;
} PACKED;

struct GEFF_SECTION
{
    duint64 signature;
    duint32 crc32;
    // Section name includes NULL
    char    name[32];
    duint64 sectionSize;
    duint64 virtualAddress;
    duint32 flags;
} PACKED;

struct GEFF_MODULE // 32 byte per record
{
    duint64 name;
    duint8  reserved[16];
    duint32 info;
    duint32 flags;
} PACKED;

struct GEFF_EXPORT_DIRECTORY // 32 byte per record
{
    duint64 name;
    duint64 address;
    // Size of data/function
    duint32 dataSize;
    duint8  reserved[8];
    duint32 flags;
} PACKED;

struct GEFF_IMPORT_DIRECTORY // 32 byte per record
{
    duint64 index;
    duint64 name;
    duint8  reserved[16];
} PACKED;

struct GEFF_RELOC_RECORD // 32 byte per record
{
    duint64 mask;
    duint64 offset;
    duint32 addend;
    duint16 shift;
    duint8  reserved[2];
    duint32 info;
    duint32 flags;
} PACKED;

PACKED_END

dint geff_validateGEFFHeader(struct GEFF_HEADER* header);
dsize geff_calculateAllSectionSize(struct GEFF_HEADER* header);
struct GEFF_SECTION* geff_getSectionById(struct GEFF_HEADER* header, duint16 sectionId);

#endif // !VIRTUALDRAGON_GEFF_H