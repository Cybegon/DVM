#include <dvm_p.h>
#include "format-i.h"

#include "dvmdef_p.h"
#include "encode.h"
#include "opcodes.h"
#include "vcpu.h"

#include "auxiliary.h"

VOID format_i(DVM* state, duint32 instruction)
{
    vmswitch(DVM_GET_OPCODE(instruction)) {
        vmcase(OP_MOV) {
            R(DVM_GET_R0(instruction)) = DVM_GET_IMM16(instruction);
            vmbreak;
        }
        vmcase(OP_PUSH) { // here
            PUSH(REGISTER, DVM_GET_R0(instruction)); // here
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
        vmcase(OP_LD) {
            PUSH(REGISTER, IP += (IREGISTER)DVM_GET_IMM16(instruction));
            state->SVI[ 0x10 ](state);

            R(DVM_GET_R0(instruction)) = POP(REGISTER);
            vmbreak;
        }
        vmcase(OP_ST) {
            PUSH(REGISTER, IP += (IREGISTER)DVM_GET_IMM16(instruction));
            PUSH(REGISTER, R(DVM_GET_R0(instruction)));
            state->SVI[ 0x11 ](state);
            vmbreak;
        }
        vmcase(OP_HWI) {
            state->HVI[ DVM_GET_IMM16(instruction) & 0xFFu ](state);
            vmbreak;
        }
        vmcase(OP_SWI) {
            state->SVI[ DVM_GET_IMM16(instruction) & 0xFFu ](state);
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

        // !~F - Flow
        vmcase(OP_JMP) {
            IP = R(DVM_GET_R0(instruction)) + DVM_GET_IMM16(instruction);
            cpu_stateHandler(state, DVM_LOAD_PAGE);
            vmbreak;
        }
        vmcase(OP_CALL) {
            PUSH(REGISTER, R(DVM_GET_R0(instruction)));
            IP = R(DVM_GET_R0(instruction)) + DVM_GET_IMM16(instruction);
            cpu_stateHandler(state, DVM_LOAD_PAGE);
            vmbreak;
        }
        vmcase(OP_RET) {
            IP = POP(REGISTER);
            cpu_stateHandler(state, DVM_LOAD_PAGE);
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
        vmdefault: {
            dvm_getClass(state)->msgCallback(1, "INTERRUPT: illegal opcode \n");
            vmbreak;
        }
    }
}
