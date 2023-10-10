#ifndef VIRTUALDRAGON_DVMID_H
#define VIRTUALDRAGON_DVMID_H

typedef struct DVM_ID DVM_ID;

#define DVM_ARCH_8      (1)
#define DVM_ARCH_16     (2)
#define DVM_ARCH_32     (3)
#define DVM_ARCH_64     (4)
#define DVM_ARCH_128    (5)

struct DVM_ID
{
    struct
    {
        // If the epoch has been changed,
        // it means that backward compatibility support has come to the end
        duint16 epoch;
        duint16 major;
        duint16 minor;
        duint16 maintenance;
        duint32 build;
    } version;

    struct
    {
        char        vendorID[32];
        char        brand[64];
        duint32     bits; // example 64 = 64bit arch
        duint32     archID; // DVM CLASSIFICATION
    } cpu_id; // The architecture on which dvm works
};

#endif // VIRTUALDRAGON_DVMID_H
