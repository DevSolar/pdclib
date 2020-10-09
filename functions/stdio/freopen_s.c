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
    TESTCASE( NO_TESTDRIVER );
#endif
    return TEST_RESULTS;
}

#endif
