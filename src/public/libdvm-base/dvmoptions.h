#ifndef VIRTUALDRAGON_DVMOPTIONS_H
#define VIRTUALDRAGON_DVMOPTIONS_H

#include "dvmclass.h"

#include "dvmfileapi.h"

typedef struct DVMOptions DVMOptions;

DVMOptions* dvm_createOptions( DVM_CLASS* dvmClass );
void        dvm_optionsDelete( DVMOptions* options, DVM_CLASS* dvmClass );

void        dvm_loadOptionsFile( DVMOptions* options, DESCRIPTOR file );

void        dvm_optionsAdd( DVMOptions* options, char* key, char* value );
char*       dvm_optionsGet( DVMOptions* options, char* key );

#endif //VIRTUALDRAGON_DVMOPTIONS_H
