#ifndef VIRTUALDRAGON_LOPCODES_H
#define VIRTUALDRAGON_LOPCODES_H

#define OP_JMP  ( 0x00 )
#define OP_JEQ  ( 0x01 )
#define OP_JNE  ( 0x02 )

// Signed
#define OP_JLT  ( 0x03 )
#define OP_JGT  ( 0x04 )
#define OP_JGE  ( 0x05 )
#define OP_JLE  ( 0x06 )

// Unsigned
#define OP_JLS  ( 0x07 )
#define OP_JHS  ( 0x08 )
#define OP_JLO  ( 0x09 )
#define OP_JHI  ( 0x0A )

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

#endif //VIRTUALDRAGON_LOPCODES_H
