/* _PDCLIB_print_float

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

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
    if ( fp->data[ fp->size ] & 1<<0 )
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

    if ( fp->data[ fp->size ] & 1<<2 )
    {
        _PDCLIB_print_inf_nan( fp, status, sign );
        return;
    }

    switch ( status->flags & ( E_decimal | E_exponent | E_generic | E_hexa ) )
    {
        case E_hexa:
            _PDCLIB_print_fp_hexa( fp, status, sign );
            break;
        default:
            break;
    }
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

extern int dprintf( int, char const *, ... );

int main( int argc, char * argv[] )
{
    /* Tested by _PDCLIB_print testdriver */
    return TEST_RESULTS;
}

#endif
