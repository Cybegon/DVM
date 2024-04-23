#ifndef VIRTUALDRAGON_OSFS_H
#define VIRTUALDRAGON_OSFS_H

#include "datatypes.h"

#include "dvmfsapi.h"

DVM_FIO*    osfs_createFs  (POINTER space, POINTER path, DVM_CLASS* dvmClass);
void        osfs_destroyFs (DVM_FIO *fIO, DVM_CLASS* dvmClass);

#endif //VIRTUALDRAGON_OSFS_H
