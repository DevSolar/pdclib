/* _PDCLIB_bigint_div( bigint_t *, bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <assert.h>

unsigned _PDCLIB_bigint_div( _PDCLIB_bigint_t * dividend, _PDCLIB_bigint_t const * divisor )
{
    _PDCLIB_bigint_digit_t quotient;
    _PDCLIB_size_t s = dividend->size;
    _PDCLIB_size_t i;

    assert( divisor->size > 0 );
    assert( s <= divisor->size );
    assert( divisor->data[ divisor->size - 1 ] < _PDCLIB_BIGINT_DIGIT_MAX );

    if ( s < divisor->size || dividend->data[ s - 1 ] < divisor->data[ s - 1 ])
    {
        return 0;
    }

    /* With dividend truncated, and divisor + 1,
       this quotient might be one short of correct.
    */
    quotient = dividend->data[ s - 1 ] / ( divisor->data[ s - 1 ] + 1 );

    if ( quotient > 0 )
    {
        /* dividend = dividend - (divisor * quotient) */
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
       but that does not matter for the compare or
       the subsequent substraction.
    */
    if ( _PDCLIB_bigint_cmp( dividend, divisor ) >= 0 )
    {
        /* quotient was too small, substract divisor once more. */
        _PDCLIB_bigint_arith_t d = 0;
        ++quotient;

        for ( i = 0; i < s; ++i )
        {
            d = (_PDCLIB_bigint_arith_t)dividend->data[i] - divisor->data[i] - d;
            dividend->data[i] = d & _PDCLIB_BIGINT_DIGIT_MAX;
            d >>= _PDCLIB_BIGINT_DIGIT_BITS;
            d &= 1;
        }
    }

    /* size down dividend if it has leading zero digits. */
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
    _PDCLIB_bigint_t dividend;
    _PDCLIB_bigint_t divisor;
    _PDCLIB_bigint_t testdata[] =
    {
        { 1, { 0x1234 } },
        { 2, { 0x2345, 0x0001 } },
        { 1, { 0x4000 } },
        { 1, { 0x3FFF } },
        { 1, { 0x0001 } },
        { 1, { _PDCLIB_BIGINT_DIGIT_MAX } },
        { 1, { 0xFFF9 } },
        { 1, { 0x1C71 } }
    };

    /* dividend < divisor */
    _PDCLIB_bigint_from_bigint( &dividend, &testdata[0] );
    _PDCLIB_bigint_from_bigint( &divisor, &testdata[1] );
    TESTCASE( _PDCLIB_bigint_div( &dividend, &divisor ) == 0 );
    TESTCASE( _PDCLIB_bigint_cmp( &dividend, &testdata[0] ) == 0 );

    _PDCLIB_bigint_from_bigint( &dividend, &testdata[3] );
    _PDCLIB_bigint_from_bigint( &divisor, &testdata[2] );
    TESTCASE( _PDCLIB_bigint_div( &dividend, &divisor ) == 0 );
    TESTCASE( _PDCLIB_bigint_cmp( &dividend, &testdata[3] ) == 0 );

    /* dividend = divisor + 1 */
    _PDCLIB_bigint_from_bigint( &dividend, &testdata[2] );
    _PDCLIB_bigint_from_bigint( &divisor, &testdata[3] );
    TESTCASE( _PDCLIB_bigint_div( &dividend, &divisor ) == 1 );
    TESTCASE( _PDCLIB_bigint_cmp( &dividend, &testdata[4] ) == 0 );

    /* dividend = divisor * 9 */
    _PDCLIB_bigint_from_bigint( &dividend, &testdata[6] );
    _PDCLIB_bigint_from_bigint( &divisor, &testdata[7] );
    TESTCASE( _PDCLIB_bigint_div( &dividend, &divisor ) == 9 );
    TESTCASE( dividend.size == 0 );

    /* dividend = divisor * 9 + rem */
    _PDCLIB_bigint_from_bigint( &dividend, &testdata[5] );
    _PDCLIB_bigint_from_digit( &divisor, testdata[5].data[0] / 9 );
    TESTCASE( _PDCLIB_bigint_div( &dividend, &divisor ) == 9 );
    TESTCASE( dividend.data[0] == ( testdata[5].data[0] % 9 ) );
#endif

    return TEST_RESULTS;
}

#endif
