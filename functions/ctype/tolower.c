/* $Id$ */

/* tolower( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>

#ifndef REGTEST

int tolower( int c )
{
    if ( ( c >= 'A' ) && ( c <= 'Z' ) )
    {
        c += ( 'a' - 'A' );
    }
    return c;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( tolower( 'A' ) == 'a' );
    TESTCASE( tolower( 'Z' ) == 'z' );
    TESTCASE( tolower( 'a' ) == 'a' );
    TESTCASE( tolower( 'z' ) == 'z' );
    TESTCASE( tolower( '@' ) == '@' );
    TESTCASE( tolower( '[' ) == '[' );
    return TEST_RESULTS;
}
#endif
