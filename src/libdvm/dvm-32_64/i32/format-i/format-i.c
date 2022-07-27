#include <dvm_p.h>
#include "format-i.h"

#include "dvmdef_p.h"
#include "encode.h"
#include "opcodes.h"
#include "vcpu.h"

#define DVM_ENABLE_JUMP16

#include "flags.h"
#include "auxiliary.h"

#define STUB return

VOID format_i(DVM* state, duint32 instruction)
{
    vmswitch(DVM_GET_OPCODE(instruction)) {
        vmcase(OP_MOV) {
            R(DVM_GET_R0(instruction)) = DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_PUSH) {
            PUSH(REGISTER, R(DVM_GET_R0(instruction)));
            vmbreak;
        }
        vmcase(OP_POP) {
            R(DVM_GET_R0(instruction)) = POP(REGISTER);
            vmbreak;
        }
        vmcase(OP_SWP) {
            DVM_BSWAP64(R(DVM_GET_R0(instruction)));
            vmbreak;
        }
        vmcase(OP_LD) { // make
            PUSH(REGISTER, IP += (IREGISTER)DVM_GET_IMM16(instruction));
            state->SVI[ 0x10 ](state);

            R(DVM_GET_R0(instruction)) = POP(REGISTER);
            vmbreak;
        }
        vmcase(OP_ST) { // make
            PUSH(REGISTER, IP += (IREGISTER)DVM_GET_IMM16(instruction));
            PUSH(REGISTER, R(DVM_GET_R0(instruction)));
            state->SVI[ 0x11 ](state);
            vmbreak;
        }
        vmcase(OP_BK) {
            state->SVI[ SVI_BREAKPOINT ](state);
            vmbreak;
        }
        vmcase(OP_HWI) {
            state->HVI[ DVM_GET_IMM8(instruction) ](state);
            vmbreak;
        }
        vmcase(OP_SWI) {
            state->SVI[ DVM_GET_IMM8(instruction) ](state);
            vmbreak;
        }
        vmcase(OP_ENTER) {
            PUSH(REGISTER, BP);
            BP = SP;
            SP += DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_LEAVE) {
            SP = BP;
            BP = POP(REGISTER);
            vmbreak;
        }
        vmcase(OP_INV) { // invoke
            state->SVI[ SVI_INVOKE ](state);
            vmbreak;
        }

        // !~IA - Integer arithmetic
        vmcase(OP_ADD) {
            R(DVM_GET_R0(instruction)) += DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_SUB) {
            R(DVM_GET_R0(instruction)) -= DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_INC) {
            ++R(DVM_GET_R0(instruction));
            vmbreak;
        }
        vmcase(OP_DEC) {
            --R(DVM_GET_R0(instruction));
            vmbreak;
        }
        vmcase(OP_MUL) {
            R(DVM_GET_R0(instruction)) *= DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_DIV) {
            R(DVM_GET_R0(instruction)) /= DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_IMUL) {
            R(DVM_GET_R0(instruction)) =
                    (( (IREGISTER)R(DVM_GET_R0(instruction)) ) * ( (IREGISTER)DVM_GET_IMM16(instruction) ));
            vmbreak;
        }
        vmcase(OP_IDIV) {
            R(DVM_GET_R0(instruction)) =
                    (( (IREGISTER)R(DVM_GET_R0(instruction)) ) / ( (IREGISTER)DVM_GET_IMM16(instruction) ));
            vmbreak;
        }
        vmcase(OP_MOD) {
            R(DVM_GET_R0(instruction)) %= DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_SHL) {
            R(DVM_GET_R0(instruction)) <<= DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_SHR) {
            R(DVM_GET_R0(instruction)) >>= DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_ROL) {
            R(DVM_GET_R0(instruction)) =
                    ( R(DVM_GET_R0(instruction)) << DVM_GET_IMM16(instruction) ) | // or
                    ( R(DVM_GET_R0(instruction)) >> ( C4146_FIX(-,DVM_GET_IMM16(instruction)) & 63u ) );
            vmbreak;
        }
        vmcase(OP_ROR) {
            R(DVM_GET_R0(instruction)) =
                    ( R(DVM_GET_R0(instruction)) >> DVM_GET_IMM16(instruction) ) | // or
                    ( R(DVM_GET_R0(instruction)) << ( C4146_FIX(-,DVM_GET_IMM16(instruction)) & 63u ) );
            vmbreak;
        }

        // !~L - Logic
        vmcase(OP_AND) {
            R(DVM_GET_R0(instruction)) &= DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_NAND) {
            R(DVM_GET_R0(instruction)) &= ~DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_OR) {
            R(DVM_GET_R0(instruction)) |= DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_NOR) {
            R(DVM_GET_R0(instruction)) |= ~DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_XOR) {
            R(DVM_GET_R0(instruction)) ^= DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_NOT) {
            R(DVM_GET_R0(instruction)) = ~R(DVM_GET_R0(instruction));
            vmbreak;
        }
        vmcase(OP_NEG) {
            R(DVM_GET_R0(instruction)) = C4146_FIX(-, R(DVM_GET_R0(instruction)));
            vmbreak;
        }
        vmdefault: {
            vmsignal(FLOW);
            vmbreak;
        }
    }
    STUB;

vmslot(FLOW)
    vmswitch(DVM_GET_OPCODE(instruction)) {
        // !~F - Flow
        vmcase(OP_JMP) {
            IP = CP + DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_JEQ) {
            IF_EQ() { JUMP16(); }
            vmbreak;
        }
        vmcase(OP_JNE) {
            IF_NE() { JUMP16(); }
            vmbreak;
        }
        vmcase(OP_JLT) {
            IF_LT() { JUMP16(); }
            vmbreak;
        }
        vmcase(OP_JGT) {
            IF_GT() { JUMP16(); }
            vmbreak;
        }
        vmcase(OP_JLE) {
            IF_LE() { JUMP16(); }
            vmbreak;
        }
        vmcase(OP_JGE) {
            IF_GE() { JUMP16(); }
            vmbreak;
        }
        vmcase(OP_JLS) {
            IF_LS() { JUMP16(); }
            vmbreak;
        }
        vmcase(OP_JHS) {
            IF_HS() { JUMP16(); }
            vmbreak;
        }
        vmcase(OP_JLO) {
            IF_LO() { JUMP16(); }
            vmbreak;
        }
        vmcase(OP_JHI) {
            IF_HI() { JUMP16(); }
            vmbreak;
        }
        vmcase(OP_CALL) {
            PUSH(REGISTER, IP); JUMP16();
            vmbreak;
        }
        vmcase(OP_CEQ) {
            IF_EQ() { PUSH(REGISTER, IP); JUMP16(); }
            vmbreak;
        }
        vmcase(OP_CNE) {
            IF_NE() { PUSH(REGISTER, IP); JUMP16(); }
            vmbreak;
        }
        vmcase(OP_CLT) {
            IF_LT() { PUSH(REGISTER, IP); JUMP16(); }
            vmbreak;
        }
        vmcase(OP_CGT) {
            IF_GT() { PUSH(REGISTER, IP); JUMP16(); }
            vmbreak;
        }
        vmcase(OP_CLE) {
            IF_LE() { PUSH(REGISTER, IP); JUMP16(); }
            vmbreak;
        }
        vmcase(OP_CGE) {
            IF_GE() { PUSH(REGISTER, IP); JUMP16(); }
            vmbreak;
        }
        vmcase(OP_CLS) {
            IF_LS() { PUSH(REGISTER, IP); JUMP16(); }
            vmbreak;
        }
        vmcase(OP_CHS) {
            IF_HS() { PUSH(REGISTER, IP); JUMP16(); }
            vmbreak;
        }
        vmcase(OP_CLO) {
            IF_LO() { PUSH(REGISTER, IP); JUMP16(); }
            vmbreak;
        }
        vmcase(OP_CHI) {
            IF_HI() { PUSH(REGISTER, IP); JUMP16(); }
            vmbreak;
        }
        vmcase(OP_RET) {
            IP = POP(REGISTER);
            vmbreak;
        }
        vmdefault: {
            state->SVI[ SVI_ILLEGAL_OPCODE ](state);
            vmbreak;
        }
    }
    cpu_stateHandler(state, DVM_LOAD_PAGE);
}
