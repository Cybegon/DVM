#include "vcpu.h"

#include "dvmstate.h"

#define HANDLER(s, c) \
    BL = (IP / s->dvmClass->chunkSize) * s->dvmClass->chunkSize;                                                \
    BH = BL + s->dvmClass->chunkSize;                                                                           \
    vmswitch(c) {                                                                                               \
        vmcase(DVM_LOAD_PAGE)                                                                                   \
            s->text = s->dvmClass                                                                               \
                    ->getChunk(s->dvmClass->imageDescriptor, BL, s->dvmClass->chunkSize);                       \
            vmbreak;                                                                                            \
        vmcase(DVM_SUCCESS)                                                                                     \
        vmcase(DVM_FAIL)                                                                                        \
            vmrelease(c)                                                                                        \
        vmdefault:                                                                                              \
            vmrelease(DVM_UNDEFINED_VMCODE)                                                                     \
    }

vm_code cpu_init(DVM* state)
{
    return state->vcpu->init(state);
}

vm_code cpu_stateHandler(DVM* state, vm_code vmCode) {
    HANDLER(state, vmCode)

    return vmCode;
}

vm_code cpu_attach(DVM* state)
{
    vm_code vmCode;

    for (;;) {
        vmCode = state->vcpu->pipeline(state);

        HANDLER(state, vmCode)
    }
}

vm_code cpu_unload(DVM* state)
{
    return state->vcpu->deinit(state);
}
