#include "format-j.h"

#include "dvmstate.h"
#include "vcpu.h"
#include "dvmflags.h"

#define CAR_FORMAT_J
#include "opcodes.h"

#define CAR_32
#define DVM_ENABLE_RJUMP24
#include "auxiliary.h"

VOID DVM_FASTCALL format_j32(DVM* state, duint32 instruction)
{
    vmswitch(GET_OPCODE4(instruction)) {
        vmcase(OP_JMP) {
            RJUMP24();
            vmbreak;
        }
        vmcase(OP_JEQ) {
            IF_EQ() { RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_JNE) {
            IF_NE() { RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_JLT) {
            IF_LT() { RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_JGT) {
            IF_GT() { RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_JLE) {
            IF_LE() { RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_JGE) {
            IF_GE() { RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_JLS) {
            IF_LS() { RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_JHS) {
            IF_HS() { RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_JLO) {
            IF_LO() { RJUMP24(); }
            vmbreak;
        }
        vmcase(OP_JHI) {
            IF_HI() { RJUMP24(); }
            vmbreak;
        }
    }
    cpu_stateHandler(state, DVM_LOAD_PAGE);
}
