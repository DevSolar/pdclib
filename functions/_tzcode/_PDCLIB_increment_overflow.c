/* _PDCLIB_increment_overflow( int *, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_tzcode.h"

/* Normalize logic courtesy Paul Eggert. */

bool _PDCLIB_increment_overflow( int * ip, int j )
{
    int const i = *ip;

    /* If i >= 0 there can only be overflow if i + j > INT_MAX
       or if j > INT_MAX - i; given i >= 0, INT_MAX - i cannot overflow.
       If i < 0 there can only be overflow if i + j < INT_MIN
       or if j < INT_MIN - i; given i < 0, INT_MIN - i cannot overflow.
    */
    if ( ( i >= 0 ) ? ( j > _PDCLIB_INT_MAX - i ) : ( j < _PDCLIB_INT_MIN - i ) )
    {
        return true;
    }

    *ip += j;
    return false;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
#endif

    return TEST_RESULTS;
}

#endif
