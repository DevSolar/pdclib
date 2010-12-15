/* $Id$ */

/* _PDCLIB_print( const char *, struct _PDCLIB_status_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>

/* Using an integer's bits as flags for both the conversion flags and length
   modifiers.
*/
/* FIXME: one too many flags to work on a 16-bit machine, join some (e.g. the
          width flags) into a combined field.
*/
#define E_minus    1<<0
#define E_plus     1<<1
#define E_alt      1<<2
#define E_space    1<<3
#define E_zero     1<<4
#define E_done     1<<5
#define E_char     1<<6
#define E_short    1<<7
#define E_long     1<<8
#define E_llong    1<<9
#define E_intmax   1<<10
#define E_size     1<<11
#define E_ptrdiff  1<<12
#define E_intptr   1<<13
#define E_ldouble  1<<14
#define E_lower    1<<15
#define E_unsigned 1<<16

/* This macro delivers a given character to either a memory buffer or a stream,
   depending on the contents of 'status' (struct _PDCLIB_status_t).
   x - the character to be delivered
   i - pointer to number of characters already delivered in this call
   n - pointer to maximum number of characters to be delivered in this call
   s - the buffer into which the character shall be delivered
*/
#define PUT( x ) \
do { \
    int character = x; \
    if ( status->i < status->n ) { \
        if ( status->stream != NULL ) \
            putc( character, status->stream ); \
        else \
            status->s[status->i] = character; \
    } \
    ++(status->i); \
} while ( 0 )


static void intformat( intmax_t value, struct _PDCLIB_status_t * status )
{
    /* At worst, we need two prefix characters (hex prefix). */
    char preface[3] = "\0";
    size_t preidx = 0;
    if ( ( status->flags & E_alt ) && ( status->base == 16 || status->base == 8 ) )
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
    else if ( ! ( status->flags & E_unsigned ) )
    {
        /* plus sign / extra space are only for unsigned conversions */
        if ( status->flags & E_plus )
        {
            preface[ preidx++ ] = '+';
        }
        else if ( status->flags & E_space )
        {
            preface[ preidx++ ] = ' ';
        }
    }
    {
    size_t prec_pads = ( status->prec > status->current ) ? ( status->prec - status->current ) : 0;
    if ( ! ( status->flags & ( E_minus | E_zero ) ) )
    {
        /* Space padding is only done if no zero padding or left alignment
           is requested. Leave space for any prefixes determined above.
        */
        /* The number of characters to be printed, plus prefixes if any. */
        /* This line contained probably the most stupid, time-wasting bug
           I've ever perpetrated. Greetings to Samface, DevL, and all
           sceners at Breakpoint 2006.
        */
        size_t characters = preidx + ( ( status->current > status->prec ) ? status->current : status->prec );
        if ( status->width > characters )
        {
            for ( size_t i = 0; i < status->width - characters; ++i )
            {
                PUT( ' ' );
                ++(status->current);
            }
        }
    }
    /* Now we did the padding, do the prefixes (if any). */
    preidx = 0;
    while ( preface[ preidx ] != '\0' )
    {
        PUT( preface[ preidx++ ] );
        ++(status->current);
    }
    if ( ( ! ( status->flags & E_minus ) ) && ( status->flags & E_zero ) )
    {
        /* If field is not left aligned, and zero padding is requested, do
           so.
        */
        while ( status->current < status->width )
        {
            PUT( '0' );
            ++(status->current);
        }
    }
    /* Do the precision padding if necessary. */
    for ( size_t i = 0; i < prec_pads; ++i )
    {
        PUT( '0' );
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
static void int2base( intmax_t value, struct _PDCLIB_status_t * status )
{
    /* Registering the character being printed at the end of the function here
       already so it will be taken into account when the deepestmost recursion
       does the prefix / padding stuff.
    */
    ++(status->current);
    if ( ( value / status->base ) != 0 )
    {
        /* More digits to be done - recurse deeper */
        int2base( value / status->base, status );
    }
    else
    {
        /* We reached the last digit, the deepest point of our recursion, and
           only now know how long the number to be printed actually is. Now we
           have to do the sign, prefix, width, and precision padding stuff
           before printing the numbers while we resurface from the recursion.
        */
        intformat( value, status );
    }
    /* Recursion tail - print the current digit. */
    {
    int digit = value % status->base;
    if ( digit < 0 )
    {
        digit *= -1;
    }
    if ( status->flags & E_lower )
    {
        /* Lowercase letters. Same array used for strto...(). */
        PUT( _PDCLIB_digits[ digit ] );
    }
    else
    {
        /* Uppercase letters. Array only used here, only 0-F. */
        PUT( _PDCLIB_Xdigits[ digit ] );
    }
    }
}


const char * _PDCLIB_print( const char * spec, struct _PDCLIB_status_t * status )
{
    const char * orig_spec = spec;
    if ( *(++spec) == '%' )
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
    status->prec  = 0;

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
    } while ( ! ( status->flags & E_done ) );

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
        status->width = (int)strtol( spec, (char**)&spec, 10 );
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
        }
        else
        {
            char * endptr;
            status->prec = (int)strtol( spec, &endptr, 10 );
            if ( spec == endptr )
            {
                /* Decimal point but no number - bad conversion specifier. */
                return orig_spec;
            }
            spec = endptr;
        }
        /* Having a precision cancels out any zero flag. */
        status->flags ^= E_zero;
    }

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
        case 'F':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
            break;
        case 'a':
        case 'A':
            break;
        case 'c':
            /* TODO: Flags, wide chars. */
            PUT( va_arg( status->arg, int ) );
            return ++spec;
        case 's':
            /* TODO: Flags, wide chars. */
            {
                char * s = va_arg( status->arg, char * );
                while ( *s != '\0' )
                {
                    PUT( *(s++) );
                }
                return ++spec;
            }
        case 'p':
            /* TODO: E_long -> E_intptr */
            status->base = 16;
            status->flags |= ( E_lower | E_unsigned | E_alt | E_long );
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
        /* Integer conversions */
        /* TODO: Check for invalid flag combinations. */
        if ( status->flags & E_unsigned )
        {
            uintmax_t value;
            switch ( status->flags & ( E_char | E_short | E_long | E_llong | E_size ) )
            {
                case E_char:
                    value = (uintmax_t)(unsigned char)va_arg( status->arg, int );
                    break;
                case E_short:
                    value = (uintmax_t)(unsigned short)va_arg( status->arg, int );
                    break;
                case 0:
                    value = (uintmax_t)va_arg( status->arg, unsigned int );
                    break;
                case E_long:
                    value = (uintmax_t)va_arg( status->arg, unsigned long );
                    break;
                case E_llong:
                    value = (uintmax_t)va_arg( status->arg, unsigned long long );
                    break;
                case E_size:
                    value = (uintmax_t)va_arg( status->arg, size_t );
                    break;
            }
            ++(status->current);
            /* FIXME: The if clause means one-digit values do not get formatted */
            /* Was introduced originally to get value to "safe" levels re. uintmax_t. */
            if ( ( value / status->base ) != 0 )
            {
                int2base( (intmax_t)(value / status->base), status );
            }
            else
            {
                intformat( (intmax_t)value, status );
            }
            int digit = value % status->base;
            if ( digit < 0 )
            {
                digit *= -1;
            }
            if ( status->flags & E_lower )
            {
                PUT( _PDCLIB_digits[ digit ] );
            }
            else
            {
                PUT( _PDCLIB_Xdigits[ digit ] );
            }
        }
        else
        {
            switch ( status->flags & ( E_char | E_short | E_long | E_llong | E_intmax ) )
            {
                case E_char:
                    int2base( (intmax_t)(char)va_arg( status->arg, int ), status );
                    break;
                case E_short:
                    int2base( (intmax_t)(short)va_arg( status->arg, int ), status );
                    break;
                case 0:
                    int2base( (intmax_t)va_arg( status->arg, int ), status );
                    break;
                case E_long:
                    int2base( (intmax_t)va_arg( status->arg, long ), status );
                    break;
                case E_llong:
                    int2base( (intmax_t)va_arg( status->arg, long long ), status );
                    break;
                case E_ptrdiff:
                    int2base( (intmax_t)va_arg( status->arg, ptrdiff_t ), status );
                    break;
                case E_intmax:
                    int2base( va_arg( status->arg, intmax_t ), status );
                    break;
            }
        }
        if ( status->flags & E_minus )
        {
            while ( status->current < status->width )
            {
                PUT( ' ' );
                ++(status->current);
            }
        }
        if ( status->i >= status->n && status->n > 0 )
        {
            status->s[status->n - 1] = '\0';
        }
    }
    return ++spec;
}

#ifdef TEST
#define _PDCLIB_FILEID "_PDCLIB/print.c"
#define _PDCLIB_STRINGIO

#include <_PDCLIB_test.h>

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
    status.prec = 0;
    status.stream = NULL;
    va_start( status.arg, format );
    memset( buffer, '\0', 100 );
    if ( *(_PDCLIB_print( format, &status )) != '\0' )
    {
        printf( "_PDCLIB_print() did not return end-of-specifier on '%s'.\n", format );
        ++TEST_RESULTS;
    }
    va_end( status.arg );
    return status.i;
}

#define TEST_CONVERSION_ONLY

int main( void )
{
    char target[100];
#include "printf_testcases.h"
    return TEST_RESULTS;
}

#endif
