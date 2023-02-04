#include "format-i.h"

#include "dvmstate.h"
#include "dvmdef.h"
#include "vcpu.h"
#include "dvmflags.h"

#define CAR_FORMAT_I
#include "opcodes.h"

#define CAR_64
#define DVM_ENABLE_JUMP32
#include "auxiliary.h"

VOID DVM_FASTCALL format_i64(DVM* state, duint64 instruction)
{
    vmdispatch(GET_OPCODE8(instruction)) {
        vmcase(OP_MOV) {
            R(GET_R0(instruction)) = GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_PUSH) {
            PUSH(REGISTER, GET_IMM32(instruction));
            vmbreak;
        }
        vmcase(OP_POP) {
            R(GET_R0(instruction)) = POP(REGISTER);
            vmbreak;
        }
        vmcase(OP_SWP) {
            DVM_BSWAP64(R(GET_R0(instruction)));
            vmbreak;
        }
        vmcase(OP_LD) { // make
            PUSH(REGISTER, DP += (IREGISTER)GET_IMM32(instruction));
            state->SVI[ 0x10 ](state);

            R(GET_R0(instruction)) = POP(REGISTER);
            vmbreak;
        }
        vmcase(OP_ST) { // make
            PUSH(REGISTER, DP += (IREGISTER)GET_IMM32(instruction));
            PUSH(REGISTER, R(GET_R0(instruction)));
            state->SVI[ 0x11 ](state);
            vmbreak;
        }
        vmcase(OP_BK) {
            state->SVI[ SVI_BREAKPOINT ](state);
            vmbreak;
        }
        vmcase(OP_HWI) {
            state->HVI[ GET_IMM8(instruction) ](state);
            vmbreak;
        }
        vmcase(OP_SWI) {
            state->SVI[ GET_IMM8(instruction) ](state);
            vmbreak;
        }
        vmcase(OP_ENTER) {
            PUSH(REGISTER, BP);
            BP = SP;
            SP += GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_LEAVE) {
            SP = BP;
            BP = POP(REGISTER);
            vmbreak;
        }

        // !~IA - Integer arithmetic
        vmcase(OP_ADD) {
            R(GET_R0(instruction)) += GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_SUB) {
            R(GET_R0(instruction)) -= GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_INC) {
            ++R(GET_R0(instruction));
            vmbreak;
        }
        vmcase(OP_DEC) {
            --R(GET_R0(instruction));
            vmbreak;
        }
        vmcase(OP_MUL) {
            R(GET_R0(instruction)) *= GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_DIV) {
            R(GET_R0(instruction)) /= GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_IMUL) {
            R(GET_R0(instruction)) =
                    (( (IREGISTER)R(GET_R0(instruction)) ) * ( (IREGISTER)GET_IMM32(instruction) ));
            vmbreak;
        }
        vmcase(OP_IDIV) {
            R(GET_R0(instruction)) =
                    (( (IREGISTER)R(GET_R0(instruction)) ) / ( (IREGISTER)GET_IMM32(instruction) ));
            vmbreak;
        }
        vmcase(OP_MOD) {
            R(GET_R0(instruction)) %= GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_SHL) {
            R(GET_R0(instruction)) <<= GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_SHR) {
            R(GET_R0(instruction)) >>= GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_ROL) {
            R(GET_R0(instruction)) =
                    ( R(GET_R0(instruction)) << GET_IMM32(instruction) ) | // or
                    ( R(GET_R0(instruction)) >> ( C4146_FIX(-,GET_IMM32(instruction)) & 63u ) );
            vmbreak;
        }
        vmcase(OP_ROR) {
            R(GET_R0(instruction)) =
                    ( R(GET_R0(instruction)) >> GET_IMM32(instruction) ) | // or
                    ( R(GET_R0(instruction)) << ( C4146_FIX(-,GET_IMM32(instruction)) & 63u ) );
            vmbreak;
        }

        // !~L - Logic
        vmcase(OP_AND) {
            R(GET_R0(instruction)) &= GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_NAND) {
            R(GET_R0(instruction)) &= ~GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_OR) {
            R(GET_R0(instruction)) |= GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_NOR) {
            R(GET_R0(instruction)) |= ~GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_XOR) {
            R(GET_R0(instruction)) ^= GET_IMM32(instruction);
            vmbreak;
        }
        vmcase(OP_NOT) {
            R(GET_R0(instruction)) = ~R(GET_R0(instruction));
            vmbreak;
        }
        vmcase(OP_NEG) {
            R(GET_R0(instruction)) = C4146_FIX(-, R(GET_R0(instruction)));
            vmbreak;
        }
        vmcase(OP_CMP) {
            cvtR2FR(FR)->vm_status &= ~( EQ | LO | LT ); // clear flags
            cvtR2FR(FR)->vm_status |=
                    (((REGISTER)R(GET_R0(instruction)) < (REGISTER)GET_IMM32(instruction)) ? LO : 0) |
                    (((REGISTER)R(GET_R0(instruction)) == (REGISTER)GET_IMM32(instruction)) ? EQ : 0);
            vmbreak;
        }
        vmcase(OP_ICMP) {
            cvtR2FR(FR)->vm_status &= ~( EQ | LO | LT ); // clear flags
            cvtR2FR(FR)->vm_status |=
                    (((IREGISTER)R(GET_R0(instruction)) < (IREGISTER)GET_IMM32(instruction)) ? LT : 0) |
                    (((IREGISTER)R(GET_R0(instruction)) == (IREGISTER)GET_IMM32(instruction)) ? EQ : 0);
            vmbreak;
        }
        vmdefault: {
            vmsignal(FLOW);
            vmbreak;
        }
    }
    STUB;

vmslot(FLOW)
    vmswitch(GET_OPCODE8(instruction)) {
        // !~F - Flow
        vmcase(OP_JMP) {
            JUMP32();
            vmbreak;
        }
        vmcase(OP_JEQ) {
            IF_EQ() { JUMP32(); }
            vmbreak;
        }
        vmcase(OP_JNE) {
            IF_NE() { JUMP32(); }
            vmbreak;
        }
        vmcase(OP_JLT) {
            IF_LT() { JUMP32(); }
            vmbreak;
        }
        vmcase(OP_JGT) {
            IF_GT() { JUMP32(); }
            vmbreak;
        }
        vmcase(OP_JLE) {
            IF_LE() { JUMP32(); }
            vmbreak;
        }
        vmcase(OP_JGE) {
            IF_GE() { JUMP32(); }
            vmbreak;
        }
        vmcase(OP_JLS) {
            IF_LS() { JUMP32(); }
            vmbreak;
        }
        vmcase(OP_JHS) {
            IF_HS() { JUMP32(); }
            vmbreak;
        }
        vmcase(OP_JLO) {
            IF_LO() { JUMP32(); }
            vmbreak;
        }
        vmcase(OP_JHI) {
            IF_HI() { JUMP32(); }
            vmbreak;
        }
        vmcase(OP_CALL) {
            PUSH(REGISTER, IP); JUMP32();
            vmbreak;
        }
        vmcase(OP_CEQ) {
            IF_EQ() { PUSH(REGISTER, IP); JUMP32(); }
            vmbreak;
        }
        vmcase(OP_CNE) {
            IF_NE() { PUSH(REGISTER, IP); JUMP32(); }
            vmbreak;
        }
        vmcase(OP_CLT) {
            IF_LT() { PUSH(REGISTER, IP); JUMP32(); }
            vmbreak;
        }
        vmcase(OP_CGT) {
            IF_GT() { PUSH(REGISTER, IP); JUMP32(); }
            vmbreak;
        }
        vmcase(OP_CLE) {
            IF_LE() { PUSH(REGISTER, IP); JUMP32(); }
            vmbreak;
        }
        vmcase(OP_CGE) {
            IF_GE() { PUSH(REGISTER, IP); JUMP32(); }
            vmbreak;
        }
        vmcase(OP_CLS) {
            IF_LS() { PUSH(REGISTER, IP); JUMP32(); }
            vmbreak;
        }
        vmcase(OP_CHS) {
            IF_HS() { PUSH(REGISTER, IP); JUMP32(); }
            vmbreak;
        }
        vmcase(OP_CLO) {
            IF_LO() { PUSH(REGISTER, IP); JUMP32(); }
            vmbreak;
        }
        vmcase(OP_CHI) {
            IF_HI() { PUSH(REGISTER, IP); JUMP32(); }
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
