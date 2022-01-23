#ifndef VIRTUALDRAGON_OPCODE_H
#define VIRTUALDRAGON_OPCODE_H

#define OP_JMP  ( 0x00 )
#define OP_JE   ( 0x01 )
#define OP_JNE  ( 0x02 )
#define OP_JL   ( 0x03 )
#define OP_JGE  ( 0x04 )
//#define OP_

#if defined(DASM)

#include "assembler/opcode_struct.h"

#define DEFAULT_MAP "0|000|0000|000000000000000000000000-sw|f|op|imm"

INSTRUCTION_INFO inf[] = {
        {
                .category       = "Flow",
                .mnemonic       = "JMP",
                .template       = "%mnemonic %imm",
                .opcode         = OP_JMP,
                .instructionMap = DEFAULT_MAP,
                .description    = "IP = Imm"
        },
};

#endif

#endif //VIRTUALDRAGON_OPCODE_H
