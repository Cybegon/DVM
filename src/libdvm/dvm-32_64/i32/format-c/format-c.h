#ifndef VIRTUALDRAGON_FORMAT_C_H
#define VIRTUALDRAGON_FORMAT_C_H

#define DVM_FORMAT_C (4)

#include "dvm.h"
#include "dvmclass.h"

// jump 24 bit imm
VOID DVM_FASTCALL format_c(DVM* state, duint32 instruction);

#endif //VIRTUALDRAGON_FORMAT_C_H
