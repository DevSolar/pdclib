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
} ldbl;
#endif

#if __LDBL_DECIMAL_DIG__ == 36 || __FLT128_DECIMAL_DIG__ == 36
#define FLOAT128
#if __LDBL_DECIMAL_DIG__ == 36
typedef long double float128_t;
#define strtof128 strtold
#elif __FLT128_DEVIMAL_DIG__ == 36
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
    unsigned char        ldbl[ sizeof( long double ) ];
#endif
#ifdef FLOAT128
    unsigned char flt128_byte[ sizeof( float128_t ) ];
#endif

    int exp;

    if ( argc != 2 )
    {
        puts( "Usage: fpconvert2 <floating-point>" );
        return 1;
    }

    flt.value    =    strtof( argv[1], NULL );
    dbl.value    =    strtod( argv[1], NULL );
#ifdef FLOAT80
    ldbl.value   =   strtold( argv[1], NULL );
#endif
#ifdef FLOAT128
    flt128.value = strtof128( argv[1], NULL );
#endif

    memcpy(    flt_byte,    &flt.value, sizeof( float ) );
    memcpy(    dbl_byte,    &dbl.value, sizeof( double ) );
#ifdef FLOAT80
    memcpy(   ldbl_byte,   &ldbl.value, sizeof( long double ) );
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
    printf( "Bin:  seee.eeee.emmm.mmmm.mmmm.mmmm.mmmm.mmmm.\n      " );

    for ( unsigned i = sizeof( float ); i > 0; --i )
    {
        unsigned high_nibble = ( flt_byte[ i - 1 ] & 0xf0 ) >> 4;
        printf( "%s.%s.", nibbles[ high_nibble ], nibbles[ flt_byte[ i - 1 ] & 0x0f ] );
    }

    puts( "" );

    /* Extracting exponent from memcpy bytes */
    exp = ( ( (unsigned)flt_byte[3] & 0x7f ) << 1 ) | ( (unsigned)flt_byte[2] >> 7 );

    printf( "Exp:  %#x      Bias: %#x\n", exp, exp - _PDCLIB_FLT_BIAS );

    /* Adjusting mantissa from memcpy bytes */
    shl( flt_byte, 3 );

    /* Printing binary dump of mantissa */
    printf( "Mant: mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.\n      " );

    for ( unsigned i = 3; i > 0; --i )
    {
        unsigned high_nibble = ( flt_byte[ i - 1 ] & 0xf0 ) >> 4;
        printf( "%s.%s.", nibbles[ high_nibble ], nibbles[ flt_byte[ i - 1 ] & 0x0f ] );
    }

    /* Printing hexadecimal dump of adjusted mantissa */
    printf( "\n      " );

    for ( unsigned i = 3; i > 0; --i )
    {
        printf( "       %02x.", flt_byte[ i - 1 ] );
    }

    puts( "" );

    puts( "------------------ double --------------------" );

    printf( "Bits: %zu\n", sizeof( double ) * CHAR_BIT );

    printf( "Hex:  %02x%02x.%02x%02x.%02x%02x.%02x%02x.\n", dbl_byte[ 7 ], dbl_byte[ 6 ], dbl_byte[ 5 ], dbl_byte[ 4 ], dbl_byte[ 3 ], dbl_byte[ 2 ], dbl_byte[ 1 ], dbl_byte[ 0 ] );

    /* Asserting identity of memcpy bytes and union bytes */
    for ( unsigned i = 0; i < sizeof( double ); ++i )
    {
        assert( dbl_byte[ i ] == dbl.byte[ i ] );
    }

    /* Printing binary dump of whole register */
    printf( "Bin:  seee.eeee.eeee.mmmm.mmmm.mmmm.mmmm.mmmm.\n      " );

    for ( unsigned i = sizeof( double ); i > 0; --i )
    {
        unsigned high_nibble = ( dbl_byte[ i - 1 ] & 0xf0 ) >> 4;
        printf( "%s.%s.", nibbles[ high_nibble ], nibbles[ dbl_byte[ i - 1 ] & 0x0f ] );
        if ( ( i > 1 ) && ( i % 4 == 1 ) ) printf( "\n      mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.\n      " );
    }

    puts( "" );

    /* Extracting exponent from memcpy bytes */
    exp = ( ( (unsigned)dbl_byte[7] & 0x7f ) << 4 ) | ( ( (unsigned)dbl_byte[6] & 0xf0 ) >> 4 );

    printf( "Exp:  %#x      Bias: %#x\n", exp, exp - _PDCLIB_DBL_BIAS );

    /* Adjusting mantissa from memcpy bytes */
    shl( dbl_byte, 7 );
    shl( dbl_byte, 7 );
    shl( dbl_byte, 7 );
    shl( dbl_byte, 7 );

    /* Printing binary dump of mantissa */
    printf( "Mant: mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.\n      " );

    for ( unsigned i = 7; i > 0; --i )
    {
        unsigned high_nibble = ( dbl_byte[ i - 1 ] & 0xf0 ) >> 4;
        printf( "%s.%s.", nibbles[ high_nibble ], nibbles[ dbl_byte[ i - 1 ] & 0x0f ] );
        if ( ( i > 1 ) && ( i % 4 == 1 ) ) printf( "\n      mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.xxxx.\n      " );
    }

    /* Printing hexadecimal dump of adjusted mantissa */
    printf( "\n      " );

    for ( unsigned i = 7; i > 0; --i )
    {
        printf( "       %02x.", dbl_byte[ i - 1 ] );
        if ( ( i > 1 ) && ( i % 4 == 1 ) ) printf( "\n      " );
    }

    puts( "" );

#ifdef FLOAT80
    puts( "------------------ float80 -------------------" );

    printf( "Bits: %zu (48 unused, 80 encoded)\n", sizeof( long double ) * CHAR_BIT );

    printf( "Hex:  %02x%02x.%02x%02x.%02x%02x.%02x%02x.%02x%02x.\n",
            ldbl_byte[ 9 ], ldbl_byte[ 8 ],
            ldbl_byte[ 7 ], ldbl_byte[ 6 ], ldbl_byte[ 5 ], ldbl_byte[ 4 ],
            ldbl_byte[ 3 ], ldbl_byte[ 2 ], ldbl_byte[ 1 ], ldbl_byte[ 0 ] );

    /* Asserting identity of memcpy bytes and union bytes */
    for ( unsigned i = 0; i < sizeof( long double ); ++i )
    {
        assert( ldbl_byte[ i ] == ldbl.byte[ i ] );
    }

    /* Printing binary dump of significant parts of register */
    printf( "Bin:  seee.eeee.eeee.eeee.\n      " );

    for ( unsigned i = sizeof( long double ) - 6; i > 0; --i )
    {
        unsigned high_nibble = ( ldbl_byte[ i - 1 ] & 0xf0 ) >> 4;
        printf( "%s.%s.", nibbles[ high_nibble ], nibbles[ ldbl_byte[ i - 1 ] & 0x0f ] );
        if ( i == 9 ) printf( "\n      immm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.\n      " );
        if ( i == 5 ) printf( "\n      mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.\n      " );
    }

    puts( "" );

    /* Extracting exponent from memcpy bytes */
    exp = ( ( (unsigned)ldbl_byte[9] & 0x7f ) << 8 ) | (unsigned)ldbl_byte[8];

    printf( "Exp:  %#x      Bias: %#x\n", exp, exp - _PDCLIB_LDBL_BIAS );

    /* Printing decimal */
    printf( "Dec:  %d\n", ( (unsigned)ldbl_byte[7] & 0x80 ) == 0x80 );

    /* Adjusting mantissa from memcpy bytes */
    shl( ldbl_byte, 7 );

    /* Printing binary dump of mantissa */
    printf( "Mant: mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.\n      " );

    for ( unsigned i = 8; i > 0; --i )
    {
        unsigned high_nibble = ( dbl_byte[ i - 1 ] & 0xf0 ) >> 4;
        printf( "%s.%s.", nibbles[ high_nibble ], nibbles[ dbl_byte[ i - 1 ] & 0x0f ] );
        if ( ( i > 1 ) && ( i % 4 == 1 ) ) printf( "\n      mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.\n      " );
    }

    /* Printing hexadecimal dump of mantissa */
    printf( "\n      " );

    for ( unsigned i = 8; i > 0; --i )
    {
        printf( "       %02x.", dbl_byte[ i - 1 ] );
    }

    puts( "" );
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
    printf( "Bin:  seee.eeee.eeee.eeee.mmmm.mmmm.mmmm.mmmm.\n      " );

    for ( unsigned i = sizeof( float128_t ); i > 0; --i )
    {
        unsigned high_nibble = ( flt128_byte[ i - 1 ] & 0xf0 ) >> 4;
        printf( "%s.%s.", nibbles[ high_nibble ], nibbles[ flt128_byte[ i - 1 ] & 0x0f ] );
        if ( ( i > 1 ) && ( i % 4 == 1 ) ) printf( "\n      mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.\n      " );
    }

    puts( "" );

    /* Extracting exponent from memcpy bytes */
    exp = ( ( (unsigned)flt128_byte[ 15 ] & 0x7f ) << 8 ) | (unsigned)flt128_byte[ 14 ];

    printf( "Exp:  %#x      Bias: %#x\n", exp, exp - _PDCLIB_FLT128_BIAS );

    /* Printing binary dump of mantissa */
    printf( "Mant: mmmm.mmmm.mmmm.mmmm.\n      " );

    for ( unsigned i = 14; i > 0; --i )
    {
        unsigned high_nibble = ( flt128_byte[ i - 1 ] & 0xf0 ) >> 4;
        printf( "%s.%s.", nibbles[ high_nibble ], nibbles[ flt128_byte[ i - 1 ] & 0x0f ] );
        if ( ( i > 1 ) && ( i % 4 == 1 ) ) printf( "\n      mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.mmmm.\n      " );
    }

    /* Printing hexadecimal dump of mantissa */
    printf( "\n      " );

    for ( unsigned i = 14; i > 0; --i )
    {
        printf( "       %02x.", flt128_byte[ i - 1 ] );
        if ( ( i > 1 ) && ( i % 4 == 1 ) ) printf( "\n      " );
    }

    puts( "" );
#endif

    puts( "----------------------------------------------" );
}
