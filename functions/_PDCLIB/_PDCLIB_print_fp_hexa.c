/* _PDCLIB_print_float

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <stdlib.h>

int dprintf( int, char const *, ... );

static void _PDCLIB_print_fp_hexa_mant( _PDCLIB_bigint_t * fp, int prec, int mant_dig, int log2, char * buffer )
{
    size_t i;

    if ( ( mant_dig % 4 ) > 0 )
    {
        int shift = 4 - ( mant_dig % 4 );
        _PDCLIB_bigint_shl( fp, shift );
        mant_dig += shift;
        log2 += shift;
    }

    if ( mant_dig > log2 )
    {
        *buffer++ = '0';

        for ( i = 0; i < ( mant_dig - log2 - 1 ) / 4; ++i )
        {
            *buffer++ = '0';
        }
    }

    for ( i = log2 / 4 + 1; i > 0; --i )
    {
        div_t dv = div( i - 1, _PDCLIB_BIGINT_DIGIT_BITS / 4 );
        *buffer++ = _PDCLIB_digits[ ( fp->data[ dv.quot ] >> ( dv.rem * 4 ) ) & 0xfu ];
    }

    *buffer = '\0';
}

void _PDCLIB_print_fp_hexa( _PDCLIB_bigint_t * fp,
                                struct _PDCLIB_status_t * status,
                                char sign )
{
    _PDCLIB_static_assert( _PDCLIB_FLT_RADIX == 2, "Assuming 2-based Floating Point" );

    /* lowercase or uppercase digits */
    char const * digits;
    /* number of mantissa bits */
    size_t mant_dig = ( ( status->flags & E_ldouble ) ? _PDCLIB_LDBL_MANT_DIG : _PDCLIB_DBL_MANT_DIG ) - 1;
    int state = (int)fp->data[ fp->size ];
    int exp = (int)fp->data[ fp->size + 1 ];
    char exponent[6];
    size_t i;

    /* prefix */
    PUT( '0' );
    status->current++;

    if ( status->flags & E_lower )
    {
        PUT( 'x' );
        status->current++;
        digits = _PDCLIB_digits;
    }
    else
    {
        PUT( 'X' );
        status->current++;
        digits = _PDCLIB_Xdigits;
    }

    if ( ( mant_dig % 4 ) > 0 )
    {
        _PDCLIB_bigint_shl( fp, mant_dig % 4 );
    }

    if ( state & 1<<1 )
    {
        /* subnormal */
        size_t log2 = _PDCLIB_bigint_log2( fp );

        PUT( '0' );
        status->current++;
        PUT( '.' );
        status->current++;

        for ( i = 0; i < ( mant_dig - log2 ) / 4; ++i )
        {
            PUT( '0' );
            status->current++;
        }

        for ( i = log2 / 4; i > 0; --i )
        {
            div_t dv = div( i - 1, _PDCLIB_BIGINT_DIGIT_BITS / 4 );
            PUT( digits[ ( fp->data[ dv.quot ] >> ( dv.rem * 4 ) ) & 0xfu ] );
            status->current++;
        }
    }
    else
    {
        /* normal */
        PUT( '1' );
        PUT( '.' );
        status->current += 2;

        for ( i = mant_dig / 4; i > 0; --i )
        {
            div_t dv = div( i - 1, _PDCLIB_BIGINT_DIGIT_BITS / 4 );
            PUT( digits[ ( fp->data[ dv.quot ] >> ( dv.rem * 4 ) ) & 0xfu ] );
            status->current += 2;
        }
    }

    if ( status->flags & E_lower )
    {
        PUT( 'p' );
    }
    else
    {
        PUT( 'P' );
    }

    if ( exp < 0 )
    {
        PUT( '-' );
        exp *= -1;
    }
    else
    {
        PUT( '+' );
    }
    status->current += 2;

    for ( i = 0; exp > 0; ++i )
    {
        /* Putting exponent digits in reverse order */
        div_t dv = div( exp, 10 );
        exponent[i] = digits[ dv.rem ];
        exp = dv.quot;
    }

    for ( ; i > 0; --i )
    {
        PUT( exponent[i - 1] );
    }
}

#if 0

#define OP -
static void _PDCLIB_print_fp_hexa( _PDCLIB_bigint_t * fp,
                                struct _PDCLIB_status_t * status )
{
    char const * digits = ( status->flags & E_lower ) ? _PDCLIB_digits : _PDCLIB_Xdigits;

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
            exponent[e] = digits[ d.rem ];
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

    PUT( digits[ mantissa[0] ] );

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
        PUT( digits[ mantissa[i] ] );
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

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( int argc, char * argv[] )
{
    /* Tested by _PDCLIB_print testdriver */
#ifndef REGTEST
    _PDCLIB_bigint_t bigint;
    char buffer[ 100 ];
    _PDCLIB_bigint_from_dbl( &bigint, 31.4 );
    _PDCLIB_print_fp_hexa_mant( &bigint, 0, _PDCLIB_DBL_MANT_DIG - 1, _PDCLIB_bigint_log2( &bigint ), buffer );
    TESTCASE( strcmp( buffer, "1f666666666666" ) == 0 );
    _PDCLIB_bigint_from_dbl( &bigint, _PDCLIB_DBL_MIN );
    _PDCLIB_print_fp_hexa_mant( &bigint, 0, _PDCLIB_DBL_MANT_DIG - 1, _PDCLIB_bigint_log2( &bigint ), buffer );
    TESTCASE( strcmp( buffer, "10000000000000" ) == 0 );
    _PDCLIB_bigint_from_dbl( &bigint, _PDCLIB_DBL_MIN / 2 );
    _PDCLIB_print_fp_hexa_mant( &bigint, 0, _PDCLIB_DBL_MANT_DIG - 1, _PDCLIB_bigint_log2( &bigint ), buffer );
    TESTCASE( strcmp( buffer, "08000000000000" ) == 0 );
    _PDCLIB_bigint_from_dbl( &bigint, _PDCLIB_DBL_MIN / 4 );
    _PDCLIB_print_fp_hexa_mant( &bigint, 0, _PDCLIB_DBL_MANT_DIG - 1, _PDCLIB_bigint_log2( &bigint ), buffer );
    TESTCASE( strcmp( buffer, "04000000000000" ) == 0 );
    _PDCLIB_bigint_from_dbl( &bigint, _PDCLIB_DBL_MIN / 8 );
    _PDCLIB_print_fp_hexa_mant( &bigint, 0, _PDCLIB_DBL_MANT_DIG - 1, _PDCLIB_bigint_log2( &bigint ), buffer );
    TESTCASE( strcmp( buffer, "02000000000000" ) == 0 );
    _PDCLIB_bigint_from_dbl( &bigint, _PDCLIB_DBL_MIN / 16 );
    _PDCLIB_print_fp_hexa_mant( &bigint, 0, _PDCLIB_DBL_MANT_DIG - 1, _PDCLIB_bigint_log2( &bigint ), buffer );
    TESTCASE( strcmp( buffer, "01000000000000" ) == 0 );
    _PDCLIB_bigint_from_dbl( &bigint, _PDCLIB_DBL_MIN / 256 );
    _PDCLIB_print_fp_hexa_mant( &bigint, 0, _PDCLIB_DBL_MANT_DIG - 1, _PDCLIB_bigint_log2( &bigint ), buffer );
    TESTCASE( strcmp( buffer, "00100000000000" ) == 0 );
    _PDCLIB_bigint_from_ldbl( &bigint, 31.4 );
    _PDCLIB_print_fp_hexa_mant( &bigint, 0, _PDCLIB_LDBL_MANT_DIG - 1, _PDCLIB_bigint_log2( &bigint ), buffer );
    TESTCASE( strcmp( buffer, "1f666666666666000" ) == 0 );
    _PDCLIB_bigint_from_ldbl( &bigint, _PDCLIB_LDBL_MIN );
    _PDCLIB_print_fp_hexa_mant( &bigint, 0, _PDCLIB_LDBL_MANT_DIG - 1, _PDCLIB_bigint_log2( &bigint ), buffer );
    TESTCASE( strcmp( buffer, "10000000000000000" ) == 0 );
    _PDCLIB_bigint_from_ldbl( &bigint, _PDCLIB_LDBL_MIN / 2 );
    _PDCLIB_print_fp_hexa_mant( &bigint, 0, _PDCLIB_LDBL_MANT_DIG - 1, _PDCLIB_bigint_log2( &bigint ), buffer );
    TESTCASE( strcmp( buffer, "08000000000000000" ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
