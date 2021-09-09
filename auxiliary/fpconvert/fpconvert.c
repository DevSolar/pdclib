#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _PDCLIB_FLT_BIAS 127
#define _PDCLIB_DBL_BIAS 1023
#define _PDCLIB_FLT80_BIAS 16383
#define _PDCLIB_FLT128_BIAS 16383

char * nibbles[] =
{
    "0000", "0001", "0010", "0011",
    "0100", "0101", "0110", "0111",
    "1000", "1001", "1010", "1011",
    "1100", "1101", "1110", "1111"
};

union
{
    float value;
    unsigned char byte[ sizeof( float ) ];
} flt;

union
{
    double value;
    unsigned char byte[ sizeof( double ) ];
} dbl;

#if __LDBL_DECIMAL_DIG__ == 21
#define FLOAT80
union
{
    long double value;
    unsigned char byte[ sizeof( long double ) ];
} flt80;
#endif

#if __LDBL_DECIMAL_DIG__ == 36 || __FLT128_DECIMAL_DIG__ == 36
#define FLOAT128
#if __LDBL_DECIMAL_DIG__ == 36
typedef long double float128_t;
#define strtof128 strtold
#elif __FLT128_DECIMAL_DIG__ == 36
#include "quadmath.h"
typedef __float128 float128_t;
#define strtof128 strtoflt128
#endif
union
{
    float128_t value;
    unsigned char byte[ sizeof( float128_t ) ];
} flt128;
#endif

void shl( unsigned char * byte, size_t size )
{
    for ( unsigned i = size; i > 1; --i )
    {
        byte[ i - 1 ] <<= 1;
        byte[ i - 1 ] |= ( byte[ i - 2 ] >> 7 );
    }

    byte[ 0 ] <<= 1;
}

int main( int argc, char * argv[] )
{
    unsigned char    flt_byte[ sizeof( float ) ];
    unsigned char    dbl_byte[ sizeof( double ) ];
#ifdef FLOAT80
    unsigned char  flt80_byte[ sizeof( long double ) ];
#endif
#ifdef FLOAT128
    unsigned char flt128_byte[ sizeof( float128_t ) ];
#endif

    int exp;

    if ( argc < 2 || argc > 3 )
    {
        puts( "Usage: fpconvert <floating-point> [<conversion>]" );
        return 1;
    }

    flt.value    =    strtof( argv[1], NULL );
    dbl.value    =    strtod( argv[1], NULL );
#ifdef FLOAT80
    flt80.value  =   strtold( argv[1], NULL );
#endif
#ifdef FLOAT128
    flt128.value = strtof128( argv[1], NULL );
#endif

    memcpy(    flt_byte,    &flt.value, sizeof( float ) );
    memcpy(    dbl_byte,    &dbl.value, sizeof( double ) );
#ifdef FLOAT80
    memcpy(  flt80_byte,  &flt80.value, sizeof( long double ) );
#endif
#ifdef FLOAT128
    memcpy( flt128_byte, &flt128.value, sizeof( float128_t ) );
#endif

    puts( "------------------- float --------------------" );

    printf( "Bits: %zu\n", sizeof( float ) * CHAR_BIT );

    printf( "Hex:  %02x%02x.%02x%02x.\n", flt_byte[ 3 ], flt_byte[ 2 ], flt_byte[ 1 ], flt_byte[ 0 ] );

    /* Asserting identity of memcpy bytes and union bytes */
    for ( unsigned i = 0; i < sizeof( float ); ++i )
    {
        assert( flt_byte[ i ] == flt.byte[ i ] );
    }

    /* Printing binary dump of whole register */
    printf( "Bin:  seee.eeee.efff.ffff.ffff.ffff.ffff.ffff.\n      " );

    for ( unsigned i = sizeof( float ); i > 0; --i )
    {
        unsigned high_nibble = ( flt_byte[ i - 1 ] & 0xf0 ) >> 4;
        printf( "%s.%s.", nibbles[ high_nibble ], nibbles[ flt_byte[ i - 1 ] & 0x0f ] );
    }

    puts( "" );

    /* Extracting exponent from memcpy bytes */
    exp = ( ( (unsigned)flt_byte[3] & 0x7f ) << 1 ) | ( (unsigned)flt_byte[2] >> 7 );

    printf( "Exp:  %#x      Unbiased: %d\n", exp, exp - _PDCLIB_FLT_BIAS );

    puts( "------------------ double --------------------" );

    printf( "Bits: %zu\n", sizeof( double ) * CHAR_BIT );

    printf( "Hex:  %02x%02x.%02x%02x.%02x%02x.%02x%02x.\n", dbl_byte[ 7 ], dbl_byte[ 6 ], dbl_byte[ 5 ], dbl_byte[ 4 ], dbl_byte[ 3 ], dbl_byte[ 2 ], dbl_byte[ 1 ], dbl_byte[ 0 ] );

    /* Asserting identity of memcpy bytes and union bytes */
    for ( unsigned i = 0; i < sizeof( double ); ++i )
    {
        assert( dbl_byte[ i ] == dbl.byte[ i ] );
    }

    /* Printing binary dump of whole register */
    printf( "Bin:  seee.eeee.eeee.ffff.ffff.ffff.ffff.ffff.\n      " );

    for ( unsigned i = sizeof( double ); i > 0; --i )
    {
        unsigned high_nibble = ( dbl_byte[ i - 1 ] & 0xf0 ) >> 4;
        printf( "%s.%s.", nibbles[ high_nibble ], nibbles[ dbl_byte[ i - 1 ] & 0x0f ] );
        if ( ( i > 1 ) && ( i % 4 == 1 ) ) printf( "\n      ffff.ffff.ffff.ffff.ffff.ffff.ffff.ffff.\n      " );
    }

    puts( "" );

    /* Extracting exponent from memcpy bytes */
    exp = ( ( (unsigned)dbl_byte[7] & 0x7f ) << 4 ) | ( ( (unsigned)dbl_byte[6] & 0xf0 ) >> 4 );

    printf( "Exp:  %#x      Unbiased: %d\n", exp, exp - _PDCLIB_DBL_BIAS );

#ifdef FLOAT80
    puts( "------------------ float80 -------------------" );

    printf( "Bits: %zu (48 unused, 80 encoded)\n", sizeof( long double ) * CHAR_BIT );

    printf( "Hex:  %02x%02x.%02x%02x.%02x%02x.%02x%02x.%02x%02x.\n",
            flt80_byte[ 9 ], flt80_byte[ 8 ],
            flt80_byte[ 7 ], flt80_byte[ 6 ], flt80_byte[ 5 ], flt80_byte[ 4 ],
            flt80_byte[ 3 ], flt80_byte[ 2 ], flt80_byte[ 1 ], flt80_byte[ 0 ] );

    /* Asserting identity of memcpy bytes and union bytes */
    for ( unsigned i = 0; i < sizeof( long double ); ++i )
    {
        assert( flt80_byte[ i ] == flt80.byte[ i ] );
    }

    /* Printing binary dump of significant parts of register */
    printf( "Bin:  seee.eeee.eeee.eeee.\n      " );

    for ( unsigned i = sizeof( long double ) - 6; i > 0; --i )
    {
        unsigned high_nibble = ( flt80_byte[ i - 1 ] & 0xf0 ) >> 4;
        printf( "%s.%s.", nibbles[ high_nibble ], nibbles[ flt80_byte[ i - 1 ] & 0x0f ] );
        if ( i == 9 ) printf( "\n      ifff.ffff.ffff.ffff.ffff.ffff.ffff.ffff.\n      " );
        if ( i == 5 ) printf( "\n      ffff.ffff.ffff.ffff.ffff.ffff.ffff.ffff.\n      " );
    }

    puts( "" );

    /* Extracting exponent from memcpy bytes */
    exp = ( ( (unsigned)flt80_byte[9] & 0x7f ) << 8 ) | (unsigned)flt80_byte[8];

    printf( "Exp:  %#x      Unbiased: %d\n", exp, exp - _PDCLIB_FLT80_BIAS );

    /* Printing decimal */
    printf( "Dec:  %d\n", ( (unsigned)flt80_byte[7] & 0x80 ) == 0x80 );

#endif

#ifdef FLOAT128
    puts( "----------------- float128 -------------------" );

    printf( "Bits: %zu\n", sizeof( float128_t ) * CHAR_BIT );

    printf( "Hex:  %02x%02x.%02x%02x.%02x%02x.%02x%02x.%02x%02x.%02x%02x.%02x%02x.%02x%02x.\n",
            flt128_byte[ 15 ], flt128_byte[ 14 ], flt128_byte[ 13 ], flt128_byte[ 12 ],
            flt128_byte[ 11 ], flt128_byte[ 10 ], flt128_byte[  9 ], flt128_byte[  8 ],
            flt128_byte[  7 ], flt128_byte[  6 ], flt128_byte[  5 ], flt128_byte[  4 ],
            flt128_byte[  3 ], flt128_byte[  2 ], flt128_byte[  1 ], flt128_byte[  0 ] );

    /* Asserting identity of memcpy bytes and union bytes */
    for ( unsigned i = 0; i < sizeof( float128_t ); ++i )
    {
        assert( flt128_byte[ i ] == flt128.byte[ i ] );
    }

    /* Printing binary dump of whole register */
    printf( "Bin:  seee.eeee.eeee.eeee.ffff.ffff.ffff.ffff.\n      " );

    for ( unsigned i = sizeof( float128_t ); i > 0; --i )
    {
        unsigned high_nibble = ( flt128_byte[ i - 1 ] & 0xf0 ) >> 4;
        printf( "%s.%s.", nibbles[ high_nibble ], nibbles[ flt128_byte[ i - 1 ] & 0x0f ] );
        if ( ( i > 1 ) && ( i % 4 == 1 ) ) printf( "\n      ffff.ffff.ffff.ffff.ffff.ffff.ffff.ffff.\n      " );
    }

    puts( "" );

    /* Extracting exponent from memcpy bytes */
    exp = ( ( (unsigned)flt128_byte[ 15 ] & 0x7f ) << 8 ) | (unsigned)flt128_byte[ 14 ];

    printf( "Exp:  %#x      Unbiased: %d\n", exp, exp - _PDCLIB_FLT128_BIAS );
#endif

    puts( "----------------------------------------------" );

    if ( argc == 3 )
    {
        char conversion[ 10 ] = "%";
        size_t len;

        if ( argv[ 2 ][ 0 ] == '%' )
        {
            ++argv[ 2 ];
        }

        if ( strlen( argv[ 2 ] ) > 8 )
        {
            puts( "Conversion too long (8 characters max)" );
            return 1;
        }

        /* Print the fp value with the conversion given */
        strcat( conversion, argv[ 2 ] );
        strcat( conversion, "\n" );
        printf( conversion, strtod( argv[ 1 ], NULL ) );

        /* Do the same with long double precision */
        len = strlen( conversion );
        memmove( conversion + len - 1, conversion + len - 2, 3 );
        conversion[ len - 2 ] = 'L';
        printf( conversion, strtold( argv[ 1 ], NULL ) );
    }
}
