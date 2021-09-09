/* _PDCLIB_print( const char *, struct _PDCLIB_status_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <inttypes.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

const char * _PDCLIB_print( const char * spec, struct _PDCLIB_status_t * status )
{
    const char * orig_spec = spec;

    if ( *( ++spec ) == '%' )
    {
        /* %% -> print single '%' */
        PUT( *spec );
        return ++spec;
    }

    /* Initializing status structure */
    status->flags = 0;
    status->base  = 0;
    status->current  = 0;
    status->width = 0;
    status->prec  = EOF;

    /* First come 0..n flags */
    do
    {
        switch ( *spec )
        {
            case '-':
                /* left-aligned output */
                status->flags |= E_minus;
                ++spec;
                break;

            case '+':
                /* positive numbers prefixed with '+' */
                status->flags |= E_plus;
                ++spec;
                break;

            case '#':
                /* alternative format (leading 0x for hex, 0 for octal) */
                status->flags |= E_alt;
                ++spec;
                break;

            case ' ':
                /* positive numbers prefixed with ' ' */
                status->flags |= E_space;
                ++spec;
                break;

            case '0':
                /* right-aligned padding done with '0' instead of ' ' */
                status->flags |= E_zero;
                ++spec;
                break;

            default:
                /* not a flag, exit flag parsing */
                status->flags |= E_done;
                break;
        }
    } while ( !( status->flags & E_done ) );

    /* Optional field width */
    if ( *spec == '*' )
    {
        /* Retrieve width value from argument stack */
        int width = va_arg( status->arg, int );

        if ( width < 0 )
        {
            status->flags |= E_minus;
            status->width = abs( width );
        }
        else
        {
            status->width = width;
        }

        ++spec;
    }
    else
    {
        /* If a width is given, strtol() will return its value. If not given,
           strtol() will return zero. In both cases, endptr will point to the
           rest of the conversion specifier - just what we need.
        */
        status->width = ( int )strtol( spec, ( char ** )&spec, 10 );
    }

    /* Optional precision */
    if ( *spec == '.' )
    {
        ++spec;

        if ( *spec == '*' )
        {
            /* Retrieve precision value from argument stack. A negative value
               is as if no precision is given - as precision is initalized to
               EOF (negative), there is no need for testing for negative here.
            */
            status->prec = va_arg( status->arg, int );
            ++spec;
        }
        else
        {
            char * endptr;
            status->prec = ( int )strtol( spec, &endptr, 10 );

            if ( spec == endptr )
            {
                /* Decimal point but no number - equals zero */
                status->prec = 0;
            }

            spec = endptr;
        }

        /* Having a precision cancels out any zero flag. */
        status->flags &= ~E_zero;
    }

    /* Optional length modifier
       We step one character ahead in any case, and step back only if we find
       there has been no length modifier (or step ahead another character if it
       has been "hh" or "ll").
    */
    switch ( *( spec++ ) )
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
                /* k -> long */
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
            /* FALLTHROUGH */

        case 'i':
            status->base = 10;
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
            status->flags |= ( E_lower | E_unsigned );
            break;

        case 'X':
            status->base = 16;
            status->flags |= E_unsigned;
            break;

        case 'f':
            status->base = 2;
            status->flags |= ( E_decimal | E_double | E_lower );
            break;

        case 'F':
            status->base = 2;
            status->flags |= ( E_decimal | E_double );
            break;

        case 'e':
            status->base = 2;
            status->flags |= ( E_exponent | E_double | E_lower );
            break;

        case 'E':
            status->base = 2;
            status->flags |= ( E_exponent | E_double );
            break;

        case 'g':
            status->base = 2;
            status->flags |= ( E_generic | E_double | E_lower );
            break;

        case 'G':
            status->base = 2;
            status->flags |= ( E_generic | E_double );
            break;

        case 'a':
            status->base = 2;
            status->flags |= ( E_hexa | E_double | E_lower );
            break;

        case 'A':
            status->base = 2;
            status->flags |= ( E_hexa | E_double );
            break;

        case 'c':
            /* TODO: wide chars. */
            {
                char c[1];
                c[0] = ( char )va_arg( status->arg, int );
                status->flags |= E_char;
                _PDCLIB_print_string( c, status );
                return ++spec;
            }

        case 's':
            /* TODO: wide chars. */
            _PDCLIB_print_string( va_arg( status->arg, char * ), status );
            return ++spec;

        case 'p':
            status->base = 16;
            status->flags |= ( E_lower | E_unsigned | E_alt | E_pointer );
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

    /* Do the actual output based on our findings */
    if ( status->base != 0 )
    {
        /* TODO: Check for invalid flag combinations. */
        if ( status->flags & E_double )
        {
            /* Floating Point conversions */
            if ( status->flags & E_ldouble )
            {
                long double value = va_arg( status->arg, long double );
                _PDCLIB_print_ldouble( value, status );
            }
            else
            {
                double value = va_arg( status->arg, double );
                _PDCLIB_print_double( value, status );
            }
        }
        else
        {
            if ( status->flags & E_unsigned )
            {
                /* Integer conversions (unsigned) */
                uintmax_t value;
                imaxdiv_t div;

                switch ( status->flags & ( E_char | E_short | E_long | E_llong | E_size | E_pointer | E_intmax ) )
                {
                    case E_char:
                        value = ( uintmax_t )( unsigned char )va_arg( status->arg, int );
                        break;

                    case E_short:
                        value = ( uintmax_t )( unsigned short )va_arg( status->arg, int );
                        break;

                    case 0:
                        value = ( uintmax_t )va_arg( status->arg, unsigned int );
                        break;

                    case E_long:
                        value = ( uintmax_t )va_arg( status->arg, unsigned long );
                        break;

                    case E_llong:
                        value = ( uintmax_t )va_arg( status->arg, unsigned long long );
                        break;

                    case E_size:
                        value = ( uintmax_t )va_arg( status->arg, size_t );
                        break;

                    case E_pointer:
                        value = ( uintmax_t )( uintptr_t )va_arg( status->arg, void * );
                        break;

                    case E_intmax:
                        value = va_arg( status->arg, uintmax_t );
                        break;

                    default:
                        puts( "UNSUPPORTED PRINTF FLAG COMBINATION" );
                        return NULL;
                }

                div.quot = value / status->base;
                div.rem = value % status->base;
                _PDCLIB_print_integer( div, status );
            }
            else
            {
                /* Integer conversions (signed) */
                intmax_t value;

                switch ( status->flags & ( E_char | E_short | E_long | E_llong | E_intmax ) )
                {
                    case E_char:
                        value = ( intmax_t )( char )va_arg( status->arg, int );
                        break;

                    case E_short:
                        value = ( intmax_t )( short )va_arg( status->arg, int );
                        break;

                    case 0:
                        value = ( intmax_t )va_arg( status->arg, int );
                        break;

                    case E_long:
                        value = ( intmax_t )va_arg( status->arg, long );
                        break;

                    case E_llong:
                        value = ( intmax_t )va_arg( status->arg, long long );
                        break;

                    case E_ptrdiff:
                        value = ( intmax_t )va_arg( status->arg, ptrdiff_t );
                        break;

                    case E_intmax:
                        value = va_arg( status->arg, intmax_t );
                        break;

                    default:
                        puts( "UNSUPPORTED PRINTF FLAG COMBINATION" );
                        return NULL;
                }

                _PDCLIB_print_integer( imaxdiv( value, status->base ), status );
            }
        }

        if ( status->flags & E_minus )
        {
            /* Left-aligned filling */
            while ( status->current < status->width )
            {
                PUT( ' ' );
                ++( status->current );
            }
        }

        if ( status->i >= status->n && status->n > 0 )
        {
            status->s[status->n - 1] = '\0';
        }
    }

    return ++spec;
}

#endif

#ifdef TEST
#define _PDCLIB_FILEID "_PDCLIB/print.c"
#define _PDCLIB_STRINGIO

#include "_PDCLIB_test.h"

#ifndef REGTEST

static int testprintf( char * buffer, const char * format, ... )
{
    /* Members: base, flags, n, i, current, s, width, prec, stream, arg      */
    struct _PDCLIB_status_t status;
    status.base = 0;
    status.flags = 0;
    status.n = 100;
    status.i = 0;
    status.current = 0;
    status.s = buffer;
    status.width = 0;
    status.prec = EOF;
    status.stream = NULL;
    va_start( status.arg, format );
    memset( buffer, '\0', 100 );

    if ( *( _PDCLIB_print( format, &status ) ) != '\0' )
    {
        printf( "_PDCLIB_print() did not return end-of-specifier on '%s'.\n", format );
        ++TEST_RESULTS;
    }

    va_end( status.arg );
    return status.i;
}

#endif

#define TEST_CONVERSION_ONLY

#include <float.h>

int main( void )
{
#ifndef REGTEST
    char target[100];
#include "printf_testcases.h"
#endif
    return TEST_RESULTS;
}

#endif
