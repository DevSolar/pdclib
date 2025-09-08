/* _PDCLIB_naive_ptod( const char *, char ** endptr )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <ctype.h>
#include <string.h>

long double _PDCLIB_naive_ptod( const char * s, char ** endptr )
{
    /* This is nowhere good enough, just a quick approximation */
    long double rc = 0.0;
    const char * x;

    while ( ( x = (const char *)memchr( _PDCLIB_digits, tolower( (unsigned char)*s ), 16 ) ) != NULL )
    {
        rc = rc * 16 + ( x - _PDCLIB_digits );
    }

    if ( *s == '.' )
    {
        long double fraction = 0.0;
        long double scale = 1.0;
        ++s;

        while ( ( x = (const char *)memchr( _PDCLIB_digits, tolower( (unsigned char)*s ), 16 ) ) != NULL )
        {
            fraction = fraction * 16 + ( x - _PDCLIB_digits );
            scale *= 16;
        }

        rc += ( fraction / scale );
    }

    if ( tolower( (unsigned char)*s ) == 'p' )
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
            scale *= 2;
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
