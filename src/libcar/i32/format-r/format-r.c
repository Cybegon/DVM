

#include "dvm_state.h"
#include "format-r.h"

#include "dvmdef.h"
#include "opcodes.h"
#include "vcpu.h"

#define DVM_ENABLE_JUMPR

#include "flags.h"
#include "auxiliary.h"

// rename later
#define IF_REG(inst, sign, typeCast)                    \
            if (inst & 0x00000001) {                    \
            R(GET_R0(inst)) =                       \
                (((typeCast)R(GET_R1(inst))         \
                sign (typeCast)R(GET_R2(inst)))     \
                sign (typeCast)R(GET_R3(inst)));    \
            }                                           \
            else {                                      \
                R(GET_R0(inst)) =                   \
                ((typeCast)R(GET_R1(inst))          \
                sign (typeCast)R(GET_R2(inst)));    \
            }

VOID DVM_FASTCALL format_r(DVM* state, duint32 instruction)
{
    vmswitch(GET_OPCODE(instruction))
    {
        vmcase(OP_MOV) {
            R(GET_R0(instruction)) = R(GET_R1(instruction));
            vmbreak;
        }
        vmcase(OP_PUSH) { // make reglist
            PUSH(REGISTER, R(GET_R0(instruction)));
            vmbreak;
        }
        vmcase(OP_POP) { // make reglist
            R(GET_R0(instruction)) = POP(REGISTER);
            vmbreak;
        }
        vmcase(OP_SWP) { // make reglist
            DVM_BSWAP64(R(GET_R0(instruction)));
            vmbreak;
        }
        vmcase(OP_ENTER) {
            PUSH(REGISTER, BP);
            BP = SP;
            SP += R(GET_R0(instruction));
            vmbreak;
        }

        // !~IA - Integer arithmetic
        vmcase(OP_ADD) {
            IF_REG(instruction, +, REGISTER)
            vmbreak;
        }
        vmcase(OP_SUB) {
            IF_REG(instruction, -, REGISTER)
            vmbreak;
        }
        vmcase(OP_INC) { // make reglist
            ++R(GET_R0(instruction));
            vmbreak;
        }
        vmcase(OP_DEC) { // make reglist
            --R(GET_R0(instruction));
            vmbreak;
        }
        vmcase(OP_MUL) {
            IF_REG(instruction, *, REGISTER)
            vmbreak;
        }
        vmcase(OP_DIV) {
            IF_REG(instruction, /, REGISTER)
            vmbreak;
        }
        vmcase(OP_IMUL) {
            IF_REG(instruction, *, IREGISTER)
            vmbreak;
        }
        vmcase(OP_IDIV) {
            IF_REG(instruction, /, IREGISTER)
            vmbreak;
        }
        vmcase(OP_MOD) {
            R(GET_R0(instruction)) = R(GET_R1(instruction)) % R(GET_R2(instruction));
            vmbreak;
        }
        vmcase(OP_SHL) {
            R(GET_R0(instruction)) = R(GET_R1(instruction)) << R(GET_R2(instruction));
            vmbreak;
        }
        vmcase(OP_SHR) {
            R(GET_R0(instruction)) = R(GET_R1(instruction)) >> R(GET_R2(instruction));
            vmbreak;
        }
        vmcase(OP_ROL) {
            R(GET_R0(instruction)) =
                    ( R(GET_R1(instruction)) << R(GET_R2(instruction)) ) | // or
                    ( R(GET_R1(instruction)) >> ( C4146_FIX(-, R(GET_R2(instruction))) & 63u ) );
            vmbreak;
        }
        vmcase(OP_ROR) {
            R(GET_R0(instruction)) =
                    ( R(GET_R1(instruction)) >> R(GET_R2(instruction)) ) | // or
                    ( R(GET_R1(instruction)) << ( C4146_FIX(-, R(GET_R2(instruction))) & 63u ) );
            vmbreak;
        }

        // !~L - Logic
        vmcase(OP_AND) {
            R(GET_R0(instruction)) = R(GET_R1(instruction)) & R(GET_R2(instruction));
            vmbreak;
        }
        vmcase(OP_NAND) {
            R(GET_R0(instruction)) = R(GET_R1(instruction)) & ~R(GET_R2(instruction));
            vmbreak;
        }
        vmcase(OP_OR) {
            R(GET_R0(instruction)) = R(GET_R1(instruction)) | R(GET_R2(instruction));
            vmbreak;
        }
        vmcase(OP_NOR) {
            R(GET_R0(instruction)) = R(GET_R1(instruction)) | ~R(GET_R2(instruction));
            vmbreak;
        }
        vmcase(OP_XOR) {
            R(GET_R0(instruction)) = R(GET_R1(instruction)) ^ R(GET_R2(instruction));
            vmbreak;
        }
        vmcase(OP_NOT) { // make reglist
            R(GET_R0(instruction)) = ~R(GET_R0(instruction));
            vmbreak;
        }
        vmcase(OP_NEG) { // make reglist
            R(GET_R0(instruction)) = C4146_FIX(-, R(GET_R0(instruction)));
            vmbreak;
        }
        vmcase(OP_CMP) {
            cvtR2FR(FR)->vm_status &= ~( EQ | LO | LT ); // clear flags
            cvtR2FR(FR)->vm_status |=
                    (((REGISTER)R(GET_R0(instruction)) < (REGISTER)R(GET_R1(instruction))) ? LO : 0) |
                    (((REGISTER)R(GET_R0(instruction)) == (REGISTER)R(GET_R1(instruction))) ? EQ : 0);
            vmbreak;
        }
        vmcase(OP_ICMP) {
            cvtR2FR(FR)->vm_status &= ~( EQ | LO | LT ); // clear flags
            cvtR2FR(FR)->vm_status |=
                    (((IREGISTER)R(GET_R0(instruction)) < (IREGISTER)R(GET_R1(instruction))) ? LT : 0) |
                    (((IREGISTER)R(GET_R0(instruction)) == (IREGISTER)R(GET_R1(instruction))) ? EQ : 0);
            vmbreak;
        }
        vmdefault: {
            vmsignal(FLOW);
            vmbreak;
        }
    }
    STUB;

vmslot(FLOW)
    vmswitch(GET_OPCODE(instruction)) {
        // !~F - Flow
        vmcase(OP_JMP) {
            JUMPR(R(GET_R0(instruction)));
            vmbreak;
        }
        vmcase(OP_JEQ) {
            IF_EQ() { JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_JNE) {
            IF_NE() { JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_JLT) {
            IF_LT() { JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_JGT) {
            IF_GT() { JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_JLE) {
            IF_LE() { JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_JGE) {
            IF_GE() { JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_JLS) {
            IF_LS() { JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_JHS) {
            IF_HS() { JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_JLO) {
            IF_LO() { JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_JHI) {
            IF_HI() { JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_CALL) {
            PUSH(REGISTER, IP); JUMPR(R(GET_R0(instruction)));
            vmbreak;
        }
        vmcase(OP_CEQ) {
            IF_EQ() { PUSH(REGISTER, IP); JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_CNE) {
            IF_NE() { PUSH(REGISTER, IP); JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_CLT) {
            IF_LT() { PUSH(REGISTER, IP); JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_CGT) {
            IF_GT() { PUSH(REGISTER, IP); JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_CLE) {
            IF_LE() { PUSH(REGISTER, IP); JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_CGE) {
            IF_GE() { PUSH(REGISTER, IP); JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_CLS) {
            IF_LS() { PUSH(REGISTER, IP); JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_CHS) {
            IF_HS() { PUSH(REGISTER, IP); JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_CLO) {
            IF_LO() { PUSH(REGISTER, IP); JUMPR(R(GET_R0(instruction))); }
            vmbreak;
        }
        vmcase(OP_CHI) {
            IF_HI() { PUSH(REGISTER, IP); JUMPR(R(GET_R0(instruction))); }
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