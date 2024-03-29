#ifndef VIRTUALDRAGON_DVMDEF_H
#define VIRTUALDRAGON_DVMDEF_H

#include "datatypes.h"

#define DVM_DEFAULT_PAGE_SIZE   512u
#define DVM_DEFAULT_PAGE_SHIFT  3u

#define DVM_ENDIAN_BIG      1u
#define DVM_ENDIAN_LITTLE   0u

#define DVM_EXIT                (0u)
#define DVM_SUCCESS             (1u)
#define DVM_FAIL                (2u)
#define DVM_UNDEFINED_VMCODE    (3u)

#define DVM_LOAD_PAGE           (8u) // get next block to cache // Hello transition delay ;)
#define DVM_TRANSFER_CONTROL    (65535u)

#define REGISTER_COUNT          ( 32u ) // do not edit
#define REGISTER_MASK           ( REGISTER_COUNT - 1u ) // equals 0b00011111

#define nR(n)                   ( (n) & REGISTER_MASK )
#define  R(n)                   ( state->rn[ nR(n) ] )

#define SPECIAL_REGISTER_COUNT  ( 8u )
#define SPECIAL_REGISTER_MASK   ( SPECIAL_REGISTER_COUNT - 1u )

#define nSR(n)                  ( (n) & SPECIAL_REGISTER_MASK )
#define  SR(n)                  ( state->sr[ nSR(n) ] )

#define FR  SR(7u) // flag register
#define CP  SR(5u) // code pointer
#define DP  SR(4u) // data pinter
#define BH  SR(3u) // border high
#define BL  SR(2u) // border low
#define IP  SR(0u) // instruction pointer

#define SP  R(31u) // stack pointer
#define BP  R(30u) // base pointer
#define TP  R(29u) // this pointer
// ...
#define RA  R(0u)  // Using for return address or value. accumulator

// Convert Register to flag register
#define cvtR2FR(r) ((FLREGISTER*)&(r))

#define DVM_FETCH(s) (( (INSTRUCTION*)( &(((duint8*)(s)->text)[ IP ]) ) ))

//#define DVM_NEXT_INSTRUCTION(ip, s) \
//    ip += sizeof( s );              \
//    om_nom_nom += sizeof( s )

#define PUSH( type, var ) \
    ( *((type*) (&((duint8*)state->stack)[ SP -= sizeof(type) ])) = (var) )

#define POP( type ) \
    *((type*)(&((duint8*)state->stack)[ SP ])); \
    SP += sizeof(type)

#define vmchunkexec()   for(; IP < BH;) // Chunk
#define afterexec
#define vmdispatch(o)	switch(o)
#define vmswitch(o)     switch(o)
#define vmcase(l)	    case l:
#define vmbreak		    break
#define vmdefault       default
#define vmslot(s)       s:
#define vmsignal(s)     goto s
#define vmrelease(c)    return c;

#define DVM_SWAP_UNSAFE( varA, varB ) \
        ( (varA) ^= (varB), (varB) ^= (varA), (varA) ^= (varB) )

#define DVM_SWAP( varA, varB ) \
        ( ( &(varA) == &(varB) ) ? (varA) : DVM_SWAP_UNSAFE( varA, varB ) )

#define DVM_SIGN_EXTEND(x, b) \
    ((x ^ (1ull << (b - 1ull))) - (1ull << (b - 1ull)))

union INSTRUCTION64 {
    duint64 i64;
    struct {
        duint32 i32H;
        duint32 i32L;
    };
};

union INSTRUCTION32 {
    duint32 v32;
    struct {
        duint16 v16H;
        duint16 v16L;
    };
};

struct FLREGISTER {
    duint8  vm_control;
    duint8  vm_status;
    duint8  vm_privilege;
    duint8  vm_reserved;
    duint32 vm_user;
};

#endif // VIRTUALDRAGON_DVMDEF_H
