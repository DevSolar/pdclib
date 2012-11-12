/* $Id$ */

/* clearerr( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

void clearerr_unlocked( struct _PDCLIB_file_t * stream )
{
    stream->status &= ~( _PDCLIB_ERRORFLAG | _PDCLIB_EOFFLAG );
}

void clearerr( struct _PDCLIB_file_t * stream )
{
    flockfile( stream );
    clearerr_unlocked( stream );
    funlockfile( stream );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    FILE * fh;
    TESTCASE( ( fh = tmpfile() ) != NULL );
    /* Flags should be clear */
    TESTCASE( ! ferror( fh ) );
    TESTCASE( ! feof( fh ) );
    /* Reading from input stream - should provoke error */
    /* FIXME: Apparently glibc disagrees on this assumption. How to provoke error on glibc? */
    TESTCASE( fgetc( fh ) == EOF );
    TESTCASE( ferror( fh ) );
    TESTCASE( ! feof( fh ) );
    /* clearerr() should clear flags */
    clearerr( fh );
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
    TESTCASE( fclose( fh ) == 0 );
    return TEST_RESULTS;
}

#endif

