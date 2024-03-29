#ifndef VIRTUALDRAGON_VCPU_H
#define VIRTUALDRAGON_VCPU_H

#include "dvm.h"

vm_code DVM_CALLBACK cpu_init        (DVM* state);
vm_code DVM_CALLBACK cpu_attach      (DVM* state);
vm_code DVM_FASTCALL cpu_stateHandler(DVM* state, vm_code vmCode);
vm_code DVM_CALLBACK cpu_unload      (DVM* state);

#endif // VIRTUALDRAGON_VCPU_H
