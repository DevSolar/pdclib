/* _PDCLIB_print( const char *, struct _PDCLIB_status_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#ifndef REGTEST

/* Using an integer's bits as flags for both the conversion flags and length
   modifiers.
*/
/* FIXME: too many flags to work on a 16-bit machine, join some (e.g. the
          width flags) into a combined field.
*/
#define E_minus    (1u<<0)
#define E_plus     (1u<<1)
#define E_alt      (1u<<2)
#define E_space    (1u<<3)
#define E_zero     (1u<<4)
#define E_done     (1u<<5)

#define E_char     (1u<<6)
#define E_short    (1u<<7)
#define E_long     (1u<<8)
#define E_llong    (1u<<9)
#define E_intmax   (1u<<10)
#define E_size     (1u<<11)
#define E_ptrdiff  (1u<<12)
#define E_pointer  (1u<<13)

#define E_ldouble  (1u<<14)

#define E_lower    (1u<<15)
#define E_unsigned (1u<<16)

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
    /* At this point, status->current has the number of digits queued up.
       Determine if we have a precision requirement to pad those.
    */
    size_t prec_pads = ( (_PDCLIB_size_t)status->prec > status->current ) ? ( (_PDCLIB_size_t)status->prec - status->current ) : 0;
    if ( ! ( status->flags & ( E_minus | E_zero ) ) )
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
        size_t characters = preidx + ( ( status->current > (_PDCLIB_size_t)status->prec ) ? status->current : (_PDCLIB_size_t)status->prec );
        if ( status->width > characters )
        {
            size_t i;
            for ( i = 0; i < status->width - characters; ++i )
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
    /* Do the precision padding if necessary. */
    while ( prec_pads-- > 0 )
    {
        PUT( '0' );
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
#define INT2BASE() \
do \
{ \
    /* Special case: zero value, zero precision -- no output (but padding) */ \
    if ( status->current == 0 && value == 0 && status->prec == 0 ) \
    { \
        intformat( value, status ); \
    } \
    else \
    { \
        /* Registering the character being printed at the end of the function here \
           already so it will be taken into account when the deepestmost recursion \
           does the prefix / padding stuff. \
        */ \
        ++(status->current); \
        if ( ( value / status->base ) != 0 ) \
        { \
            /* More digits to be done - recurse deeper */ \
            int2base( value / status->base, status ); \
        } \
        else \
        { \
            /* We reached the last digit, the deepest point of our recursion, and \
               only now know how long the number to be printed actually is. Now we \
               have to do the sign, prefix, width, and precision padding stuff \
               before printing the numbers while we resurface from the recursion. \
            */ \
            intformat( value, status ); \
        } \
        /* Recursion tail - print the current digit. */ \
        { \
        int digit = value % status->base; \
        if ( digit < 0 ) \
        { \
            digit *= -1; \
        } \
        if ( status->flags & E_lower ) \
        { \
            /* Lowercase letters. Same array used for strto...(). */ \
            PUT( _PDCLIB_digits[ digit ] ); \
        } \
        else \
        { \
            /* Uppercase letters. Array only used here, only 0-F. */ \
            PUT( _PDCLIB_Xdigits[ digit ] ); \
        } \
        } \
    } \
} while ( 0 )


static void int2base( intmax_t value, struct _PDCLIB_status_t * status )
{
    INT2BASE();
}


static void stringformat( const char * s, struct _PDCLIB_status_t * status )
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
    if ( ! ( status->flags & E_minus ) && ( status->width > (_PDCLIB_size_t)status->prec ) )
    {
        while ( status->current < ( status->width - status->prec ) )
        {
            PUT( ' ' );
            ++(status->current);
        }
    }
    while ( status->prec > 0 )
    {
        PUT( *(s++) );
        --(status->prec);
        ++(status->current);
    }
    if ( status->flags & E_minus )
    {
        while ( status->width > status->current )
        {
            PUT( ' ' );
            ++(status->current);
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
            ++spec;
        }
        else
        {
            char * endptr;
            status->prec = (int)strtol( spec, &endptr, 10 );
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
            /* TODO: wide chars. */
            {
                char c[1];
                c[0] = (char)va_arg( status->arg, int );
                status->flags |= E_char;
                stringformat( c, status );
                return ++spec;
            }
        case 's':
            /* TODO: wide chars. */
            stringformat( va_arg( status->arg, char * ), status );
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
        /* Integer conversions */
        /* TODO: Check for invalid flag combinations. */
        if ( status->flags & E_unsigned )
        {
            uintmax_t value;
            switch ( status->flags & ( E_char | E_short | E_long | E_llong | E_size | E_pointer | E_intmax ) )
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
                case E_pointer:
                    value = (uintmax_t)(uintptr_t)va_arg( status->arg, void * );
                    break;
                case E_intmax:
                    value = va_arg( status->arg, uintmax_t );
                    break;
                default:
                    puts( "UNSUPPORTED PRINTF FLAG COMBINATION" );
                    return NULL;
            }
            INT2BASE();
        }
        else
        {
            intmax_t value;
            switch ( status->flags & ( E_char | E_short | E_long | E_llong | E_intmax ) )
            {
                case E_char:
                    value = (intmax_t)(char)va_arg( status->arg, int );
                    break;
                case E_short:
                    value = (intmax_t)(short)va_arg( status->arg, int );
                    break;
                case 0:
                    value = (intmax_t)va_arg( status->arg, int );
                    break;
                case E_long:
                    value = (intmax_t)va_arg( status->arg, long );
                    break;
                case E_llong:
                    value = (intmax_t)va_arg( status->arg, long long );
                    break;
                case E_ptrdiff:
                    value = (intmax_t)va_arg( status->arg, ptrdiff_t );
                    break;
                case E_intmax:
                    value = va_arg( status->arg, intmax_t );
                    break;
                default:
                    puts( "UNSUPPORTED PRINTF FLAG COMBINATION" );
                    return NULL;
            }
            INT2BASE();
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
    if ( *(_PDCLIB_print( format, &status )) != '\0' )
    {
        printf( "_PDCLIB_print() did not return end-of-specifier on '%s'.\n", format );
        ++TEST_RESULTS;
    }
    va_end( status.arg );
    return status.i;
}

#endif

#define TEST_CONVERSION_ONLY

int main( void )
{
#ifndef REGTEST
    char target[100];
#include "printf_testcases.h"
#endif
    return TEST_RESULTS;
}

#endif
