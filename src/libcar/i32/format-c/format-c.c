#include "format-c.h"

#include "dvmstate.h"
#include "vcpu.h"
#include "dvmflags.h"

#define CAR_FORMAT_C
#include "opcodes.h"

#define CAR_32
#define DVM_ENABLE_RJUMP24
#include "auxiliary.h"

VOID DVM_FASTCALL format_c32(DVM* state, duint32 instruction) {
    vmswitch(GET_OPCODE4(instruction)) {
        vmcase(OP_CALL) {
            PUSH(REGISTER, IP); RJUMP24();
            vmbreak;
        }
        vmcase(OP_CEQ) {
            IF_EQ() { PUSH(REGISTER, IP); RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_CNE) {
            IF_NE() { PUSH(REGISTER, IP); RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_CLT) {
            IF_LT() { PUSH(REGISTER, IP); RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_CGT) {
            IF_GT() { PUSH(REGISTER, IP); RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_CLE) {
            IF_LE() { PUSH(REGISTER, IP); RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_CGE) {
            IF_GE() { PUSH(REGISTER, IP); RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_CLS) {
            IF_LS() { PUSH(REGISTER, IP); RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_CHS) {
            IF_HS() { PUSH(REGISTER, IP); RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_CLO) {
            IF_LO() { PUSH(REGISTER, IP); RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_CHI) {
            IF_HI() { PUSH(REGISTER, IP); RJUMP24(); }
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
