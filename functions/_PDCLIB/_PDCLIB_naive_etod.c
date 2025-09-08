/* _PDCLIB_naive_ptod( const char *, char ** endptr )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <ctype.h>
#include <string.h>

long double _PDCLIB_naive_etod( const char * s, char ** endptr )
{
    /* This is nowhere good enough, just a quick approximation */
    long double rc = 0.0;

    while ( isdigit( (unsigned char)*s ) )
    {
        rc = rc * 10 + ( *s++ - '0' );
    }

    if ( *s == '.' )
    {
        long double fraction = 0.0;
        long double scale = 1.0;
        ++s;

        while ( isdigit( (unsigned char)*s ) )
        {
            fraction = fraction * 10 + ( *s++ - '0' );
            scale *= 10;
        }

        rc += ( fraction / scale );
    }

    if ( tolower( (unsigned char)*s ) == 'e' )
    {
        char sign = '+';
        long double exp = 0.0;
        long double scale = 1.0;
        ++s;

        if ( *s == '-' )
        {
            sign = *s++;
        }
        else if ( *s == '+' )
        {
            ++s;
        }

        while ( isdigit( (unsigned char)*s ) )
        {
            exp = ( exp * 10 ) + ( *s++ - '0' );
        }

        while ( exp > 0 )
        {
            scale *= 10;
            --exp;
        }

        if ( sign == '+' )
        {
            rc *= scale;
        }
        else
        {
            rc /= scale;
        }
    }

    if ( endptr != NULL )
    {
        *endptr = (char *)s;
    }

    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* Tested by strtof / strtol / strtold */
    return TEST_RESULTS;
}

#endif
