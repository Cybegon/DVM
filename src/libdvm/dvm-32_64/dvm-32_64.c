#include "dvm-32_64.h"

#include "vcpuclass.h"
#include "dvm-32_64/format-i/encode.h"

#include "format-i/format-i.h"

#define DVM_LONG_MODE   (7)
#define DVM_FORMAT_NOP  (0)

// 1 bit transfer control,
// 3 bits for format
#define DVM_GET_FORMAT(i)   ( (i & 0xF0000000u) >> 28u )

typedef union INSTRUCTION* INSTRUCTION;

union INSTRUCTION {
    duint64 value64;
    struct {
        duint32 value32H;
        duint32 value32L;
    };
};

extern const VCPU d32_64;

const VCPU* dvm_32_64_getVCPU(DVM* state)
{
    return &d32_64;
}

vm_code DVM_CALLBACK load(DVM* state)
{
    state->dvmClass->msgCallback( 0, "LOAD\n" );

    return 0;
}

vm_code DVM_FASTCALL longMode(DVM* state, INSTRUCTION in);
vm_code DVM_CALLBACK entry(DVM* state)
{
    DVM_CLASS* dvmClass = dvm_getClass(state);

    INSTRUCTION in;
    vmpagexec(dvmClass) {
        in = DVM_FETCH(state);
        vmdispatch(DVM_GET_FORMAT(in->value32H)) {
            vmcase(DVM_FORMAT_NOP) {
                // No operation
                vmbreak;
            }
            vmcase(DVM_FORMAT_I) {
                format_i(state, in->value32H);
//                // This is maddness!
//                // no this is COSTYL!!!
//                // for better performance with love :3
//                vmswitch() {
//                    vmcase(DVM_TRANSFER_CONTROL) {
//                        return DVM_TRANSFER_CONTROL;
//                    }
//                    vmcase(DVM_LOAD_PAGE) {
//                        return DVM_LOAD_PAGE;
//                    }
//                    vmdefault:
//                        vmbreak;
//                }
//                vmbreak;
            }
            vmcase(DVM_LONG_MODE) {
                longMode(state, in);
                continue;
            }
            vmdefault: {
                return DVM_TRANSFER_CONTROL;
            }
        }

        IP += sizeof(INSTRUCTION);
    } afterexec {
        // global ip ++
        GIP += IP;
        IP  = 0;
    }

    return DVM_LOAD_PAGE;
}

vm_code DVM_FASTCALL longMode(DVM* state, INSTRUCTION in)
{

    return DVM_SUCCESS;
}

vm_code DVM_CALLBACK unload(DVM* state)
{
    dvm_getClass(state)->msgCallback(0, "UNLOAD\n");

    return 0;
}

const VCPU d32_64 = {
        .guid = {
                .data1 = 0xbbac154c,
                .data2 = 0x308b,
                .data3 = 0x455d,
                .data4 = 0xb28c,
                .node = {
                    .node_h = 0x541a,
                    .node_l = 0x5222866b
                }
        },
        .vendorID = "DVM-32_64",
        .vcpuOpcodeBitType = BASIC_SET,
        .main   = { load, entry, unload },
        .debug  = { load, entry, unload },
        .jit    = {NULL, NULL, NULL},
};