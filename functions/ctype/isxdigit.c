/* isxdigit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>

#ifndef REGTEST

#include <locale.h>

int isxdigit( int c )
{
    return ( isdigit( c ) ||
             ( c >= _PDCLIB_lc_ctype->Xdigits_low && c <= _PDCLIB_lc_ctype->Xdigits_high ) ||
             ( c >= _PDCLIB_lc_ctype->xdigits_low && c <= _PDCLIB_lc_ctype->xdigits_high )
           );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( isxdigit( '0' ) );
    TESTCASE( isxdigit( '9' ) );
    TESTCASE( isxdigit( 'a' ) );
    TESTCASE( isxdigit( 'f' ) );
    TESTCASE( ! isxdigit( 'g' ) );
    TESTCASE( isxdigit( 'A' ) );
    TESTCASE( isxdigit( 'F' ) );
    TESTCASE( ! isxdigit( 'G' ) );
    TESTCASE( ! isxdigit( '@' ) );
    TESTCASE( ! isxdigit( ' ' ) );
    return TEST_RESULTS;
}

#endif
