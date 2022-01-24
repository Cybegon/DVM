#include "format-c.h"

#include "dvmdef.h"
#include "encode.h"
#include "opcode.h"
#include "vcpu.h"

#define DVM_ENABLE_JUMP

#include "flags.h"
#include "auxiliary.h"

VOID DVM_FASTCALL format_c(DVM* state, duint32 instruction) {
    vmswitch(DVM_GET_OPCODE(instruction)) {
        vmcase(OP_CALL) {
            PUSH(REGISTER, IP); JUMP();
            vmbreak;
        }
        vmcase(OP_CEQ) {
            IF_EQ() { PUSH(REGISTER, IP); JUMP(); }
            vmbreak;
        }
        vmcase(OP_CNE) {
            IF_NE() { PUSH(REGISTER, IP); JUMP(); }
            vmbreak;
        }
        vmcase(OP_CLT) {
            IF_LT() { PUSH(REGISTER, IP); JUMP(); }
            vmbreak;
        }
        vmcase(OP_CGT) {
            IF_GT() { PUSH(REGISTER, IP); JUMP(); }
            vmbreak;
        }
        vmcase(OP_CLE) {
            IF_LE() { PUSH(REGISTER, IP); JUMP(); }
            vmbreak;
        }
        vmcase(OP_CGE) {
            IF_GE() { PUSH(REGISTER, IP); JUMP(); }
            vmbreak;
        }
    }
}