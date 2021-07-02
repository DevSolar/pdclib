/* _PDCLIB_print_string

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "pdclib/_PDCLIB_print.h"

/* Print a "string" (%c, %s) under control of a given status struct. See
   INT2BASE().
*/
void _PDCLIB_print_string( const char * s, struct _PDCLIB_status_t * status )
{
    if ( status->flags & E_char )
    {
        status->prec = 1;
    }
    else
    {
        if ( status->prec < 0 )
        {
            status->prec = strlen( s );
        }
        else
        {
            int i;

            for ( i = 0; i < status->prec; ++i )
            {
                if ( s[i] == 0 )
                {
                    status->prec = i;
                    break;
                }
            }
        }
    }

    if ( !( status->flags & E_minus ) && ( status->width > ( _PDCLIB_size_t )status->prec ) )
    {
        while ( status->current < ( status->width - status->prec ) )
        {
            PUT( ' ' );
            ++( status->current );
        }
    }

    while ( status->prec > 0 )
    {
        PUT( *( s++ ) );
        --( status->prec );
        ++( status->current );
    }

    if ( status->flags & E_minus )
    {
        while ( status->width > status->current )
        {
            PUT( ' ' );
            ++( status->current );
        }
    }
}

#endif

#ifdef TEST

#include <stddef.h>

#include "_PDCLIB_test.h"

int main( void )
{
    /* Tested by _PDCLIB_print testdriver */
    return TEST_RESULTS;
}

#endif
