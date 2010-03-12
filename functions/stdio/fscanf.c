/* $Id$ */

/* fscanf( FILE *, const char *, ... )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int fscanf( FILE * _PDCLIB_restrict stream, const char * _PDCLIB_restrict format, ... )
{
    int rc;
    va_list ap;
    va_start( ap, format );
    rc = vfscanf( stream, format, ap );
    va_end( ap );
    return rc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <string.h>
#include <limits.h>
#include <_PDCLIB_aux.h>

#if 0
#define CHECK_TRUE( a ) do { if ( a == 0 ) { fprintf( stderr, "Unexpected failure in " _PDCLIB_symbol2string( __LINE__ ) ": '" #a "' evaluated to false.\n" ); } } while ( 0 )
#define CHECK_FALSE( a ) do { if ( a != 0 ) { fprintf( stderr, "Unexpected failure in " _PDCLIB_symbol2string( __LINE__ ) ": '" #a "' evaluated to true.\n" ); } } while ( 0 )
#define CHECK_EQUAL( a, b ) do { int x = a; int y = b; if ( x != y ) { fprintf( stderr, "Mismatch in " _PDCLIB_symbol2string( __LINE__ ) ": result is %d, expected %d.\n", x, y ); } } while ( 0 )
#define CHECK_FEQUAL( a, b, T, F ) do { T x = a; T y = b; if ( x != y ) { fprintf( stderr, "Mismatch in " _PDCLIB_symbol2string( __LINE__ ) ": result is " F ", expected " F ".\n", x, y ); } } while ( 0 )
#endif

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

int main()
{
    suite_one();
    suite_two();
    suite_three();
    suite_four();
    suite_five();
}

// literal matches, character matches, and basic integer matches
void suite_one()
{
    FILE * file;
    if ( ( file = fopen( "tmpfile", "wb+" ) ) == NULL )
    {
        puts( "Failed to open tmpfile for writing." );
        return;
    }
    fprintf( file, "1234567890" );
    fprintf( file, "1%c3-5+7%c9%c", 0, 0, -1 );
    fprintf( file, "2 4 6 8 0%c", 255 );
    fprintf( file, "1 \011 5%%%%  0" );
    CHECK_EQUAL( ftell( file ), 40 );

    // -----------------------------------------------------------------------
    // Literal matching
    // -----------------------------------------------------------------------
    {
    // matching six characters literally
    // checking via %n
    // should report six characters read
    fseek( file, 0, SEEK_SET );
    int n;
    CHECK_EQUAL( fscanf( file, "123456%n", &n ), 0 );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 6 );
    }
    {
    // matching a character, three whitespace chars, and another character
    // checking via %n
    // should report five characters read
    fseek( file, 30, SEEK_SET );
    int n;
    CHECK_EQUAL( fscanf( file, "1 5%n", &n ), 0 );
    CHECK_EQUAL( n, 5 );
    CHECK_EQUAL( ftell( file ), 35 );
    }
    {
    // matching three characters, not matching whitespaces, and matching another three characters
    // checking via %n
    // should report six characters matched
    fseek( file, 0, SEEK_SET );
    int n;
    CHECK_EQUAL( fscanf( file, "123  456%n", &n ), 0 );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 6 );
    }
    {
    // matching a character, two '%' characters, and two whitespaces
    // checking via %n
    // should report five characters matched
    fseek( file, 34, SEEK_SET );
    int n;
    CHECK_EQUAL( fscanf( file, "5%%%% %n", &n ), 0 );
    CHECK_EQUAL( n, 5 );
    CHECK_EQUAL( ftell( file ), 39 );
    }
    {
    // seeking to last character in file, trying to match that char and a whitespace
    // checking via %n
    // should report one character matched and EOF
    fseek( file, -1, SEEK_END );
    int n;
    CHECK_EQUAL( fscanf( file, "0 %n", &n ), 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_TRUE( feof( file ) );
    CHECK_FALSE( ferror( file ) );
    CHECK_EQUAL( ftell( file ), 40 );
    }
    {
    // seeking to end of file, trying to match a -1
    // checking via %n
    // should report error, not executing %n
    fseek( file, 0, SEEK_END );
    int n = -1;
    CHECK_EQUAL( fscanf( file, "\377%n", &n ), -1 );
    CHECK_EQUAL( n, -1 );
    CHECK_TRUE( feof( file ) );
    CHECK_FALSE( ferror( file ) );
    CHECK_EQUAL( ftell( file ), 40 );
    }

    // -----------------------------------------------------------------------
    // Character matching ('%c')
    // -----------------------------------------------------------------------
    {
    // reading a char array of specified width, including zero bytes
    // should report the characters read, no zero termination of the array
    fseek( file, 10, SEEK_SET );
    char buffer[ 8 ];
    memset( buffer, '\177', 8 );
    CHECK_EQUAL( fscanf( file, "%7c", buffer ), 1 );
    CHECK_FALSE( memcmp( buffer, "1\0003-5+7\177", 8 ) );
    CHECK_EQUAL( ftell( file ), 17 );
    }
    {
    // reading a char array of unspecified width when positioned at -1 value 
    // should default to width one, read the -1 value, no zero termination of the array
    fseek( file, 19, SEEK_SET );
    char buffer[ 2 ];
    memset( buffer, '\177', 2 );
    CHECK_EQUAL( fscanf( file, "%c", buffer ), 1 );
    CHECK_FALSE( memcmp( buffer, "\377\177", 2 ) );
    CHECK_EQUAL( ftell( file ), 20 );
    }
    {
    // reading a char array of specified width 1 when positioned at (non-space) whitespace
    // should read the whitespace (literally), no zero termination of the array
    fseek( file, 32, SEEK_SET );
    char buffer[ 2 ];
    memset( buffer, '\177', 2 );
    CHECK_EQUAL( fscanf( file, "%1c", buffer ), 1 );
    CHECK_FALSE( memcmp( buffer, "\011\177", 2 ) );
    CHECK_EQUAL( ftell( file ), 33 );
    }
    {
    // reading a char array of specified width 2 when positioned at last char of file
    // should read the character, and report EOF
    fseek( file, -1, SEEK_END );
    char buffer[ 2 ];
    memset( buffer, '\177', 2 );
    CHECK_EQUAL( fscanf( file, "%2c", buffer ), 1 );
    CHECK_FALSE( memcmp( buffer, "0\177", 2 ) );
    CHECK_TRUE( feof( file ) );
    CHECK_FALSE( ferror( file ) );
    CHECK_EQUAL( ftell( file ), 40 );
    }
    {
    // reading a char array of specified width 1 when positioned at last char of file
    // should read the character, and NOT report EOF
    fseek( file, -1, SEEK_END );
    char buffer[ 2 ];
    memset( buffer, '\177', 2 );
    CHECK_EQUAL( fscanf( file, "%1c", buffer ), 1 );
    CHECK_FALSE( memcmp( buffer, "0\177", 2 ) );
    CHECK_FALSE( feof( file ) );
    CHECK_EQUAL( ftell( file ), 40 );
    }
    {
    // reading a char array of specified width 1 when positioned at EOF
    // should report input error before any conversion (-1)
    fseek( file, 0, SEEK_END );
    char buffer[ 2 ];
    memset( buffer, '\177', 2 );
    CHECK_EQUAL( fscanf( file, "%1c", buffer ), -1 );
    CHECK_FALSE( memcmp( buffer, "\177\177", 2 ) );
    CHECK_TRUE( feof( file ) );
    CHECK_FALSE( ferror( file ) );
    CHECK_EQUAL( ftell( file ), 40 );
    }

    // -----------------------------------------------------------------------
    // Integer matching ('%d')
    // -----------------------------------------------------------------------
    {
    // reading a whitespace-terminated integer
    fseek( file, 20, SEEK_SET );
    int i;
    int n;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 21 );
    }
    {
    // reading a -1 terminated integer
    fseek( file, 18, SEEK_SET );
    int i;
    int n;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 9 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 19 );
    }
    {
    // reading a EOF terminated integer
    fseek( file, -1, SEEK_END );
    int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 40 );
    }
    {
    // trying to read an integer when positioned at whitespace
    // should skip whitespaces
    fseek( file, 32, SEEK_SET );
    int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 5 );
    CHECK_EQUAL( n, 3 );
    CHECK_EQUAL( ftell( file ), 35 );
    }
    {
    // trying to read an integer when positioned at -1 value
    // should report matching failure
    fseek( file, 19, SEEK_SET );
    int i = 0;
    int n = -1;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 0 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, -1 );
    CHECK_EQUAL( ftell( file ), 19 );
    }
    {
    // trying to read an integer when positioned at EOF
    // should report reading failure
    fseek( file, 0, SEEK_END );
    int i = 0;
    int n = -1;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), -1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, -1 );
    CHECK_EQUAL( ftell( file ), 40 );
    }
    {
    // reading a '-'-prefixed integer
    fseek( file, 13, SEEK_SET );
    int i;
    int n;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -5 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 15 );
    }
    {
    // reading a '+'-prefixed integer
    fseek( file, 15, SEEK_SET );
    int i;
    int n;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 7 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 17 ); 
    }

    fclose( file );
    remove( "tmpfile" );
}

// decimal integer matches
void suite_two()
{
    FILE * file;
    if ( ( file = fopen( "tmpfile", "wb+" ) ) == NULL )
    {
        puts( "Failed to open tmpfile for writing." );
        return;
    }
    fprintf( file, "-0 +0 -128 +127 +255 -32768 +32767 +65535\n" );
    fprintf( file, "-2147483648 +2147483647 +4294967295\n" );
    fprintf( file, "-9223372036854775808 +9223372036854775807 +18446744073709551615\n" );
    CHECK_EQUAL( ftell( file ), 142 );
    {
    // reading 0, d
    fseek( file, 1, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, d
    fseek( file, 0, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, d
    fseek( file, 3, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading -128, d
    fseek( file, 6, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -128 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 10 );
    }
    {
    // reading 127, d
    fseek( file, 12, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 3 );
    CHECK_EQUAL( ftell( file ), 15 );
    }
    {
    // reading +127, d
    fseek( file, 11, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 15 );
    }
    {
    // reading 0, u
    fseek( file, 1, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, u
    fseek( file, 0, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, u
    fseek( file, 3, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading 127, u
    fseek( file, 12, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 3 );
    CHECK_EQUAL( ftell( file ), 15 );
    }
    {
    // reading +127, u
    fseek( file, 11, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 15 );
    }
    {
    // reading 255, u
    fseek( file, 17, SEEK_SET );
    unsigned char i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 255 );
    CHECK_EQUAL( n, 3 );
    CHECK_EQUAL( ftell( file ), 20 );
    }
    {
    // reading +255, u
    fseek( file, 16, SEEK_SET );
    unsigned char i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 255 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 20 );
    }
    {
    // reading 0, i
    fseek( file, 1, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, i
    fseek( file, 0, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, i
    fseek( file, 3, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading -128, i
    fseek( file, 6, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -128 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 10 );
    }
    {
    // reading 127, i
    fseek( file, 12, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 3 );
    CHECK_EQUAL( ftell( file ), 15 );
    }
    {
    // reading +127, i
    fseek( file, 11, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 15 );
    }
    {
    // reading 0, d
    fseek( file, 1, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, d
    fseek( file, 0, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, d
    fseek( file, 3, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading -32768, d
    fseek( file, 21, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -32768 );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 27 );
    }
    {
    // reading 32767, d
    fseek( file, 29, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 5 );
    CHECK_EQUAL( ftell( file ), 34 );
    }
    {
    // reading +32767, d
    fseek( file, 28, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hd%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 34 );
    }
    {
    // reading 0, u
    fseek( file, 1, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, u
    fseek( file, 0, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, u
    fseek( file, 3, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading 32767, u
    fseek( file, 29, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 5 );
    CHECK_EQUAL( ftell( file ), 34 );
    }
    {
    // reading +32767, u
    fseek( file, 28, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 34 );
    }
    {
    // reading 65535, u
    fseek( file, 36, SEEK_SET );
    unsigned short i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 65535 );
    CHECK_EQUAL( n, 5 );
    CHECK_EQUAL( ftell( file ), 41 );
    }
    {
    // reading +65535, u
    fseek( file, 35, SEEK_SET );
    unsigned short i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%hu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 65535 );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 41 );
    }
    {
    // reading 0, i
    fseek( file, 1, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, i
    fseek( file, 0, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, i
    fseek( file, 3, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading -32768, i
    fseek( file, 21, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -32768 );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 27 );
    }
    {
    // reading 32767, i
    fseek( file, 29, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 5 );
    CHECK_EQUAL( ftell( file ), 34 );
    }
    {
    // reading +32767, i
    fseek( file, 28, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 34 );
    }
    {
    // reading 0, d
    fseek( file, 1, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, d
    fseek( file, 0, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, d
    fseek( file, 3, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading -2147483648, d
    fseek( file, 42, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -2147483648 );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 53 );
    }
    {
    // reading 2147483647, d
    fseek( file, 55, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 10 );
    CHECK_EQUAL( ftell( file ), 65 );
    }
    {
    // reading +2147483647, d
    fseek( file, 54, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%d%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 65 );
    }
    {
    // reading 0, u
    fseek( file, 1, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%u%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, u
    fseek( file, 0, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%u%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, u
    fseek( file, 3, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%u%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading 2147483647, u
    fseek( file, 55, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%u%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 10 );
    CHECK_EQUAL( ftell( file ), 65 );
    }
    {
    // reading +2147483647, u
    fseek( file, 54, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%u%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 65 );
    }
    {
    // reading 4294967295, u
    fseek( file, 67, SEEK_SET );
    unsigned int i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%u%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295, unsigned int, "%u" );
    CHECK_EQUAL( n, 10 );
    CHECK_EQUAL( ftell( file ), 77 );
    }
    {
    // reading +4294967295, u
    fseek( file, 66, SEEK_SET );
    unsigned int i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%u%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295, unsigned int, "%u" );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 77 );
    }
    {
    // reading 0, i
    fseek( file, 1, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, i
    fseek( file, 0, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, i
    fseek( file, 3, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading -2147483648, i
    fseek( file, 42, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -2147483648 );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 53 );
    }
    {
    // reading 2147483647, i
    fseek( file, 55, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 10 );
    CHECK_EQUAL( ftell( file ), 65 );
    }
    {
    // reading +2147483647, i
    fseek( file, 54, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 65 );
    }
    {
    // reading 0, d
    fseek( file, 1, SEEK_SET );
    signed long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%ld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0l );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, d
    fseek( file, 0, SEEK_SET );
    signed long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%ld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0l );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, d
    fseek( file, 3, SEEK_SET );
    signed long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%ld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0l );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading -2147483648, d
    fseek( file, 42, SEEK_SET );
    signed long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%ld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -2147483648l );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 53 );
    }
    {
    // reading 2147483647, d
    fseek( file, 55, SEEK_SET );
    signed long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%ld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647l );
    CHECK_EQUAL( n, 10 );
    CHECK_EQUAL( ftell( file ), 65 );
    }
    {
    // reading +2147483647, d
    fseek( file, 54, SEEK_SET );
    signed long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%ld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647l );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 65 );
    }
    {
    // reading 0, u
    fseek( file, 1, SEEK_SET );
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ul );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, u
    fseek( file, 0, SEEK_SET );
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ul );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, u
    fseek( file, 3, SEEK_SET );
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ul );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading 2147483647, u
    fseek( file, 55, SEEK_SET );
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647ul );
    CHECK_EQUAL( n, 10 );
    CHECK_EQUAL( ftell( file ), 65 );
    }
    {
    // reading +2147483647, u
    fseek( file, 54, SEEK_SET );
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647ul );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 65 );
    }
    {
    // reading 4294967295, u
    fseek( file, 67, SEEK_SET );
    unsigned long i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%lu%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295ul, unsigned long, "%lu" );
    CHECK_EQUAL( n, 10 );
    CHECK_EQUAL( ftell( file ), 77 );
    }
    {
    // reading +4294967295, u
    fseek( file, 66, SEEK_SET );
    unsigned long i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%lu%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295ul, unsigned long, "%lu" );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 77 );
    }
    {
    // reading 0, i
    fseek( file, 1, SEEK_SET );
    signed long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%li%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0l );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, i
    fseek( file, 0, SEEK_SET );
    signed long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%li%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0l );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, i
    fseek( file, 3, SEEK_SET );
    signed long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%li%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0l );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading -2147483648, i
    fseek( file, 42, SEEK_SET );
    signed long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%li%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -2147483648l );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 53 );
    }
    {
    // reading 2147483647, i
    fseek( file, 55, SEEK_SET );
    signed long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%li%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647l );
    CHECK_EQUAL( n, 10 );
    CHECK_EQUAL( ftell( file ), 65 );
    }
    {
    // reading +2147483647, i
    fseek( file, 54, SEEK_SET );
    signed long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%li%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647l );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 65 );
    }
    {
    // reading 0, d
    fseek( file, 1, SEEK_SET );
    signed long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ll );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, d
    fseek( file, 0, SEEK_SET );
    signed long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ll );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, d
    fseek( file, 3, SEEK_SET );
    signed long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lld%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ll );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading -9223372036854775808, d
    fseek( file, 78, SEEK_SET );
    signed long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lld%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, LLONG_MIN, signed long long, "%lld" ); // should be literal -9223372036854775808ll but GCC balks.
    CHECK_EQUAL( i < 0ll, 1 );
    CHECK_EQUAL( n, 20 );
    CHECK_EQUAL( ftell( file ), 98 );
    }
    {
    // reading 9223372036854775807, d
    fseek( file, 100, SEEK_SET );
    signed long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lld%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807ll, signed long long, "%lld" );
    CHECK_EQUAL( n, 19 );
    CHECK_EQUAL( ftell( file ), 119 );
    }
    {
    // reading +9223372036854775807, d
    fseek( file, 99, SEEK_SET );
    signed long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lld%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807ll, signed long long, "%lld" );
    CHECK_EQUAL( n, 20 );
    CHECK_EQUAL( ftell( file ), 119 );
    }
    {
    // reading 0, u
    fseek( file, 1, SEEK_SET );
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%llu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ull );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, u
    fseek( file, 0, SEEK_SET );
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%llu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ull );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, u
    fseek( file, 3, SEEK_SET );
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%llu%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ull );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading 9223372036854775807, u
    fseek( file, 100, SEEK_SET );
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%llu%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807ull, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 19 );
    CHECK_EQUAL( ftell( file ), 119 );
    }
    {
    // reading +9223372036854775807, u
    fseek( file, 99, SEEK_SET );
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%llu%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807ull, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 20 );
    CHECK_EQUAL( ftell( file ), 119 );
    }
    {
    // reading 18446744073709551615, u
    fseek( file, 121, SEEK_SET );
    unsigned long long i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%llu%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 18446744073709551615ull, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 20 );
    CHECK_EQUAL( ftell( file ), 141 );
    }
    {
    // reading +18446744073709551615, u
    fseek( file, 120, SEEK_SET );
    unsigned long long i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%llu%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 18446744073709551615ull, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 21 );
    CHECK_EQUAL( ftell( file ), 141 );
    }
    {
    // reading 0, i
    fseek( file, 1, SEEK_SET );
    signed long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lli%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ll );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading -0, i
    fseek( file, 0, SEEK_SET );
    signed long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lli%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ll );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 2 );
    }
    {
    // reading +0, i
    fseek( file, 3, SEEK_SET );
    signed long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lli%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0ll );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading -9223372036854775808, i
    fseek( file, 78, SEEK_SET );
    signed long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lli%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, LLONG_MIN, signed long long, "%lli" ); // should be literal -9223372036854775808ll but GCC balks.
    CHECK_EQUAL( i < 0ll, 1 );
    CHECK_EQUAL( n, 20 );
    CHECK_EQUAL( ftell( file ), 98 );
    }
    {
    // reading 9223372036854775807, i
    fseek( file, 100, SEEK_SET );
    signed long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lli%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807ll, signed long long, "%lli" );
    CHECK_EQUAL( n, 19 );
    CHECK_EQUAL( ftell( file ), 119 );
    }
    {
    // reading +9223372036854775807, i
    fseek( file, 99, SEEK_SET );
    signed long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lli%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807ll, signed long long, "%lli" );
    CHECK_EQUAL( n, 20 );
    CHECK_EQUAL( ftell( file ), 119 );
    }
    
    fclose( file );
    remove( "tmpfile" );
}

// hexadecimal integer matches
void suite_three()
{
    FILE * file;
    if ( ( file = fopen( "tmpfile", "wb+" ) ) == NULL )
    {
        puts( "Failed to open tmpfile for writing." );
        return;
    }
    fprintf( file, "-0x0 -0x000 -0x7f 0x80 0xff -0x7fff 0x8000 0xffff -0x7fffffff 0x80000000 0xffffffff\n" );
    fprintf( file, "-0x7fffffffffffffff 0x8000000000000000 0xffffffffffffffff -0x\n" );
    CHECK_EQUAL( ftell( file ), 146 );
    {
    // reading 0, x
    fseek( file, 3, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 4 );
    }
    {
    // reading -0x0, x
    fseek( file, 0, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 4 );
    }
    {
    // reading -0x, x
    fseek( file, -4, SEEK_END );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 3 );
    CHECK_EQUAL( ftell( file ), 145 );
    }
    {
    // reading 0x000, x
    fseek( file, 5, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 11 );
    }
    {
    // reading 0x0, i
    fseek( file, 0, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 4 );
    }
    {
    // reading 7f, x
    fseek( file, 15, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127 );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 17 );
    }
    {
    // reading -0x7f, x
    fseek( file, 12, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhx%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -127, unsigned char, "%hhu" );
    CHECK_EQUAL( n, 5 );
    CHECK_EQUAL( ftell( file ), 17 );
    }
    {
    // reading 0x80, i
    fseek( file, 18, SEEK_SET );
    signed char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhi%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -128, signed char, "%hd" );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 22 );
    }
    {
    // reading ff, x
    fseek( file, 25, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0xff );
    CHECK_EQUAL( n, 2 );
    CHECK_EQUAL( ftell( file ), 27 );
    }
    {
    // reading 0xff, x
    fseek( file, 23, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 255 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 27 );
    }
    {
    // reading 0xff, i
    fseek( file, 23, SEEK_SET );
    signed char i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%hhi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, -1 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 27 );
    }
    {
    // reading 0, x
    fseek( file, 3, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 4 );
    }
    {
    // reading -0x0, x
    fseek( file, 0, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 4 );
    }
    {
    // reading -0x, x
    fseek( file, -4, SEEK_END );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 3 );
    CHECK_EQUAL( ftell( file ), 145 );
    }
    {
    // reading 0x000, x
    fseek( file, 5, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 11 );
    }
    {
    // reading 0x0, i
    fseek( file, 0, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hi%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 4 );
    }
    {
    // reading 7fff, x
    fseek( file, 31, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 35 );
    }
    {
    // reading -0x7fff, x
    fseek( file, 28, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hx%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -32767, unsigned short, "%hu" );
    CHECK_EQUAL( n, 7 );
    CHECK_EQUAL( ftell( file ), 35 );
    }
    {
    // reading 0x8000, i
    fseek( file, 36, SEEK_SET );
    signed short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hi%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -32768, signed short, "%hd" );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 42 );
    }
    {
    // reading ffff, x
    fseek( file, 45, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 65535 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 49 );
    }
    {
    // reading 0xffff, x
    fseek( file, 43, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hx%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 65535 );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 49 );
    }
    {
    // reading 0xffff, i
    fseek( file, 43, SEEK_SET );
    signed short i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%hi%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -1, signed short, "%hd" );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 49 );
    }
    {
    // reading 0, x
    fseek( file, 3, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%x%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 4 );
    }
    {
    // reading -0x0, x
    fseek( file, 0, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%x%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 4 );
    }
    {
    // reading -0x, x
    fseek( file, -4, SEEK_END );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%x%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 3 );
    CHECK_EQUAL( ftell( file ), 145 );
    }
    {
    // reading 0x000, x
    fseek( file, 5, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%x%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 11 );
    }
    {
    // reading 0x0, i
    fseek( file, 0, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%i%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0 );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 4 );
    }
    {
    // reading 7fffffff, x
    fseek( file, 53, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%x%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647 );
    CHECK_EQUAL( n, 8 );
    CHECK_EQUAL( ftell( file ), 61 );
    }
    {
    // reading -0x7fffffff, x
    fseek( file, 50, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%x%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, -2147483647, unsigned int, "%u" );
    CHECK_EQUAL( n, 11 );
    CHECK_EQUAL( ftell( file ), 61 );
    }
    {
    // reading 0x80000000, i
    fseek( file, 62, SEEK_SET );
    signed int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%i%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 2147483647, signed int, "%d" ); // NOT overflowing, see strtol() specs.
    CHECK_EQUAL( n, 10 );
    CHECK_EQUAL( ftell( file ), 72 );
    }
    {
    // reading ffffffff, x
    fseek( file, 75, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%x%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295, unsigned int, "%d" );
    CHECK_EQUAL( n, 8 );
    CHECK_EQUAL( ftell( file ), 83 );
    }
    {
    // reading 0xffffffff, x
    fseek( file, 73, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%x%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295, unsigned int, "%d" );
    CHECK_EQUAL( n, 10 );
    CHECK_EQUAL( ftell( file ), 83 );
    }
    {
    // reading 0xffffffff, i
    fseek( file, 73, SEEK_SET );
    signed int i = 0;
    int n;
    CHECK_EQUAL( fscanf( file, "%i%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 2147483647, signed int, "%d" ); // NOT overflowing; see strtol() specs.
    CHECK_EQUAL( n, 10 );
    CHECK_EQUAL( ftell( file ), 83 );
    }
    fclose( file );
    remove( "tmpfile" );    
}

// octal integer matches
void suite_four()
{
    FILE * file;
    if ( ( file = fopen( "tmpfile", "wb+" ) ) == NULL )
    {
        puts( "Failed to open tmpfile for writing." );
        return;
    }
    fprintf( file, "+0000 -0000 +0177 +0377 -0377 +077777 +0177777 -0177777\n" );
    fprintf( file, "+017777777777 +037777777777 -037777777777\n" );
    fprintf( file, "+0777777777777777777777 +01777777777777777777777\n" );
    fprintf( file, "-01777777777777777777777\n" );
    CHECK_EQUAL( ftell( file ), 172 );
    {
    // reading 0, o
    fseek( file, 4, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0u );
    CHECK_EQUAL( n, 1 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading +0000, o
    fseek( file, 0, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0u );
    CHECK_EQUAL( n, 5 );
    CHECK_EQUAL( ftell( file ), 5 );
    }
    {
    // reading -0000, o
    fseek( file, 6, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 0u );
    CHECK_EQUAL( n, 5 );
    CHECK_EQUAL( ftell( file ), 11 );
    }
    {
    // reading 0177, o
    fseek( file, 13, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127u );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 17 );
    }
    {
    // reading +0177, o
    fseek( file, 12, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 127u );
    CHECK_EQUAL( n, 5 );
    CHECK_EQUAL( ftell( file ), 17 );
    }
    {
    // reading 0377, o
    fseek( file, 19, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hho%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 255u, unsigned char, "%hhu" );
    CHECK_EQUAL( n, 4 );
    CHECK_EQUAL( ftell( file ), 23 );
    }
    {
    // reading +0377, o
    fseek( file, 18, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hho%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 255u, unsigned char, "%hhu" );
    CHECK_EQUAL( n, 5 );
    CHECK_EQUAL( ftell( file ), 23 );
    }
    {
    // reading -0377, o
    fseek( file, 24, SEEK_SET );
    unsigned char i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%hho%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 1u, unsigned char, "%hhu" );
    CHECK_EQUAL( n, 5 );
    CHECK_EQUAL( ftell( file ), 29 );
    }
    {
    // reading 077777, o
    fseek( file, 31, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%ho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767u );
    CHECK_EQUAL( n, 6 );
    CHECK_EQUAL( ftell( file ), 37 );
    }
    {
    // reading +077777, o
    fseek( file, 30, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%ho%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 32767u );
    CHECK_EQUAL( n, 7 );
    CHECK_EQUAL( ftell( file ), 37 );
    }
    {
    // reading 0177777, o
    fseek( file, 39, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%ho%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 65535u, unsigned short, "%hu" );
    CHECK_EQUAL( n, 7 );
    CHECK_EQUAL( ftell( file ), 46 );
    }
    {
    // reading +0177777, o
    fseek( file, 38, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%ho%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 65535u, unsigned short, "%hu" );
    CHECK_EQUAL( n, 8 );
    CHECK_EQUAL( ftell( file ), 46 );
    }
    {
    // reading -0177777, o
    fseek( file, 47, SEEK_SET );
    unsigned short i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%ho%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 1u, unsigned short, "%hu" );
    CHECK_EQUAL( n, 8 );
    CHECK_EQUAL( ftell( file ), 55 );
    }
    {
    // reading 017777777777, o
    fseek( file, 57, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%o%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647u );
    CHECK_EQUAL( n, 12 );
    CHECK_EQUAL( ftell( file ), 69 );
    }
    {
    // reading +017777777777, o
    fseek( file, 56, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%o%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647u );
    CHECK_EQUAL( n, 13 );
    CHECK_EQUAL( ftell( file ), 69 );
    }
    {
    // reading 037777777777, o
    fseek( file, 71, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%o%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295u, unsigned int, "%u" );
    CHECK_EQUAL( n, 12 );
    CHECK_EQUAL( ftell( file ), 83 );
    }
    {
    // reading +037777777777, o
    fseek( file, 70, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%o%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295u, unsigned int, "%u" );
    CHECK_EQUAL( n, 13 );
    CHECK_EQUAL( ftell( file ), 83 );
    }
    {
    // reading -037777777777, o
    fseek( file, 84, SEEK_SET );
    unsigned int i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%o%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 1u, unsigned int, "%u" );
    CHECK_EQUAL( n, 13 );
    CHECK_EQUAL( ftell( file ), 97 );
    }
    {
    // reading 017777777777, o
    fseek( file, 57, SEEK_SET );
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lo%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647lu );
    CHECK_EQUAL( n, 12 );
    CHECK_EQUAL( ftell( file ), 69 );
    }
    {
    // reading +017777777777, o
    fseek( file, 56, SEEK_SET );
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lo%n", &i, &n ), 1 );
    CHECK_EQUAL( i, 2147483647lu );
    CHECK_EQUAL( n, 13 );
    CHECK_EQUAL( ftell( file ), 69 );
    }
    {
    // reading 037777777777, o
    fseek( file, 71, SEEK_SET );
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295lu, unsigned long, "%lu" );
    CHECK_EQUAL( n, 12 );
    CHECK_EQUAL( ftell( file ), 83 );
    }
    {
    // reading +037777777777, o
    fseek( file, 70, SEEK_SET );
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 4294967295lu, unsigned long, "%lu" );
    CHECK_EQUAL( n, 13 );
    CHECK_EQUAL( ftell( file ), 83 );
    }
    {
    // reading -037777777777, o
    fseek( file, 84, SEEK_SET );
    unsigned long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%lo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 1lu, unsigned long, "%lu" );
    CHECK_EQUAL( n, 13 );
    CHECK_EQUAL( ftell( file ), 97 );
    }
    {
    // reading 0777777777777777777777, o
    fseek( file, 99, SEEK_SET );
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%llo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807llu, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 22 );
    CHECK_EQUAL( ftell( file ), 121 );
    }
    {
    // reading +0777777777777777777777, o
    fseek( file, 98, SEEK_SET );
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%llo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 9223372036854775807llu, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 23 );
    CHECK_EQUAL( ftell( file ), 121 );
    }
    {
    // reading 01777777777777777777777, o
    fseek( file, 123, SEEK_SET );
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%llo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 18446744073709551615llu, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 23 );
    CHECK_EQUAL( ftell( file ), 146 );
    }
    {
    // reading +01777777777777777777777, o
    fseek( file, 122, SEEK_SET );
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%llo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 18446744073709551615llu, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 24 );
    CHECK_EQUAL( ftell( file ), 146 );
    }
    {
    // reading -01777777777777777777777, o
    fseek( file, 147, SEEK_SET );
    unsigned long long i = -1;
    int n;
    CHECK_EQUAL( fscanf( file, "%llo%n", &i, &n ), 1 );
    CHECK_FEQUAL( i, 1llu, unsigned long long, "%llu" );
    CHECK_EQUAL( n, 24 );
    CHECK_EQUAL( ftell( file ), 171 );
    }
    fclose( file );
    remove( "tmpfile" );    
}

// string matches
void suite_five()
{
    int const BUFSIZE = 1000;
    FILE * file;
    if ( ( file = fopen( "tmpfile", "wb+" ) ) == NULL )
    {
        puts( "Failed to open tmpfile for writing." );
        return;
    }
    fprintf( file, "abcdefgh-ijklmnop[qrs%%uvw]xyz" );
    CHECK_EQUAL( ftell( file ), 29 );
    char buffer[ BUFSIZE ];
    {
    // reading abc
    fseek( file, 0, SEEK_SET );
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( fscanf( file, "%[abc]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 3 );
    CHECK_FALSE( memcmp( buffer, "abc", n + 1 ) );
    CHECK_EQUAL( ftell( file ), 3 );
    }
    {
    // reading a-c
    fseek( file, 0, SEEK_SET );
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( fscanf( file, "%[a-c]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 3 );
    CHECK_FALSE( memcmp( buffer, "abc", n + 1 ) );
    CHECK_EQUAL( ftell( file ), 3 );
    }
    {
    // reading a-h
    fseek( file, 0, SEEK_SET );
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( fscanf( file, "%[a-h]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 8 );
    CHECK_FALSE( memcmp( buffer, "abcdefgh", n + 1 ) );
    CHECK_EQUAL( ftell( file ), 8 );
    }
    {
    // reading o-r, including [, seperate char
    fseek( file, 15, SEEK_SET );
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( fscanf( file, "%[[o-qr]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 5 );
    CHECK_FALSE( memcmp( buffer, "op[qr", n + 1 ) );
    CHECK_EQUAL( ftell( file ), 20 );
    }
    {
    // reading v-y, including ], two groups
    fseek( file, 23, SEEK_SET );
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( fscanf( file, "%[]v-wx-y]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 5 );
    CHECK_FALSE( memcmp( buffer, "vw]xy", n + 1 ) );
    CHECK_EQUAL( ftell( file ), 28 );
    }
    {
    // missing on first character
    fseek( file, 0, SEEK_SET );
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( fscanf( file, "%[b]%n", buffer, &n ), 0 );
    CHECK_FALSE( memcmp( buffer, "", 1 ) );
    CHECK_EQUAL( ftell( file ), 0 );
    }
    {
    // eof while reading, two groups
    fseek( file, 27, SEEK_SET );
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( fscanf( file, "%[a-zA-Z]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 2 );
    CHECK_FALSE( memcmp( buffer, "yz", n + 1 ) );
    CHECK_TRUE( feof( file ) );
    CHECK_FALSE( ferror( file ) );
    CHECK_EQUAL( ftell( file ), 29 );
    }
    {
    // eof before reading
    fseek( file, 29, SEEK_SET );
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( fscanf( file, "%[a-z]%n", buffer, &n ), -1 );
    CHECK_FALSE( memcmp( buffer, "", 1 ) );
    CHECK_TRUE( feof( file ) );
    CHECK_FALSE( ferror( file ) );
    CHECK_EQUAL( ftell( file ), 29 );
    }
    {
    // negation - [^...]
    fseek( file, 0, SEEK_SET );
    memset( buffer, '\0', BUFSIZE );
    int n;
    CHECK_EQUAL( fscanf( file, "%[^d-f]%n", buffer, &n ), 1 );
    CHECK_EQUAL( n, 3 );
    CHECK_FALSE( memcmp( buffer, "abc", 4 ) );
    CHECK_EQUAL( ftell( file ), 3 );
    }
    fclose( file );
    remove( "tmpfile" );    
}

#if 0
char scanstring[] = "  1 23\00045\000\00067 ";

void scantest( int testnr, FILE * fh, size_t position, char const * format, 
               int expected_fscan_rc, char const * expected_fscan_output, size_t expected_fscan_length, 
               int expected_sscan_rc, char const * expected_sscan_output, size_t expected_sscan_length )
{
    char buffer[15];
    printf( "Test %d\n", testnr );
    TESTCASE( memset( buffer, -1, 15 ) == buffer );
    TESTCASE( fseek( fh, position, SEEK_SET ) == 0 );
    TESTCASE( fscanf( fh, format, buffer ) == expected_fscan_rc );
    TESTCASE( memcmp( buffer, expected_fscan_output, expected_fscan_length ) == 0 );
    TESTCASE( memset( buffer, -1, 15 ) == buffer );
    TESTCASE( sscanf( scanstring + position, format, buffer ) == expected_sscan_rc );
    TESTCASE( memcmp( buffer, expected_sscan_output, expected_sscan_length ) == 0 );
}

int main( void )
{
    FILE * fh;
    TESTCASE( ( fh = fopen( "testfile", "w+" ) ) != NULL );
    TESTCASE( fwrite( scanstring, 14, 1, fh ) == 1 );
    rewind( fh );

    /* %14c - full scan */
    scantest( 1, fh, 0, "%14c",
              1, "  1 23\00045\000\00067 \377", 15,
              1, "  1 23\377", 7 );

    /* %c - default to one, reading whitespace */
    scantest( 2, fh, 0, "%c",
              1, " \377", 2,
              1, " \377", 2 );

    /* %1c - reading zero byte */
    scantest( 3, fh, 9, "%1c",
              1, "\000\377", 2,
              -1, "\377", 1 );

    /* %0c - NOT reading EOF */
    scantest( 4, fh, 13, "%0c",
              0, "\377", 1,
              0, "\377", 1 );
              
    TESTCASE( fclose( fh ) == 0 );
    //TESTCASE( remove( "testfile" ) == 0 );

    return TEST_RESULTS;
}
#endif

#endif
