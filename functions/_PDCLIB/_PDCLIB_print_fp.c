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

#if 0

#define OP -
/* dec:      1 - normalized, 0 - subnormal
   mant:     MSB of the mantissa
   mant_dig: base FLT_RADIX digits in the mantissa, including the decimal
*/
static void _PDCLIB_print_hexa( _PDCLIB_bigint_t * fp,
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

    int index_offset = 0;

    _PDCLIB_static_assert( _PDCLIB_FLT_RADIX == 2, "Assuming 2-based FP" );
    _PDCLIB_static_assert( _PDCLIB_CHAR_BIT == 8, "Assuming 8-bit bytes" );

    /* Mantissa */
    /* -------- */

    /* Handle the most significant byte (which might need masking) */
    excess_bits = ( mant_dig - 1 ) % 8;

    if ( excess_bits > 0 )
    {
        value = *mant & ( ( 1 << excess_bits ) - 1 );

        if ( excess_bits >= 4 )
        {
            mantissa[1] = value & 0x0f;
            value >>= 4;
            excess_bits -= 4;
            ++m;
        }

        index_offset = 1;
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
        value = *(mant OP ( ( m / 2 ) + index_offset ) );
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

#endif

static void _PDCLIB_print_inf_nan( _PDCLIB_bigint_t * fp,
                                   struct _PDCLIB_status_t * status,
                                   char sign )
{
    char const * s = ( status->flags & E_lower )
                     ? ( ( fp->size > 0 ) ? "nan" : "inf" )
                     : ( ( fp->size > 0 ) ? "NAN" : "INF" );

    /* "Count" the characters before actually printing them */
    /* This allows us to pad properly if necessary */
    status->current = ( sign == '\0' ) ? 3 : 4;

    /* Pad if necessary */
    if ( ! ( status->flags & E_minus ) )
    {
        while ( status->current < status->width )
        {
            PUT( ' ' );
            ++status->current;
        }
    }

    /* Output -- we already counted the characters above */
    if ( sign != '\0' )
    {
        PUT( sign );
    }

    while ( *s )
    {
        PUT( *s++ );
    }
}

void _PDCLIB_print_fp( _PDCLIB_bigint_t * fp,
                       struct _PDCLIB_status_t * status )
{
    char sign;

    /* Turning sign bit into sign character. */
    if ( fp->data[ fp->size + 1 ] > 0 )
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

    if ( fp->data[ fp->size ] == _PDCLIB_BIGINT_DIGIT_MAX )
    {
        _PDCLIB_print_inf_nan( fp, status, sign );
        return;
    }

    switch ( status->flags & ( E_decimal | E_exponent | E_generic | E_hexa ) )
    {
        case E_hexa:
            _PDCLIB_print_hexa( fp, status, sign );
            break;
        default:
            break;
    }
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
