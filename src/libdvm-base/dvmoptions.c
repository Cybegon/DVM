#include "dvmoptions.h"
#include "dvmutils.h"

#include <hashmap/hashmap.h>
#include <cJSON/cJSON.h>

#include <mz.h>
#include <mz_strm_mem.h>

// hello govnocod

struct DVMOptions
{
    DVM_CLASS*      dvmClass;
    hashmap_t*      map;
};

int deleteKeyValue ( void* const context, struct hashmap_element_s* const e );
void recursiveOptionsAdd( DVMOptions* options, cJSON* root, MEMORY stream );

DVMOptions* dvm_createOptions( DVM_CLASS* dvmClass )
{
    DVMOptions* options = dvmClass->malloc( sizeof( DVMOptions ) );

    options->dvmClass   = dvmClass;
    options->map        = dvmClass->malloc( sizeof( hashmap_t ) );

    if ( hashmap_create( 32, options->map ) != 0 )
        return NULL;

    return options;
}

void dvm_optionsDelete( DVMOptions* options, DVM_CLASS* dvmClass )
{
    hashmap_iterate_pairs( options->map, deleteKeyValue, dvmClass );
    hashmap_destroy( options->map );
    dvmClass->free( options->map );
    dvmClass->free( options );
}

void dvm_loadOptionsFile( DVMOptions* options, DESCRIPTOR file )
{
    DVM_FSTAT fStat = { 0 };
    char* buffer    = NULL;
    void* stream    = NULL;

    dvm_fileFStat( file, &fStat );

    buffer = options->dvmClass->malloc( fStat.uncompressedSize );
    dvm_fileRead( file, buffer, fStat.uncompressedSize );

    stream = mz_stream_mem_create();
    mz_stream_mem_open( stream, NULL, MZ_OPEN_MODE_CREATE | MZ_OPEN_MODE_READWRITE | MZ_OPEN_MODE_APPEND );

    cJSON* root = cJSON_ParseWithLength( buffer, fStat.uncompressedSize );

    recursiveOptionsAdd( options, root, stream );

    cJSON_Delete( root );

    mz_stream_mem_close( stream );
    mz_stream_mem_delete( &stream );
}

void dvm_optionsAdd( DVMOptions* options, char* key, char* value )
{
    DVM_CLASS* dvmClass = options->dvmClass;

    MEMORY  newKey          = NULL;
    MEMORY  newValue        = NULL;
    dsize   keyLength       = dvm_strlen( key );
    dsize   valueLength     = dvm_strlen( value );

    newKey      = dvmClass->malloc( keyLength + 1 );
    newValue    = dvmClass->malloc( valueLength + 1 );

    memcpy( newKey, key, keyLength + 1 );
    memcpy( newValue, value, valueLength + 1 );

    hashmap_put( options->map, newKey, keyLength, newValue );
}

char* dvm_optionsGet( DVMOptions* options, char* key )
{
    dsize len = dvm_strlen( key );
    return hashmap_get( options->map, key, len );
}

void recursiveOptionsAdd( DVMOptions* options, cJSON* root, MEMORY stream )
{
    cJSON* item = NULL;
    dsize lastPosition = mz_stream_mem_tell( stream );

    cJSON_ArrayForEach( item, root )
    {
        if ( cJSON_IsObject( item ) ) {
            mz_stream_mem_write( stream, item->string, dvm_strlen( item->string ) );
            mz_stream_mem_write( stream, ".", sizeof(".") - 1 );

            recursiveOptionsAdd( options, item, stream );

            mz_stream_mem_seek( stream, lastPosition, MZ_SEEK_SET );
        } else if ( cJSON_IsString( item ) ) {
            MEMORY  buffer          = NULL;
            mz_stream_mem_write( stream, item->string, dvm_strlen( item->string ) + 1 );
            mz_stream_mem_seek( stream, lastPosition, MZ_SEEK_SET );
            mz_stream_mem_get_buffer(stream, (const void **)&buffer);

            dvm_optionsAdd( options, buffer, cJSON_GetStringValue( item ) );
        }
    }
}

int deleteKeyValue( void* const context, struct hashmap_element_s* const e )
{
    DVM_CLASS* dvmClass = (DVM_CLASS*)context;

    dvmClass->free( (MEMORY)e->key );
    dvmClass->free( (MEMORY)e->data );

    return -1; // auto delete element
}