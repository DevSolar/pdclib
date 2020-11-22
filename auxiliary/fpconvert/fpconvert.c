#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

union
{
    float value;
    unsigned char byte[ sizeof( float ) ];
    struct
    {
        unsigned mant : 23;
        unsigned exp  :  8;
        unsigned sign :  1;
    } bits;
} float32;

union
{
    double value;
    unsigned char byte[ sizeof( double ) ];
    struct
    {
        unsigned mant_low  : 32;
        unsigned mant_high : 20;
        unsigned exp       : 11;
        unsigned sign      :  1;
    } bits;
} float64;

#if __LDBL_DECIMAL_DIG__ == 21

#define FLOAT80

union
{
    long double value;
    unsigned char byte[ sizeof( long double ) ];
    struct
    {
        unsigned mant_low  : 32;
        unsigned mant_high : 32;
        unsigned exp       : 15;
        unsigned sign      :  1;
    } bits;
} float80;

#endif

#if __LDBL_DECIMAL_DIG__ == 36 || __FLT128_DECIMAL_DIG__ == 36


#if __LDBL_DECIMAL_DIG__ == 36
#define FLOAT128 " long double "
typedef long double float128_t;
#define strtof128 strtold
#elif __FLT128_DECIMAL_DIG__ == 36
#define FLOAT128 " __float128 -"
#include <quadmath.h>
typedef __float128 float128_t;
#define strtof128 strtoflt128
#endif

union
{
    float128_t value;
    unsigned char byte[ sizeof( float128_t ) ];
    struct
    {
        unsigned mant_l1 : 32;
        unsigned mant_l2 : 32;
        unsigned mant_h1 : 32;
        unsigned mant_h2 : 16;
        unsigned exp     : 15;
        unsigned sign    :  1;
    } bits;
} float128;

#endif

int main( int argc, char * argv[] )
{
    int i;

    unsigned sign;
    unsigned exp;
    unsigned mant[4];

    if ( argc != 2 )
    {
        puts( "Usage: fpconvert <floating-point>" );
        return 1;
    }

    float32.value  =    strtof( argv[1], NULL );
    float64.value  =    strtod( argv[1], NULL );
#ifdef FLOAT80
    float80.value  =   strtold( argv[1], NULL );
#endif
#ifdef FLOAT128
    float128.value = strtof128( argv[1], NULL );
#endif

    puts( "\n---------------------------------- float ----------------------------------" );

    for ( i = sizeof( float ); i > 0; --i )
    {
        printf( "%02hhx ", float32.byte[i - 1] );
    }

    puts( "" );

    sign    = float32.byte[3] >> 7;
    exp     = ( ( (unsigned)float32.byte[3] & 0x7F ) <<  1 ) |   ( (unsigned)float32.byte[2]   >> 7 );
    mant[0] = ( ( (unsigned)float32.byte[2] & 0x7F ) << 16 ) | ( ( (unsigned)float32.byte[1] ) << 8 ) | ( (unsigned)float32.byte[0] );

    assert( sign    == float32.bits.sign );
    assert( exp     == float32.bits.exp );
    assert( mant[0] == float32.bits.mant );

    printf( "sign: %u exponent: 0x%04x significand: 0x%08x\n\n", sign, exp, mant[0] );

    puts( "--------------------------------- double ----------------------------------" );

    for ( i = sizeof( double ); i > 0; --i )
    {
        printf( "%02hhx ", float64.byte[i - 1] );
    }

    puts( "" );

    sign     = float64.byte[7] >> 7;
    exp      = ( ( (unsigned)float64.byte[7] & 0x7F ) <<  4 ) | ( ( (unsigned)float64.byte[6] & 0xF0 ) >>  4 );
    mant[0]  = ( ( (unsigned)float64.byte[6] & 0x0F ) << 16 ) |   ( (unsigned)float64.byte[5]          <<  8 ) |   (unsigned)float64.byte[4];
    mant[1]  =   ( (unsigned)float64.byte[3]          << 24 ) |   ( (unsigned)float64.byte[2]          << 16 ) | ( (unsigned)float64.byte[1] << 8 ) | (unsigned)float64.byte[0];

    assert( sign    == float64.bits.sign );
    assert( exp     == float64.bits.exp );
    assert( mant[0] == float64.bits.mant_high );
    assert( mant[1] == float64.bits.mant_low );

    printf( "sign: %u exponent: 0x%04x significand: 0x%08x.%08x\n\n", sign, exp, mant[0], mant[1] );

#ifdef FLOAT80

    puts( "------------------------------- long double -------------------------------" );

    for ( i = sizeof( long double ); i > 0; --i )
    {
        printf( "%02hhx ", float80.byte[i - 1] );
    }

    puts( "" );

    sign    = float80.byte[9] >> 7;
    exp     = ( ( (unsigned)float80.byte[9] & 0x7F ) <<  8 ) |     (unsigned)float80.byte[8];
    mant[0] =   ( (unsigned)float80.byte[7]          << 24 ) |   ( (unsigned)float80.byte[6] << 16 ) | ( (unsigned)float80.byte[5] << 8 ) | (unsigned)float80.byte[4];
    mant[1] =   ( (unsigned)float80.byte[3]          << 24 ) |   ( (unsigned)float80.byte[2] << 16 ) | ( (unsigned)float80.byte[1] << 8 ) | (unsigned)float80.byte[0];

    assert( sign    == float80.bits.sign );
    assert( exp     == float80.bits.exp );
    assert( mant[0] == float80.bits.mant_high );
    assert( mant[1] == float80.bits.mant_low );

    printf( "sign: %u exponent: 0x%04x significand: 0x%08x.%08x\n\n", sign, exp, mant[0], mant[1] );

#endif

#ifdef FLOAT128

    puts( "-------------------------------" FLOAT128 "-------------------------------" );

    for ( i = sizeof( float128_t ); i > 0; --i )
    {
        printf( "%02hhx ", float128.byte[i - 1] );
    }

    puts( "" );

    sign    = float128.byte[15] >> 7;
    exp     = ( ( (unsigned)float128.byte[15] & 0x7F ) <<  8 ) |   (unsigned)float128.byte[14];
    mant[0] =   ( (unsigned)float128.byte[13]          <<  8 ) |   (unsigned)float128.byte[12];
    mant[1] =   ( (unsigned)float128.byte[11]          << 24 ) | ( (unsigned)float128.byte[10] << 16 ) | ( (unsigned)float128.byte[9] << 8 ) | (unsigned)float128.byte[8];
    mant[2] =   ( (unsigned)float128.byte[ 7]          << 24 ) | ( (unsigned)float128.byte[ 6] << 16 ) | ( (unsigned)float128.byte[5] << 8 ) | (unsigned)float128.byte[4];
    mant[3] =   ( (unsigned)float128.byte[ 3]          << 24 ) | ( (unsigned)float128.byte[ 2] << 16 ) | ( (unsigned)float128.byte[1] << 8 ) | (unsigned)float128.byte[0];

    assert( sign    == float128.bits.sign );
    assert( exp     == float128.bits.exp );
    assert( mant[0] == float128.bits.mant_h2 );
    assert( mant[1] == float128.bits.mant_h1 );
    assert( mant[2] == float128.bits.mant_l2 );
    assert( mant[3] == float128.bits.mant_l1 );

    printf( "sign: %u exponent: 0x%04x significand: 0x%08x.%08x.%08x.%08x\n\n", sign, exp, mant[0], mant[1], mant[2], mant[3] );

#endif
}
