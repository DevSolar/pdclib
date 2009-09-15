/* $Id$ */

/* isspace( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>
#include <stdbool.h>

#ifndef REGTEST

int isspace( int c )
{
    switch ( c )
    {
        case ' ':
        case '\f':
        case '\n':
        case '\r':
        case '\t':
        case '\v':
            return true;
        default:
            return false;
    }
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( isspace( ' ' ) );
    TESTCASE( isspace( '\f' ) );
    TESTCASE( isspace( '\n' ) );
    TESTCASE( isspace( '\r' ) );
    TESTCASE( isspace( '\t' ) );
    TESTCASE( isspace( '\v' ) );
    TESTCASE( ! isspace( 'a' ) );
    return TEST_RESULTS;
}

#endif
