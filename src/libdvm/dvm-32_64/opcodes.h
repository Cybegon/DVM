#ifndef VIRTUALDRAGON_OPCODES_H
#define VIRTUALDRAGON_OPCODES_H

// Basic
#define OP_MOV      ( 0x00 )
#define OP_PUSH     ( 0x01 )
#define OP_POP      ( 0x02 )
#define OP_SWP      ( 0x04 )
#define OP_LD       ( 0x07 )
#define OP_ST       ( 0x08 )
//#define OP_NOP      ( 0x03 )

// interrupts
#define OP_HWI  ( 0x0A ) // hardware/exception interrupts
#define OP_SWI  ( 0x0B ) // software interrupts

// Integer arithmetic
#define OP_ADD      ( 0x10 )
#define OP_SUB      ( 0x11 )
#define OP_EADD     ( 0x12 )
#define OP_ESUB     ( 0x13 )
#define OP_EADC     ( 0x14 )
#define OP_ESBB     ( 0x15 )

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
#define OP_JMP      ( 0x40 )
#define OP_JEQ      ( 0x41 )
#define OP_JNE      ( 0x42 )
#define OP_JLT      ( 0x43 )
#define OP_JGT      ( 0x44 )
#define OP_JGE      ( 0x45 )
#define OP_JLE      ( 0x46 )

#define OP_CALL     ( 0x50 )
#define OP_CEQ      ( 0x51 )
#define OP_CNE      ( 0x52 )
#define OP_CLT      ( 0x53 )
#define OP_CGT      ( 0x54 )
#define OP_CGE      ( 0x55 )
#define OP_CLE      ( 0x56 )

#define OP_RET      ( 0x60 )
#define OP_ENTER    ( 0x6A )
#define OP_LEAVE    ( 0x6B )

#endif //VIRTUALDRAGON_OPCODES_H
