/* _PDCLIB_is_leap( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

int _PDCLIB_is_leap( int year_offset )
{
    /* year given as offset from 1900, matching tm.tm_year in <time.h> */
    long long year = year_offset + 1900ll;
    return ( ( year % 4 ) == 0 && ( ( year % 25 ) != 0 || ( year % 400 ) == 0 ) );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    /* 1901 not leap */
    TESTCASE( ! _PDCLIB_is_leap( 1 ) );
    /* 1904 leap */
    TESTCASE( _PDCLIB_is_leap( 4 ) );
    /* 1900 not leap */
    TESTCASE( ! _PDCLIB_is_leap( 0 ) );
    /* 2000 leap */
    TESTCASE( _PDCLIB_is_leap( 100 ) );
#endif
    return TEST_RESULTS;
}

#endif
