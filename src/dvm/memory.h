//
// Created by Limaaron on 22.01.2022.
//

#ifndef VIRTUALDRAGON_MEMORY_H
#define VIRTUALDRAGON_MEMORY_H

//#define DT_DISABLE_VOID
//#define DT_DISABLE_GUID


#include "libdvm/dvmclass.h"
#ifdef CYBEGON_PLATFORM_WINDOWS
#include <windows.h>
#else
// TODO: not all platforms that are not Windows are UNIX-compatible
#include <fcntl.h>
#include <sys/errno.h>
#include <sys/mman.h>

#include <string.h>
#endif
#include "datatypes.h"

MEMORY  DVM_CALLBACK allocVM    (dsize size, duint32 flags, duint32 protection);
MEMORY  DVM_CALLBACK reallocVM  (MEMORY address, dsize size);
VOID    DVM_CALLBACK freeVM     (MEMORY address);

DESCRIPTOR  DVM_CALLBACK mmapVM     (MEMORY address, dsize size, duint32 flags, duint32 protection);
MEMORY      DVM_CALLBACK viewMmapVM (DESCRIPTOR handle, duint64 offset, duint64 length);
VOID        DVM_CALLBACK freeMmapVM (DESCRIPTOR handle);

#endif //VIRTUALDRAGON_MEMORY_H
