/* memset_s( void *, rsize_t, int, rsize_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>

#ifndef REGTEST

errno_t memset_s( void * s, rsize_t smax, int c, rsize_t n )
{
    unsigned char * p = (unsigned char *) s;
    while ( n-- )
    {
        *p++ = (unsigned char) c;
    }
    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    char s[] = "xxxxxxxxx";
    TESTCASE( memset( s, 'o', 10 ) == s );
    TESTCASE( s[9] == 'o' );
    TESTCASE( memset( s, '_', (0) ) == s );
    TESTCASE( s[0] == 'o' );
    TESTCASE( memset( s, '_', 1 ) == s );
    TESTCASE( s[0] == '_' );
    TESTCASE( s[1] == 'o' );
    return TEST_RESULTS;
}

#endif
