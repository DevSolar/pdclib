/* memcpy_s( void *, rsize_t, const void *, rsize_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>

#ifndef REGTEST

errno_t memcpy_s( void * _PDCLIB_restrict s1, rsize_t s1max, const void * _PDCLIB_restrict s2, rsize_t n )
{
    char * dest = (char *) s1;
    const char * src = (const char *) s2;
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
    char s[] = "xxxxxxxxxxx";
    TESTCASE( memcpy( s, abcde, 6 ) == s );
    TESTCASE( s[4] == 'e' );
    TESTCASE( s[5] == '\0' );
    TESTCASE( memcpy( s + 5, abcde, 5 ) == s + 5 );
    TESTCASE( s[9] == 'e' );
    TESTCASE( s[10] == 'x' );
    return TEST_RESULTS;
}

#endif
