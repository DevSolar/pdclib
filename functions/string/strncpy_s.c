/* strncpy_s( char *, rsize_t, const char *, rsize_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef REGTEST

errno_t strncpy_s( char * _PDCLIB_restrict s1, rsize_t s1max, const char * _PDCLIB_restrict s2, rsize_t n )
{
    char * dest = s1;
    const char * src = s2;

    if ( s1 != NULL && s2 != NULL && s1max <= RSIZE_MAX && n <= RSIZE_MAX && s1max != 0 )
    {
        while ( s1max-- )
        {
            if ( dest == s2 || src == s1 )
            {
                goto runtime_constraint_violation;
            }

            if ( n-- == 0 || ( *dest++ = *src++ ) == '\0' )
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
    char s[] = "xxxxxxx";
    set_constraint_handler_s( test_handler );

    TESTCASE( strncpy_s( s, 8, "", 1 ) == 0 );
    TESTCASE( s[0] == '\0' );
    TESTCASE( s[1] == 'x' );
    TESTCASE( strncpy_s( s, 8, abcde, 6 ) == 0 );
    TESTCASE( s[0] == 'a' );
    TESTCASE( s[4] == 'e' );
    TESTCASE( s[5] == '\0' );
    TESTCASE( s[6] == 'x' );
    TESTCASE( strncpy_s( s, 8, abcde, 7 ) == 0 );
    /* Different from strncpy()! */
    TESTCASE( s[5] == '\0' );
    TESTCASE( s[6] == 'x' );
    TESTCASE( strncpy_s( s, 8, "xxxx", 3 ) == 0 );
    TESTCASE( s[0] == 'x' );
    TESTCASE( s[2] == 'x' );
    TESTCASE( s[3] == 'd' );

    /* Overrun. */
    TESTCASE( strncpy_s( s, 8, "abcdefgh", 9 ) != 0 );
    TESTCASE( strncpy_s( s, 8, "abcdefgh", 9 ) != 0 );

    TESTCASE( HANDLER_CALLS == 2 );
#endif
    return TEST_RESULTS;
}

#endif
