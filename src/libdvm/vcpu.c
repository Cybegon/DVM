#include "vcpu.h"

#include "flags.h"

#define HANDLER(s, c)                                                                                           \
    vmswitch(c) {                                                                                               \
        vmcase(DVM_LOAD_PAGE)                                                                                   \
            s->text = s->dvmClass                                                                               \
                    ->viewMemoryMap(s->dvmClass->imageDescriptor, IP, s->dvmClass->codeChunkSize);              \
            vmbreak;                                                                                            \
        vmcase(DVM_TRANSFER_CONTROL)                                                                            \
            if (FR & TF)                                                                                        \
                c = s->vcpus[s->extensionID]->main.pipeline(s);                                                 \
            else                                                                                                \
                c = s->vcpus[s->processorID]->main.pipeline(s);                                                 \
        vmcase(DVM_SUCCESS)                                                                                     \
        vmcase(DVM_FAIL)                                                                                        \
            vmrelease(c)                                                                                        \
        vmdefault:                                                                                              \
            vmrelease(DVM_UNDEFINED_VMCODE)                                                                     \
    }

vm_code cpu_init(DVM* state)
{
    for (duint32 i = 0; state->vcpus[i] != NULL; ++i) // &state->vcpus[i] like (state->vcpus + i)
    {
        if (state->vcpus[i]->main.init != NULL)
            state->vcpus[i]->main.init(state);
    }

    return 0; // return code replace later
}

vm_code cpu_stateHandler(DVM* state, vm_code vmCode) {
    HANDLER(state, vmCode)

    return vmCode;
}

vm_code cpu_attach(DVM* state)
{
    vm_code vmCode;

    for (;;) {
        vmCode = state->vcpus[state->processorID]->main.pipeline(state);

        HANDLER(state, vmCode)
    }
}

vm_code cpu_unload(DVM* state)
{
    vm_code processorCode;
    vm_code coprocessorCode;

    for (duint32 i = 0; state->vcpus[i] != NULL; ++i) // &state->vcpus[i] like (state->vcpus + i)
    {
        if (state->vcpus[i]->main.unload != NULL)
            state->vcpus[i]->main.unload(state);
    }

    return 0; // return code replace later
}
