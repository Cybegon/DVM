#ifndef VIRTUALDRAGON_DVMDEF_H
#define VIRTUALDRAGON_DVMDEF_H

#include "virtualdragon.h"

#define REGISTER_COUNT          ( 32u ) // do not edit
#define REGISTER_MASK           ( REGISTER_COUNT - 1u ) // equals 0b00011111

#define nR(n)                   ( n & REGISTER_MASK )
#define  R(n)                   ( state->rn[ nR(n) ] )

#define SPECIAL_REGISTER_COUNT  ( 8u )
#define SPECIAL_REGISTER_MASK   ( SPECIAL_REGISTER_COUNT - 1u )

#define nSR(n)                  ( n & SPECIAL_REGISTER_MASK )
#define  SR(n)                  ( state->sr[ nSR(n) ] )

#define FR  SR(7u) // flag register
#define AX  SR(5u) // auxiliary register
#define CH  SR(2u) // cache register
#define IP  SR(0u) // instruction pointer

#define SP  R(30u) // stack pointer
#define BP  R(29u) // base pointer
#define TP  R(28u) // this pointer
// ...
#define RA  R(0u)  // Using for return address or value. accumulator

#define DVM_FETCH(s) (( (INSTRUCTION)( &(((duint8*)s->text)[ IP ]) ) ))

//#define DVM_NEXT_INSTRUCTION(ip, s) \
//    ip += sizeof( s );              \
//    om_nom_nom += sizeof( s )

#define PUSH( type, var ) \
    ( *((type*) (&((duint8*)state->stack)[ SP -= sizeof(type) ])) = var )

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

#define vmchunkexec(c)  for(REGISTER codeChunkSize = c->codeChunkSize + IP; IP < codeChunkSize;) // Chunk
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
        ( (var >> pos)  & 0x01u )

#define DVM_BIT_SET( var, pos ) \
        ( (var) |= (1u << (pos) ) )

#define DVM_BIT_CLEAR( var, pos ) \
        ( (var) &= ~(1u << (pos) ) )

#define DVM_SWAP_UNSAFE( varA, varB ) \
        ( (varA) ^= (varB), (varB) ^= (varA), (varA) ^= (varB) )

#define DVM_SWAP( varA, varB ) \
        ( ( &(varA) == &(varB) ) ? (varA) : DVM_SWAP_UNSAFE( varA, varB ) )

#endif // VIRTUALDRAGON_DVMDEF_H
