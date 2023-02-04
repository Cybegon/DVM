#include "format-j.h"

#include "dvmstate.h"
#include "vcpu.h"
#include "dvmflags.h"

#define CAR_FORMAT_J
#include "opcodes.h"

#define CAR_32
#define DVM_ENABLE_JUMP24
#include "auxiliary.h"

VOID DVM_FASTCALL format_j32(DVM* state, duint32 instruction)
{
    vmswitch(GET_OPCODE4(instruction)) {
        vmcase(OP_JMP) {
            JUMP24();
            vmbreak;
        }
        vmcase(OP_JEQ) {
            IF_EQ() { JUMP24(); }
            vmbreak;
        }
        vmcase(OP_JNE) {
            IF_NE() { JUMP24(); }
            vmbreak;
        }
        vmcase(OP_JLT) {
            IF_LT() { JUMP24(); }
            vmbreak;
        }
        vmcase(OP_JGT) {
            IF_GT() { JUMP24(); }
            vmbreak;
        }
        vmcase(OP_JLE) {
            IF_LE() { JUMP24(); }
            vmbreak;
        }
        vmcase(OP_JGE) {
            IF_GE() { JUMP24(); }
            vmbreak;
        }
        vmcase(OP_JLS) {
            IF_LS() { JUMP24(); }
            vmbreak;
        }
        vmcase(OP_JHS) {
            IF_HS() { JUMP24(); }
            vmbreak;
        }
        vmcase(OP_JLO) {
            IF_LO() { JUMP24(); }
            vmbreak;
        }
        vmcase(OP_JHI) {
            IF_HI() { JUMP24(); }
            vmbreak;
        }
    }
    cpu_stateHandler(state, DVM_LOAD_PAGE);
}
