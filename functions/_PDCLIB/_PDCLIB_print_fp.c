/* _PDCLIB_print_float

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "pdclib/_PDCLIB_print.h"

/* The 'mant' pointer arguments to the functions below always refer to
   the most significant byte of the mantissa. On little endian machines,
   this is the byte with the highest index, while on big endian machines
   it is the lowest. The purpose of the OP macro is to abstract the move
   from the most significant byte to the next.
*/
#if _PDCLIB_ENDIANESS == 1234
#define OP -
#elif _PDCLIB_ENDIANESS == 4321
#define OP +
#else
#error Unsupported endianess.
#endif

static void print_hexa( char sign, int exp, int dec, unsigned char * mant, size_t size, struct _PDCLIB_status_t * status )
{
    /* Array of hexadecimal digits, the 0th element being the decimal */
    size_t digits;
    size_t i;
    unsigned char digit[ _PDCLIB_LDBL_MANT_SIZE * 2 + 1 ] = { dec, 0 };

    /* Array holding the decimal exponent */
    size_t expdigits = 0;
    char exponent[ 6 ] = "+";

    /* Pointer to lowercase / uppercase digit array depending on flag */
    char const * digit_chars = ( status->flags & E_lower ) ? _PDCLIB_digits : _PDCLIB_Xdigits;
    char const * special_chars = ( status->flags & E_lower ) ? "xp" : "XP";

    /* Writing out the mantissa as a sequence of nibbles */
    for ( digits = 0; digits < size; ++digits )
    {
        unsigned char byte = *( mant OP digits );
        /* Remember that digit[0] holds the decimal, and that digit[] holds
           nibbles, not bytes.
        */
        digit[ digits * 2 + 1 ] = ( byte & 0xf0 ) >> 4;
        digit[ digits * 2 + 2 ] = ( byte & 0x0f );
    }

    /* Adjust digits for nibbles */
    digits *= 2;

    /* Ignore trailing zeroes, also make digits refer to fractional
       digits (i.e., total minus one) for later ease-of-use.
    */
    while ( ( --digits > 0 ) && ( digit[ digits ] == 0 ) )
    {
        /* EMPTY */
    }

    /* Precision smaller than number of digits requires rounding */
    if ( ( status->prec >= 0 ) && ( (size_t)status->prec < digits ) )
    {
        /* Round up for .51 through .99. Round-to-even for .5. */
        if ( ( digit[ status->prec + 1 ] > 5 ) || ( digits > (size_t)( status->prec + 1 ) )
          || ( digit[ status->prec ] % 2 ) )
        {
            ++digit[ status->prec ];
        }

        digits = status->prec;
    }

    /* Write out the exponent */
    if ( exp < 0 )
    {
        exponent[ 0 ] = '-';
        exp *= -1;
    }

    do
    {
        div_t d = div( exp, 10 );
        exponent[ ++expdigits ] = _PDCLIB_digits[ d.rem ];
        exp = d.quot;
    } while ( exp > 0 );

    status->current = ( status->prec > (int)digits ) ? (size_t)status->prec : digits;
    status->current = 5 + ( sign != '\0' ) + ( ( status->current > 0 ) || ( status->flags & E_alt ) ) + expdigits + status->current;

    if ( ! ( status->flags & ( E_zero | E_minus ) ) )
    {
        unsigned pad;

        for ( pad = status->current; pad < status->width; ++pad )
        {
            PUT( ' ' );
        }
    }

    if ( sign != '\0' )
    {
        PUT( sign );
    }

    PUT( '0' );
    PUT( special_chars[0] );

    if ( ( status->flags & E_zero ) && ! ( status->flags & E_minus ) )
    {
        unsigned pad;

        for ( pad = status->current; pad < status->width; ++pad )
        {
            PUT( '0' );
        }
    }

    PUT( digit_chars[ digit[0] ] );

    if ( ( digits > 0 ) || ( status->flags & E_alt ) )
    {
        PUT( '.' );
    }

    for ( i = 1; i <= digits; ++i )
    {
        PUT( digit_chars[ digit[ i ] ] );
    }

    while ( (int)i <= status->prec )
    {
        PUT( '0' );
        ++i;
    }

    PUT( special_chars[1] );
    PUT( exponent[0] );

    while ( expdigits > 0 )
    {
        PUT( exponent[ expdigits-- ] );
    }
}

static void print_fp( char sign, int exp, int dec, unsigned char * mant, size_t size, struct _PDCLIB_status_t * status )
{
    switch ( status->flags & ( E_decimal | E_exponent | E_generic | E_hexa ) )
    {
        case E_hexa:
            print_hexa( sign, exp, dec, mant, size, status );
            return;
        case E_decimal:
        case E_exponent:
        case E_generic:
        default:
            break;
    }
}

static void print_infnan_padding( char sign, struct _PDCLIB_status_t * status )
{
    status->current = ( sign != '\0' ) ? 4 : 3;

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
}

static void print_inf( char sign, struct _PDCLIB_status_t * status )
{
    print_infnan_padding( sign, status );

    if ( status->flags & E_lower )
    {
        PUT( 'i' );
        PUT( 'n' );
        PUT( 'f' );
    }
    else
    {
        PUT( 'I' );
        PUT( 'N' );
        PUT( 'F' );
    }
}

static void print_nan( char sign, struct _PDCLIB_status_t * status )
{
    print_infnan_padding( sign, status );

    if ( status->flags & E_lower )
    {
        PUT( 'n' );
        PUT( 'a' );
        PUT( 'n' );
    }
    else
    {
        PUT( 'N' );
        PUT( 'A' );
        PUT( 'N' );
    }
}

static void shift_left( unsigned char * start, size_t size, size_t offset )
{
    unsigned char * end = start OP ( size - 1 );

    assert( size > 0 );
    assert( offset > 0 );
    assert( offset < CHAR_BIT );

    while ( start != end )
    {
        *start <<= offset;
        *start |= ( *( start OP 1 ) >> ( CHAR_BIT - offset ) );
        start = start OP 1;
    }

    *start <<= offset;
}

void _PDCLIB_print_ldouble( long double value, struct _PDCLIB_status_t * status )
{
    unsigned char bytes[ sizeof( long double ) ];
    char sign;

    memcpy( bytes, &value, sizeof( long double ) );

    sign = _PDCLIB_LDBL_SIGN( bytes );

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

    if ( _PDCLIB_LDBL_IS_NAN_OR_INF( bytes ) )
    {
        if ( _PDCLIB_LDBL_ISNAN( value ) )
        {
            print_nan( sign, status );
        }
        else
        {
            print_inf( sign, status );
        }
    }
    else
    {
        int exp = _PDCLIB_LDBL_EXP( bytes ) - _PDCLIB_LDBL_BIAS;
        shift_left( _PDCLIB_LDBL_MANT( bytes ), _PDCLIB_LDBL_MANT_SIZE, _PDCLIB_LDBL_OFF );
        print_fp( sign, exp, _PDCLIB_LDBL_DEC( bytes ), _PDCLIB_LDBL_MANT( bytes ), _PDCLIB_LDBL_MANT_SIZE, status );
    }
}

void _PDCLIB_print_double( double value, struct _PDCLIB_status_t * status )
{
    unsigned char bytes[ sizeof( double ) ];
    char sign;

    memcpy( bytes, &value, sizeof( double ) );

    sign = _PDCLIB_DBL_SIGN( bytes );

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

    if ( _PDCLIB_DBL_IS_NAN_OR_INF( bytes ) )
    {
        if ( _PDCLIB_DBL_ISNAN( value ) )
        {
            print_nan( sign, status );
        }
        else
        {
            print_inf( sign, status );
        }
    }
    else
    {
        int exp = _PDCLIB_DBL_EXP( bytes ) - _PDCLIB_DBL_BIAS;
        shift_left( _PDCLIB_DBL_MANT( bytes ), _PDCLIB_DBL_MANT_SIZE, _PDCLIB_DBL_OFF );
        print_fp( sign, exp, _PDCLIB_DBL_DEC( bytes ), _PDCLIB_DBL_MANT( bytes ), _PDCLIB_DBL_MANT_SIZE, status );
    }
}

#endif

#ifdef TEST

#include <stddef.h>

#include "_PDCLIB_test.h"

int main( int argc, char * argv[] )
{
    /* Tested by the various *printf() drivers. */
    return TEST_RESULTS;
}

#endif
