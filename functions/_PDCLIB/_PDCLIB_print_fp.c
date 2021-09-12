/* _PDCLIB_print_float

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "pdclib/_PDCLIB_print.h"

#define OP -
/* dec:      1 - normalized, 0 - subnormal
   mant:     MSB of the mantissa
   mant_dig: base FLT_RADIX digits in the mantissa, including the decimal
*/
static void _PDCLIB_print_hexa( int sign,
                                int exp,
                                int dec,
                                unsigned char const * mant,
                                size_t mant_dig,
                                struct _PDCLIB_status_t * status )
{
    size_t excess_bits;
    char value;

    unsigned char mantissa[ _PDCLIB_LDBL_MANT_DIG / 4 + 2 ] = { 0 };
    size_t m = 0;

    char exponent[ 7 ];
    size_t e = 0;

    size_t i;

    char const * digit_chars = ( status->flags & E_lower ) ? _PDCLIB_digits : _PDCLIB_Xdigits;

    _PDCLIB_static_assert( _PDCLIB_FLT_RADIX == 2, "Assuming 2-based FP" );
    _PDCLIB_static_assert( _PDCLIB_CHAR_BIT == 8, "Assuming 8-bit bytes" );

    /* Mantissa */
    /* -------- */

    /* Handle the most significant byte (which might need masking) */
    excess_bits = ( mant_dig - 1 ) % 8;
    value = *mant & ( ( 1 << excess_bits ) - 1 );

    if ( excess_bits >= 4 )
    {
        mantissa[1] = value & 0x0f;
        value >>= 4;
        excess_bits -= 4;
        ++m;
    }

    mantissa[0] = ( dec << excess_bits ) | ( value & ( ( 1 << excess_bits ) - 1 ) );

    /* Now handle the remaining bytes. */
    /* This is doing a little trick: m is the highest valid index
       (or a count of *fractional* digits, if you like), not a count
       of elements (0..1, not 1..2), so it can double as an index
       into the mant[] array (when divided by 2).
    */
    while ( m < ( ( mant_dig + 3 ) / 4 - 1 ) )
    {
        value = *(mant OP ( ( m / 2 ) + 1 ) );
        mantissa[++m] = ( value & 0xf0 ) >> 4;
        mantissa[++m] = ( value & 0x0f );
    }

    /* Roll back trailing zeroes */
    while ( m > 0 && mantissa[m] == 0 )
    {
        --m;
    }

    /* Exponent */
    /* -------- */

    exp -= excess_bits;

    if ( ( m == 0 && dec == 0 ) || exp == 0 )
    {
        /* All zero */
        exponent[0] = '+';
        exponent[1] = '0';
        e = 2;
    }
    else
    {
        if ( dec == 0 )
        {
            /* Subnormal */
            ++exp;
        }

        if ( exp >= 0 )
        {
            exponent[0] = '+';
        }
        else
        {
            exponent[0] = '-';
            exp *= -1;
        }

        for ( e = 1; exp > 0; ++e )
        {
            div_t d = div( exp, 10 );
            exponent[e] = digit_chars[ d.rem ];
            exp = d.quot;
        }
    }

    exponent[e] = '\0';

    /* Rounding */
    /* -------- */

    if ( ( status->prec >= 0 ) && ( m > (size_t)status->prec ) )
    {
        i = status->prec;

        if ( ( mantissa[ i + 1 ] > 8 ) || 
             ( ( mantissa[ i + 1 ] == 8 ) &&
               ( ( m >= i + 2 ) || ( mantissa[ i ] % 2 ) )
             )
           )
        {
            while ( ( ++mantissa[ i ] ) > 0xf )
            {
                mantissa[ i-- ] = 0;
            }
        }

        m = i;
    }

    /* Padding */
    /* ------- */

    status->current = m + 4 + ( sign != '\0' ) + ( ( m > 0 ) || ( status->prec > 0 ) || ( status->flags & E_alt ) ) + e;

    if ( ! ( status->flags & ( E_zero | E_minus ) ) )
    {
        for ( i = status->current; i < status->width; ++i )
        {
            PUT( ' ' );
        }
    }

    if ( sign != '\0' )
    {
        PUT( sign );
    }

    /* Output */
    /* ------ */

    PUT( '0' );
    PUT( ( status->flags & E_lower ) ? 'x' : 'X' );

    PUT( digit_chars[ mantissa[0] ] );

    if ( ( ( m > 0 ) && ( status->prec != 0 ) ) || ( status->prec > 0 ) || ( status->flags & E_alt ) )
    {
        PUT( '.' );
    }

    if ( ( status->flags & E_zero ) && ! ( status->flags & E_minus ) )
    {
        for ( i = status->current; i < status->width; ++i )
        {
            PUT( '0' );
        }
    }

    for ( i = 1; i <= m; ++i )
    {
        PUT( digit_chars[ mantissa[i] ] );
    }

    while ( (int)i <= status->prec )
    {
        PUT( '0' );
        ++i;
    }

    PUT( ( status->flags & E_lower ) ? 'p' : 'P' );
    PUT( exponent[0] );

    for ( i = e - 1; i > 0; --i )
    {
        PUT( exponent[i] );
    }
}

/* dec:      1 - normalized, 0 - subnormal
   exp:      INT_MAX - infinity, INT_MIN - Not a Number
   mant:     MSB of the mantissa
   mant_dig: base FLT_RADIX digits in the mantissa, including the decimal
*/
static void _PDCLIB_print_fp( int sign,
                              int exp,
                              int dec,
                              unsigned char const * mant,
                              size_t mant_dig,
                              struct _PDCLIB_status_t * status )
{
    /* Turning sign bit into sign character. */
    if ( sign )
    {
        sign = '-';
    }
    else if ( status->flags & E_plus )
    {
        sign = '+';
    }
    else if ( status->flags & E_space )
    {
        sign = ' ';
    }
    else
    {
        sign = '\0';
    }

    if ( exp == INT_MIN || exp == INT_MAX )
    {
        /* "nan" / "inf" */
        char const * s = ( status->flags & E_lower )
                         ? ( ( exp == INT_MIN ) ? "nan" : "inf" )
                         : ( ( exp == INT_MIN ) ? "NAN" : "INF" );

        status->current = ( sign == '\0' ) ? 3 : 4;

        if ( ! ( status->flags & E_minus ) )
        {
            while ( status->current < status->width )
            {
                PUT( ' ' );
                ++status->current;
            }
        }

        if ( sign != '\0' )
        {
            PUT( sign );
        }

        while ( *s )
        {
            PUT( *s++ );
        }

        return;
    }

    switch ( status->flags & ( E_decimal | E_exponent | E_generic | E_hexa ) )
    {
        case E_hexa:
            _PDCLIB_print_hexa( sign, exp, dec, mant, mant_dig, status );
            break;
        case E_decimal:
        case E_exponent:
        case E_generic:
        default:
            break;
    }
}

void _PDCLIB_print_double( double value, struct _PDCLIB_status_t * status )
{
    unsigned char bytes[ sizeof( double ) ];
    int exp;
    memcpy( bytes, &value, sizeof( double ) );
    exp = _PDCLIB_DBL_EXP( bytes ) - _PDCLIB_DBL_BIAS;

    if ( exp == _PDCLIB_DBL_MAX_EXP )
    {
        /*                           NAN       INF */
        exp = ( value != value ) ? INT_MIN : INT_MAX;
    }

    _PDCLIB_print_fp( _PDCLIB_DBL_SIGN( bytes ),
                      exp,
                      _PDCLIB_DBL_DEC( bytes ),
                      _PDCLIB_DBL_MANT_START( bytes ),
                      _PDCLIB_DBL_MANT_DIG,
                      status );
}

void _PDCLIB_print_ldouble( long double value, struct _PDCLIB_status_t * status )
{
    unsigned char bytes[ sizeof( long double ) ];
    int exp;
    memcpy( bytes, &value, sizeof( long double ) );
    exp = _PDCLIB_LDBL_EXP( bytes ) - _PDCLIB_LDBL_BIAS;

    if ( exp == _PDCLIB_LDBL_MAX_EXP )
    {
        /*                           NAN       INF */
        exp = ( value != value ) ? INT_MIN : INT_MAX;
    }

    _PDCLIB_print_fp( _PDCLIB_LDBL_SIGN( bytes ),
                      exp,
                      _PDCLIB_LDBL_DEC( bytes ),
                      _PDCLIB_LDBL_MANT_START( bytes ),
                      _PDCLIB_LDBL_MANT_DIG,
                      status );
}

#endif

#ifdef TEST

#include <stdlib.h>

#include "_PDCLIB_test.h"

int main( int argc, char * argv[] )
{
    /* Tested by _PDCLIB_print testdriver */
    return TEST_RESULTS;
}

#endif
