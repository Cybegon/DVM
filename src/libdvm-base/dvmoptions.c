#include "dvmoptions.h"
#include "dvmutils.h"

#include "hashmap.h"

struct DVMOptions
{
    void* map;
};

DVMOptions* dvm_createOptions( DVM_CLASS* dvmClass )
{
    DVMOptions* options = dvmClass->malloc( sizeof( DVMOptions ) );

    if ( hashmap_create( 256, options->map ) != 0 )
        return NULL;
    return options;
}

void dvm_deleteOptions( DVMOptions* options, DVM_CLASS* dvmClass )
{
    hashmap_destroy( options->map );
    dvmClass->free( options );
}

void dvm_optionsAdd( DVMOptions* options, char* key, char* value )
{
    dsize len = dvm_strlen( key );
    hashmap_put( options->map, key, len, value );
}

char* dvm_optionsGet( DVMOptions* options, char* key )
{
    dsize len = dvm_strlen( key );
    return hashmap_get( options->map, key, len );
}
