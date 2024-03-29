#include "format-c.h"

#include "dvmstate.h"
#include "vcpu.h"
#include "dvmflags.h"

#define CAR_64
#define CAR_FORMAT_C
#include "opcodes.h"

#define DVM_ENABLE_JUMP48
#define DVM_ENABLE_RJUMP48
#include "auxiliary.h"

VOID DVM_FASTCALL format_c64(DVM* state, duint64 instruction)
{
    vmswitch(GET_OPCODE8(instruction)) {
        //~! Call
        vmcase(OP_CALL) {
            PUSH(REGISTER, IP); JUMP48();
            vmbreak;
        }
        vmcase(OP_CEQ) {
            IF_EQ() { PUSH(REGISTER, IP); JUMP48(); }
            vmbreak;
        }
        vmcase(OP_CNE) {
            IF_NE() { PUSH(REGISTER, IP); JUMP48(); }
            vmbreak;
        }
        vmcase(OP_CLT) {
            IF_LT() { PUSH(REGISTER, IP); JUMP48(); }
            vmbreak;
        }
        vmcase(OP_CGT) {
            IF_GT() { PUSH(REGISTER, IP); JUMP48(); }
            vmbreak;
        }
        vmcase(OP_CLE) {
            IF_LE() { PUSH(REGISTER, IP); JUMP48(); }
            vmbreak;
        }
        vmcase(OP_CGE) {
            IF_GE() { PUSH(REGISTER, IP); JUMP48(); }
            vmbreak;
        }
        vmcase(OP_CLS) {
            IF_LS() { PUSH(REGISTER, IP); JUMP48(); }
            vmbreak;
        }
        vmcase(OP_CHS) {
            IF_HS() { PUSH(REGISTER, IP); JUMP48(); }
            vmbreak;
        }
        vmcase(OP_CLO) {
            IF_LO() { PUSH(REGISTER, IP); JUMP48(); }
            vmbreak;
        }
        vmcase(OP_CHI) {
            IF_HI() { PUSH(REGISTER, IP); JUMP48(); }
            vmbreak;
        }

        //~! Relative call
        vmcase(OP_RCALL) {
            PUSH(REGISTER, IP); RJUMP48();
            vmbreak;
        }
        vmcase(OP_RCEQ) {
            IF_EQ() { PUSH(REGISTER, IP); RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RCNE) {
            IF_NE() { PUSH(REGISTER, IP); RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RCLT) {
            IF_LT() { PUSH(REGISTER, IP); RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RCGT) {
            IF_GT() { PUSH(REGISTER, IP); RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RCLE) {
            IF_LE() { PUSH(REGISTER, IP); RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RCGE) {
            IF_GE() { PUSH(REGISTER, IP); RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RCLS) {
            IF_LS() { PUSH(REGISTER, IP); RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RCHS) {
            IF_HS() { PUSH(REGISTER, IP); RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RCLO) {
            IF_LO() { PUSH(REGISTER, IP); RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RCHI) {
            IF_HI() { PUSH(REGISTER, IP); RJUMP48(); }
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
