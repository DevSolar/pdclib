/* _PDCLIB_realpath( const char * path )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

extern char * realpath( const char * file_name, char * resolved_name );

#ifdef __cplusplus
}
#endif

char * _PDCLIB_realpath( const char * path )
{
    /* TODO: PATH_MAX but that seems difficult to come by */
    char buffer[ 4096 ];
    char * resolved_name;

    if ( realpath( path, buffer ) == NULL )
    {
        return NULL;
    }

    /* Need to do our own alloc-and-copy here, as realpath()
       would be linked to the system malloc(), and if our
       fclose() would run our free() on someone else's memory,
       results are more interesting than we would like to see.
    */
    if ( ( resolved_name = malloc( strlen( buffer + 1 ) ) ) == NULL )
    {
        return NULL;
    }

    return strcpy( resolved_name, buffer );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* No test drivers. */
    return TEST_RESULTS;
}

#endif
