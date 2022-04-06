#ifndef VIRTUALDRAGON_ENCODE_H
#define VIRTUALDRAGON_ENCODE_H

#define DVM_GET_OPCODE(i)   ( (i & 0x0FE00000u) >> 21u )    // 7    bit
#define DVM_GET_R0(i)       ( (i & 0x001F0000u) >> 16u )    // 5    bit
#define DVM_GET_R1(i)       ( (i & 0x0000F800u) >> 11u )    // 5    bit
#define DVM_GET_R2(i)       ( (i & 0x000007C0u) >> 6u )     // 5    bit

#endif //VIRTUALDRAGON_ENCODE_H
