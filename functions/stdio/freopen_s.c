/* freopen_s( FILE **, const char *, const char *, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST

_PDCLIB_PUBLIC errno_t freopen_s( FILE * _PDCLIB_restrict * _PDCLIB_restrict newstreamptr, const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode, FILE * _PDCLIB_restrict stream )
{
    if ( newstreamptr == NULL || mode == NULL || stream == NULL )
    {
        if ( newstreamptr != NULL )
        {
            *newstreamptr = NULL;
        }

        _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
        return _PDCLIB_EINVAL;
    }

    if ( ( *newstreamptr = freopen( filename, mode, stream ) ) == NULL )
    {
        return *_PDCLIB_errno_func();
    }

    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

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
    FILE * fin;
    FILE * fout;
    FILE * dummy;
    set_constraint_handler_s( test_handler );

    TESTCASE( ( fin = fopen( testfile1, "wb+" ) ) != NULL );
    TESTCASE( fputc( 'x', fin ) == 'x' );
    TESTCASE( fclose( fin ) == 0 );
    TESTCASE( freopen_s( &fin, testfile1, "rb", stdin ) == 0 );
    TESTCASE( getchar() == 'x' );

    TESTCASE( freopen_s( &fout, testfile2, "wb+", stdout ) == 0 );
    TESTCASE( putchar( 'x' ) == 'x' );
    rewind( fout );
    TESTCASE( fgetc( fout ) == 'x' );

    dummy = fin;
    TESTCASE( freopen_s( &dummy, testfile1, "rb", NULL ) != 0 );
    dummy = fin;
    TESTCASE( freopen_s( &dummy, testfile1, NULL, stdin ) != 0 );
    TESTCASE( freopen_s( NULL, testfile1, "rb", fin ) != 0 );

    TESTCASE( fclose( fin ) == 0 );
    TESTCASE( fclose( fout ) == 0 );
    TESTCASE( remove( testfile1 ) == 0 );
    TESTCASE( remove( testfile2 ) == 0 );

    TESTCASE( HANDLER_CALLS == 3 );
#else
    TESTCASE( NO_TESTDRIVER );
#endif
    return TEST_RESULTS;
}

#endif
