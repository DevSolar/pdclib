/* memset_s( void *, rsize_t, int, rsize_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef REGTEST

errno_t memset_s( void * s, rsize_t smax, int c, rsize_t n )
{
    unsigned char * p = ( unsigned char * ) s;

    if ( s == NULL || smax > RSIZE_MAX || n > RSIZE_MAX || n > smax )
    {
        if ( s != NULL && smax <= RSIZE_MAX )
        {
            memset( s, c, smax );
        }

        _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
        return _PDCLIB_EINVAL;
    }

    while ( n-- )
    {
        *p++ = ( unsigned char ) c;
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
    char s[] = "xxxxxxxxx";
    set_constraint_handler_s( test_handler );

    TESTCASE( memset_s( s, 10, 'o', 10 ) == 0 );
    TESTCASE( s[9] == 'o' );
    TESTCASE( memset_s( s, 10, '_', ( 0 ) ) == 0 );
    TESTCASE( s[0] == 'o' );
    TESTCASE( memset_s( s, 10, '_', 1 ) == 0 );
    TESTCASE( s[0] == '_' );
    TESTCASE( s[1] == 'o' );

    TESTCASE( HANDLER_CALLS == 0 );
#endif
    return TEST_RESULTS;
}

#endif
