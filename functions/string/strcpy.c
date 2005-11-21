/* $Id$ */

/* Release $Name$ */

/* strcpy( char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <_PDCLIB_aux.h>

char * strcpy( char * _PDCLIB_restrict s1, const char * _PDCLIB_restrict s2 )
{
    char * rc = s1;
    while ( ( *s1++ = *s2++ ) );
    return rc;
}

#ifdef TEST
#include <_PDCLIB_test.h>

int main()
{
    char s[] = "xxxxx";
    BEGIN_TESTS;
    TESTCASE( strcpy( s, "" ) == s );
    TESTCASE( s[0] == '\0' );
    TESTCASE( s[1] == 'x' );
    TESTCASE( strcpy( s, abcde ) == s );
    TESTCASE( s[0] == 'a' );
    TESTCASE( s[4] == 'e' );
    TESTCASE( s[5] == '\0' );
    return TEST_RESULTS;
}
#endif
