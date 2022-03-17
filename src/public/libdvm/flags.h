#ifndef VIRTUALDRAGON_FLAGS_H
#define VIRTUALDRAGON_FLAGS_H

// state

// ENDIAN FLAG
// 1xxx... = big-endian
#define EF ( 1u << 7u ) // endian flag
#define TF ( 1u << 6u ) // trap flag
#define VF ( 1u << 5u ) // vcpu flag

#define EQ ( 1u << 7u ) // equal
#define LO ( 1u << 6u ) // unsigned lower
#define LT ( 1u << 5u ) // signed less than

#endif //VIRTUALDRAGON_FLAGS_H
