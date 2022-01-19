#ifndef VIRTUALDRAGON_ENCODE_H
#define VIRTUALDRAGON_ENCODE_H

#define DVM_GET_OPCODE(i)   ( (i & 0x0F000000u) >> 24u )    // 4    bit

#define DVM_GET_IMM24(i)    ( i & 0x00FFFFFFu )             // 24   bit

#endif //VIRTUALDRAGON_ENCODE_H
