/* strncpy_s( char *, rsize_t, const char *, rsize_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>

#ifndef REGTEST

errno_t strncpy_s( char * _PDCLIB_restrict s1, rsize_t s1max, const char * _PDCLIB_restrict s2, rsize_t n )
{
    while ( n && ( *s1++ = *s2++ ) )
    {
        /* Cannot do "n--" in the conditional as size_t is unsigned and we have
           to check it again for >0 in the next loop below, so we must not risk
           underflow.
        */
        --n;
    }
    /* Checking against 1 as we missed the last --n in the loop above. */
    while ( n-- > 1 )
    {
        *s1++ = '\0';
    }
    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    char s[] = "xxxxxxx";
    TESTCASE( strncpy( s, "", 1 ) == s );
    TESTCASE( s[0] == '\0' );
    TESTCASE( s[1] == 'x' );
    TESTCASE( strncpy( s, abcde, 6 ) == s );
    TESTCASE( s[0] == 'a' );
    TESTCASE( s[4] == 'e' );
    TESTCASE( s[5] == '\0' );
    TESTCASE( s[6] == 'x' );
    TESTCASE( strncpy( s, abcde, 7 ) == s );
    TESTCASE( s[6] == '\0' );
    TESTCASE( strncpy( s, "xxxx", 3 ) == s );
    TESTCASE( s[0] == 'x' );
    TESTCASE( s[2] == 'x' );
    TESTCASE( s[3] == 'd' );
    return TEST_RESULTS;
}

#endif
