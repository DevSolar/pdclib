/* gmtime( const time_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>

#ifndef REGTEST

static struct tm gm_tm;

struct tm * gmtime( const time_t * timer )
{
    /* The following code implements the public domain date algorithm
       descriptions given on http://howardhinnant.github.io/date_algorithms.html
    */

    /* Split time into days and seconds. To be able to convert it into date and
       time, make sure that the seconds part is positive.
    */
    long long days = *timer / ( 60 * 60 * 24 );
    int seconds = *timer % ( 60 * 60 * 24 );
    if ( seconds < 0 )
    {
        seconds += 60 * 60 * 24;
        days--;
    }


    /* Shift the epoch from 1970-01-01 to 0000-03-01 (719468 days) */
    const long long epochdays = days + 719468;
    /* Split into era, day-of-era [0, 146096] and year-of-era [0, 399] */
    const int era = ( epochdays >= 0 ? epochdays : epochdays - 146096 ) / 146097;
    const int doe = ( epochdays - era * 146097 );
    const int yoe = ( doe - doe / 1460 + doe / 36524 - doe / 146096 ) / 365;
    /* Calculate year, day-of-year [0, 365], day [1, 31] and month [0, 11] */
    const int y = yoe + era * 400;
    const int doy = doe - ( 365 * yoe + yoe / 4 - yoe / 100);
    const int mp = ( 5 * doy + 2 ) / 153;
    const int d = doy - ( 153 * mp + 2 ) / 5 + 1;
    const int m = mp + ( mp < 10 ? 3 : -9 );

    /* Convert to the representation specified by struct tm */
    /* Years are counted relative to 1900 and start on 01.01 instead of 01.03 */
    gm_tm.tm_year = y - 1900 + ( m <= 2 );
    /* Months are counted with January = 0 */
    gm_tm.tm_mon = m - 1;
    gm_tm.tm_mday = d;
    /* With 1970-01-01 being a Thursday, calculate day-of-week (Sunday = 0)*/
    gm_tm.tm_wday = ( days >= -4 ? ( days + 4 ) % 7 : ( days + 5 ) % 7 + 6 );
    /* Day-of-year needs to do the 01.03->01.01 shift as well and wrap-around */
    gm_tm.tm_yday = ( doy + ( 31 + 28 ) ) % 365;
    /* If this is a leap year we need to insert an additional day in February */
    if ( _PDCLIB_is_leap( y - 1900 ) && gm_tm.tm_yday >= 31 + 28 )
        gm_tm.tm_yday++;

    const unsigned h = seconds / ( 60 * 60 );
    const unsigned min = ( seconds % ( 60 * 60) ) / 60;
    const unsigned s = seconds % 60;

    gm_tm.tm_hour = h;
    gm_tm.tm_min = min;
    gm_tm.tm_sec = s;

    /* This is UTC, so no Daylight Saving Time */
    gm_tm.tm_isdst = 0;

    return &gm_tm;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

static int cmptm( struct tm * res, int hour, int min, int sec, int year, int mon, int mday, int wday, int yday )
{
    return res->tm_hour == hour &&
           res->tm_min == min &&
           res->tm_sec == sec &&
           res->tm_year == year &&
           res->tm_mon == mon &&
           res->tm_mday == mday &&
           res->tm_wday == wday &&
           res->tm_yday == yday &&
           res->tm_isdst == 0;
}

int main( void )
{
    struct tm * res;
    time_t t;
    t = 0;
    TESTCASE( ( res = gmtime( &t ) ) );
    TESTCASE( cmptm( res, 0, 0, 0, 70, 0, 1, 4, 0 ) );
    t = -1;
    TESTCASE( ( res = gmtime( &t ) ) );
    TESTCASE( cmptm( res, 23, 59, 59, 69, 11, 31, 3, 364 ) );
    t = 1;
    TESTCASE( ( res = gmtime( &t ) ) );
    TESTCASE( cmptm( res, 0, 0, 1, 70, 0, 1, 4, 0 ) );
    t = 68169600;
    TESTCASE( ( res = gmtime( &t ) ) );
    TESTCASE( cmptm( res, 0, 0, 0, 72, 1, 29, 2, 59 ) );
    t = 946684800;
    TESTCASE( ( res = gmtime( &t ) ) );
    TESTCASE( cmptm( res, 0, 0, 0, 100, 0, 1, 6, 0 ) );
    t = -2209032000;
    TESTCASE( ( res = gmtime( &t ) ) );
    TESTCASE( cmptm( res, 12, 0, 0, -1, 11, 31, 0, 364 ) );
    t = 94608000;
    TESTCASE( ( res = gmtime( &t ) ) );
    TESTCASE( cmptm( res, 0, 0, 0, 72, 11, 31, 0, 365 ) );
    t = 126144000;
    TESTCASE( ( res = gmtime( &t ) ) );
    TESTCASE( cmptm( res, 0, 0, 0, 73, 11, 31, 1, 364 ) );
    t = -62198755200;
    TESTCASE( ( res = gmtime( &t ) ) );
    TESTCASE( cmptm( res, 0, 0, 0, -1901, 0, 1, 5, 0 ) );
    return TEST_RESULTS;
}

#endif
