#ifndef VIRTUALDRAGON_FORMAT_J_H
#define VIRTUALDRAGON_FORMAT_J_H

#include "dvm.h"

// jump 48 bit imm
VOID DVM_FASTCALL format_j64(DVM* state, duint64 instruction);

#endif //VIRTUALDRAGON_FORMAT_J_H
