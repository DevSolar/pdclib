/* memmove_s( void *, rsize_t, const void *, rsize_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef REGTEST

errno_t memmove_s( void * s1, rsize_t s1max, const void * s2, rsize_t n )
{
    char * dest = ( char * ) s1;
    const char * src = ( const char * ) s2;

    if ( s1 == NULL || s2 == NULL || s1max > RSIZE_MAX || n > RSIZE_MAX || n > s1max )
    {
        if ( s1 != NULL && s1max <= RSIZE_MAX )
        {
            memset( s1, 0, s1max );
        }

        _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
        return _PDCLIB_EINVAL;
    }

    while ( n )
    {
        if ( dest == s2 || src == s1 )
        {
            src += n;
            dest += n;

            while ( n-- )
            {
                *--dest = *--src;
            }

            return 0;
        }

        *dest++ = *src++;
        --n;
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
    char s[] = "xxxxabcde";
    set_constraint_handler_s( test_handler );

    TESTCASE( memmove_s( s, 10, s + 4, 5 ) == 0 );
    TESTCASE( s[0] == 'a' );
    TESTCASE( s[4] == 'e' );
    TESTCASE( s[5] == 'b' );
    TESTCASE( memmove_s( s + 4, 6, s, 5 ) == 0 );
    TESTCASE( s[4] == 'a' );

    TESTCASE( HANDLER_CALLS == 0 );
#endif
    return TEST_RESULTS;
}

#endif
