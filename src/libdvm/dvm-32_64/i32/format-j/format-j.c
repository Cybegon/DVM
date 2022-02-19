#include "format-j.h"

#include "dvmdef.h"
#include "encode.h"
#include "lopcodes.h"
#include "vcpu.h"

#define DVM_ENABLE_JUMP

#include "flags.h"
#include "auxiliary.h"

VOID DVM_FASTCALL format_j(DVM* state, duint32 instruction)
{
    vmswitch(DVM_GET_OPCODE(instruction)) {
        vmcase(OP_JMP) {
            IP = DVM_GET_IMM24(instruction);
            cpu_stateHandler(state, DVM_LOAD_PAGE);
            vmbreak;
        }
        vmcase(OP_JEQ) {
            IF_EQ() { JUMP(); }
            cpu_stateHandler(state, DVM_LOAD_PAGE);
            vmbreak;
        }
        vmcase(OP_JNE) {
            IF_NE() { JUMP(); }
            cpu_stateHandler(state, DVM_LOAD_PAGE);
            vmbreak;
        }
        vmcase(OP_JLT) {
            IF_LT() { JUMP(); }
            cpu_stateHandler(state, DVM_LOAD_PAGE);
            vmbreak;
        }
        vmcase(OP_JGT) {
            IF_GT() { JUMP(); }
            cpu_stateHandler(state, DVM_LOAD_PAGE);
            vmbreak;
        }
        vmcase(OP_JLE) {
            IF_LE() { JUMP(); }
            cpu_stateHandler(state, DVM_LOAD_PAGE);
            vmbreak;
        }
        vmcase(OP_JGE) {
            IF_GE() { JUMP(); }
            cpu_stateHandler(state, DVM_LOAD_PAGE);
            vmbreak;
        }
    }
}
