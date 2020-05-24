/* _PDCLIB_load_lines( FILE *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST

char * _PDCLIB_load_lines( FILE * fh, size_t lines )
{
    size_t required = 0;
    long pos = ftell( fh );
    char * rc = NULL;
    int c;

    /* Count the number of characters */
    while ( lines && ( c = fgetc( fh ) ) != EOF )
    {
        if ( c == '\n' )
        {
            --lines;
        }

        ++required;
    }

    if ( ! feof( fh ) )
    {
        if ( ( rc = (char *)malloc( required ) ) != NULL )
        {
            size_t i;

            fseek( fh, pos, SEEK_SET );
            fread( rc, 1, required, fh );

            for ( i = 0; i < required; ++i )
            {
                if ( rc[ i ] == '\n' )
                {
                    rc[ i ] = '\0';
                }
            }
        }
    }

    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    FILE * fh = fopen( "test_lines.txt", "w+" );
    char * rc;

    TESTCASE( fh != NULL );
    TESTCASE( fputs( "Foo\n\nBar\n", fh ) != EOF );

    rewind( fh );
    rc = _PDCLIB_load_lines( fh, 3 );
    fclose( fh );
    remove( "test_lines.txt" );

    TESTCASE( rc != NULL );
    TESTCASE( strcmp( rc, "Foo" ) == 0 );
    TESTCASE( strcmp( rc + 4, "" ) == 0 );
    TESTCASE( strcmp( rc + 5, "Bar" ) == 0 );

#endif
    return TEST_RESULTS;
}

#endif
