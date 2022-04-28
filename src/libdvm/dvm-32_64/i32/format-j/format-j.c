#include "format-j.h"

#include "dvmdef_p.h"
#include "encode.h"
#include "lopcodes.h"
#include "vcpu.h"

#define DVM_ENABLE_JUMP24

#include "flags.h"
#include "auxiliary.h"

VOID DVM_FASTCALL format_j(DVM* state, duint32 instruction)
{
    vmswitch(DVM_GET_OPCODE(instruction)) {
        vmcase(OP_JMP) {
            IP = CP + DVM_GET_IMM24(instruction);
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
