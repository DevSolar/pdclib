#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#undef TEST
#include </home/solar/src/pdclib/functions/_PDCLIB/digits.c>

/* Using an integer's bits as flags for both the conversion flags and length
   modifiers.
*/
#define E_minus   1<<0
#define E_plus    1<<1
#define E_alt     1<<2
#define E_space   1<<3
#define E_zero    1<<4
#define E_done    1<<5
#define E_char    1<<6
#define E_short   1<<7
#define E_long    1<<8
#define E_llong   1<<9
#define E_intmax  1<<10
#define E_size    1<<11
#define E_ptrdiff 1<<12
#define E_double  1<<13
#define E_lower   1<<14
#define E_term    1<<15

void parse_out( const char * spec, va_list ap );

struct status_t
{
    int    base;  /* base to which the value shall be converted              */
    int    flags; /* flags and length modifiers                              */
    size_t n;     /* maximum number of characters to be written              */
    size_t i;     /* number of characters already written                    */
    size_t this;  /* number of output chars in the current conversion        */
    char * s;     /* target buffer                                           */
    size_t width; /* width of current field                                  */
    int    prec;  /* precision of current field                              */
};

/* x - the character to be delivered
   i - pointer to number of characters already delivered in this call
   n - pointer to maximum number of characters to be delivered in this call
   s - the buffer into which the character shall be delivered
   TODO: Overruns.
*/
#define DELIVER( x ) if ( status->i < status->n ) status->s[status->i] = x; ++(status->i)

/* TODO: Left / right alignment - requires track-keeping of width and printed chars.
   "Father function", die für right alignment "tail recursive" gerufen wird, und
   "after" für left alignment? Parameter als struct?
*/

static void int2base( int value, struct status_t * status )
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
        else
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
    if ( value < 0 )
    {
        value *= -1;
    }
    if ( status->flags & E_lower )
    {
        DELIVER( _PDCLIB_digits[ value % status->base ] );
    }
    else
    {
        DELIVER( toupper( _PDCLIB_digits[ value % status->base ] ) );
    }
}

static void padwrap( int value, struct status_t * status )
{
    int2base( value, status );
    if ( status->flags & E_minus )
    {
        while ( status->this < status->width )
        {
            DELIVER( ' ' );
            ++(status->this);
        }
    }
    if ( status->i == status->n )
    {
        status->s[status->i] = '\0';
    }
}

void parse_out( const char * spec, va_list ap )
{
    /* TODO: '%' handled correctly? */
    struct status_t status = { 0, 0, 0, 0, 0, NULL, 0, EOF };
    /* First come 0..n flags */
    while ( ! ( status.flags & E_done ) )
    {
        switch ( *(++spec) )
        {
            case '-':
                status.flags |= E_minus;
                break;
            case '+':
                status.flags |= E_plus;
                break;
            case '#':
                status.flags |= E_alt;
                break;
            case ' ':
                status.flags |= E_space;
                break;
            case '0':
                status.flags |= E_zero;
                break;
            default:
                status.flags |= E_done;
                break;
        }
    }
    if ( *spec == '*' )
    {
        /* Retrieve width value from argument stack */
        if ( ( status.width = va_arg( ap, int ) ) < 0 )
        {
            /* Negative value is '-' flag plus absolute value */
            status.flags |= E_minus;
            status.width *= -1;
        }
        ++spec;
    }
    else
    {
        /* If a width is given, strtol() will return its value. If not given,
           strtol() will return zero. In both cases, endptr will point to the
           rest of the conversion specifier.
        */
        char * endptr;
        status.width = (int)strtol( spec, &endptr, 10 );
        spec = endptr;
    }
    if ( *spec == '.' )
    {
        if ( *(++spec) == '*' )
        {
            /* Retrieve precision value from argument stack. A negative value
               is as if no precision is given - as precision is initalized to
               EOF (negative), there is no need for testing for negative here.
            */
            status.prec = va_arg( ap, int );
        }
        else
        {
            char * endptr;
            status.prec = (int)strtol( spec, &endptr, 10 );
            spec = endptr;
        }
    }
    /* We step one character ahead in any case, and step back only if we find
       there has been no length modifier (or step ahead another character if it
       has been "hh" or "ll").
    */
    switch ( *(spec++) )
    {
        case 'h':
            if ( *spec == 'h' )
            {
                status.flags |= E_char;
                ++spec;
            }
            else
            {
                status.flags |= E_short;
            }
            break;
        case 'l':
            if ( *spec == 'l' )
            {
                status.flags |= E_llong;
                ++spec;
            }
            else
            {
                status.flags |= E_long;
            }
            break;
        case 'j':
            status.flags |= E_intmax;
            break;
        case 'z':
            status.flags |= E_size;
            break;
        case 't':
            status.flags |= E_ptrdiff;
            break;
        case 'L':
            status.flags |= E_double;
            break;
        default:
            ++spec;
            break;
    }
    switch ( *spec )
    {
        case 'd':
        case 'i':
            /* int2base( 10, value, true ) */
            break;
        case 'o':
            /* int2base( 8, value, true ) */
            break;
        case 'u':
            /* uint2base( 10, value, true ) */
            break;
        case 'x':
            /* uint2base( 16, value, true ) */
            break;
        case 'X':
            /* uint2base( 16, value, false ) */
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
            break;
        default:
            // undefined
            return;
    }
}

/*
static void int2base( int value, int base, struct status_t * status )

#define E_minus   1<<0
#define E_plus    1<<1
#define E_alt     1<<2
#define E_space   1<<3
#define E_zero    1<<4
#define E_done    1<<5
#define E_char    1<<6
#define E_short   1<<7
#define E_long    1<<8
#define E_llong   1<<9
#define E_intmax  1<<10
#define E_size    1<<11
#define E_ptrdiff 1<<12
#define E_double  1<<13
#define E_lower   1<<14

        struct status_t
{
    int    flags; 
    size_t n;     
    size_t i;     
    char * s;     
    size_t width; 
    size_t prec;  
};
*/

#define TESTCASE( _flags, _n, _width, _prec, _value, _base, _expect ) \
    status.flags = _flags | E_term; \
    status.n = _n; \
    status.i = 0; \
    status.width = _width; \
    status.prec = _prec; \
    status.base = _base; \
    status.this = 0; \
    memset( status.s, '\0', 20 ); \
    padwrap( _value, &status ); \
    printf( "Output '%s', RC %d \t- ", status.s, status.i ); \
    rc = snprintf( buffer, _n, _expect, _value ); \
    printf( "Expect '%s', RC %d\n", buffer, rc );

int main()
{
    struct status_t status;
    int rc;
    char * buffer = malloc( 20 );
    status.s = malloc( 20 );
    TESTCASE( E_plus, 5, 0, 0, 1234, 10, "%+d" );
    TESTCASE( E_space, 3, 0, 0, 1234, 10, "% d" );
    TESTCASE( E_space, 3, 0, 0, -1234, 10, "% d" );
    TESTCASE( E_plus, 3, 0, 0, -1234, 10, "%+d" );
    TESTCASE( E_done, 4, 0, 0, 65535, 16, "%X" );
    TESTCASE( E_lower | E_alt, 4, 0, 0, 65534, 16, "%#x" );
    TESTCASE( E_done, 4, 0, 0, 62, 8, "%o" );
    TESTCASE( E_alt, 4, 0, 0, 62, 8, "%#o" );
    TESTCASE( E_done, 6, 6, 0, 1234, 10, "%6d" );
    TESTCASE( E_minus, 6, 6, 0, 1234, 10, "%-6d" );
    TESTCASE( E_minus, 6, 2, 0, 1234, 10, "%-2d" );
    TESTCASE( E_done, 6, 2, 0, 1234, 10, "%2d" );
    TESTCASE( E_zero, 6, 6, 0, -1234, 10, "%06d" );
    TESTCASE( E_zero, 7, 7, 0, -65535, 16, "%07X" );
    TESTCASE( E_zero | E_minus, 6, 6, 0, 1234, 10, "%-06d" );
    TESTCASE( E_plus, 6, 6, 0, 1234, 10, "%+6d" );
    TESTCASE( E_space, 6, 6, 0, 1234, 10, "% 6d" );
    TESTCASE( E_space, 6, 6, 0, -1234, 10, "% 6d" );
    TESTCASE( E_space | E_minus, 6, 6, 0, -1234, 10, "%- 6d" );
    return 0;
}
