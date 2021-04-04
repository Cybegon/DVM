#ifndef VIRTUALDRAGON_VMUTILLS_H
#define VIRTUALDRAGON_VMUTILLS_H

#define IP  31u     // instruction pointer
#define SP  30u     // stack pointer
#define BP  29u     // base pointer
#define TP  28u     // this pointer
#define RA  27u     // return address

typedef duint8      REGISTER8;
typedef duint16     REGISTER16;
typedef duint32     REGISTER32;
typedef duint64     REGISTER64;
typedef REGISTER64  REGISTER;

typedef double      FREGISTER;

void        SetIP(DVM* state, REGISTER ip);
REGISTER    GetIP(DVM* state);

void        SetSP(DVM* state, REGISTER sp);
REGISTER    GetSP(DVM* state);

void        SetBP(DVM* state, REGISTER bp);
REGISTER    GetBP(DVM* state);

void        SetTP(DVM* state, REGISTER tp);
REGISTER    GetTP(DVM* state);

void        SetRA(DVM* state, REGISTER ra);
REGISTER    GetRA(DVM* state);

#endif // VIRTUALDRAGON_VMUTILLS_H
