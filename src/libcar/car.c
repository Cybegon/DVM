#include "car.h"

#include "dvmstate.h"
#include "dvmflags.h"

#include "interrupts.h"

#include "i32/format-i/format-i.h"
#include "i32/format-r/format-r.h"

#include "i64/format-i/format-i.h"
#include "i64/format-j/format-j.h"
#include "i64/format-c/format-c.h"
#include "i64/format-l/format-l.h"

#include "formats.h"

// 4 bits for format
#define GET_FORMAT32(i)   ( (i & 0x70000000u) >> 28u )
#define GET_FORMAT64(i)   ( (i & 0x3F00000000000000ull) >> 56u )

// 0xC000000000000000ull

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
        in  = DVM_FETCH(state);
        IP += sizeof(INSTRUCTION);

        if (cvtR2FR(FR)->vm_control & EF) {
            tmp = *in;                      // copy to temporary instruction
            _BSWAP64(tmp.i64);              // swap data
            in = &tmp;                      // set pointer to temporary instruction
        }

        step(state, in);
    }

vmslot(OUT)
    return DVM_LOAD_PAGE;
}

vm_code DVM_FASTCALL longMode(DVM* state, INSTRUCTION* in)
{
    vmdispatch(GET_FORMAT64(in->i64)) {
        vmcase(CAR_FORMAT_I) {
            format_i64(state, in->i64);
            vmbreak;
        }
        vmcase(CAR_FORMAT_J) {
            format_j64(state, in->i64);
            vmbreak;
        }
        vmcase(CAR_FORMAT_C) {
            format_c64(state, in->i64);
            vmbreak;
        }
        vmcase(CAR_FORMAT_L) {
            format_l64(state, in->i64);
            vmbreak;
        }
        vmdefault: {
            return DVM_FAIL;
        }
    }
    return DVM_SUCCESS;
}

vm_code DVM_FASTCALL step(DVM* state, INSTRUCTION* in)
{
    vmdispatch(GET_FORMAT32(in->i32L)) {
        vmcase(CAR_FORMAT_N) {
            // No operation
            vmbreak;
        }
        vmcase(CAR_FORMAT_I) {
            format_i32(state, in->i32L);
            vmbreak;
        }
        vmcase(CAR_FORMAT_R) {
            format_r32(state, in->i32L);
            vmbreak;
        }
        vmcase(CAR_FORMAT_LONG) {
            vmsignal(SKIP);
        }
        vmdefault: {
            longMode( state, in );
        }
    }
    vmdispatch(GET_FORMAT32(in->i32H)) {
        vmcase(CAR_FORMAT_N) {
            // No operation
            vmbreak;
        }
        vmcase(CAR_FORMAT_I) {
            format_i32(state, in->i32H);
            vmbreak;
        }
        vmcase(CAR_FORMAT_R) {
            format_r32(state, in->i32H);
            vmbreak;
        }
        vmcase(CAR_FORMAT_LONG) {
            state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
            vmsignal(SKIP);
        }
        vmdefault: {
            state->SVI[ SVI_ILLEGAL_OPCODE ]( state );
            return DVM_FAIL;
        }
    }
    vmslot(SKIP)

    return DVM_SUCCESS;
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
        .vendorID   = "CAR",
        .init       = load,
        .step       = step,
        .pipeline   = entry,
        .deinit     = unload
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
