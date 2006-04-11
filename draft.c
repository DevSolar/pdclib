#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>

#undef TEST
#include </home/solar/src/pdclib/functions/_PDCLIB/digits.c>

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
    int_fast16_t  flags; /* flags and length modifiers                       */
    size_t        n;     /* maximum number of characters to be written       */
    size_t        i;     /* number of characters already written             */
    size_t        this;  /* number of output chars in the current conversion */
    char *        s;     /* target buffer                                    */
    size_t        width; /* width of current field                           */
    size_t        prec;  /* precision of current field                       */
};

/* x - the character to be delivered
   i - pointer to number of characters already delivered in this call
   n - pointer to maximum number of characters to be delivered in this call
   s - the buffer into which the character shall be delivered
   TODO: Overruns.
*/
#define DELIVER( x ) do { if ( status->i < status->n ) status->s[status->i] = x; ++(status->i); } while ( 0 )

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
        if ( ! ( ( status->flags & E_minus ) || ( status->flags & E_zero ) ) )
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
        DELIVER( toupper( _PDCLIB_digits[ digit ] ) );
    }
    }
}

static void padwrap( intmax_t value, struct status_t * status )
{
    if ( status->flags & E_char )
    {
        value = (char)value;
    }
    else if ( status->flags & E_short )
    {
        value = (short)value;
    }
    else if ( status->flags & E_long )
    {
        value = (long)value;
    }
    else if ( status->flags & E_llong )
    {
        value = (long long)value;
    }
    else if ( status->flags & E_ptrdiff )
    {
        value = (ptrdiff_t)value;
    }
    else if ( ! ( status->flags & E_intmax ) )
    {
        value = (int)value;
    }
    int2base( value, status );
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

static void upadwrap( uintmax_t value, struct status_t * status )
{
    if ( status->flags & E_char )
    {
        value = (unsigned char)value;
    }
    else if ( status->flags & E_short )
    {
        value = (unsigned short)value;
    }
    else if ( status->flags & E_long )
    {
        value = (unsigned long)value;
    }
    else if ( status->flags & E_llong )
    {
        value = (unsigned long long)value;
    }
    else if ( status->flags & E_size )
    {
        value = (size_t)value;
    }
    else
    {
        value = (unsigned int)value;
    }
    status->flags |= E_unsigned;
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
        DELIVER( toupper( _PDCLIB_digits[ digit ] ) );
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

void parse_out( const char * spec, struct status_t * status, va_list ap );

void parse_out( const char * spec, struct status_t * status, va_list ap )
{
    /* TODO: "%%" handled correctly? */

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
                /* TODO: Decimal point but no number - bad conversion specifier. */
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
            status->flags = E_unsigned;
            status->base = 16;
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
        case '%':
            // conversion specifier
            /* TODO: May this be accompaigned by flags, width, precision, length modifier at all? */
            break;
        default:
            /* TODO: No conversion specifier. Bad conversion. */
            return;
    }
    switch ( status->flags )
    {
        /* TODO */
    }
    if ( status->base != 0 )
    {
        /* Integer conversions */
        switch ( status->flags & ( E_char | E_short | E_long | E_llong | E_unsigned ) )
        {
            case E_char:
                padwrap( (intmax_t)(char)va_arg( ap, int ), status );
                break;
            case E_char | E_unsigned:
                upadwrap( (uintmax_t)(unsigned char)va_arg( ap, int ), status );
                break;
            case E_short:
                padwrap( (intmax_t)(short)va_arg( ap, int ), status );
                break;
            case E_short | E_unsigned:
                upadwrap( (uintmax_t)(unsigned short)va_arg( ap, int ), status );
                break;
            case 0:
                padwrap( (intmax_t)va_arg( ap, int ), status );
                break;
            case E_unsigned:
                upadwrap( (uintmax_t)va_arg( ap, unsigned int ), status );
                break;
            case E_long:
                padwrap( (intmax_t)va_arg( ap, long ), status );
                break;
            case E_long | E_unsigned:
                upadwrap( (uintmax_t)va_arg( ap, unsigned long ), status );
                break;
            case E_llong:
                padwrap( (intmax_t)va_arg( ap, long long ), status );
                break;
            case E_llong | E_unsigned:
                upadwrap( (uintmax_t)va_arg( ap, unsigned long long ), status );
                break;
        }
    }
}

void parse_out_wrapper( const char * spec, struct status_t * status, ... );

void parse_out_wrapper( const char * spec, struct status_t * status, ... )
{
    va_list ap;
    va_start( ap, status );
    parse_out( spec, status, ap );
    va_end( ap );
}

#define TESTCASE( _flags, _n, _width, _prec, _value, _base, _expect ) \
    status.flags = _flags; \
    status.n = _n; \
    status.i = 0; \
    status.width = _width; \
    status.prec = _prec; \
    status.base = _base; \
    status.this = 0; \
    memset( status.s, '\0', 50 ); \
    padwrap( (intmax_t)_value, &status ); \
    rc = snprintf( buffer, _n, _expect, _value ); \
    if ( ( strcmp( status.s, buffer ) != 0 ) || ( status.i != rc ) ) \
    { \
        printf( "Output '%s', RC %d\nExpect '%s', RC %d\n\n", status.s, status.i, buffer, rc ); \
    }

#define UTESTCASE( _flags, _n, _width, _prec, _value, _base, _expect ) \
    status.flags = _flags; \
    status.n = _n; \
    status.i = 0; \
    status.width = _width; \
    status.prec = _prec; \
    status.base = _base; \
    status.this = 0; \
    memset( status.s, '\0', 50 ); \
    upadwrap( (uintmax_t)_value, &status ); \
    rc = snprintf( buffer, _n, _expect, _value ); \
    if ( ( strcmp( status.s, buffer ) != 0 ) || ( status.i != rc ) ) \
    { \
        printf( "Output '%s', RC %d\nExpect '%s', RC %d\n\n", status.s, status.i, buffer, rc ); \
    }

int main( void )
{
    struct status_t status;
    int rc;
    char * buffer = malloc( 50 );
    status.s = calloc( 50, 1 );
    status.i = 0;
    status.n = SIZE_MAX;
    puts( "- parse_out() -\n" );
    parse_out_wrapper( "d", &status, 1234 );
    puts( status.s );
    puts( "- Signed min / max -\n" );
    TESTCASE( E_char, SIZE_MAX, 0, 0, CHAR_MIN, 10, "%hhd" );
    TESTCASE( E_char, SIZE_MAX, 0, 0, CHAR_MAX, 10, "%hhd" );
    TESTCASE( E_char, SIZE_MAX, 0, 0, 0, 10, "%hhd" );
    TESTCASE( E_short, SIZE_MAX, 0, 0, SHRT_MIN, 10, "%hd" );
    TESTCASE( E_short, SIZE_MAX, 0, 0, SHRT_MAX, 10, "%hd" );
    TESTCASE( E_short, SIZE_MAX, 0, 0, 0, 10, "%hd" );
    TESTCASE( E_done, SIZE_MAX, 0, 0, INT_MIN, 10, "%d" );
    TESTCASE( E_done, SIZE_MAX, 0, 0, INT_MAX, 10, "%d" );
    TESTCASE( E_done, SIZE_MAX, 0, 0, 0, 10, "%d" );
    TESTCASE( E_long, SIZE_MAX, 0, 0, LONG_MIN, 10, "%ld" );
    TESTCASE( E_long, SIZE_MAX, 0, 0, LONG_MAX, 10, "%ld" );
    TESTCASE( E_long, SIZE_MAX, 0, 0, 0l, 10, "%ld" );
    TESTCASE( E_llong, SIZE_MAX, 0, 0, LLONG_MIN, 10, "%lld" );
    TESTCASE( E_llong, SIZE_MAX, 0, 0, LLONG_MAX, 10, "%lld" );
    TESTCASE( E_llong, SIZE_MAX, 0, 0, 0ll, 10, "%lld" ); 
    puts( "- Unsigned min / max -\n" );
    UTESTCASE( E_char, SIZE_MAX, 0, 0, UCHAR_MAX, 10, "%hhu" );
    UTESTCASE( E_char, SIZE_MAX, 0, 0, (unsigned char)-1, 10, "%hhu" );
    UTESTCASE( E_short, SIZE_MAX, 0, 0, USHRT_MAX, 10, "%hu" );
    UTESTCASE( E_short, SIZE_MAX, 0, 0, (unsigned short)-1, 10, "%hu" );
    UTESTCASE( E_done, SIZE_MAX, 0, 0, UINT_MAX, 10, "%u" );
    UTESTCASE( E_done, SIZE_MAX, 0, 0, -1u, 10, "%u" );
    UTESTCASE( E_long, SIZE_MAX, 0, 0, ULONG_MAX, 10, "%lu" );
    UTESTCASE( E_long, SIZE_MAX, 0, 0, -1ul, 10, "%lu" );
    UTESTCASE( E_llong, SIZE_MAX, 0, 0, ULLONG_MAX, 10, "%llu" );
    UTESTCASE( E_llong, SIZE_MAX, 0, 0, -1ull, 10, "%llu" );
    puts( "- Hex and Octal, normal and alternative, upper and lowercase -\n" );
    UTESTCASE( E_done, SIZE_MAX, 0, 0, UINT_MAX, 16, "%X" );
    UTESTCASE( E_alt, SIZE_MAX, 0, 0, -1u, 16, "%#X" );
    UTESTCASE( E_done | E_lower, SIZE_MAX, 0, 0, UINT_MAX, 16, "%x" );
    UTESTCASE( E_alt | E_lower, SIZE_MAX, 0, 0, -1u, 16, "%#x" );
    UTESTCASE( E_done, SIZE_MAX, 0, 0, UINT_MAX, 8, "%o" );
    UTESTCASE( E_alt, SIZE_MAX, 0, 0, -1u, 8, "%#o" );
    puts( "- Plus flag -\n" );
    TESTCASE( E_plus, SIZE_MAX, 0, 0, INT_MIN, 10, "%+d" );
    TESTCASE( E_plus, SIZE_MAX, 0, 0, INT_MAX, 10, "%+d" );
    TESTCASE( E_plus, SIZE_MAX, 0, 0, 0, 10, "%+d" );
    UTESTCASE( E_plus, SIZE_MAX, 0, 0, UINT_MAX, 10, "%+u" );
    UTESTCASE( E_plus, SIZE_MAX, 0, 0, -1u, 10, "%+u" );
    puts( "- Space flag -\n" );
    TESTCASE( E_space, SIZE_MAX, 0, 0, INT_MIN, 10, "% d" );
    TESTCASE( E_space, SIZE_MAX, 0, 0, INT_MAX, 10, "% d" );
    TESTCASE( E_space, SIZE_MAX, 0, 0, 0, 10, "% d" );
    UTESTCASE( E_space, SIZE_MAX, 0, 0, UINT_MAX, 10, "% u" );
    UTESTCASE( E_space, SIZE_MAX, 0, 0, -1u, 10, "% u" );
    puts( "- Field width -\n" );
    TESTCASE( E_done, SIZE_MAX, 9, 0, INT_MIN, 10, "%9d" );
    TESTCASE( E_done, SIZE_MAX, 9, 0, INT_MAX, 10, "%9d" );
    TESTCASE( E_done, SIZE_MAX, 10, 0, INT_MIN, 10, "%10d" );
    TESTCASE( E_done, SIZE_MAX, 10, 0, INT_MAX, 10, "%10d" );
    TESTCASE( E_done, SIZE_MAX, 11, 0, INT_MIN, 10, "%11d" );
    TESTCASE( E_done, SIZE_MAX, 11, 0, INT_MAX, 10, "%11d" );
    TESTCASE( E_done, SIZE_MAX, 12, 0, INT_MIN, 10, "%12d" );
    TESTCASE( E_done, SIZE_MAX, 12, 0, INT_MAX, 10, "%12d" );
    puts( "- Field width (left bound) -\n" );
    TESTCASE( E_minus, SIZE_MAX, 9, 0, INT_MIN, 10, "%-9d" );
    TESTCASE( E_minus, SIZE_MAX, 9, 0, INT_MAX, 10, "%-9d" );
    TESTCASE( E_minus, SIZE_MAX, 10, 0, INT_MIN, 10, "%-10d" );
    TESTCASE( E_minus, SIZE_MAX, 10, 0, INT_MAX, 10, "%-10d" );
    TESTCASE( E_minus, SIZE_MAX, 11, 0, INT_MIN, 10, "%-11d" );
    TESTCASE( E_minus, SIZE_MAX, 11, 0, INT_MAX, 10, "%-11d" );
    TESTCASE( E_minus, SIZE_MAX, 12, 0, INT_MIN, 10, "%-12d" );
    TESTCASE( E_minus, SIZE_MAX, 12, 0, INT_MAX, 10, "%-12d" );
    puts( "- Field width, zero padding -\n");
    TESTCASE( E_done | E_zero, SIZE_MAX, 9, 0, INT_MIN, 10, "%09d" );
    TESTCASE( E_done | E_zero, SIZE_MAX, 9, 0, INT_MAX, 10, "%09d" );
    TESTCASE( E_done | E_zero, SIZE_MAX, 10, 0, INT_MIN, 10, "%010d" );
    TESTCASE( E_done | E_zero, SIZE_MAX, 10, 0, INT_MAX, 10, "%010d" );
    TESTCASE( E_done | E_zero, SIZE_MAX, 11, 0, INT_MIN, 10, "%011d" );
    TESTCASE( E_done | E_zero, SIZE_MAX, 11, 0, INT_MAX, 10, "%011d" );
    TESTCASE( E_done | E_zero, SIZE_MAX, 12, 0, INT_MIN, 10, "%012d" );
    TESTCASE( E_done | E_zero, SIZE_MAX, 12, 0, INT_MAX, 10, "%012d" );
    puts( "- Field width, zero padding (left bound) -\n" );
    TESTCASE( E_minus | E_zero, SIZE_MAX, 9, 0, INT_MIN, 10, "%-09d" );
    TESTCASE( E_minus | E_zero, SIZE_MAX, 9, 0, INT_MAX, 10, "%-09d" );
    TESTCASE( E_minus | E_zero, SIZE_MAX, 10, 0, INT_MIN, 10, "%-010d" );
    TESTCASE( E_minus | E_zero, SIZE_MAX, 10, 0, INT_MAX, 10, "%-010d" );
    TESTCASE( E_minus | E_zero, SIZE_MAX, 11, 0, INT_MIN, 10, "%-011d" );
    TESTCASE( E_minus | E_zero, SIZE_MAX, 11, 0, INT_MAX, 10, "%-011d" );
    TESTCASE( E_minus | E_zero, SIZE_MAX, 12, 0, INT_MIN, 10, "%-012d" );
    TESTCASE( E_minus | E_zero, SIZE_MAX, 12, 0, INT_MAX, 10, "%-012d" );
    return 0;
}
