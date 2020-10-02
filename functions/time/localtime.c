/* localtime( const time_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

struct tm * localtime( const time_t * timer )
{
    return _PDCLIB_localtime_tzset( timer, &_PDCLIB_tm, true );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* TODO: System Clock DST */

    time_t t;
    struct tm * time;

    t = -2147483648l;
    time = localtime( &t );
    TESTCASE( time->tm_sec == 52 );
    TESTCASE( time->tm_min == 45 );
    TESTCASE( time->tm_hour == 21 );
    TESTCASE( time->tm_mday == 13 );
    TESTCASE( time->tm_mon == 11 );
    TESTCASE( time->tm_year == 1 );
    TESTCASE( time->tm_wday == 5 );
    TESTCASE( time->tm_yday == 346 );

    t = 2147483647l;
    time = localtime( &t );
    TESTCASE( time->tm_sec == 7 );
    TESTCASE( time->tm_min == 14 );
    TESTCASE( time->tm_hour == 4 );
    TESTCASE( time->tm_mday == 19 );
    TESTCASE( time->tm_mon == 0 );
    TESTCASE( time->tm_year == 138 );
    TESTCASE( time->tm_wday == 2 );
    TESTCASE( time->tm_yday == 18 );

    return TEST_RESULTS;
}

#endif
