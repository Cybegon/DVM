#ifndef VIRTUALDRAGON_FLAGS_H
#define VIRTUALDRAGON_FLAGS_H

// ENDIAN FLAG
// 1xxx... = big-endian
#define EF ( 1ULL << 63ULL ) // endian flag
#define TF ( 1ULL << 62ULL )

#define RESERVED0 0x4000000000000000u //
#define RESERVED1 0x2000000000000000u //
#define RESERVED2 0x1000000000000000u // feature: TRAP FLAG

#define EQ  ( 1ULL << 56ULL ) // equal
#define LT  ( 1ULL << 55ULL ) // less than
#define CF  ( 1ULL << 54ULL ) // carry



#endif //VIRTUALDRAGON_FLAGS_H
