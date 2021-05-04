#ifndef VIRTUALDRAGON_DVMDEF_H
#define VIRTUALDRAGON_DVMDEF_H

#define REGISTER_COUNT 32

#if REGISTER_COUNT < 8
#   error Minimum allowed value in REGISTER_COUNT 8
#endif

#define nIP  31     // n instruction pointer
#define nSP  30     // n stack pointer
#define nBP  29     // n base pointer
#define nTP  28     // n this pointer
#define nRA  27     // n return address

#define IP  state->rn[ nIP ]    // instruction pointer
#define SP  state->rn[ nSP ]    // stack pointer
#define BP  state->rn[ nBP ]    // base pointer
#define TP  state->rn[ nTP ]    // this pointer
#define RA  state->rn[ nRA ]    // return address

#define PUSH( type, var )                   \
    ( (type*)state->stack )[ SP ] = var;    \
    SP += sizeof(type)

#define POP( type )             \
    SP -= sizeof(type);         \
    ((type*)state->stack)[ SP ]

#define vmdispatch(o)	switch(o)
#define vmswitch(o)     switch(o)
#define vmcase(l)	    case l:
#define vmbreak		    break
#define vmdefault       default:
#define vmrelease       return

#endif // VIRTUALDRAGON_DVMDEF_H
