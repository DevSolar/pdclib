/* clearerr( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

void clearerr( struct _PDCLIB_file_t * stream )
{
    stream->status &= ~( _PDCLIB_ERRORFLAG | _PDCLIB_EOFFLAG );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    FILE * fh;
    TESTCASE( ( fh = tmpfile() ) != NULL );
    /* Flags should be clear */
    TESTCASE( ! ferror( fh ) );
    TESTCASE( ! feof( fh ) );
    /* Reading from empty stream - should provoke EOF */
    rewind( fh );
    TESTCASE( fgetc( fh ) == EOF );
    TESTCASE( ! ferror( fh ) );
    TESTCASE( feof( fh ) );
    /* clearerr() should clear flags */
    clearerr( fh );
    TESTCASE( ! ferror( fh ) );
    TESTCASE( ! feof( fh ) );
    /* reopen() the file write-only */
    TESTCASE( ( fh = freopen( NULL, "w", fh ) ) != NULL );
    /* Reading from write-only stream - should provoke error */
    TESTCASE( fgetc( fh ) == EOF );
    TESTCASE( ferror( fh ) );
    TESTCASE( ! feof( fh ) );
    /* clearerr() should clear flags */
    clearerr( fh );
    TESTCASE( ! ferror( fh ) );
    TESTCASE( ! feof( fh ) );
    TESTCASE( fclose( fh ) == 0 );
    return TEST_RESULTS;
}

#endif
