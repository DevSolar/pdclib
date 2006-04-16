#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* These can be removed once integrated into PDCLIB make procedure */
#undef TEST
#include </home/solar/src/pdclib/functions/_PDCLIB/digits.c>
#include </home/solar/src/pdclib/functions/_PDCLIB/Xdigits.c>

/* Using an integer's bits as flags for both the conversion flags and length
   modifiers.
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
#define E_double   1<<13
#define E_lower    1<<14
#define E_unsigned 1<<15

struct status_t
{
    int           base;  /* base to which the value shall be converted       */
    int_fast32_t  flags; /* flags and length modifiers                       */
    size_t        n;     /* maximum number of characters to be written       */
    size_t        i;     /* number of characters already written             */
    size_t        this;  /* number of output chars in the current conversion */
    char *        s;     /* target buffer                                    */
    size_t        width; /* width of current field                           */
    size_t        prec;  /* precision of current field                       */
    FILE *        stream;/* for to-stream output                             */
    va_list       ap;    /* the argument stack passed to the printf function */
};

const char * parse_out( const char * spec, struct status_t * status );
inline void test( size_t n, const char * expect, ... );
int _PDCLIB_sprintf( char * buffer, size_t n, const char * format, va_list ap );

/* The following only for testing. */
#include <limits.h>
#include <string.h>

int main( void )
{
    int rc;
    puts( "- Signed min / max -\n" );
    test( SIZE_MAX, "%hhd", CHAR_MIN );
    test( SIZE_MAX, "%hhd", CHAR_MAX );
    test( SIZE_MAX, "%hhd", 0 );
    test( SIZE_MAX, "%hd", SHRT_MIN );
    test( SIZE_MAX, "%hd", SHRT_MAX );
    test( SIZE_MAX, "%hd", 0 );
    test( SIZE_MAX, "%d", INT_MIN );
    test( SIZE_MAX, "%d", INT_MAX );
    test( SIZE_MAX, "%d", 0 );
    test( SIZE_MAX, "%ld", LONG_MIN );
    test( SIZE_MAX, "%ld", LONG_MAX );
    test( SIZE_MAX, "%ld", 0l );
    test( SIZE_MAX, "%lld", LLONG_MIN );
    test( SIZE_MAX, "%lld", LLONG_MAX );
    test( SIZE_MAX, "%lld", 0ll );
    puts( "- Unsigned min / max -\n" );
    test( SIZE_MAX, "%hhu", UCHAR_MAX );
    test( SIZE_MAX, "%hhu", (unsigned char)-1 );
    test( SIZE_MAX, "%hu", USHRT_MAX );
    test( SIZE_MAX, "%hu", (unsigned short)-1 );
    test( SIZE_MAX, "%u", UINT_MAX );
    test( SIZE_MAX, "%u", -1u );
    test( SIZE_MAX, "%lu", ULONG_MAX );
    test( SIZE_MAX, "%lu", -1ul );
    test( SIZE_MAX, "%llu", ULLONG_MAX );
    test( SIZE_MAX, "%llu", -1ull );
    puts( "- Hex and Octal, normal and alternative, upper and lowercase -\n" );
    test( SIZE_MAX, "%X", UINT_MAX );
    test( SIZE_MAX, "%#X", -1u );
    test( SIZE_MAX, "%x", UINT_MAX );
    test( SIZE_MAX, "%#x", -1u );
    test( SIZE_MAX, "%o", UINT_MAX );
    test( SIZE_MAX, "%#o", -1u );
    puts( "- Plus flag -\n" );
    test( SIZE_MAX, "%+d", INT_MIN );
    test( SIZE_MAX, "%+d", INT_MAX );
    test( SIZE_MAX, "%+d", 0 );
    test( SIZE_MAX, "%+u", UINT_MAX );
    test( SIZE_MAX, "%+u", -1u );
    puts( "- Space flag -\n" );
    test( SIZE_MAX, "% d", INT_MIN );
    test( SIZE_MAX, "% d", INT_MAX );
    test( SIZE_MAX, "% d", 0 );
    test( SIZE_MAX, "% u", UINT_MAX );
    test( SIZE_MAX, "% u", -1u );
    puts( "- Field width -\n" );
    test( SIZE_MAX, "%9d", INT_MIN );
    test( SIZE_MAX, "%9d", INT_MAX );
    test( SIZE_MAX, "%10d", INT_MIN );
    test( SIZE_MAX, "%10d", INT_MAX );
    test( SIZE_MAX, "%11d", INT_MIN );
    test( SIZE_MAX, "%11d", INT_MAX );
    test( SIZE_MAX, "%12d", INT_MIN );
    test( SIZE_MAX, "%12d", INT_MAX );
    puts( "- Field width (left bound) -\n" );
    test( SIZE_MAX, "%-9d", INT_MIN );
    test( SIZE_MAX, "%-9d", INT_MAX );
    test( SIZE_MAX, "%-10d", INT_MIN );
    test( SIZE_MAX, "%-10d", INT_MAX );
    test( SIZE_MAX, "%-11d", INT_MIN );
    test( SIZE_MAX, "%-11d", INT_MAX );
    test( SIZE_MAX, "%-12d", INT_MIN );
    test( SIZE_MAX, "%-12d", INT_MAX );
    puts( "- Field width, zero padding -\n");
    test( SIZE_MAX, "%09d", INT_MIN );
    test( SIZE_MAX, "%09d", INT_MAX );
    test( SIZE_MAX, "%010d", INT_MIN );
    test( SIZE_MAX, "%010d", INT_MAX );
    test( SIZE_MAX, "%011d", INT_MIN );
    test( SIZE_MAX, "%011d", INT_MAX );
    test( SIZE_MAX, "%012d", INT_MIN );
    test( SIZE_MAX, "%012d", INT_MAX );
    puts( "- Field width, zero padding (left bound) -\n" );
    test( SIZE_MAX, "%-09d", INT_MIN );
    test( SIZE_MAX, "%-09d", INT_MAX );
    test( SIZE_MAX, "%-010d", INT_MIN );
    test( SIZE_MAX, "%-010d", INT_MAX );
    test( SIZE_MAX, "%-011d", INT_MIN );
    test( SIZE_MAX, "%-011d", INT_MAX );
    test( SIZE_MAX, "%-012d", INT_MIN );
    test( SIZE_MAX, "%-012d", INT_MAX );
    puts( "- Limited n -\n" );
    test( 8, "%9d", INT_MAX );
    test( 8, "%9d", INT_MIN );
    test( 9, "%9d", INT_MAX );
    test( 9, "%9d", INT_MIN );
    test( 10, "%9d", INT_MAX );
    test( 10, "%9d", INT_MIN );
    test( 9, "%10d", INT_MAX );
    test( 9, "%10d", INT_MIN );
    test( 10, "%10d", INT_MAX );
    test( 10, "%10d", INT_MIN );
    test( 11, "%10d", INT_MAX );
    test( 11, "%10d", INT_MIN );
    test( 10, "%11d", INT_MAX );
    test( 10, "%11d", INT_MIN );
    test( 11, "%11d", INT_MAX );
    test( 11, "%11d", INT_MIN );
    test( 12, "%11d", INT_MAX );
    test( 12, "%11d", INT_MIN );
    test( 11, "%12d", INT_MAX );
    test( 11, "%12d", INT_MIN );
    test( 12, "%12d", INT_MAX );
    test( 12, "%12d", INT_MIN );
    test( 13, "%12d", INT_MAX );
    test( 13, "%12d", INT_MIN );
    puts( "- Precision (tbd) -\n" );
    {
        const char * format = "%030.20d";
        printf( "glibc  '" );
        rc = printf( format, INT_MAX );
        printf( "', RC %d\n", rc );
        test( SIZE_MAX, format, INT_MAX );
    }
    puts( "- vanilla -" );
    printf( "No width, no precision:     %#x\n", 42 );
    printf( "Width, no precision:        %#6x\n", 42 );
    printf( "No width, precision:        %#.6x\n", 42 );
    printf( "Big width, small precision: %#6.3x\n", 42 );
    printf( "Small width, big precision: %#3.6x\n", 42 );
    printf( "No width, no precision:     %#d\n", 42 );
    printf( "Width, no precision:        %#6d\n", 42 );
    printf( "No width, precision:        %#.6d\n", 42 );
    printf( "Big width, small precision: %#6.3d\n", 42 );
    printf( "Small width, big precision: %#3.6d\n", 42 );
    puts( "- zero flag -" );
    printf( "No width, no precision:     %#0x\n", 42 );
    printf( "Width, no precision:        %#06x\n", 42 );
    printf( "No width, precision:        %#0.6x\n", 42 );
    printf( "Big width, small precision: %#06.3x\n", 42 );
    printf( "Small width, big precision: %#03.6x\n", 42 );
    printf( "No width, no precision:     %#0d\n", 42 );
    printf( "Width, no precision:        %#06d\n", 42 );
    printf( "No width, precision:        %#0.6d\n", 42 );
    printf( "Big width, small precision: %#06.3d\n", 42 );
    printf( "Small width, big precision: %#03.6d\n", 42 );
    puts( "- plus flag -" );
    printf( "No width, no precision:     %#+d\n", 42 );
    printf( "Width, no precision:        %#+6d\n", 42 );
    printf( "No width, precision:        %#+.6d\n", 42 );
    printf( "Big width, small precision: %#+6.3d\n", 42 );
    printf( "Small width, big precision: %#+3.6d\n", 42 );
    puts( "- plus and zero flag -" );
    printf( "No width, no precision:     %#+0d\n", 42 );
    printf( "Width, no precision:        %#+06d\n", 42 );
    printf( "No width, precision:        %#+0.6d\n", 42 );
    printf( "Big width, small precision: %#+06.3d\n", 42 );
    printf( "Small width, big precision: %#+03.6d\n", 42 );
    return 0;
}

/* This macro delivers a given character to either a memory buffer or a stream,
   depending on the contents of 'status' (struct status_t).
   x - the character to be delivered
   i - pointer to number of characters already delivered in this call
   n - pointer to maximum number of characters to be delivered in this call
   s - the buffer into which the character shall be delivered
   TODO: Overruns.
*/
#define DELIVER( x ) do { if ( status->i < status->n ) { if ( status->stream != NULL ) putc( x, status->stream ); else status->s[status->i] = x; } ++(status->i); } while ( 0 )

/* This function recursively converts a given integer value to a given base
   into a character string. Persistent information - like the number of digits
   parsed so far - is recorded in a struct status_t, which allows to avoid
   overwriting snprintf() limits, and enables the function to do the necessary
   padding / prefixing of the character string eventually printed.
*/
static void int2base( intmax_t value, struct status_t * status )
{
    /* Registering the character being printed at the end of the function here
       already so it will be taken into account when the deepestmost recursion
       does the prefix / padding stuff.
    */
    ++(status->this);
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
        /* At worst, we need two prefix characters (hex prefix). */
        char preface[3] = "\0";
        size_t preidx = 0;
        if ( ( status->flags & E_alt ) && ( status->base == 16 || status->base == 8 ) )
        {
            /* Octal / hexadecimal prefix for "%#" conversions */
            preface[ preidx++ ] = '0'; /* TODO: For octal, standard states "extend the precision" */
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
            size_t characters = preidx + ( ( status->this > status->prec ) ? status->this : status->prec );
            if ( status->width > characters )
            {
                for ( int i = 0; i < status->width - characters; ++i )
                {
                    DELIVER( ' ' );
                    ++(status->this); /* TODO: Probably have to do something so I still know how many zeroes are required, later. */
                }
            }
        }
        /* Now we did the padding, do the prefixes (if any). */
        preidx = 0;
        while ( preface[ preidx ] != '\0' )
        {
            DELIVER( preface[ preidx++ ] );
            ++(status->this);
        }
        if ( ( ! ( status->flags & E_minus ) ) && ( status->flags & E_zero ) )
        {
            /* If field is not left aligned, and zero padding is requested, do
               so. TODO: This should include precision handling (probably).
            */
            while ( status->this < status->width )
            {
                DELIVER( '0' );
                ++(status->this);
            }
        }
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
        DELIVER( _PDCLIB_digits[ digit ] );
    }
    else
    {
        /* Uppercase letters. Array only used here, only 0-F. */
        DELIVER( _PDCLIB_Xdigits[ digit ] );
    }
    }
}

/* This function is to be called with spec pointing to the leading '%' of a
   printf() conversion specifier, with ap being 
*/
const char * parse_out( const char * spec, struct status_t * status )
{
    const char * orig_spec = spec;
    if ( *(++spec) == '%' )
    {
        DELIVER( *spec );
        return spec;
    }
    /* Initializing status structure */
    status->flags = 0;
    status->base  = 0;
    status->this  = 0;
    status->width = 0;
    status->prec  = 0;

    /* First come 0..n flags */
    do
    {
        switch ( *spec )
        {
            case '-':
                status->flags |= E_minus;
                ++spec;
                break;
            case '+':
                status->flags |= E_plus;
                ++spec;
                break;
            case '#':
                status->flags |= E_alt;
                ++spec;
                break;
            case ' ':
                status->flags |= E_space;
                ++spec;
                break;
            case '0':
                status->flags |= E_zero;
                ++spec;
                break;
            default:
                status->flags |= E_done;
                break;
        }
    } while ( ! ( status->flags & E_done ) );

    /* Optional field width */
    if ( *spec == '*' )
    {
        /* Retrieve width value from argument stack */
        if ( ( status->width = va_arg( status->ap, int ) ) < 0 )
        {
            /* Negative value is '-' flag plus absolute value */
            status->flags |= E_minus;
            status->width *= -1;
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
            status->prec = va_arg( status->ap, int );
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
        status->flags &= ! E_zero;
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
                status->flags |= E_char;
                ++spec;
            }
            else
            {
                status->flags |= E_short;
            }
            break;
        case 'l':
            if ( *spec == 'l' )
            {
                status->flags |= E_llong;
                ++spec;
            }
            else
            {
                status->flags |= E_long;
            }
            break;
        case 'j':
            status->flags |= E_intmax;
            break;
        case 'z':
            status->flags |= E_size;
            break;
        case 't':
            status->flags |= E_ptrdiff;
            break;
        case 'L':
            status->flags |= E_double;
            break;
        default:
            --spec;
            break;
    }

    /* Conversion specifier */
    switch ( *spec )
    {
        case 'd':
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
            break;
        case 's':
            break;
        case 'p':
            /* uint2base( 16, (intptr_t)value, true ) */
        case 'n':
            break;
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
                    value = (uintmax_t)(unsigned char)va_arg( status->ap, int );
                    break;
                case E_short:
                    value = (uintmax_t)(unsigned short)va_arg( status->ap, int );
                    break;
                case 0:
                    value = (uintmax_t)va_arg( status->ap, unsigned int );
                    break;
                case E_long:
                    value = (uintmax_t)va_arg( status->ap, unsigned long );
                    break;
                case E_llong:
                    value = (uintmax_t)va_arg( status->ap, unsigned long long );
                    break;
                case E_size:
                    value = (uintmax_t)va_arg( status->ap, size_t );
                    break;
            }
            ++(status->this);
            if ( ( value / status->base ) != 0 )
            {
                int2base( (intmax_t)(value / status->base), status );
            }
            int digit = value % status->base;
            if ( digit < 0 )
            {
                digit *= -1;
            }
            if ( status->flags & E_lower )
            {
                DELIVER( _PDCLIB_digits[ digit ] );
            }
            else
            {
                DELIVER( _PDCLIB_Xdigits[ digit ] );
            }
        }
        else
        {
            switch ( status->flags & ( E_char | E_short | E_long | E_llong | E_intmax ) )
            {
                case E_char:
                    int2base( (intmax_t)(char)va_arg( status->ap, int ), status );
                    break;
                case E_short:
                    int2base( (intmax_t)(short)va_arg( status->ap, int ), status );
                    break;
                case 0:
                    int2base( (intmax_t)va_arg( status->ap, int ), status );
                    break;
                case E_long:
                    int2base( (intmax_t)va_arg( status->ap, long ), status );
                    break;
                case E_llong:
                    int2base( (intmax_t)va_arg( status->ap, long long ), status );
                    break;
                case E_ptrdiff:
                    int2base( (intmax_t)va_arg( status->ap, ptrdiff_t ), status );
                    break;
                case E_intmax:
                    int2base( va_arg( status->ap, intmax_t ), status );
                    break;
            }
        }
        if ( status->flags & E_minus )
        {
            while ( status->this < status->width )
            {
                DELIVER( ' ' );
                ++(status->this);
            }
        }
        if ( status->i >= status->n )
        {
            status->s[status->n - 1] = '\0';
        }
    }
    return ++spec;
}

inline void test( size_t n, const char * expect, ... )
{
    char * buffer1 = malloc( 50 );
    char * buffer2 = malloc( 50 );
    int myrc;
    int rc;
    va_list ap;
    va_start( ap, expect );
    myrc = _PDCLIB_sprintf( buffer1, n, expect, ap );
    rc = vsnprintf( buffer2, n, expect, ap );
    if ( ( strcmp( buffer1, buffer2 ) != 0 ) || ( myrc != rc ) )
    {
        printf( "Output '%s', RC %d\nExpect '%s', RC %d\n\n", buffer1, myrc, buffer2, rc );
    }
    free( buffer1 );
    free( buffer2 );
}

int _PDCLIB_sprintf( char * buffer, size_t n, const char * format, va_list ap )
{
    struct status_t status = { 0, 0, n, 0, 0, buffer, 0, 0, NULL, ap };
    while ( *format != '\0' )
    {
        const char * rc;
        if ( ( *format != '%' ) || ( ( rc = parse_out( format, &status ) ) == format ) )
        {
            /* No conversion specifier, print verbatim */
            buffer[ status.i++ ] = *(format++);
        }
        else
        {
            /* Continue parsing after conversion specifier */
            format = rc;
        }
    }
    buffer[ status.i ] = '\0';
    return status.i;
}

#if 0
int _PDCLIB_fprintf( FILE * stream, const char * format, va_list ap )
{
    struct status_t status = { 0, 0, SIZE_MAX, 0, 0, NULL, 0, 0, stream, ap };
    while ( *format != '\0' )
    {
        const char * rc;
        if ( ( *format != '%' ) || ( ( rc = parse_out( format, &status, ap ) ) == format ) )
        {
            /* No conversion specifier, print verbatim */
            putc( *(format++), stream );
        }
        else
        {
            /* Continue parsing after conversion specifier */
            format = rc;
        }
    }
    return status.i;
}
#endif
