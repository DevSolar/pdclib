/* $Id$ */

/* sscanf( const char *, const char *, ... )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int sscanf( const char * _PDCLIB_restrict s, const char * _PDCLIB_restrict format, ... )
{
    int rc;
    va_list ap;
    va_start( ap, format );
    rc = vsscanf( s, format, ap );
    va_end( ap );
    return rc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <string.h>
#include <limits.h>

#define CHECK_TRUE( a ) TESTCASE( a != 0 )
#define CHECK_FALSE( a ) TESTCASE( a == 0 )
#define CHECK_EQUAL( a, b ) do { int x = a; int y = b; TESTCASE( x == y ); } while ( 0 )
#define CHECK_FEQUAL( a, b, T, F ) do { T x = a; T y = b; TESTCASE( x == y ); } while ( 0 )

// literal matches, character matches, and basic integer matches
void suite_one( void );
// decimal integer matches
void suite_two( void );
// hexadecimal integer matches
void suite_three( void );
// octal integer matches
void suite_four( void );
// string matches
void suite_five( void );
// 0xz special case
void suite_six( void );

int main()
{
    suite_one();
    suite_two();
    suite_three();
    suite_four();
    suite_five();
#ifndef REGTEST
    // This test driver fails for many common libraries, so it's disabled for
    // regression testing. See the function for explanation.
    suite_six();
#endif
}

// literal matches, character matches, and basic integer matches
void suite_one()
{
    char const * string = "12345678901\0003-5+7\0009\3772 4 6 8 0\3771 \011 5%%  0";
    CHECK_EQUAL( string[39], '0' );

    // -----------------------------------------------------------------------
    // Literal matching
    // -----------------------------------------------------------------------
    {
    // matching six characters literally
    // checking via %n
    // should report six characters read
    int n;
    CHECK_EQUAL( sscanf( string + 0, "123456%n", &n ), 0 );
    CHECK_EQUAL( n, 6 );
    }
    {
    // matching a character, three whitespace chars, and another character
    // checking via %n
    // should report five characters read
    int n;
    CHECK_EQUAL( sscanf( string + 30, "1 5%n", &n ), 0 );
    CHECK_EQUAL( n, 5 );
    }
    {
    // matching three characters, not matching whitespaces, and matching another three characters
    // checking via %n
    // should report six characters matched
    int n;
    CHECK_EQUAL( sscanf( string + 0, "123  456%n", &n ), 0 );
    CHECK_EQUAL( n, 6 );
    }
    {
    // matching a character, two '%' characters, and two whitespaces
    // checking via %n
    // should report five characters matched
    int n;
    CHECK_EQUAL( sscanf( string + 34, "5%%%% %n", &n ), 0 );
    CHECK_EQUAL( n, 5 );
    }
    {
    // seeking to last character in file, trying to match that char and a whitespace
    // checking via %n
    // should report one character matched and EOF
    int n;
    CHECK_EQUAL( sscanf( string + 39, "0 %n", &n ), 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // seeking to end of file, trying to match a -1
    // checking via %n
    // should report error, not executing %n
    int n = -1;
    CHECK_EQUAL( sscanf( string + 0, "\377%n", &n ), 0 );
    CHECK_EQUAL( n, -1 );
    }

    // -----------------------------------------------------------------------
    // Character matching ('%c')
    // -----------------------------------------------------------------------
    {
    // reading a char array of specified width, including zero bytes
    // should report the characters read up to first zero
    char buffer[ 8 ];
    memset( buffer, '\177', 8 );
    CHECK_EQUAL( sscanf( string + 10, "%7c", buffer ), 1 );
    CHECK_FALSE( memcmp( buffer, "1\177\177", 3 ) );
    }
    {
    // reading a char array of unspecified width when positioned at -1 value 
    // should default to width one, read the -1 value, no zero termination of the array
    char buffer[ 2 ];
    memset( buffer, '\177', 2 );
    CHECK_EQUAL( sscanf( string + 19, "%c", buffer ), 1 );
    CHECK_FALSE( memcmp( buffer, "\377\177", 2 ) );
    }
    {
    // reading a char array of specified width 1 when positioned at (non-space) whitespace
    // should read the whitespace (literally), no zero termination of the array
    char buffer[ 2 ];
    memset( buffer, '\177', 2 );
    CHECK_EQUAL( sscanf( string + 32, "%1c", buffer ), 1 );
    CHECK_FALSE( memcmp( buffer, "\011\177", 2 ) );
    }
    {
    // reading a char array of specified width 2 when positioned at last char of file
    // should read the character, and report EOF
    char buffer[ 2 ];
    memset( buffer, '\177', 2 );
    CHECK_EQUAL( sscanf( string + 39, "%2c", buffer ), 1 );
    CHECK_FALSE( memcmp( buffer, "0\177", 2 ) );
    }
    {
    // reading a char array of specified width 1 when positioned at last char of file
    // should read the character, and NOT report EOF
    char buffer[ 2 ];
    memset( buffer, '\177', 2 );
    CHECK_EQUAL( sscanf( string + 39, "%1c", buffer ), 1 );
    CHECK_FALSE( memcmp( buffer, "0\177", 2 ) );
    }
    {
    // reading a char array of specified width 1 when positioned at EOF
    // should report input error before any conversion (-1)
    char buffer[ 2 ];
    memset( buffer, '\177', 2 );
    CHECK_EQUAL( sscanf( string + 40, "%1c", buffer ), -1 );
    CHECK_FALSE( memcmp( buffer, "\177\177", 2 ) );
    }

    // -----------------------------------------------------------------------
    // Integer matching ('%d')
    // -----------------------------------------------------------------------
    {
    // reading a whitespace-terminated integer
    int i;
    int n;
    CHECK_EQUAL( sscanf( string + 20, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading a -1 terminated integer
    int i;
    int n;
    CHECK_EQUAL( sscanf( string + 18, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 9 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading a EOF terminated integer
    int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 39, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // trying to read an integer when positioned at whitespace
    // should skip whitespaces
    int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 32, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 5 );
    CHECK_EQUAL( n, 3 );
    }
    {
    // trying to read an integer when positioned at -1 value
    // should report matching failure
    int i = 0;
    int n = -1;
    CHECK_EQUAL( sscanf( string + 19, "%d%n", &i, &n ), 0 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, -1 );
    }
    {
    // trying to read an integer when positioned at EOF
    // should report reading failure
    int i = 0;
    int n = -1;
    CHECK_EQUAL( sscanf( string + 40, "%d%n", &i, &n ), -1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, -1 );
    }
    {
    // reading a '-'-prefixed integer
    int i;
    int n;
    CHECK_EQUAL( sscanf( string + 13, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -5 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading a '+'-prefixed integer
    int i;
    int n;
    CHECK_EQUAL( sscanf( string + 15, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 7 );
    CHECK_EQUAL( n, 2 );
    }
}

// decimal integer matches
void suite_two()
{
    char const * string = "-0 +0 -128 +127 +255 -32768 +32767 +65535\n"
                          "-2147483648 +2147483647 +4294967295\n"
                          "-9223372036854775808 +9223372036854775807\n"
                          "+18446744073709551615\n";
    CHECK_EQUAL( string[141], '\n' );
    {
    // reading 0, d
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%hhd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, d
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%hhd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, d
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%hhd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading -128, d
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 6, "%hhd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -128 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 127, d
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 12, "%hhd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 3 );
    }
    {
    // reading +127, d
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 11, "%hhd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 0, u
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, u
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, u
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading 127, u
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 12, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 3 );
    }
    {
    // reading +127, u
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 11, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 255, u
    unsigned char i = 0;
    int n;
    CHECK_EQUAL( sscanf( string + 17, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 255 );
    CHECK_EQUAL( n, 3 );
    }
    {
    // reading +255, u
    unsigned char i = 0;
    int n;
    CHECK_EQUAL( sscanf( string + 16, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 255 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 0, i
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, i
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, i
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading -128, i
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 6, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -128 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 127, i
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 12, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 3 );
    }
    {
    // reading +127, i
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 11, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 0, d
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%hd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, d
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%hd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, d
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%hd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading -32768, d
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 21, "%hd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -32768 );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading 32767, d
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 29, "%hd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 5 );
    }
    {
    // reading +32767, d
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 28, "%hd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading 0, u
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, u
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, u
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading 32767, u
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 29, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 5 );
    }
    {
    // reading +32767, u
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 28, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading 65535, u
    unsigned short i = 0;
    int n;
    CHECK_EQUAL( sscanf( string + 36, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 65535 );
    CHECK_EQUAL( n, 5 );
    }
    {
    // reading +65535, u
    unsigned short i = 0;
    int n;
    CHECK_EQUAL( sscanf( string + 35, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 65535 );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading 0, i
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, i
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, i
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading -32768, i
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 21, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -32768 );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading 32767, i
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 29, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 5 );
    }
    {
    // reading +32767, i
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 28, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading 0, d
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, d
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, d
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading -2147483648, d
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 42, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -2147483648 );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 2147483647, d
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 55, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 10 );
    }
    {
    // reading +2147483647, d
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 54, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 0, u
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%u%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, u
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%u%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, u
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%u%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading 2147483647, u
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 55, "%u%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 10 );
    }
    {
    // reading +2147483647, u
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 54, "%u%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 4294967295, u
    unsigned int i = 0;
    int n;
    CHECK_EQUAL( sscanf( string + 67, "%u%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295, unsigned int, "%u" );
    CHECK_EQUAL( n, 10 );
    }
    {
    // reading +4294967295, u
    unsigned int i = 0;
    int n;
    CHECK_EQUAL( sscanf( string + 66, "%u%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295, unsigned int, "%u" );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 0, i
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, i
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, i
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading -2147483648, i
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 42, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -2147483648 );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 2147483647, i
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 55, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 10 );
    }
    {
    // reading +2147483647, i
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 54, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 0, d
    signed long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%ld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0l );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, d
    signed long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%ld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0l );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, d
    signed long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%ld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0l );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading -2147483648, d
    signed long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 42, "%ld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -2147483648l );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 2147483647, d
    signed long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 55, "%ld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647l );
    CHECK_EQUAL( n, 10 );
    }
    {
    // reading +2147483647, d
    signed long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 54, "%ld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647l );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 0, u
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%lu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ul );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, u
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%lu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ul );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, u
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%lu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ul );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading 2147483647, u
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 55, "%lu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647ul );
    CHECK_EQUAL( n, 10 );
    }
    {
    // reading +2147483647, u
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 54, "%lu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647ul );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 4294967295, u
    unsigned long i = 0;
    int n;
    CHECK_EQUAL( sscanf( string + 67, "%lu%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295ul, unsigned long, "%lu" );
    CHECK_EQUAL( n, 10 );
    }
    {
    // reading +4294967295, u
    unsigned long i = 0;
    int n;
    CHECK_EQUAL( sscanf( string + 66, "%lu%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295ul, unsigned long, "%lu" );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 0, i
    signed long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%li%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0l );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, i
    signed long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%li%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0l );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, i
    signed long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%li%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0l );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading -2147483648, i
    signed long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 42, "%li%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -2147483648l );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 2147483647, i
    signed long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 55, "%li%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647l );
    CHECK_EQUAL( n, 10 );
    }
    {
    // reading +2147483647, i
    signed long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 54, "%li%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647l );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 0, d
    signed long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%lld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ll );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, d
    signed long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%lld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ll );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, d
    signed long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%lld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ll );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading -9223372036854775808, d
    signed long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 78, "%lld%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, LLONG_MIN, signed long long, "%lld" ); // should be literal -9223372036854775808ll but GCC balks.
    CHECK_EQUAL( i < 0ll, 1 );
    CHECK_EQUAL( n, 20 );
    }
    {
    // reading 9223372036854775807, d
    signed long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 100, "%lld%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807ll, signed long long, "%lld" );
    CHECK_EQUAL( n, 19 );
    }
    {
    // reading +9223372036854775807, d
    signed long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 99, "%lld%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807ll, signed long long, "%lld" );
    CHECK_EQUAL( n, 20 );
    }
    {
    // reading 0, u
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%llu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ull );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, u
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%llu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ull );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, u
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%llu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ull );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading 9223372036854775807, u
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 100, "%llu%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807ull, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 19 );
    }
    {
    // reading +9223372036854775807, u
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 99, "%llu%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807ull, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 20 );
    }
    {
    // reading 18446744073709551615, u
    unsigned long long i = 0;
    int n;
    CHECK_EQUAL( sscanf( string + 121, "%llu%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 18446744073709551615ull, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 20 );
    }
    {
    // reading +18446744073709551615, u
    unsigned long long i = 0;
    int n;
    CHECK_EQUAL( sscanf( string + 120, "%llu%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 18446744073709551615ull, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 21 );
    }
    {
    // reading 0, i
    signed long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 1, "%lli%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ll );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0, i
    signed long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%lli%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ll );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading +0, i
    signed long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%lli%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ll );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading -9223372036854775808, i
    signed long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 78, "%lli%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, LLONG_MIN, signed long long, "%lli" ); // should be literal -9223372036854775808ll but GCC balks.
    CHECK_EQUAL( i < 0ll, 1 );
    CHECK_EQUAL( n, 20 );
    }
    {
    // reading 9223372036854775807, i
    signed long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 100, "%lli%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807ll, signed long long, "%lli" );
    CHECK_EQUAL( n, 19 );
    }
    {
    // reading +9223372036854775807, i
    signed long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 99, "%lli%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807ll, signed long long, "%lli" );
    CHECK_EQUAL( n, 20 );
    }
}

// hexadecimal integer matches
void suite_three()
{
    char const * string = "-0x0 -0x000 -0x7f 0x80 0xff -0x7fff 0x8000\n"
                          "0xffff -0x7fffffff 0x80000000 0xffffffff\n"
                          "-0x7fffffffffffffff 0x8000000000000000\n"
                          "0xffffffffffffffff\n";
    CHECK_EQUAL( string[141], '\n' );
    {
    // reading 0, x
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0x0, x
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 0x000, x
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 5, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading 0x0, i
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 7f, x
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 15, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading -0x7f, x
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 12, "%hhx%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -127, unsigned char, "%hhu" );
    CHECK_EQUAL( n, 5 );
    }
    {
    // reading 0x80, i
    signed char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 18, "%hhi%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -128, signed char, "%hhd" );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading ff, x
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 25, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0xff );
    CHECK_EQUAL( n, 2 );
    }
    {
    // reading 0xff, x
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 23, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 255 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 0xff, i
    signed char i = 0;
    int n;
    CHECK_EQUAL( sscanf( string + 23, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -1 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 0, x
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0x0, x
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 0x000, x
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 5, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading 0x0, i
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 7fff, x
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 31, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading -0x7fff, x
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 28, "%hx%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -32767, unsigned short, "%hu" );
    CHECK_EQUAL( n, 7 );
    }
    {
    // reading 0x8000, i
    signed short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 36, "%hi%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -32768, signed short, "%hd" );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading ffff, x
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 45, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 65535 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 0xffff, x
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 43, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 65535 );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading 0xffff, i
    signed short i = 0;
    int n;
    CHECK_EQUAL( sscanf( string + 43, "%hi%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -1, signed short, "%hd" );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading 0, x
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 3, "%x%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading -0x0, x
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%x%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 0x000, x
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 5, "%x%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading 0x0, i
    signed int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading 7fffffff, x
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 53, "%x%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 8 );
    }
    {
    // reading -0x7fffffff, x
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 50, "%x%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -2147483647, unsigned int, "%u" );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading 0x80000000, i
    signed int i = -1;
    int n;
    //CHECK_EQUAL( sscanf( string + 62, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( sscanf( "-0x80000000", "%i%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -2147483648, signed int, "%d" );
    CHECK_EQUAL( n, 11 );
    }
    {
    // reading ffffffff, x
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 75, "%x%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295, unsigned int, "%d" );
    CHECK_EQUAL( n, 8 );
    }
    {
    // reading 0xffffffff, x
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 73, "%x%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295, unsigned int, "%d" );
    CHECK_EQUAL( n, 10 );
    }
}

// octal integer matches
void suite_four()
{
    char const * string = "+0000 -0000 +0177 +0377 -0377 +077777 +0177777\n"
                          "-0177777 +017777777777 +037777777777\n"
                          "-037777777777 +0777777777777777777777\n"
                          "+01777777777777777777777\n"
                          "-01777777777777777777777\n";
    CHECK_EQUAL( string[171], '\n' );
    {
    // reading 0, o
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 4, "%hho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0u );
    CHECK_EQUAL( n, 1 );
    }
    {
    // reading +0000, o
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%hho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0u );
    CHECK_EQUAL( n, 5 );
    }
    {
    // reading -0000, o
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 6, "%hho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0u );
    CHECK_EQUAL( n, 5 );
    }
    {
    // reading 0177, o
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 13, "%hho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127u );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading +0177, o
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 12, "%hho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127u );
    CHECK_EQUAL( n, 5 );
    }
    {
    // reading 0377, o
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 19, "%hho%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 255u, unsigned char, "%hhu" );
    CHECK_EQUAL( n, 4 );
    }
    {
    // reading +0377, o
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 18, "%hho%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 255u, unsigned char, "%hhu" );
    CHECK_EQUAL( n, 5 );
    }
    {
    // reading -0377, o
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 24, "%hho%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 1u, unsigned char, "%hhu" );
    CHECK_EQUAL( n, 5 );
    }
    {
    // reading 077777, o
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 31, "%ho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767u );
    CHECK_EQUAL( n, 6 );
    }
    {
    // reading +077777, o
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 30, "%ho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767u );
    CHECK_EQUAL( n, 7 );
    }
    {
    // reading 0177777, o
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 39, "%ho%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 65535u, unsigned short, "%hu" );
    CHECK_EQUAL( n, 7 );
    }
    {
    // reading +0177777, o
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 38, "%ho%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 65535u, unsigned short, "%hu" );
    CHECK_EQUAL( n, 8 );
    }
    {
    // reading -0177777, o
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 47, "%ho%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 1u, unsigned short, "%hu" );
    CHECK_EQUAL( n, 8 );
    }
    {
    // reading 017777777777, o
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 57, "%o%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647u );
    CHECK_EQUAL( n, 12 );
    }
    {
    // reading +017777777777, o
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 56, "%o%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647u );
    CHECK_EQUAL( n, 13 );
    }
    {
    // reading 037777777777, o
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 71, "%o%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295u, unsigned int, "%u" );
    CHECK_EQUAL( n, 12 );
    }
    {
    // reading +037777777777, o
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 70, "%o%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295u, unsigned int, "%u" );
    CHECK_EQUAL( n, 13 );
    }
    {
    // reading -037777777777, o
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 84, "%o%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 1u, unsigned int, "%u" );
    CHECK_EQUAL( n, 13 );
    }
    {
    // reading 017777777777, o
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 57, "%lo%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647lu );
    CHECK_EQUAL( n, 12 );
    }
    {
    // reading +017777777777, o
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 56, "%lo%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647lu );
    CHECK_EQUAL( n, 13 );
    }
    {
    // reading 037777777777, o
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 71, "%lo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295lu, unsigned long, "%lu" );
    CHECK_EQUAL( n, 12 );
    }
    {
    // reading +037777777777, o
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 70, "%lo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295lu, unsigned long, "%lu" );
    CHECK_EQUAL( n, 13 );
    }
    {
    // reading -037777777777, o
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 84, "%lo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 1lu, unsigned long, "%lu" );
    CHECK_EQUAL( n, 13 );
    }
    {
    // reading 0777777777777777777777, o
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 99, "%llo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807llu, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 22 );
    }
    {
    // reading +0777777777777777777777, o
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 98, "%llo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807llu, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 23 );
    }
    {
    // reading 01777777777777777777777, o
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 123, "%llo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 18446744073709551615llu, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 23 );
    }
    {
    // reading +01777777777777777777777, o
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 122, "%llo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 18446744073709551615llu, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 24 );
    }
    {
    // reading -01777777777777777777777, o
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( sscanf( string + 147, "%llo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 1llu, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 24 );
    }
}

// string matches
void suite_five()
{
    char const * string = "abcdefgh-ijklmnop[qrs%uvw]xyz";
    CHECK_EQUAL( string[28], 'z' );
    size_t const BUFSIZE = 29;
    char buffer[ BUFSIZE ];
    {
    // reading abc
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%[abc]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 3 );
    CHECK_FALSE( memcmp( buffer, "abc", n + 1 ) );
    }
    {
    // reading a-c
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%[a-c]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 3 );
    CHECK_FALSE( memcmp( buffer, "abc", n + 1 ) );
    }
    {
    // reading a-h
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%[a-h]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 8 );
    CHECK_FALSE( memcmp( buffer, "abcdefgh", n + 1 ) );
    }
    {
    // reading o-r, including [, seperate char
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( sscanf( string + 15, "%[[o-qr]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 5 );
    CHECK_FALSE( memcmp( buffer, "op[qr", n + 1 ) );
    }
    {
    // reading v-y, including ], two groups
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( sscanf( string + 23, "%[]v-wx-y]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 5 );
    CHECK_FALSE( memcmp( buffer, "vw]xy", n + 1 ) );
    }
    {
    // missing on first character
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%[b]%n", buffer, &n ), 0 );
    CHECK_FALSE( memcmp( buffer, "", 1 ) );
    }
    {
    // eof while reading, two groups
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( sscanf( string + 27, "%[a-zA-Z]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 2 );
    CHECK_FALSE( memcmp( buffer, "yz", n + 1 ) );
    }
    {
    // eof before reading
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( sscanf( string + 29, "%[a-z]%n", buffer, &n ), -1 );
    CHECK_FALSE( memcmp( buffer, "", 1 ) );
    }
    {
    // negation - [^...]
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( sscanf( string + 0, "%[^d-f]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 3 );
    CHECK_FALSE( memcmp( buffer, "abc", 4 ) );
    }
}

void suite_six()
{
    char const * string = "-0xz\n";
    CHECK_EQUAL( string[4], '\n' );
    {
    // reading -0x, x
    unsigned char i = 1;
    int n = -1;
    /* Most existing libraries disagree with this test driver, so a little
       explanation of why PDCLib chose the implementation it did might be
       necessary. All references are from ISO/IEC 9899:1999 "Programming
       languages - C". Wording critical to the explanation is in UPPERCASE.
       6.4.4.1 Integer constants - states that '0' is a valid (hexa)decimal
           constant, whereas '0x' IS NOT.
       7.19.6.2 The fscanf function - states...
           ...in paragraph 9 that "an INPUT ITEM is defined as the longest
               sequence of input characters [...] which is, OR IS A PREFIX OF,
               a matching input sequence".
           ...in paragraph 10 that "if the INPUT ITEM is not a matching
               sequence, the execution of THE DIRECTIVE FAILS; this condition
               is a matching failure".
           ...in footnote 242) that "fscanf pushes back AT MOST ONE input
               character onto the input stream."
           ...in paragraph 12 that either of the conversion specifiers d, i,
              o, u, or x "matches an [...] integer whose format is the same as
              expected for THE SUBJECT SEQUENCE of the [strtol|strtoul]
              function".
       7.20.1.4 The strtol, strtoll, strtoul, and strtoull functions - states
           in paragraph 3 that "the EXPECTED FORM OF THE SUBJECT SEQUENCE is
           that of an integer constant AS DESCRIBED IN 6.4.4.1".
       These parts of the standard result in the following reasoning:
       - The longest sequence of input characters which is a prefix of a
         matching input sequence is "-0x" (negative sign, hexadecimal-prefix).
         The 'z' is the first character remaining unread as "-0xz" is not a
         (prefix of a) matching input sequence. This is according to 7.19.6.2
         paragraph 9.
       - "0x", without a valid hexadecimal digit following it, is not a valid
         integer constant according to 6.4.4.1.
       - "0x" is thus also not of the expected form for a strto[u]l subject
         sequence according to 7.20.1.4 paragraph 3. (strto[u]l() would parse
         it as zero, but leave the "x" in the final string, i.e. outside the
         subject sequence.)
       - "0x" is therefore also not a matching sequence to the i or x
         conversion specifier according to 7.19.6.2 paragraph 12.
       - The conversion should therefore result in a matching failure
         according to 7.19.6.2 paragraph 10.
    */
    CHECK_EQUAL( sscanf( string, "%hhx%n", &i, &n ), 0 );
    CHECK_EQUAL( i, 1 );
    CHECK_EQUAL( n, -1 );
    }
    {
    // reading -0x, x
    unsigned short i = 1;
    int n = -1;
    CHECK_EQUAL( sscanf( string, "%hx%n", &i, &n ), 0 );
    CHECK_EQUAL( i, 1 );
    CHECK_EQUAL( n, -1 );
    }
    {
    // reading -0x, x
    unsigned int i = 1;
    int n = -1;
    CHECK_EQUAL( sscanf( string, "%x%n", &i, &n ), 0 );
    CHECK_EQUAL( i, 1 );
    CHECK_EQUAL( n, -1 );
    }
}

#endif

