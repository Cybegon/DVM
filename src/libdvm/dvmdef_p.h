#ifndef VIRTUALDRAGON_DVMDEF_P_H
#define VIRTUALDRAGON_DVMDEF_P_H

#include "dvm.h"

typedef struct FLREGISTER FLREGISTER;

#define REGISTER_COUNT          ( 32u ) // do not edit
#define REGISTER_MASK           ( REGISTER_COUNT - 1u ) // equals 0b00011111

#define nR(n)                   ( (n) & REGISTER_MASK )
#define  R(n)                   ( state->rn[ nR(n) ] )

#define SPECIAL_REGISTER_COUNT  ( 8u )
#define SPECIAL_REGISTER_MASK   ( SPECIAL_REGISTER_COUNT - 1u )

#define nSR(n)                  ( (n) & SPECIAL_REGISTER_MASK )
#define  SR(n)                  ( state->sr[ nSR(n) ] )

#define FR  SR(7u) // flag register
#define BH  SR(3u) // border high
#define BL  SR(2u) // border low
#define IP  SR(0u) // instruction pointer

#define SP  R(30u) // stack pointer
#define BP  R(29u) // base pointer
#define TP  R(28u) // this pointer
// ...
#define RA  R(0u)  // Using for return address or value. accumulator

#define cvtR2FR(r) ((FLREGISTER*)&(r))

#define DVM_FETCH(s) (( (INSTRUCTION)( &(((duint8*)(s)->text)[ IP ]) ) ))

//#define DVM_NEXT_INSTRUCTION(ip, s) \
//    ip += sizeof( s );              \
//    om_nom_nom += sizeof( s )

#define PUSH( type, var ) \
    ( *((type*) (&((duint8*)state->stack)[ SP -= sizeof(type) ])) = (var) )

#define POP( type ) \
    *((type*)(&((duint8*)state->stack)[ SP ])); \
    SP += sizeof(type)

///////////////// DEPRECATED /////////////////
//#define DEPRECATED_DVM_FETCH(s) ( ( (duint32*)s->text )[ IP ] )
//
//#define PUSH( type, var )                   \
//    ( (type*)state->stack )[ SP ] = var;    \
//    SP -= sizeof(type)
//
//#define POP( type )             \
//    SP += sizeof(type);         \
//    ((type*)state->stack)[ SP ]
///////////////// DEPRECATED /////////////////

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

#define DVM_BIT_GET( var, pos ) \
        ( ((var) >> (pos))  & 0x01u )

#define DVM_BIT_SET( var, pos ) \
        ( (var) |= (1u << (pos) ) )

#define DVM_BIT_CLEAR( var, pos ) \
        ( (var) &= ~(1u << (pos) ) )

#define DVM_SWAP_UNSAFE( varA, varB ) \
        ( (varA) ^= (varB), (varB) ^= (varA), (varA) ^= (varB) )

#define DVM_SWAP( varA, varB ) \
        ( ( &(varA) == &(varB) ) ? (varA) : DVM_SWAP_UNSAFE( varA, varB ) )

#define DVM_BSWAP64( var ) \
    (var) = ( ( (var) << 8u  ) & 0xFF00FF00FF00FF00ull ) | ( ( (var) >> 8u  ) & 0x00FF00FF00FF00FFull );    \
    (var) = ( ( (var) << 16u ) & 0xFFFF0000FFFF0000ull ) | ( ( (var) >> 16u ) & 0x0000FFFF0000FFFFull );  \
    (var) = ( (var) << 32u ) | ( ( (var) >> 32u ) & 0xFFFFFFFFull )

struct FLREGISTER {
    duint8  vm_control;
    duint8  vm_status;
    duint8  vm_privilege;
    duint8  vm_reserved;
    duint32 vm_user;
};

#endif // VIRTUALDRAGON_DVMDEF_P_H
