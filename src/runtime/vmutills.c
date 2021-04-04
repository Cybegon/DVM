#include "vmutills.h"

#include "dvm.h"

void SetIP(DVM* state, REGISTER ip)
{
    state->rn[ IP ] = ip;
}

REGISTER GetIP(DVM* state)
{
    return state->rn[ IP ];
}

void SetSP(DVM* state, REGISTER sp)
{
    state->rn[ SP ] = sp;
}

REGISTER GetSP(DVM* state)
{
    return state->rn[ SP ];
}

void SetBP(DVM* state, REGISTER bp)
{
    state->rn[ BP ] = bp;
}

REGISTER GetBP(DVM* state)
{
    return state->rn[ BP ];
}

void SetTP(DVM* state, REGISTER tp)
{
    state->rn[ TP ] = tp;
}

REGISTER GetTP(DVM* state)
{
    return state->rn[ TP ];
}

void SetRA(DVM* state, REGISTER ra)
{
    state->rn[ RA ] = ra;
}

REGISTER GetRA(DVM* state)
{
    return state->rn[ RA ];
}
