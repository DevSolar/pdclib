/* $Id$ */

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
#include <_PDCLIB_test.h>

int main( void )
{
#ifndef REGTEST
    FILE file = { 0, { 0, 0 }, NULL, 0, 0, 0, _IONBF, NULL, NULL };
    FILE * fh = &file;
    TESTCASE( ! ferror( fh ) );
    TESTCASE( ! feof( fh ) );
    fh->status |= _PDCLIB_ERRORFLAG;
    TESTCASE( ferror( fh ) );
    TESTCASE( ! feof( fh ) );
    clearerr( fh );
    TESTCASE( ! ferror( fh ) );
    TESTCASE( ! feof( fh ) );
    fh->status |= _PDCLIB_EOFFLAG;
    TESTCASE( ! ferror( fh ) );
    TESTCASE( feof( fh ) );
    clearerr( fh );
    TESTCASE( ! ferror( fh ) );
    TESTCASE( ! feof( fh ) );
    fh->status |= _PDCLIB_EOFFLAG | _PDCLIB_ERRORFLAG;
    TESTCASE( ferror( fh ) );
    TESTCASE( feof( fh ) );
    clearerr( fh );
    TESTCASE( ! ferror( fh ) );
    TESTCASE( ! feof( fh ) );
#else
    /* TODO: The above is ad-hoc and PDCLib specific. A better test driver
       should be internals-agnostic (provoking the error / eof flag by
       "regular" operations).
    */
    TESTCASE( NO_TESTDRIVER );
#endif
    return TEST_RESULTS;
}

#endif
