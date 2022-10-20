#ifndef VIRTUALDRAGON_LOPCODES_H
#define VIRTUALDRAGON_LOPCODES_H

#define OP_CALL ( 0x00 )
#define OP_CEQ  ( 0x01 )
#define OP_CNE  ( 0x02 )

// Signed
#define OP_CLT  ( 0x03 )
#define OP_CGT  ( 0x04 )
#define OP_CGE  ( 0x05 )
#define OP_CLE  ( 0x06 )

// Unsigned
#define OP_CLS  ( 0x07 )
#define OP_CHS  ( 0x08 )
#define OP_CLO  ( 0x09 )
#define OP_CHI  ( 0x0A )

#define OP_RET  ( 0x0B )
#define OP_INV  ( 0x0F )

#endif //VIRTUALDRAGON_LOPCODES_H
