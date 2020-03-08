/* difftime( time_t, time_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>

#ifndef REGTEST

double difftime( time_t time1, time_t time0 )
{
    /* If we want to avoid rounding errors and overflows, we need to be
       careful with the exact type of time_t being unknown to us.
       The code below is based on tzcode's difftime.c, which is in the
       public domain, so clarified as of 1996-06-05 by Arthur David Olson.
    */

    /* If double is large enough, simply covert and substract
       (assuming that the larger type has more precision).
    */
    if ( sizeof( time_t ) < sizeof( double ) )
    {
        return ( double )time1 - ( double )time0;
    }

    /* The difference of two unsigned values cannot overflow if the
       minuend is greater or equal to the subtrahend.
    */
    if ( ! _PDCLIB_TYPE_SIGNED( time_t ) )
    {
        return ( time1 >= time0 ) ? ( double )( time1 - time0 ) : -( double )( time0 - time1 );
    }

    /* Use uintmax_t if wide enough. */
    if ( sizeof( time_t ) <= sizeof( _PDCLIB_uintmax_t ) )
    {
        _PDCLIB_uintmax_t t1 = time1, t0 = time0;
        return ( time1 >= time0 ) ? t1 - t0 : -( double )( t0 - t1 );
    }

    /* If both times have the same sign, their difference cannot overflow. */
    if ( ( time1 < 0 ) == ( time0 < 0 ) )
    {
        return time1 - time0;
    }

    /* The times have opposite signs, and uintmax_t is too narrow.
       This suffers from double rounding; attempt to lessen that
       by using long double temporaries.
    */
    {
        long double t1 = time1, t0 = time0;
        return t1 - t0;
    }
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
