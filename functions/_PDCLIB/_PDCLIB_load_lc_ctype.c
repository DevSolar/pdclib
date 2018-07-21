/* _PDCLIB_load_lc_ctype( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <inttypes.h>
#include <limits.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pdclib/_PDCLIB_int.h"

bool _PDCLIB_load_lc_ctype( const char * path, const char * locale )
{
    bool rc = false;
    const char * extension = "_ctype.dat";
    char * file = malloc( strlen( path ) + strlen( locale ) + strlen( extension ) + 1 );

    if ( file )
    {
        FILE * fh;

        strcpy( file, path );
        strcat( file, locale );
        strcat( file, extension );

        if ( ( fh = fopen( file, "rb" ) ) != NULL )
        {
            size_t charset_size = 1 << CHAR_BIT;
            struct _PDCLIB_lc_ctype_entry_t * ctype = malloc( sizeof( struct _PDCLIB_lc_ctype_entry_t ) * charset_size );

            if ( ctype != NULL )
            {
                size_t i;

                if ( fscanf( fh, "%x %x %x %x %x %x", _PDCLIB_lc_ctype.digits_low, _PDCLIB_lc_ctype.digits_high, _PDCLIB_lc_ctype.Xdigits_low, _PDCLIB_lc_ctype.Xdigits_high, _PDCLIB_lc_ctype.xdigits_low, _PDCLIB_lc_ctype.xdigits_high ) != 6 )
                {
                    fclose( fh );
                    free( ctype );
                    return false;
                }

                for ( i = 0; i < charset_size; ++i )
                {
                    if ( fscanf( fh, "%" SCNdLEAST8 "%hhu %hhu", &ctype[ i ].flags, &ctype[ i ].upper, &ctype[ i ].lower ) != 3 )
                    {
                        fclose( fh );
                        free( ctype );
                        return false;
                    }
                }

                rc = true;
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
    FILE * fh = fopen( "test_ctype.dat", "wb" );
    TESTCASE( fh != NULL );
    TESTCASE( fprintf( fh, "%x %x\n", 0x30, 0x39 ) );
    TESTCASE( fprintf( fh, "%x %x %x %x\n", 0x41, 0x46, 0x61, 0x66 ) );
    fclose( fh );
    TESTCASE( _PDCLIB_load_lc_ctype( "./", "test" ) );
    remove( "test_ctype.dat" );
#endif

    return TEST_RESULTS;
}

#endif
