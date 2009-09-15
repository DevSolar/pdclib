/* $Id$ */

/* _PDCLIB_scan( const char *, struct _PDCLIB_status_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>

/* Using an integer's bits as flags for both the conversion flags and length
   modifiers.
*/
#define E_suppressed 1<<0
#define E_char       1<<6
#define E_short      1<<7
#define E_long       1<<8
#define E_llong      1<<9
#define E_intmax     1<<10
#define E_size       1<<11
#define E_ptrdiff    1<<12
#define E_intptr     1<<13
#define E_ldouble    1<<14
#define E_unsigned   1<<16


static bool MATCH( const char x, struct _PDCLIB_status_t * status )
{
    if ( status->stream != NULL )
    {
        /* Matching against stream */
        if ( status->stream->buffer[ status->stream->bufidx ] == x )
        {
            getc( status->stream );
            ++(status->i);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        /* Matching against string */
        if ( *(status->s) == x )
        {
            ++(status->s);
            ++(status->i);
            return true;
        }
        else
        {
            return false;
        }
    }
}


const char * _PDCLIB_scan( const char * spec, struct _PDCLIB_status_t * status )
{
    const char * orig_spec = spec;
    if ( *(++spec) == '%' )
    {
        /* %% -> match single '%' */
        MATCH( *spec, status );
        return ++spec;
    }
    /* Initializing status structure */
    status->flags = 0;
    status->base = 0;
    status->this = 0;
    status->width = 0;
    status->prec = 0;

    /* '*' suppresses assigning parsed value to variable */
    if ( *spec == '*' )
    {
        status->flags |= E_suppressed;
        ++spec;
    }

    /* If a width is given, strtol() will return its value. If not given,
       strtol() will return zero. In both cases, endptr will point to the
       rest of the conversion specifier - just what we need.
    */
    status->width = (int)strtol( spec, (char**)&spec, 10 );

    /* Optional length modifier
       We step one character ahead in any case, and step back only if we find
       there has been no length modifier (or step ahead another character if it
       has been "hh" or "ll").
    */
    switch ( *(spec++) )
    {
        case 'h':
            if ( *spec == 'h' )
            {
                /* hh -> char */
                status->flags |= E_char;
                ++spec;
            }
            else
            {
                /* h -> short */
                status->flags |= E_short;
            }
            break;
        case 'l':
            if ( *spec == 'l' )
            {
                /* ll -> long long */
                status->flags |= E_llong;
                ++spec;
            }
            else
            {
                /* l -> long */
                status->flags |= E_long;
            }
            break;
        case 'j':
            /* j -> intmax_t, which might or might not be long long */
            status->flags |= E_intmax;
            break;
        case 'z':
            /* z -> size_t, which might or might not be unsigned int */
            status->flags |= E_size;
            break;
        case 't':
            /* t -> ptrdiff_t, which might or might not be long */
            status->flags |= E_ptrdiff;
            break;
        case 'L':
            /* L -> long double */
            status->flags |= E_ldouble;
            break;
        default:
            --spec;
            break;
    }

    /* Conversion specifier */
    switch ( *spec )
    {
        case 'd':
            status->base = 10;
            break;
        case 'i':
            /* status->base = 0; */
            break;
        case 'o':
            status->base = 8;
            status->flags |= E_unsigned;
            break;
        case 'u':
            status->base = 10;
            status->flags |= E_unsigned;
            break;
        case 'x':
            status->base = 16;
            status->flags |= E_unsigned;
            break;
        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'a':
        case 'A':
            break;
        case 'c':
            /* TODO */
            break;
        case 's':
            /* TODO */
            break;
        case 'p':
            /* TODO */
            status->base = 16;
            status->flags |= E_unsigned;
            break;
        case 'n':
        {
            int * val = va_arg( status->arg, int * );
            *val = status->i;
            return ++spec;
        }
        default:
            /* No conversion specifier. Bad conversion. */
            return orig_spec;
    }
    /* TODO: Actual conversions */
    return NULL;
}

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
