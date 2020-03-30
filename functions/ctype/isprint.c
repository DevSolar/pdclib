/* isprint( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>

#ifndef REGTEST

#include <locale.h>

int isprint( int c )
{
    /* FIXME: Space as of current locale charset, not source charset. */
    return ( _PDCLIB_lc_ctype->entry[c].flags & _PDCLIB_CTYPE_GRAPH ) || ( c == ' ' );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( isprint( 'a' ) );
    TESTCASE( isprint( 'z' ) );
    TESTCASE( isprint( 'A' ) );
    TESTCASE( isprint( 'Z' ) );
    TESTCASE( isprint( '@' ) );
    TESTCASE( ! isprint( '\t' ) );
    TESTCASE( ! isprint( '\0' ) );
    TESTCASE( isprint( ' ' ) );
    return TEST_RESULTS;
}

#endif
