#include "format-j.h"

#include "dvmdef.h"
#include "encode.h"
#include "opcode.h"
#include "vcpu.h"

VOID DVM_FASTCALL format_j(DVM* state, duint32 instruction)
{
    vmswitch(DVM_GET_OPCODE(instruction)) {
        vmcase(OP_JMP) {

        }
    }
}
