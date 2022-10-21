#ifndef VIRTUALDRAGON_FORMAT_J_H
#define VIRTUALDRAGON_FORMAT_J_H

#define CAR_FORMAT_J (3)

#include "dvm.h"

// jump 24 bit imm
VOID DVM_FASTCALL format_j(DVM* state, duint32 instruction);

#endif // VIRTUALDRAGON_FORMAT_J_H
