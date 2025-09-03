/* _PDCLIB_print_fp( _PDCLIB_fp_t *, struct _PDCLIB_status_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <string.h>
#include <stdlib.h>

#define MIN( x, y ) ( ( x < y ) ? x : y )

static char * exp_to_buffer( int exponent, char * buffer )
{
    div_t dv = div( exponent, 10 );

    if ( dv.quot > 0 )
    {
        buffer = exp_to_buffer( dv.quot, buffer );
    }

    *buffer++ = _PDCLIB_digits[ dv.rem ];
    return buffer;
}

static void _PDCLIB_format_e( struct _PDCLIB_status_t * status, char * buffer, int exp10, char sign )
{
    size_t len = strlen( buffer );
    int exponent = ( len + exp10 ) - 1;
    int i;
    char exp_buffer[8];
    char * current;

    /* Print exponent to exp_buffer */
    current = exp_buffer;
    *current++ = ( status->flags & E_lower ) ? 'e' : 'E';

    if ( exponent < 0 )
    {
        *current++ = '-';
        exponent *= -1;
    }
    else
    {
        *current++ = '+';
    }

    if ( exponent > -10 && exponent < 10 )
    {
        *current++ = '0';
    }

    current = exp_to_buffer( exponent, current );
    *current = '\0';

    /* Left padding, if applicable */
    if ( ! ( status->flags & E_minus ) )
    {
        i = ( sign != '\0' )
              + 1
              + ( status->prec > 0 || status->flags & E_alt )
              + ( ( status->prec > 0 ) ? status->prec : 0 )
              + ( current - exp_buffer );

        for ( ; (size_t)i < status->width; ++i )
        {
            PUT( ( status->flags & E_zero ) ? '0' : ' ' );
            status->current++;
        }
    }

    /* Print buffer */
    current = buffer;
    PUT( _PDCLIB_digits[ (size_t)*current++ ] );
    status->current++;

    if ( status->prec > 0 || status->flags & E_alt )
    {
        PUT( '.' );
        status->current++;
    }

    for ( i = 0; i < status->prec; ++i )
    {
        if ( *current != '\0' )
        {
            PUT( _PDCLIB_digits[ (size_t)*current++ ] );
            status->current++;
        }
        else if ( ! ( status->flags & E_generic ) )
        {
            PUT( '0' );
            status->current++;
        }
    }

    /* Print exponent */
    for ( current = exp_buffer; *current != '\0'; ++current )
    {
        PUT( *current );
        status->current++;
    }
}

static void _PDCLIB_format_f( struct _PDCLIB_status_t * status, char * buffer, int exp10, char sign )
{
    size_t len = strlen( buffer );

    /* Left padding, if applicable */
    if ( ! ( status->flags & E_minus ) )
    {
        size_t i = ( sign != '\0' )
            + ( ( (int)len + exp10 > 0 ) ? ( len + exp10 ) : 1 )
            + ( status->prec > 0 || status->flags & E_alt )
            + ( ( status->prec > 0 ) ? status->prec : 0 );

        for ( ; i < status->width; ++i )
        {
            PUT( ( status->flags & E_zero ) ? '0' : ' ' );
            status->current++;
        }
    }

    if ( exp10 >= 0 )
    {
        /* Print buffer, period, zeroes to precision */
        /* len + exp10 + [period + [prec]] */
        int i;

        for ( i = 0; (size_t)i < len; ++i )
        {
            PUT( _PDCLIB_digits[ (size_t)buffer[i] ] );
            status->current++;
        }

        for ( i = 0; i < exp10; ++i )
        {
            PUT( _PDCLIB_digits[0] );
            status->current++;
        }

        if ( ( ( ! ( status->flags & E_generic ) ) && status->prec > 0 ) || status->flags & E_alt )
        {
            PUT( '.' );
            status->current++;
        }

        len = status->prec;
    }
    else
    {
        int n = len + exp10;
        int i;

        if ( n > 0 )
        {
            /* Print n from buffer, period, rest from buffer, zeroes to precision */
            for ( i = 0; i < n; ++i )
            {
                PUT( _PDCLIB_digits[ (size_t)buffer[i] ] );
                status->current++;
            }

            if ( status->prec > 0 || status->flags & E_alt )
            {
                PUT( '.' );
                status->current++;
            }

            for ( i = 0; buffer[ i + n ] != '\0'; ++i )
            {
                PUT( _PDCLIB_digits[ (size_t)buffer[ i + n ] ] );
                status->current++;
            }

            len = status->prec - i;
        }
        else
        {
            /* Print zero, period, -n zeroes, buffer, zeroes to precision */
            PUT( _PDCLIB_digits[0] );
            status->current++;

            if ( status->prec > 0 || status->flags & E_alt )
            {
                PUT( '.' );
                status->current++;
            }

            for ( i = 0; i < -n; ++i )
            {
                PUT( _PDCLIB_digits[0] );
                status->current++;
            }

            for ( i = 0; buffer[i] != '\0'; ++i )
            {
                PUT( _PDCLIB_digits[ (size_t)buffer[i] ] );
                status->current++;
            }

            n = -n + i;
            len = status->prec - n;
        }
    }

    if ( ! ( status->flags & E_generic ) )
    {
        for ( ; len > 0; --len )
        {
            PUT( _PDCLIB_digits[0] );
            status->current++;
        }
    }
}

static void _PDCLIB_format_g( struct _PDCLIB_status_t * status, char * buffer, int exp10, char sign ) {
    size_t len = strlen( buffer );
    int exponent = ( len + exp10 ) - 1;
    status->prec = ( status->prec == 0 ) ? 1 : status->prec;

    if ( exponent >= -4 && status->prec > exponent )
    {
        status->prec -= exponent;
        _PDCLIB_format_f( status, buffer, exp10, sign );
    }
    else
    {
        _PDCLIB_format_e( status, buffer, exp10, sign );
    }

    return;
}

void _PDCLIB_print_fp( _PDCLIB_fp_t * fp,
                       struct _PDCLIB_status_t * status )
{
    char buffer[ _PDCLIB_LDBL_MANT_DIG + 10 ];

    /* Turning sign bit into sign character. */
    if ( fp->sign == 1 )
    {
        fp->sign = '-';
    }
    else if ( status->flags & E_plus )
    {
        fp->sign = '+';
    }
    else if ( status->flags & E_space )
    {
        fp->sign = ' ';
    }
    else
    {
        fp->sign = '\0';
    }

    switch ( fp->state )
    {
        case _PDCLIB_FP_NAN:
            {
                size_t i;
                if ( fp->sign == '-' )
                {
                    PUT( fp->sign );
                    status->current++;
                }
                for ( i = 0; i < 3; ++i )
                {
                    PUT( ( ( status->flags & E_lower ) ? "nan" : "NAN" )[i] );
                    status->current++;
                }
            }
            return;
        case _PDCLIB_FP_INF:
            {
                int i;
                if ( fp->sign == '-' )
                {
                    PUT( fp->sign );
                    status->current++;
                }
                for ( i = 0; i < 3; ++i )
                {
                    PUT( ( ( status->flags & E_lower ) ? "inf" : "INF" )[i] );
                    status->current++;
                }
            }
            return;
        default:
            if ( status->flags & E_hexa )
            {
                _PDCLIB_print_fp_hexa( fp, status, buffer );
                return;
            }
            else
            {
                int exp10;

                /* Default precision for floating points is 6 */
                if ( status->prec < 0 )
                {
                    status->prec = 6;
                }

                exp10 = _PDCLIB_print_fp_deci( fp, status, buffer );

                switch ( status->flags & ( E_decimal | E_exponent | E_generic ) )
                {
                    case E_decimal:
                        _PDCLIB_format_f( status, buffer, exp10, fp->sign );
                        break;
                    case E_exponent:
                        _PDCLIB_format_e( status, buffer, exp10, fp->sign );
                        break;
                    case E_generic:
                        _PDCLIB_format_g( status, buffer, exp10, fp->sign );
                        break;
                }
            }
            break;
    }
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( int argc, char * argv[] )
{
    /* Tested by _PDCLIB_print testdriver */
    return TEST_RESULTS;
}

#endif
