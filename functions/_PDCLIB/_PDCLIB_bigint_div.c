/* _PDCLIB_bigint_div( _PDCLIB_bigint_t *, _PDCLIB_bigint_t const *, _PDCLIB_bigint_t const * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

/* This implementation is based on code published on the companion website
   to the book Hacker's Delight by Henry Warren: www.hackersdelight.org.

   http://hackersdelight.org/hdcodetxt/divmnu.c.txt
   http://hackersdelight.org/hdcodetxt/divmnu64.c.txt

   http://www.hackersdelight.org/permissions.htm reads:

   You are free to use, copy, and distribute any of the code on this web
   site, whether modified by you or not. You need not give attribution.
   This includes the algorithms (some of which appear in Hacker's Delight),
   the Hacker's Assistant, and any code submitted by readers. Submitters
   implicitly agree to this.
*/

/* This is a fairly precise implementation of Knuth's Algorithm D. */

_PDCLIB_bigint_t * _PDCLIB_bigint_div( _PDCLIB_bigint_t * _PDCLIB_restrict result, _PDCLIB_bigint_t const * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs )
{
    _PDCLIB_bigint_t lnorm, rnorm;
    int i;

    if ( rhs->size == 0 || ( ( rhs->size == 1 ) && ( rhs->data[ 0 ] == 0 ) ) )
    {
        // Division by zero
        return NULL;
    }

    if ( lhs->size == 0 || lhs->size < rhs->size )
    {
        // Result zero
        _PDCLIB_bigint32( result, 0 );
        return result;
    }

    if ( rhs->size == 1 )
    {
        // One-digit divisor, simpler algorithm
        _PDCLIB_bigint( result, lhs );
        return _PDCLIB_bigint_div_dig( result, rhs->data[ 0 ] );
    }

    {
        /* Normalize by shifting rhs left just enough so that its high-order
           bit is on, and shift u left the same amount. We may have to append
           a high-order digit on the dividend; we do that unconditionally.
        */
        unsigned s = ( _PDCLIB_BIGINT_DIGIT_BITS - 1 ) - ( _PDCLIB_bigint_log2( rhs ) % _PDCLIB_BIGINT_DIGIT_BITS );

        _PDCLIB_bigint( &lnorm, lhs );
        _PDCLIB_bigint( &rnorm, rhs );

        lnorm.data[ lnorm.size ] = 0;  // TODO: Check capacity

        _PDCLIB_bigint_shl( &lnorm, s );
        _PDCLIB_bigint_shl( &rnorm, s );
    }

    for ( i = lhs->size - rhs->size; i >= 0; --i ) // Main loop
    {
        _PDCLIB_bigint_sarith_t t, k;
        unsigned j;

        // Compute estimate qhat of result->data[ i ].
        _PDCLIB_bigint_arith_t qhat = ( lnorm.data[ i + rhs->size ] * _PDCLIB_BIGINT_BASE + lnorm.data[ i + rhs->size - 1 ] ) / rnorm.data[ rhs->size - 1 ];
        _PDCLIB_bigint_arith_t rhat = ( lnorm.data[ i + rhs->size ] * _PDCLIB_BIGINT_BASE + lnorm.data[ i + rhs->size - 1 ] ) - qhat * rnorm.data[ rhs->size - 1 ];

again:

        if ( qhat >= _PDCLIB_BIGINT_BASE || qhat * rnorm.data[ rhs->size - 2 ] > _PDCLIB_BIGINT_BASE * rhat + lnorm.data[ i + rhs->size - 2 ] )
        {
            qhat = qhat - 1;
            rhat = rhat + rnorm.data[ rhs->size - 1 ];

            if ( rhat < _PDCLIB_BIGINT_BASE )
            {
                goto again;
            }
        }

        // Multiply and subtract.
        k = 0;

        for ( j = 0; j < rhs->size; ++j )
        {
            _PDCLIB_bigint_arith_t p = qhat * rnorm.data[ j ];
            t = lnorm.data[ j + i ] - k - ( p & _PDCLIB_BIGINT_DIGIT_MAX );
            lnorm.data[ j + i ] = t;
            k = ( p >> _PDCLIB_BIGINT_DIGIT_BITS ) - ( t >> _PDCLIB_BIGINT_DIGIT_BITS );
        }

        t = lnorm.data[ i + rhs->size ] - k;
        lnorm.data[ i + rhs->size ] = t;

        result->data[ i ] = qhat; // Store quotient digit.

        if ( t < 0 ) // If we subtracted too much,
        {
            // add back.
            result->data[ i ] = result->data[ i ] - 1;
            k = 0;

            for ( j = 0; j < rhs->size; ++j )
            {
                t = ( _PDCLIB_bigint_arith_t )lnorm.data[ j + i ] + rnorm.data[ j ] + k;
                lnorm.data[ j + i ] = t;
                k = t >> _PDCLIB_BIGINT_DIGIT_BITS;
            }

            lnorm.data[ i + rhs->size ] = lnorm.data[ i + rhs->size ] + k;
        }
    }

    result->size = lhs->size - rhs->size + 1;

    while ( result->size > 0 && result->data[ result->size - 1 ] == 0 )
    {
        --result->size;
    }

    return result;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#define _x8000 ( 1u << ( _PDCLIB_BIGINT_DIGIT_BITS - 1 ) )
#define _x4000 ( 1u << ( _PDCLIB_BIGINT_DIGIT_BITS - 2 ) )
#define _x2000 ( 1u << ( _PDCLIB_BIGINT_DIGIT_BITS - 3 ) )

#define _xFFFF ( (_PDCLIB_bigint_digit_t)-1 )

#define _x7FFF ( _xFFFF >> 1 )
#define _x3FFF ( _xFFFF >> 2 )

#define _x4001 ( _x4000 + 1 )
#define _x5555 ( _xFFFF / 3 )
#define _xFFF8 ( _xFFFF - 7 )
#define _xFFFE ( _xFFFF - 1 )

int main( void )
{
#ifndef REGTEST
    static _PDCLIB_bigint_t test2[] =
    {
        { { 3 }, 1 },                      { { 0 }, 0 },                 { { 0 }, _PDCLIB_BIGINT_DIGITS },    // Division by zero
        { { 3 }, 1 },                      { { 0 }, 1 },                 { { 0 }, _PDCLIB_BIGINT_DIGITS },    // Division by zero
        { { 7 }, 1 },                      { { 1, 3 }, 2 },              { { 0 }, 0 },
        { { 3 }, 1 },                      { { 2 }, 1 },                 { { 1 }, 1 },
        { { 3 }, 1 },                      { { 3 }, 1 },                 { { 1 }, 1 },
        { { 3 }, 1 },                      { { 4 }, 1 },                 { { 0 }, 0 },
        { { 0 }, 0 },                      { { _xFFFF }, 1 },            { { 0 }, 0 },
        { { _xFFFF }, 1 },                 { { 1 }, 1 },                 { { _xFFFF }, 1 },
        { { _xFFFF }, 1 },                 { { _xFFFF }, 1 },            { { 1 }, 1 },
        { { _xFFFF }, 1 },                 { { 3 }, 1 },                 { { _x5555 }, 1 },
        { { _xFFFF, _xFFFF }, 2 },         { { 1 }, 1 },                 { { _xFFFF, _xFFFF }, 2 },
        { { _xFFFF, _xFFFF }, 2 },         { { _xFFFF }, 1 },            { { 1, 1 }, 2 },
        { { _xFFFF, _xFFFE }, 2 },         { { _xFFFF }, 1 },            { { _xFFFF }, 1 },
        { { 0 }, 0 },                      { { 0, 1 }, 2 },              { { 0 }, 0 },
        { { 0, 7 }, 2 },                   { { 0, 3 }, 2 },              { { 2 }, 1 },
        { { 5, 7 }, 2 },                   { { 0, 3 }, 2 },              { { 2 }, 1 },
        { { 0, 6 }, 2 },                   { { 0, 2 }, 2 },              { { 3 }, 1 },
        { { _x8000 }, 1 },                 { { _x4001 }, 1 },            { { 1 }, 1 },
        { { 0, _x8000 }, 2 },              { { _x4001 }, 1 },            { { _xFFF8, 1 }, 2 },
        { { 0, _x8000 }, 2 },              { { 1, _x4000 }, 2 },         { { 1 }, 1 },
        { { 1, _x8000 }, 2 },              { { 2, _x4000 }, 2 },         { { 1 }, 1 },
        { { _x4000, _x5555 }, 2 },         { { _x4000, _x5555 }, 2 },    { { 1 }, 1 },
        { { _x4001, _x5555 }, 2 },         { { _x4000, _x5555 }, 2 },    { { 1 }, 1 },
        { { _x3FFF, _x5555 }, 2 },         { { _x4000, _x5555 }, 2 },    { { 0 }, 0 },
        { { _xFFFF, _xFFFF }, 2 },         { { _xFFFF, _xFFFF }, 2 },    { { 1 }, 1 },
        { { _xFFFF, _xFFFF }, 2 },         { { 0, 1 }, 2 },              { { _xFFFF }, 1 },
        { { _x5555, _x5555, _x2000 }, 3 }, { { 0, 1 }, 2 },              { { _x5555, _x2000 }, 2 },
        { { 0, _xFFFE, _x8000 }, 3 },      { { _xFFFF, _x8000 }, 2 },    { { _xFFFF }, 1 },
        { { 3, 0, _x8000 }, 3 },           { { 1, 0, _x2000 }, 3 },      { { 3 }, 1 },
        { { 0, 0, _x8000, _x7FFF }, 4 },   { { 1, 0, _x8000 }, 3 },      { { _xFFFE }, 1 },
        { { 0, _xFFFE, 0, _x8000 }, 4 },   { { _xFFFF, 0, _x8000 }, 3 }, { { _xFFFF }, 1 }
    };

    _PDCLIB_bigint_t lhs, rhs, exp, res;
    unsigned i = 0;

    while ( i < ( sizeof( test2 ) / sizeof( _PDCLIB_bigint_t ) ) )
    {
        _PDCLIB_bigint( &lhs, &test2[ i++ ] );
        _PDCLIB_bigint( &rhs, &test2[ i++ ] );
        _PDCLIB_bigint( &exp, &test2[ i++ ] );

        if ( _PDCLIB_bigint_div( &res, &lhs, &rhs ) == NULL )
        {
            TESTCASE( exp.size == _PDCLIB_BIGINT_DIGITS );
        }
        else
        {
            TESTCASE( _PDCLIB_bigint_cmp( &res, &exp ) == 0 );
        }
    }

#endif
    return TEST_RESULTS;
}

#endif
