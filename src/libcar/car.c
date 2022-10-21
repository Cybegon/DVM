#include "libcar/car.h"

#include "dvm_state.h"
#include "flags.h"

#include "format-i/format-i.h"
#include "format-r/format-r.h"
#include "format-j/format-j.h"
#include "format-c/format-c.h"

#define CAR_LONG_MODE   (7)
#define CAR_FORMAT_NOP  (0)

// 1 bit transfer control,
// 3 bits for format
#define GET_FORMAT(i)   ( (i & 0xF0000000u) >> 28u )

extern const VCPU CAR;

const VCPU* car_getVCPU(DVM* state)
{
    return &CAR;
}

vm_code DVM_CALLBACK load(DVM* state)
{

    return DVM_SUCCESS;
}

vm_code DVM_FASTCALL step(DVM* state, INSTRUCTION* in);
vm_code DVM_CALLBACK entry(DVM* state)
{
    DVM_CLASS* dvmClass = dvm_getClass(state);

    INSTRUCTION*    in;
    INSTRUCTION     tmp;

    vmchunkexec() {
        in = DVM_FETCH(state);
        if (cvtR2FR(FR)->vm_control & EF) {
            tmp = *in;                      // copy to temporary instruction
            DVM_BSWAP64(tmp.i64);           // swap data
            in = &tmp;                      // set pointer to temporary instruction
        }

        step(state, in);
    }

vmslot(OUT)
    return DVM_LOAD_PAGE;
}

vm_code DVM_FASTCALL longMode(DVM* state, INSTRUCTION* in)
{
//    vmdispatch()
    return DVM_SUCCESS;
}

vm_code DVM_FASTCALL step(DVM* state, INSTRUCTION* in)
{
    vmdispatch(GET_FORMAT(in->i32L)) {
        vmcase(CAR_FORMAT_NOP) {
            // No operation
            vmbreak;
        }
        vmcase(CAR_FORMAT_I) {
            format_i(state, in->i32L);
            vmbreak;
        }
        vmcase(CAR_FORMAT_R) {
            format_r(state, in->i32L);
            vmbreak;
        }
        vmcase(CAR_FORMAT_J) {
            format_j(state, in->i32L);
            vmbreak;
        }
        vmcase(CAR_FORMAT_C) {
            format_c(state, in->i32L);
            vmbreak;
        }
        vmcase(CAR_LONG_MODE) {
            R(3u) = in->i32H;
            vmsignal(SKIP);
        }
        vmdefault: {
            return DVM_FAIL;
        }
    }
    vmdispatch(GET_FORMAT(in->i32H)) {
        vmcase(CAR_FORMAT_NOP) {
            // No operation
            vmbreak;
        }
        vmcase(CAR_FORMAT_I) {
            format_i(state, in->i32H);
            vmbreak;
        }
        vmcase(CAR_FORMAT_R) {
            format_r(state, in->i32H);
            vmbreak;
        }
        vmcase(CAR_FORMAT_J) {
            format_j(state, in->i32H);
            vmbreak;
        }
        vmcase(CAR_FORMAT_C) {
            format_c(state, in->i32H);
            vmbreak;
        }
        vmdefault: {
            return DVM_FAIL;
        }
    }
    vmslot(SKIP)
    IP += sizeof(INSTRUCTION);
}

vm_code DVM_CALLBACK unload(DVM* state)
{
    return DVM_SUCCESS;
}

const VCPU CAR = {
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
        .vendorID = "CAR",
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