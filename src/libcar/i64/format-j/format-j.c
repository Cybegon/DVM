#include "format-j.h"

#include "dvmstate.h"
#include "vcpu.h"
#include "dvmflags.h"

#define CAR_64
#define CAR_FORMAT_C
#include "opcodes.h"

#define DVM_ENABLE_JUMP48
#define DVM_ENABLE_RJUMP48
#include "auxiliary.h"

VOID DVM_FASTCALL format_j64(DVM* state, duint64 instruction)
{
    vmswitch(GET_OPCODE8(instruction)) {
        vmcase(OP_JMP) {
            JUMP48();
            vmbreak;
        }
        vmcase(OP_JEQ) {
            IF_EQ() { JUMP48(); }
            vmbreak;
        }
        vmcase(OP_JNE) {
            IF_NE() { JUMP48(); }
            vmbreak;
        }
        vmcase(OP_JLT) {
            IF_LT() { JUMP48(); }
            vmbreak;
        }
        vmcase(OP_JGT) {
            IF_GT() { JUMP48(); }
            vmbreak;
        }
        vmcase(OP_JLE) {
            IF_LE() { JUMP48(); }
            vmbreak;
        }
        vmcase(OP_JGE) {
            IF_GE() { JUMP48(); }
            vmbreak;
        }
        vmcase(OP_JLS) {
            IF_LS() { JUMP48(); }
            vmbreak;
        }
        vmcase(OP_JHS) {
            IF_HS() { JUMP48(); }
            vmbreak;
        }
        vmcase(OP_JLO) {
            IF_LO() { JUMP48(); }
            vmbreak;
        }
        vmcase(OP_JHI) {
            IF_HI() { JUMP48(); }
            vmbreak;
        }

        //~! Relative jump
        vmcase(OP_RJMP) {
            RJUMP48();
            vmbreak;
        }
        vmcase(OP_RJEQ) {
            IF_EQ() { RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RJNE) {
            IF_NE() { RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RJLT) {
            IF_LT() { RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RJGT) {
            IF_GT() { RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RJLE) {
            IF_LE() { RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RJGE) {
            IF_GE() { RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RJLS) {
            IF_LS() { RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RJHS) {
            IF_HS() { RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RJLO) {
            IF_LO() { RJUMP48(); }
            vmbreak;
        }
        vmcase(OP_RJHI) {
            IF_HI() { RJUMP48(); }
            vmbreak;
        }
    }
    cpu_stateHandler(state, DVM_LOAD_PAGE);
}
