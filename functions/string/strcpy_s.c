/* strcpy_s( char *, rsize_t, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef REGTEST

errno_t strcpy_s( char * _PDCLIB_restrict s1, rsize_t s1max, const char * _PDCLIB_restrict s2 )
{
    char * dest = s1;
    const char * src = s2;

    if ( s1 != NULL && s2 != NULL && s1max <= RSIZE_MAX && s1max != 0 )
    {
        while ( s1max-- )
        {
            if ( dest == s2 || src == s1 )
            {
                goto runtime_constraint_violation;
            }

            if ( ( *dest++ = *src++ ) == '\0' )
            {
                return 0;
            }
        }
    }

runtime_constraint_violation:

    if ( s1 != NULL && s1max > 0 && s1max <= RSIZE_MAX )
    {
        s1[0] = '\0';
    }

    _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
    return _PDCLIB_EINVAL;
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
    char s[] = "xxxxx";
    set_constraint_handler_s( test_handler );

    TESTCASE( strcpy_s( s, 6, "" ) == 0 );
    TESTCASE( s[0] == '\0' );
    TESTCASE( s[1] == 'x' );
    TESTCASE( strcpy_s( s, 6, abcde ) == 0 );
    TESTCASE( s[0] == 'a' );
    TESTCASE( s[4] == 'e' );
    TESTCASE( s[5] == '\0' );

    /* Overrun. */
    TESTCASE( strcpy_s( s, 6, "abcdef" ) != 0 );

    /* Overlapping. */
    TESTCASE( strcpy_s( s, 3, s + 2 ) != 0 );
    TESTCASE( strcpy_s( s + 2, 3, s ) != 0 );

    TESTCASE( HANDLER_CALLS == 3 );
#endif
    return TEST_RESULTS;
}

#endif
