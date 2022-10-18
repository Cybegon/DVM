#ifndef VIRTUALDRAGON_LOPCODES_H
#define VIRTUALDRAGON_LOPCODES_H

#include "datatypes.h"

// Remove later
#if defined(DASM)

#include "assembler/opcode_struct.h"

#define DEFAULT_MAP "0|000|0000000|00000|0000000000000000-sw|f|op|r|imm"

INSTRUCTION_INFO inf[] = {
     {
            .category       = "BASIC",
            .mnemonic       = "MOV",
            .template       = "%mnemonic %regDst, %imm",
            .opcode         = OP_MOV,
            .instructionMap = DEFAULT_MAP,
            .description    = "RegDst = Imm"
     },
     {
             .category       = "BASIC",
             .mnemonic       = "PUSH",
             .template       = "%mnemonic %regDst",
             .opcode         = OP_PUSH,
             .instructionMap = DEFAULT_MAP,
             .description    = "SP -= 8, RAM[SP] = Reg"
     },
};

#endif

#endif //VIRTUALDRAGON_LOPCODES_H
