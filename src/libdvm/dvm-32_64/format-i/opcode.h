#ifndef VIRTUALDRAGON_OPCODE_H
#define VIRTUALDRAGON_OPCODE_H

#include "datatypes.h"

// Basic
#define OP_MOV      ( 0x00 )
#define OP_PUSH     ( 0x01 )
#define OP_PUSHF    ( 0x02 )
#define OP_POP      ( 0x03 )
#define OP_POPF     ( 0x04 )
#define OP_LEA      ( 0x05 )
//#define OP_NOP      ( 0x03 )

// interrupts
#define OP_HWI  ( 0x0A ) // hardware/exception interrupts
#define OP_SWI  ( 0x0B ) // software interrupts

// Integer arithmetic
#define OP_ADD      ( 0x10 )
#define OP_SUB      ( 0x11 )
#define OP_ADDF     ( 0x12 )
#define OP_SUBF     ( 0x13 )
#define OP_ADC      ( 0x14 )
#define OP_SBB      ( 0x15 )

#define OP_INC      ( 0x14 )
#define OP_DEC      ( 0x15 )

#define OP_MUL      ( 0x16 )
#define OP_DIV      ( 0x17 )
#define OP_IMUL     ( 0x18 )
#define OP_IDIV     ( 0x19 )
#define OP_MOD      ( 0x1A )

#define OP_SHL      ( 0x1B )
#define OP_SHR      ( 0x1C )
#define OP_ROL      ( 0x1D )
#define OP_ROR      ( 0x1E )

// Bit operations
#define OP_BS       ( 0x20 ) // bit scan
#define OP_BT       ( 0x21 ) // bit test
#define OP_BTS      ( 0x22 ) // bit test & set
#define OP_BTR      ( 0x23 ) // bit test & reset
#define OP_BTC      ( 0x24 ) // bit test & invert

// Logic
#define OP_AND      ( 0x30 )
#define OP_NAND     ( 0x31 )
#define OP_OR       ( 0x32 )
#define OP_NOR      ( 0x33 )
#define OP_XOR      ( 0x34 )
#define OP_NOT      ( 0x35 )
#define OP_NEG      ( 0x36 )

// Compare
#define OP_CMP      ( 0x3A )
#define OP_TST      ( 0x3B )

// Flow
#define OP_RET      ( 0x40 )
#define OP_ENTER    ( 0x4A )
#define OP_LEAVE    ( 0x4B )
#define OP_JMP      ( 0x50 )
#define OP_CALL     ( 0x60 )

// Easter egg
#define OP_RAWR ( 0x47 ) // I'm a dragon
#define OP_RLL  ( 0x75 ) // R Loves L

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
}



#endif

#endif //VIRTUALDRAGON_OPCODE_H
