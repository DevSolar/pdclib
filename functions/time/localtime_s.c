/* localtime_s( const time_t *, struct tm * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

struct tm * localtime_s( const time_t * _PDCLIB_restrict timer, struct tm * _PDCLIB_restrict result )
{
    if ( timer == NULL || result == NULL )
    {
        _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
        return NULL;
    }

    return _PDCLIB_localtime_tzset( timer, result, true );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    time_t t;
    struct tm time;

    /* TODO: Constraint handling, System Clock DST */

    t = -2147483648l;
    TESTCASE( localtime_s( &t, &time ) != NULL );
    TESTCASE( time.tm_sec == 52 );
    TESTCASE( time.tm_min == 45 );
    TESTCASE( time.tm_hour == 21 );
    TESTCASE( time.tm_mday == 13 );
    TESTCASE( time.tm_mon == 11 );
    TESTCASE( time.tm_year == 1 );
    TESTCASE( time.tm_wday == 5 );
    TESTCASE( time.tm_yday == 346 );

    t = 2147483647l;
    TESTCASE( localtime_s( &t, &time ) != NULL );
    TESTCASE( time.tm_sec == 7 );
    TESTCASE( time.tm_min == 14 );
    TESTCASE( time.tm_hour == 4 );
    TESTCASE( time.tm_mday == 19 );
    TESTCASE( time.tm_mon == 0 );
    TESTCASE( time.tm_year == 138 );
    TESTCASE( time.tm_wday == 2 );
    TESTCASE( time.tm_yday == 18 );
#endif

    return TEST_RESULTS;
}

#endif
