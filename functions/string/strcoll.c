/* $Id$ */

/* strcoll( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <string.h>

#ifndef REGTEST

/* TODO: Dummy function, PDCLib does not support locales yet. */
int strcoll( const char * s1, const char * s2 )
{
    return strcmp( s1, s2 );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    char cmpabcde[] = "abcde";
    char empty[] = "";
    TESTCASE( strcmp( abcde, cmpabcde ) == 0 );
    TESTCASE( strcmp( abcde, abcdx ) < 0 );
    TESTCASE( strcmp( abcdx, abcde ) > 0 );
    TESTCASE( strcmp( empty, abcde ) < 0 );
    TESTCASE( strcmp( abcde, empty ) > 0 );
    return TEST_RESULTS;
}
#endif
