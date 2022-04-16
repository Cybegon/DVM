#include "dvm-32_64.h"

#include "vcpuclass.h"
#include "flags.h"

#include "format-i/format-i.h"
#include "format-j/format-j.h"
#include "format-c/format-c.h"

#define DVM_LONG_MODE   (7)
#define DVM_FORMAT_NOP  (0)

// 1 bit transfer control,
// 3 bits for format
#define DVM_GET_FORMAT(i)   ( (i & 0xF0000000u) >> 28u )

typedef union INSTRUCTION64 INSTRUCTION64;
typedef union INSTRUCTION32 INSTRUCTION32;

typedef INSTRUCTION64 INSTRUCTION;

union INSTRUCTION64 {
    duint64 i64;
    struct {
        duint32 i32H;
        duint32 i32L;
    };
};

union INSTRUCTION32 {
    duint32 v32;
    struct {
        duint16 v16H;
        duint16 v16L;
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

    INSTRUCTION*    in;
    INSTRUCTION     tmp;
//    in->v32H = 10;
//    in->v32L = 20;
//    dvmClass->msgCallback(1, "Test");
//    DVM_BSWAP64(in->v64);

    vmchunkexec() {
        if (cvtR2FR(FR)->vm_control & EF) {
            in = DVM_FETCH(state);          // set pointer
            tmp = *in;                      // copy to temporary instruction
            DVM_BSWAP64(tmp.i64);           // swap data
            in = &tmp;                      // set pointer to temporary instruction
        } else {
            in = DVM_FETCH(state);
        }

        vmdispatch(DVM_GET_FORMAT(in->i32H)) {
            vmcase(DVM_FORMAT_NOP) {
                // No operation
                vmbreak;
            }
            vmcase(DVM_FORMAT_I) {
                format_i(state, in->i32H);
                vmbreak;
            }
            vmcase(DVM_FORMAT_J) {
                format_j(state, in->i32H);
                vmbreak;
            }
            vmcase(DVM_FORMAT_C) {
                format_c(state, in->i32H);
                vmbreak;
            }
            vmcase(DVM_LONG_MODE) {
                R(3u) = in->i32L;
                dvmClass->msgCallback(1, "this is sparta!");
                vmsignal(SKIP);
            }
            vmdefault: {
                return DVM_TRANSFER_CONTROL;
            }
        }
        vmdispatch(DVM_GET_FORMAT(in->i32L)) {
            vmcase(DVM_FORMAT_NOP) {
                // No operation
                vmbreak;
            }
            vmcase(DVM_FORMAT_I) {
                format_i(state, in->i32L);
                vmbreak;
            }
            vmcase(DVM_FORMAT_J) {
                format_j(state, in->i32L);
                vmbreak;
            }
            vmcase(DVM_FORMAT_C) {
                format_c(state, in->i32L);
                vmbreak;
            }
            vmdefault: {
                return DVM_TRANSFER_CONTROL;
            }
        }
        vmslot(SKIP)
        IP += sizeof(INSTRUCTION);
    } /*afterexec {
        // global ip ++
        GIP += IP;
        IP  = 0;
    } */

vmslot(OUT)
    return DVM_LOAD_PAGE;
}

vm_code DVM_FASTCALL longMode(DVM* state, INSTRUCTION in)
{
//    vmdispatch()
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

////////////////////////////////////////////
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
////////////////////////////////////////////
