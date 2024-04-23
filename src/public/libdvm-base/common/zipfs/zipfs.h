#ifndef VIRTUALDRAGON_ZIPFS_H
#define VIRTUALDRAGON_ZIPFS_H

#include "datatypes.h"

#include "dvmfsapi.h"

DVM_FIO*    zipfs_createFs  (POINTER space, POINTER path, DVM_CLASS* dvmClass);
void        zipfs_destroyFs (DVM_FIO *fIO, DVM_CLASS* dvmClass);

#endif //VIRTUALDRAGON_ZIPFS_H
