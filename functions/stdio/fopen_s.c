/* fopen_s( FILE **, const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST

errno_t fopen_s( FILE * _PDCLIB_restrict * _PDCLIB_restrict streamptr, const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode )
{
    if ( streamptr == NULL || filename == NULL || mode == NULL )
    {
        if ( streamptr != NULL )
        {
            *streamptr = NULL;
        }

        _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
        return _PDCLIB_EINVAL;
    }

    if ( ( *streamptr = fopen( filename, mode ) ) == NULL )
    {
        return *_PDCLIB_errno_func();
    }

    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <errno.h>

#if ! defined( REGTEST ) || defined( __STDC_LIB_EXT1__ )

static int HANDLER_CALLS = 0;

static void test_handler( const char * _PDCLIB_restrict msg, void * _PDCLIB_restrict ptr, errno_t error )
{
    ++HANDLER_CALLS;
}

#endif

int main( void )
{
#if ! defined( REGTEST ) || defined( __STDC_LIB_EXT1__ )
    /* Some of the tests are not executed for regression tests, as the libc on
       my system is at once less forgiving (segfaults on mode NULL) and more
       forgiving (accepts undefined modes).
    */
    FILE * fh;
    remove( testfile );
    set_constraint_handler_s( test_handler );

    TESTCASE( fopen_s( NULL, NULL, NULL ) != 0 );
    TESTCASE( fopen_s( &fh, NULL, "w" ) != 0 );
    TESTCASE( fopen_s( &fh, "", "w" ) != 0 );
    TESTCASE( fopen_s( &fh, testfile, "" ) != 0 );
    TESTCASE( fopen_s( &fh, testfile, NULL ) != 0 );
    TESTCASE( fopen_s( &fh, testfile, "wq" ) != 0 );
    TESTCASE( fopen_s( &fh, testfile, "wr" ) != 0 );
    TESTCASE( fopen_s( &fh, testfile, "w" ) == 0 );
    TESTCASE( fclose( fh ) == 0 );
    TESTCASE( remove( testfile ) == 0 );
    TESTCASE( HANDLER_CALLS == 3 );
#endif
    return TEST_RESULTS;
}

#endif
