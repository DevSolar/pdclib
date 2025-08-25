/* _PDCLIB_print_fp( _PDCLIB_fp_t *, struct _PDCLIB_status_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <string.h>

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
            strcpy( buffer, ( status->flags & E_lower ) ? "nan" : "NAN" );
            break;
        case _PDCLIB_FP_INF:
            strcpy( buffer, ( status->flags & E_lower ) ? "inf" : "INF" );
            break;
        default:
            switch ( status->flags & ( E_decimal | E_exponent | E_generic | E_hexa ) )
            {
                case E_hexa:
                    _PDCLIB_print_fp_hexa( fp, status, buffer );
                    break;
                case E_decimal:
                    _PDCLIB_print_fp_deci( fp, status, buffer );
                    break;
                default:
                    break;
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
