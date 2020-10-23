/* ungetc( int, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#ifndef __STDC_NO_THREADS__
#include <threads.h>
#endif

int ungetc( int c, struct _PDCLIB_file_t * stream )
{
    int rc;

    _PDCLIB_LOCK( stream->mtx );

    if ( c == EOF || stream->ungetidx == _PDCLIB_UNGETCBUFSIZE )
    {
        rc = -1;
    }
    else
    {
        rc = stream->ungetbuf[stream->ungetidx++] = ( unsigned char ) c;
    }

    _PDCLIB_UNLOCK( stream->mtx );

    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdlib.h>

int main( void )
{
    char buffer[4];
    char input[1];
    FILE * fh;
    int read;
    fpos_t pos;
    TESTCASE( ( fh = tmpfile() ) != NULL );
    TESTCASE( setvbuf( fh, buffer, _IOLBF, 4 ) == 0 );
    rewind( fh );
    TESTCASE( fprintf( fh, "123" ) == 3 );
    TESTCASE( ftell( fh ) == 3 );
    rewind( fh );
    TESTCASE( fscanf( fh, "12%n", &read ) == 0 );
    TESTCASE( read == 2 );
    TESTCASE( ftell( fh ) == 2 );
    TESTCASE( ungetc( 'x', fh ) == 'x' );
    TESTCASE( ftell( fh ) == 1 );
    read = 0;
    TESTCASE( fscanf( fh, "x3%n", &read ) == 0 );
    TESTCASE( ftell( fh ) == 3 );
    TESTCASE( read == 2 );
    TESTCASE( ungetc( 'y', fh ) == 'y' );
    TESTCASE( ftell( fh ) == 2 );
    TESTCASE( fread( input, 1, 1, fh ) == 1 );
    TESTCASE( ftell( fh ) == 3 );
    TESTCASE( input[0] == 'y' );
    rewind( fh );
    TESTCASE( ungetc( 'z', fh ) == 'z' );
    TESTCASE( ftell( fh ) == -1 );
    TESTCASE( fread( input, 1, 4, fh ) == 4 );
    TESTCASE( memcmp( input, "z123", 4 ) == 0 );
    rewind( fh );
    TESTCASE( ungetc( 'z', fh ) == 'z' );
    TESTCASE( ftell( fh ) == -1 );
    TESTCASE( fscanf( fh, "%4c", input ) == 1 );
    TESTCASE( memcmp( input, "z123", 4 ) == 0 );
    rewind( fh );
    TESTCASE( fgetc( fh ) == '1' );
    TESTCASE( ftell( fh ) == 1 );
    TESTCASE( ungetc( 'z', fh ) == 'z' );
    TESTCASE( ftell( fh ) == 0 );
    TESTCASE( fgetpos( fh, &pos ) == 0 );
    TESTCASE( fsetpos( fh, &pos ) == 0 );
    TESTCASE( ftell( fh ) == 0 );
    TESTCASE( fgetc( fh ) == '1' );
    TESTCASE( fclose( fh ) == 0 );
    return TEST_RESULTS;
}

#endif
