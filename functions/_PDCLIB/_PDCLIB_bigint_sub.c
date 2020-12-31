/* _PDCLIB_bigint_sub( _PDCLIB_bigint_t *, _PDCLIB_bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

_PDCLIB_bigint_t * _PDCLIB_bigint_sub( _PDCLIB_bigint_t * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs )
{
    size_t i;
    unsigned carry = 0;

    assert( _PDCLIB_bigint_cmp( lhs, rhs ) >= 0 );

    for ( i = 0; i < rhs->size; ++i )
    {
        int newcarry;

        if ( ( newcarry = ( lhs->data[i] < rhs->data[i] ) || ( carry && ( lhs->data[i] == rhs->data[i] ) ) ) )
        {
            lhs->data[i] += ( _PDCLIB_BIGINT_DIGIT_MAX - rhs->data[i] ) + ( 1 - carry );
        }
        else
        {
            lhs->data[i] -= ( rhs->data[i] + carry );
        }

        carry = newcarry;
    }

    for ( ; carry; ++i )
    {
        if ( lhs->data[i] > 0 )
        {
            --lhs->data[i];
            carry = 0;
        }
        else
        {
            lhs->data[i] = _PDCLIB_BIGINT_DIGIT_MAX;
        }
    }

    while ( lhs->size > 0 && lhs->data[ lhs->size - 1 ] == 0 )
    {
        --lhs->size;
    }

    return lhs;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdint.h>

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t lhs, rhs, res;
    _PDCLIB_bigint_digit_t NUL = 0;
    _PDCLIB_bigint_digit_t SML = _PDCLIB_BIGINT_DIGIT_MAX / 2;
    _PDCLIB_bigint_digit_t MID = _PDCLIB_BIGINT_DIGIT_MAX / 2 + 1;
    _PDCLIB_bigint_digit_t LRG = _PDCLIB_BIGINT_DIGIT_MAX / 2 + 2;
    _PDCLIB_bigint_digit_t MAX = _PDCLIB_BIGINT_DIGIT_MAX;

    /* Building a large number substraction that covers all kinds of
       cases. From rightmost digit to left:
    */
    /* carry 0, lhs '9', rhs '5', newcarry 0, result '4' */
    lhs.data[0] = MAX; rhs.data[0] = MID; res.data[0] = SML;
    /* carry 0, lhs '0', rhs '0', newcarry 0, result '0' */
    lhs.data[1] = NUL; rhs.data[1] = NUL; res.data[1] = NUL;
    /* carry 0, lhs '0', rhs '6', newcarry 1, result '4' */
    lhs.data[2] = NUL; rhs.data[2] = LRG; res.data[2] = SML;
    /* carry 1, lhs '0', rhs '0', newcarry 1, result '9' */
    lhs.data[3] = NUL; rhs.data[3] = NUL; res.data[3] = MAX;
    /* carry 1, lhs '0', rhs '9', newcarry 1, result '0' */
    lhs.data[4] = NUL; rhs.data[4] = MAX; res.data[4] = NUL;
    /* carry 1, lhs '0', rhs '5', newcarry 1, result '4' */
    lhs.data[5] = NUL; rhs.data[5] = MID; res.data[5] = SML;
    /* carry 1, lhs '4', rhs '9', newcarry 1, result '4' */
    lhs.data[6] = SML; rhs.data[6] = MAX; res.data[6] = SML;
    /* carry 1, lhs '5', rhs '5', newcarry 1, result '9' */
    lhs.data[7] = MID; rhs.data[7] = MID; res.data[7] = MAX;
    /* carry 1, lhs '6', rhs '5', newcarry 0, result '0' */
    lhs.data[8] = LRG; rhs.data[8] = MID; res.data[8] = NUL;
    /* carry 0, lhs '5', rhs '9', newcarry 1, result '6' */
    lhs.data[9] = MID; rhs.data[9] = MAX; res.data[9] = LRG;
    /* carry 1, lhs '5', rhs '0', newcarry 0, result '4' */
    lhs.data[10] = MID; rhs.data[10] = NUL; res.data[10] = SML;
    /* carry 0, lhs '5', rhs '6', newcarry 1, result '9' */
    lhs.data[11] = MID; rhs.data[11] = LRG; res.data[11] = MAX;
    /* carry 1, lhs '6', rhs ---, newcarry 0, result '5' */
    lhs.data[12] = LRG; res.data[12] = MID;
    lhs.size = 13; rhs.size = 12; res.size = 13;
    TESTCASE( _PDCLIB_bigint_cmp( _PDCLIB_bigint_sub( &lhs, &rhs ), &res ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
