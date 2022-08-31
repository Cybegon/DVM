#include "format-c.h"

#include "dvmdef_p.h"
#include "lopcodes.h"
#include "vcpu.h"

#define DVM_ENABLE_JUMP24

#include "flags.h"
#include "auxiliary.h"

VOID DVM_FASTCALL format_c(DVM* state, duint32 instruction) {
    vmswitch(DVM_GET_OPCODE4(instruction)) {
        vmcase(OP_CALL) {
            PUSH(REGISTER, IP); JUMP24();
            vmbreak;
        }
        vmcase(OP_CEQ) {
            IF_EQ() { PUSH(REGISTER, IP); JUMP24(); }
            vmbreak;
        }
        vmcase(OP_CNE) {
            IF_NE() { PUSH(REGISTER, IP); JUMP24(); }
            vmbreak;
        }
        vmcase(OP_CLT) {
            IF_LT() { PUSH(REGISTER, IP); JUMP24(); }
            vmbreak;
        }
        vmcase(OP_CGT) {
            IF_GT() { PUSH(REGISTER, IP); JUMP24(); }
            vmbreak;
        }
        vmcase(OP_CLE) {
            IF_LE() { PUSH(REGISTER, IP); JUMP24(); }
            vmbreak;
        }
        vmcase(OP_CGE) {
            IF_GE() { PUSH(REGISTER, IP); JUMP24(); }
            vmbreak;
        }
        vmcase(OP_CLS) {
            IF_LS() { PUSH(REGISTER, IP); JUMP24(); }
            vmbreak;
        }
        vmcase(OP_CHS) {
            IF_HS() { PUSH(REGISTER, IP); JUMP24(); }
            vmbreak;
        }
        vmcase(OP_CLO) {
            IF_LO() { PUSH(REGISTER, IP); JUMP24(); }
            vmbreak;
        }
        vmcase(OP_CHI) {
            IF_HI() { PUSH(REGISTER, IP); JUMP24(); }
            vmbreak;
        }
        vmcase(OP_RET) {
            IP = POP(REGISTER);
            vmbreak;
        }
        vmcase(OP_INV) { // invoke
            state->SVI[ SVI_INVOKE ](state);
            vmbreak;
        }
    }
    cpu_stateHandler(state, DVM_LOAD_PAGE);
}
