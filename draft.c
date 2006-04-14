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
};

const char * parse_out( const char * spec, struct status_t * status, va_list ap );
inline void test( char * buffer, size_t n, const char * expect, struct status_t * status, ... );

/* The following only for testing. */
#include <limits.h>
#include <string.h>

int main( void )
{
    struct status_t status;
    char * buffer = malloc( 50 );
    status.s = calloc( 50, 1 );
    status.i = 0;
    status.stream = NULL;
    status.n = SIZE_MAX;
    puts( "- Signed min / max -\n" );
//    inline void test( char * buffer, size_t n, const char * expect, struct status_t * status, ... );
    test( buffer, SIZE_MAX, "%hhd", &status, CHAR_MIN );
    test( buffer, SIZE_MAX, "%hhd", &status, CHAR_MAX );
    test( buffer, SIZE_MAX, "%hhd", &status, 0 );
    test( buffer, SIZE_MAX, "%hd", &status, SHRT_MIN );
    test( buffer, SIZE_MAX, "%hd", &status, SHRT_MAX );
    test( buffer, SIZE_MAX, "%hd", &status, 0 );
    test( buffer, SIZE_MAX, "%d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%d", &status, 0 );
    test( buffer, SIZE_MAX, "%ld", &status, LONG_MIN );
    test( buffer, SIZE_MAX, "%ld", &status, LONG_MAX );
    test( buffer, SIZE_MAX, "%ld", &status, 0l );
    test( buffer, SIZE_MAX, "%lld", &status, LLONG_MIN );
    test( buffer, SIZE_MAX, "%lld", &status, LLONG_MAX );
    test( buffer, SIZE_MAX, "%lld", &status, 0ll );
    puts( "- Unsigned min / max -\n" );
    test( buffer, SIZE_MAX, "%hhu", &status, UCHAR_MAX );
    test( buffer, SIZE_MAX, "%hhu", &status, (unsigned char)-1 );
    test( buffer, SIZE_MAX, "%hu", &status, USHRT_MAX );
    test( buffer, SIZE_MAX, "%hu", &status, (unsigned short)-1 );
    test( buffer, SIZE_MAX, "%u", &status, UINT_MAX );
    test( buffer, SIZE_MAX, "%u", &status, -1u );
    test( buffer, SIZE_MAX, "%lu", &status, ULONG_MAX );
    test( buffer, SIZE_MAX, "%lu", &status, -1ul );
    test( buffer, SIZE_MAX, "%llu", &status, ULLONG_MAX );
    test( buffer, SIZE_MAX, "%llu", &status, -1ull );
    puts( "- Hex and Octal, normal and alternative, upper and lowercase -\n" );
    test( buffer, SIZE_MAX, "%X", &status, UINT_MAX );
    test( buffer, SIZE_MAX, "%#X", &status, -1u );
    test( buffer, SIZE_MAX, "%x", &status, UINT_MAX );
    test( buffer, SIZE_MAX, "%#x", &status, -1u );
    test( buffer, SIZE_MAX, "%o", &status, UINT_MAX );
    test( buffer, SIZE_MAX, "%#o", &status, -1u );
    puts( "- Plus flag -\n" );
    test( buffer, SIZE_MAX, "%+d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%+d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%+d", &status, 0 );
    test( buffer, SIZE_MAX, "%+u", &status, UINT_MAX );
    test( buffer, SIZE_MAX, "%+u", &status, -1u );
    puts( "- Space flag -\n" );
    test( buffer, SIZE_MAX, "% d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "% d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "% d", &status, 0 );
    test( buffer, SIZE_MAX, "% u", &status, UINT_MAX );
    test( buffer, SIZE_MAX, "% u", &status, -1u );
    puts( "- Field width -\n" );
    test( buffer, SIZE_MAX, "%9d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%9d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%10d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%10d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%11d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%11d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%12d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%12d", &status, INT_MAX );
    puts( "- Field width (left bound) -\n" );
    test( buffer, SIZE_MAX, "%-9d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%-9d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%-10d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%-10d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%-11d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%-11d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%-12d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%-12d", &status, INT_MAX );
    puts( "- Field width, zero padding -\n");
    test( buffer, SIZE_MAX, "%09d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%09d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%010d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%010d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%011d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%011d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%012d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%012d", &status, INT_MAX );
    puts( "- Field width, zero padding (left bound) -\n" );
    test( buffer, SIZE_MAX, "%-09d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%-09d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%-010d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%-010d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%-011d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%-011d", &status, INT_MAX );
    test( buffer, SIZE_MAX, "%-012d", &status, INT_MIN );
    test( buffer, SIZE_MAX, "%-012d", &status, INT_MAX );
    return 0;
}

/* x - the character to be delivered
   i - pointer to number of characters already delivered in this call
   n - pointer to maximum number of characters to be delivered in this call
   s - the buffer into which the character shall be delivered
   TODO: Overruns.
*/
#define DELIVER( x ) do { if ( status->i < status->n ) { if ( status->stream != NULL ) putc( x, status->stream ); else status->s[status->i] = x; } ++(status->i); } while ( 0 )

static void int2base( intmax_t value, struct status_t * status )
{
    ++(status->this);
    if ( ( value / status->base ) != 0 )
    {
        int2base( value / status->base, status );
    }
    else
    {
        char preface[3] = "\0\0";
        size_t preidx = 0;
        if ( ( status->flags & E_alt ) && ( status->base == 16 || status->base == 8 ) )
        {
            preface[ preidx++ ] = '0';
            if ( status->base == 16 )
            {
                preface[ preidx++ ] = ( status->flags & E_lower ) ? 'x' : 'X';
            }
        }
        if ( value < 0 )
        {
            preface[ preidx++ ] = '-';
        }
        else if ( ! ( status->flags & E_unsigned ) )
        {
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
            while ( ( status->this + preidx ) < status->width )
            {
                DELIVER( ' ' );
                ++(status->this);
            }
        }
        preidx = 0;
        while ( preface[ preidx ] != '\0' )
        {
            DELIVER( preface[ preidx++ ] );
            ++(status->this);
        }
        if ( ( ! ( status->flags & E_minus ) ) && ( status->flags & E_zero ) )
        {
            while ( status->this < status->width )
            {
                DELIVER( '0' );
                ++(status->this);
            }
        }
    }
    {
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
}

const char * parse_out( const char * spec, struct status_t * status, va_list ap )
{
    const char * orig_spec = spec;
#if 0
    if ( *(++spec) == '%' )
    {
        DELIVER( *spec );
        return spec;
    }
#endif
    /* Initializing status structure */
    status->flags = 0;
    status->base = 0;
    status->this = 0;
    status->width = 0;
    status->prec = 0;

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
        if ( ( status->width = va_arg( ap, int ) ) < 0 )
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
            status->prec = va_arg( ap, int );
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
        }
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
                    value = (uintmax_t)(unsigned char)va_arg( ap, int );
                    break;
                case E_short:
                    value = (uintmax_t)(unsigned short)va_arg( ap, int );
                    break;
                case 0:
                    value = (uintmax_t)va_arg( ap, unsigned int );
                    break;
                case E_long:
                    value = (uintmax_t)va_arg( ap, unsigned long );
                    break;
                case E_llong:
                    value = (uintmax_t)va_arg( ap, unsigned long long );
                    break;
                case E_size:
                    value = (uintmax_t)va_arg( ap, size_t );
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
                    int2base( (intmax_t)(char)va_arg( ap, int ), status );
                    break;
                case E_short:
                    int2base( (intmax_t)(short)va_arg( ap, int ), status );
                    break;
                case 0:
                    int2base( (intmax_t)va_arg( ap, int ), status );
                    break;
                case E_long:
                    int2base( (intmax_t)va_arg( ap, long ), status );
                    break;
                case E_llong:
                    int2base( (intmax_t)va_arg( ap, long long ), status );
                    break;
                case E_ptrdiff:
                    int2base( (intmax_t)va_arg( ap, ptrdiff_t ), status );
                    break;
                case E_intmax:
                    int2base( va_arg( ap, intmax_t ), status );
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

inline void test( char * buffer, size_t n, const char * expect, struct status_t * status, ... )
{
    int rc;
    va_list ap;
    va_start( ap, status );
    status->n = n;
    status->i = 0;
    memset( status->s, '\0', 50 );
    parse_out( expect + 1, status, ap );
    rc = vsnprintf( buffer, n, expect, ap );
    if ( ( strcmp( status->s, buffer ) != 0 ) || ( status->i != rc ) )
    {
        printf( "Output '%s', RC %d\nExpect '%s', RC %d\n\n", status->s, status->i, buffer, rc );
    }
}

#if 0
int _PDCLIB_fprintf( FILE * stream, const char * format, va_list ap )
{
    char * buffer = malloc( 50 );
    struct status_t status = { 0, 0, SIZE_MAX, 0, 0, /* stream->buffer */ buffer, 0, 0, stream };
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
