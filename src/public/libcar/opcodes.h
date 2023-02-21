#ifndef VIRTUALDRAGON_OPCODES_H
#define VIRTUALDRAGON_OPCODES_H

#if defined(CAR_FORMAT_I) || defined(CAR_FORMAT_R)

// Basic
#define OP_MOV      ( 0x00 )
#define OP_PUSH     ( 0x01 )
#define OP_POP      ( 0x02 )
#define OP_SWP      ( 0x03 )
#define OP_LD       ( 0x04 )
#define OP_ST       ( 0x05 )
#define OP_BK       ( 0x09 ) // breakpoint ()

// interrupts
#define OP_HWI      ( 0x0A ) // hardware/exception interrupts
#define OP_SWI      ( 0x0B ) // software interrupts

// Special
#define OP_ENTER    ( 0x0C )
#define OP_LEAVE    ( 0x0D )
#define OP_INV      ( 0x0F )
//#define OP_NOP      ( 0x03 )

// Integer arithmetic
#define OP_ADD      ( 0x10 )
#define OP_SUB      ( 0x11 )

#define OP_INC      ( 0x14 )
#define OP_DEC      ( 0x15 )

#define OP_MUL      ( 0x16 )
#define OP_DIV      ( 0x17 )
#define OP_IMUL     ( 0x18 )
#define OP_IDIV     ( 0x19 )
#define OP_MOD      ( 0x1A )

#define OP_SHL      ( 0x20 )
#define OP_SHR      ( 0x21 )
#define OP_ROL      ( 0x24 )
#define OP_ROR      ( 0x25 )

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
#define OP_ICMP     ( 0x3B )

// Flow
#define OP_JMP      ( 0x40 )
#define OP_JEQ      ( 0x41 )
#define OP_JNE      ( 0x42 )
#define OP_JLE      ( 0x43 )
#define OP_JGE      ( 0x44 )
#define OP_JLT      ( 0x45 )
#define OP_JGT      ( 0x46 )
#define OP_JLS      ( 0x47 )
#define OP_JHS      ( 0x48 )
#define OP_JLO      ( 0x49 )
#define OP_JHI      ( 0x4A )

#define OP_CALL     ( 0x50 )
#define OP_CEQ      ( 0x51 )
#define OP_CNE      ( 0x52 )
#define OP_CLE      ( 0x53 )
#define OP_CGE      ( 0x54 )
#define OP_CLT      ( 0x55 )
#define OP_CGT      ( 0x56 )
#define OP_CLS      ( 0x57 )
#define OP_CHS      ( 0x58 )
#define OP_CLO      ( 0x59 )
#define OP_CHI      ( 0x5A )

#define OP_RET      ( 0x60 )

#elif defined(CAR_FORMAT_J) || defined(CAR_FORMAT_C)

#   define OP_JMP  ( 0x00 ) // JUMPS
#   define OP_JEQ  ( 0x01 )
#   define OP_JNE  ( 0x02 )

// Signed
#   define OP_JLT  ( 0x03 )
#   define OP_JGT  ( 0x04 )
#   define OP_JGE  ( 0x05 )
#   define OP_JLE  ( 0x06 )

// Unsigned
#   define OP_JLS  ( 0x07 )
#   define OP_JHS  ( 0x08 )
#   define OP_JLO  ( 0x09 )
#   define OP_JHI  ( 0x0A )

#   define OP_CALL ( 0x00 ) // CALLS
#   define OP_CEQ  ( 0x01 )
#   define OP_CNE  ( 0x02 )

// Signed
#   define OP_CLT  ( 0x03 )
#   define OP_CGT  ( 0x04 )
#   define OP_CGE  ( 0x05 )
#   define OP_CLE  ( 0x06 )

// Unsigned
#   define OP_CLS  ( 0x07 )
#   define OP_CHS  ( 0x08 )
#   define OP_CLO  ( 0x09 )
#   define OP_CHI  ( 0x0A )

#   define OP_RET  ( 0x0B )
#   define OP_INV  ( 0x0F )

#   if defined(CAR_64)
#       define OP_RJMP  ( 0x10 ) // Relative JUMPS
#       define OP_RJEQ  ( 0x11 )
#       define OP_RJNE  ( 0x12 )

// Signed
#       define OP_RJLT  ( 0x13 )
#       define OP_RJGT  ( 0x14 )
#       define OP_RJGE  ( 0x15 )
#       define OP_RJLE  ( 0x16 )

// Unsigned
#       define OP_RJLS  ( 0x17 )
#       define OP_RJHS  ( 0x18 )
#       define OP_RJLO  ( 0x19 )
#       define OP_RJHI  ( 0x1A )

#       define OP_RCALL ( 0x10 ) // Relative CALLS
#       define OP_RCEQ  ( 0x11 )
#       define OP_RCNE  ( 0x12 )

// Signed
#       define OP_RCLT  ( 0x13 )
#       define OP_RCGT  ( 0x14 )
#       define OP_RCGE  ( 0x15 )
#       define OP_RCLE  ( 0x16 )

// Unsigned
#       define OP_RCLS  ( 0x17 )
#       define OP_RCHS  ( 0x18 )
#       define OP_RCLO  ( 0x19 )
#       define OP_RCHI  ( 0x1A )
#   endif
#endif

#endif //VIRTUALDRAGON_OPCODES_H
