/* _PDCLIB_bigint_div( bigint_t *, bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <assert.h>

unsigned _PDCLIB_bigint_div( _PDCLIB_bigint_t * dividend, _PDCLIB_bigint_t const * divisor )
{
    _PDCLIB_bigint_digit_t quotient;
    _PDCLIB_size_t const s = dividend->size;
    _PDCLIB_size_t i;

    assert( divisor->size > 0 );
    assert( s <= divisor->size );
    assert( divisor->data[ divisor->size - 1 ] < _PDCLIB_BIGINT_DIGIT_MAX );

    if ( s-- < divisor->size || dividend->data[s] < divisor->data[s])
    {
        return 0;
    }

    /* With dividend truncated, and divisor + 1,
       this quotient might be one short of correct.
    */
    quotient = dividend->data[s] / ( divisor->data[s] + 1 );

    if ( quotient > 0 )
    {
        /* dividend = dividend - (divisor * quotient */
        _PDCLIB_bigint_arith_t t = 0;
        _PDCLIB_bigint_arith_t d = 0;

        for ( i = 0; i < s; ++i )
        {
            t += (_PDCLIB_bigint_arith_t)divisor->data[i] * quotient;
            d = (_PDCLIB_bigint_arith_t)dividend->data[i] - ( t & _PDCLIB_BIGINT_DIGIT_MAX ) - d;

            dividend->data[i] = d & _PDCLIB_BIGINT_DIGIT_MAX;
            t >>= _PDCLIB_BIGINT_DIGIT_BITS;
            d >>= _PDCLIB_BIGINT_DIGIT_BITS;
            d &= 1;
        }
    }

    /* dividend might have leading zero digits here,
       but that does not matter.
    */
    if ( _PDCLIB_bigint_cmp( dividend, divisor ) > 0 )
    {
        /* quotient was too small, substract divisor once more. */
        _PDCLIB_bigint_arith_d = 0;
        ++quotient;

        for ( i = 0; i < s; ++i )
        {
            d = (_PDCLIB_bigint_arith_t)dividend->data[i] - divisor->data[i] - d;
            dividend->data[i] = d & _PDCLIB_BIGINT_DIGIT_MAX;
            d >>= _PDCLIB_BIGINT_DIGIT_BITS;
            d &= 1;
        }
    }

    /* size down dividend if it has leading zero digits */
    while ( dividend->size > 0 && dividend->data[ dividend->size - 1 ] == 0 )
    {
        --dividend->size;
    }

    return quotient;
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
