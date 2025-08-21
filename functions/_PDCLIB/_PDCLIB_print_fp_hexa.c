/* _PDCLIB_print_fp_hexa( _PDCLIB_bigint_t *, struct _PDCLIB_status_t *, char )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <float.h>
#include <stdbool.h>
#include <stdlib.h>

static inline void round_up( char * buffer, size_t index )
{
    if ( buffer[ index ] < '\017' )
    {
        ++buffer[ index ];
    }
    else
    {
        buffer[ index ] = '\0';
        round_up( buffer, index - 1 );
    }
}

static inline void round( char * buffer, size_t last_non_zero, size_t prec, char sign )
{
    switch ( FLT_ROUNDS )
    {
        case 0: /*FE_TOWARDZERO*/
            break;
        default: /*FE_TONEAREST*/
        case 1:
            if ( buffer[ prec + 1 ] > '\005' )
            {
                round_up( buffer, prec );
            }
            else if ( buffer[ prec + 1 ] == '\005' )
            {
                if ( last_non_zero > ( prec + 1 ) || ( buffer[ prec ] % 2 ) )
                {
                    round_up( buffer, prec );
                }
            }
            break;
        case 2: /*FE_UPWARD*/
            if ( sign != '-' )
            {
               round_up( buffer, prec );
            }
            break;
        case 3: /*FE_DOWNWARD*/
            if ( sign == '-' )
            {
                round_up( buffer, prec );
            }
            break;
    }
}

static char * print_exp( char * buffer, int exp )
{
    div_t dv = div( exp, 10 );

    if ( dv.quot > 0 )
    {
        buffer = print_exp( buffer, dv.quot );
    }

    *buffer = _PDCLIB_digits[ dv.rem ];
    return ++buffer;
}

static size_t print_mant( _PDCLIB_bigint_t * fp, struct _PDCLIB_status_t * status, char * buffer, char sign )
{
    size_t i;
    int last_non_zero;
    size_t mant_dig = ( ( status->flags & E_ldouble ) ? _PDCLIB_LDBL_MANT_DIG : _PDCLIB_DBL_MANT_DIG ) - 1;
    size_t log2 = _PDCLIB_bigint_log2( fp );
    char * bufend = buffer;

    if ( ( mant_dig % 4 ) > 0 )
    {
        /* alignment */
        int shift = 4 - ( mant_dig % 4 );
        _PDCLIB_bigint_shl( fp, shift );
        mant_dig += shift;
        log2 += shift;
    }

    if ( mant_dig > log2 )
    {
        /* subnormal, leading zeroes */
        for ( i = 0; i <= ( mant_dig - log2 - 1 ) / 4; ++i )
        {
            *bufend++ = '\0';
        }
    }

    for ( i = log2 / 4 + 1; i > 0; --i, ++bufend )
    {
        /* data nibbles */
        div_t dv = div( i - 1, _PDCLIB_BIGINT_DIGIT_BITS / 4 );

        if ( ( *bufend = ( fp->data[ dv.quot ] >> ( dv.rem * 4 ) ) & 0xfu ) > 0 )
        {
            last_non_zero = bufend - buffer;
        }
    }

    if ( status->prec >= 0 )
    {
        /* check rounding */
        if ( last_non_zero > ( status->prec + 1 ) )
        {
            round( buffer, last_non_zero, status->prec, sign );
        }

        return status->prec + 1;
    }
    else
    {
        /* no precision given */
        return last_non_zero + 1;
    }
}

void _PDCLIB_print_fp_hexa( _PDCLIB_bigint_t * fp,
                            struct _PDCLIB_status_t * status,
                            char sign )
{
    _PDCLIB_static_assert( _PDCLIB_FLT_RADIX == 2, "Assuming 2-based Floating Point" );

    char const * digits = ( status->flags & E_lower ) ? _PDCLIB_digits : _PDCLIB_Xdigits;
    int exp = (_PDCLIB_bigint_sdigit_t)fp->data[ fp->size + 1 ];
    /* sign + "0x" + dec + "." + ( LDBL_MANT_DIG / 4 )
            + 'p' + sign + exp[5] + '\0' <= 41
       ...but how could I do THAT? :-)
    */
    char buffer[42];
    char * current = buffer;
    size_t count;
    size_t i;

    /* significant */
    if ( fp->size == 0 )
    {
        *current++ = '0';
        exp = 0;
    }
    else
    {
        count = print_mant( fp, status, current, sign );

        *current = digits[ (size_t)*current ];
        ++current;

        if ( ( count > 1 && status->prec != 0 ) || status->flags & E_alt )
        {
            for ( i = count; i > 1; --i )
            {
                current[ i ] = current[ i - 1 ];
            }

            *current++ = '.'; /* TODO: decimal point */
        }

        for ( i = 1; i < count; ++i )
        {
            *current = digits[ (size_t)*current ];
            ++current;
        }
    }

    /* exponent */
    *current++ = ( status->flags & E_lower ) ? 'p' : 'P';

    if ( exp < 0 )
    {
        *current++ = '-';
        exp *= -1;
    }
    else
    {
        *current++ = '+';
    }

    current = print_exp( current, exp );
    *current = '\0';

    /* output */
    count = ( current - buffer ) + ( ( sign == '\0' ) ? 2 : 3 );
    count = ( status->width > count ) ? ( status->width - count ) : 0;

    if ( ( count > 0 ) && ! ( status->flags & E_minus ) && ! ( status->flags & E_zero ) )
    {
        for ( i = 0; i < count; ++i )
        {
            PUT( ' ' );
            status->current++;
        }
    }

    if ( sign != '\0' )
    {
        PUT( sign );
        status->current++;
    }

    PUT( '0' );
    PUT( ( status->flags & E_lower ) ? 'x' : 'X' );
    status->current += 2;

    if ( ( count > 0 ) && ! ( status->flags & E_minus ) && ( status->flags & E_zero ) )
    {
        for ( i = 0; i < count; ++i )
        {
            PUT( '0' );
            status->current++;
        }
    }

    current = buffer;

    while ( *current != '\0' )
    {
        PUT( *current++ );
        status->current++;
    }

    if ( ( count > 0 ) && ( status->flags & E_minus ) )
    {
        for ( i = 0; i < count; ++i )
        {
            PUT( ' ' );
            status->current++;
        }
    }
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( int argc, char * argv[] )
{
    /* Tested by _PDCLIB_print testdriver */
#ifndef REGTEST
    char buffer[100];
    *(print_exp( buffer, 0 )) = '\0';
    TESTCASE( strcmp( buffer, "0" ) == 0 );

    *(print_exp( buffer, 9 )) = '\0';
    TESTCASE( strcmp( buffer, "9" ) == 0 );

    *(print_exp( buffer, 10 )) = '\0';
    TESTCASE( strcmp( buffer, "10" ) == 0 );

    *(print_exp( buffer, 100 )) = '\0';
    TESTCASE( strcmp( buffer, "100" ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
