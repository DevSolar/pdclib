/* _PDCLIB_load_lc_collate( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pdclib/_PDCLIB_internal.h"

struct _PDCLIB_lc_collate_t * _PDCLIB_load_lc_collate( const char * path, const char * locale )
{
    struct _PDCLIB_lc_collate_t * rc = NULL;
    const char * extension = "_collate.dat";
    char * file = (char *)malloc( strlen( path ) + strlen( locale ) + strlen( extension ) + 1 );

    if ( file )
    {
        FILE * fh;

        strcpy( file, path );
        strcat( file, locale );
        strcat( file, extension );

        if ( ( fh = fopen( file, "rb" ) ) != NULL )
        {
            if ( ( rc = (struct _PDCLIB_lc_collate_t *)malloc( sizeof( struct _PDCLIB_lc_collate_t ) ) ) != NULL )
            {
                /* TODO: Collation data */

                rc->alloced = 1;
            }

            fclose( fh );
        }

        free( file );
    }

    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    TESTCASE( NO_TESTDRIVER );
#endif

    return TEST_RESULTS;
}

#endif
