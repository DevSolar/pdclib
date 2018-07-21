/* _PDCLIB_load_lc_numeric( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pdclib/_PDCLIB_int.h"

bool _PDCLIB_load_lc_numeric( const char * path, const char * locale )
{
    bool rc = false;
    const char * extension = "_numeric.dat";
    char * file = malloc( strlen( path ) + strlen( locale ) + strlen( extension ) + 1 );

    if ( file )
    {
        FILE * fh;

        strcpy( file, path );
        strcat( file, locale );
        strcat( file, extension );

        if ( ( fh = fopen( file, "rb" ) ) != NULL )
        {
            char * data = _PDCLIB_load_lines( fh, 3 );

            if ( data != NULL )
            {
                _PDCLIB_lc_numeric_monetary.numeric_alloced = 1;
                _PDCLIB_lc_numeric_monetary.lconv->decimal_point = data;
                data += strlen( data ) + 1;
                _PDCLIB_lc_numeric_monetary.lconv->thousands_sep = data;
                data += strlen( data ) + 1;
                _PDCLIB_lc_numeric_monetary.lconv->grouping = data;

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
    FILE * fh = fopen( "test_numeric.dat", "wb" );
    struct lconv * lc;
    TESTCASE( fh != NULL );
    TESTCASE( fputs( ",\n.\n\n", fh ) != EOF );
    fclose( fh );
    TESTCASE( _PDCLIB_load_lc_numeric( "./", "test" ) );
    remove( "test_numeric.dat" );
    lc = localeconv();
    TESTCASE( strcmp( lc->decimal_point, "," ) == 0 );
    TESTCASE( strcmp( lc->thousands_sep, "." ) == 0 );
    TESTCASE( strcmp( lc->grouping, "" ) == 0 );
#endif

    return TEST_RESULTS;
}

#endif
