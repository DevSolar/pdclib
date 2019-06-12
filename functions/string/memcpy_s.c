/* memcpy_s( void *, rsize_t, const void *, rsize_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef REGTEST

errno_t memcpy_s( void * _PDCLIB_restrict s1, rsize_t s1max, const void * _PDCLIB_restrict s2, rsize_t n )
{
    char * dest = (char *) s1;
    const char * src = (const char *) s2;

    if ( s1 == NULL || s2 == NULL || s1max > RSIZE_MAX || n > RSIZE_MAX || n > s1max || ( dest < src && ( dest + n ) >= src ) || ( src < dest && ( src + n ) >= dest ) || ( n > 0 && src == dest ) )
    {
        if ( s1 != NULL && s1max <= RSIZE_MAX )
        {
            memset( s1, 0, s1max );
        }
        _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
        return _PDCLIB_EINVAL;
    }

    while ( n-- )
    {
        *dest++ = *src++;
    }

    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    char s[] = "xxxxxxxxxxx";
    TESTCASE( memcpy_s( s, 11, abcde, 6 ) == 0 );
    TESTCASE( s[4] == 'e' );
    TESTCASE( s[5] == '\0' );
    TESTCASE( memcpy_s( s + 5, 6, abcde, 5 ) == 0 );
    TESTCASE( s[9] == 'e' );
    TESTCASE( s[10] == 'x' );

    set_constraint_handler_s( ignore_handler_s );
    s[5] = 'x';

    TESTCASE( memcpy_s( s, 5, abcde, 6 ) != 0 );
    TESTCASE( memcmp( s, "\0\0\0\0\0x", 6 ) == 0 );

    TESTCASE( memcpy_s( s, 3, s + 2, 3 ) != 0 );
    TESTCASE( memcpy_s( s + 2, 3, s, 3 ) != 0 );
#endif
    return TEST_RESULTS;
}

#endif
