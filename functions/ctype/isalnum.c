/* isalnum( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>

#ifndef REGTEST

#include <locale.h>

int isalnum( int c )
{
    return ( isdigit( c ) || isalpha( c ) );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( isalnum( 'a' ) );
    TESTCASE( isalnum( 'z' ) );
    TESTCASE( isalnum( 'A' ) );
    TESTCASE( isalnum( 'Z' ) );
    TESTCASE( isalnum( '0' ) );
    TESTCASE( isalnum( '9' ) );
    TESTCASE( ! isalnum( ' ' ) );
    TESTCASE( ! isalnum( '\n' ) );
    TESTCASE( ! isalnum( '@' ) );
    return TEST_RESULTS;
}

#endif
