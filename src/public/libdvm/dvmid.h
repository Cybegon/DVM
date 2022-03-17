#ifndef VIRTUALDRAGON_DVMID_H
#define VIRTUALDRAGON_DVMID_H

typedef struct DVM_ID DVM_ID;

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
        char    vendorID[16];
        duint32 bits; // example 64 = 64bit arch
        duint32 archID;
    } cpu_id; // The architecture on which dvm works


};

#endif // VIRTUALDRAGON_DVMID_H
