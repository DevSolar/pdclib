/* _PDCLIB_print_integer

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <inttypes.h>
#include <stdio.h>

#include "pdclib/_PDCLIB_print.h"

static void intformat( intmax_t value, struct _PDCLIB_status_t * status )
{
    /* At worst, we need two prefix characters (hex prefix). */
    char preface[3] = "\0";
    size_t preidx = 0;

    if ( status->prec < 0 )
    {
        status->prec = 1;
    }

    if ( ( status->flags & E_alt ) && ( status->base == 16 || status->base == 8 ) && ( value != 0 ) )
    {
        /* Octal / hexadecimal prefix for "%#" conversions */
        preface[ preidx++ ] = '0';

        if ( status->base == 16 )
        {
            preface[ preidx++ ] = ( status->flags & E_lower ) ? 'x' : 'X';
        }
    }

    if ( value < 0 )
    {
        /* Negative sign for negative values - at all times. */
        preface[ preidx++ ] = '-';
    }
    else if ( !( status->flags & E_unsigned ) )
    {
        /* plus sign / extra space are only for signed conversions */
        if ( status->flags & E_plus )
        {
            preface[ preidx++ ] = '+';
        }
        else
        {
            if ( status->flags & E_space )
            {
                preface[ preidx++ ] = ' ';
            }
        }
    }

    {
        /* At this point, status->current has the number of digits queued up.
           Determine if we have a precision requirement to pad those.
        */
        size_t prec_pads = ( ( _PDCLIB_size_t )status->prec > status->current ) ? ( ( _PDCLIB_size_t )status->prec - status->current ) : 0;

        if ( !( status->flags & ( E_minus | E_zero ) ) )
        {
            /* Space padding is only done if no zero padding or left alignment
               is requested. Calculate the number of characters that WILL be
               printed, including any prefixes determined above.
            */
            /* The number of characters to be printed, plus prefixes if any. */
            /* This line contained probably the most stupid, time-wasting bug
               I've ever perpetrated. Greetings to Samface, DevL, and all
               sceners at Breakpoint 2006.
            */
            size_t characters = preidx + ( ( status->current > ( _PDCLIB_size_t )status->prec ) ? status->current : ( _PDCLIB_size_t )status->prec );

            if ( status->width > characters )
            {
                size_t i;

                for ( i = 0; i < status->width - characters; ++i )
                {
                    PUT( ' ' );
                    ++( status->current );
                }
            }
        }

        /* Now we did the padding, do the prefixes (if any). */
        preidx = 0;

        while ( preface[ preidx ] != '\0' )
        {
            PUT( preface[ preidx++ ] );
            ++( status->current );
        }

        /* Do the precision padding if necessary. */
        while ( prec_pads-- > 0 )
        {
            PUT( '0' );
            ++( status->current );
        }

        if ( ( !( status->flags & E_minus ) ) && ( status->flags & E_zero ) )
        {
            /* If field is not left aligned, and zero padding is requested, do
               so.
            */
            while ( status->current < status->width )
            {
                PUT( '0' );
                ++( status->current );
            }
        }
    }
}

/* This function recursively converts a given integer value to a character
   stream. The conversion is done under the control of a given status struct
   and written either to a character string or a stream, depending on that
   same status struct. The status struct also keeps the function from exceeding
   snprintf() limits, and enables any necessary padding / prefixing of the
   output once the number of characters to be printed is known, which happens
   at the lowermost recursion level.
*/
void _PDCLIB_print_integer( imaxdiv_t div, struct _PDCLIB_status_t * status )
{
    if ( status->current == 0 && div.quot == 0 && div.rem == 0 && status->prec == 0 )
    {
        intformat( 0, status );
    }
    else
    {
        ++(status->current);

        if ( div.quot != 0 )
        {
            _PDCLIB_print_integer( imaxdiv( div.quot, status->base ), status );
        }
        else
        {
            intformat( div.rem, status );
        }

        if ( div.rem < 0 )
        {
            div.rem *= -1;
        }

        if ( status->flags & E_lower )
        {
            PUT( _PDCLIB_digits[ div.rem ] );
        }
        else
        {
            PUT( _PDCLIB_Xdigits[ div.rem ] );
        }
    }
}

#endif

#ifdef TEST

#include <stddef.h>

#include "_PDCLIB_test.h"

int main( void )
{
    /* Tested by the various *printf() drivers. */
    return TEST_RESULTS;
}

#endif
