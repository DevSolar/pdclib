/* toupper( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>

#ifndef REGTEST

#include <locale.h>

int toupper( int c )
{
    return _PDCLIB_lc_ctype->entry[c].upper;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( toupper( 'a' ) == 'A' );
    TESTCASE( toupper( 'z' ) == 'Z' );
    TESTCASE( toupper( 'A' ) == 'A' );
    TESTCASE( toupper( 'Z' ) == 'Z' );
    TESTCASE( toupper( '@' ) == '@' );
    TESTCASE( toupper( '[' ) == '[' );
    return TEST_RESULTS;
}

#endif
