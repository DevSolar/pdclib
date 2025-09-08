/* _PDCLIB_strtod_prelim( const char *, char *, int * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>
#include <stddef.h>
#include <string.h>

#ifndef REGTEST

int _PDCLIB_strtod_prelim( const char * p, char * sign, char ** endptr )
{
    int base = 10;

    /* skipping leading whitespace */
    while ( isspace( (unsigned char)*p ) )
    {
        ++p;
    }

    /* determining / skipping sign */
    if ( *p != '+' && *p != '-' )
    {
        *sign = '+';
    }
    else
    {
        *sign = *( p++ );
    }

    /* determining base */
    if ( *p == '0' )
    {
        ++p;

        if ( *p == 'x' || *p == 'X' )
        {
            int period = 0;
            base = 16;
            ++p;

            if ( *p == '.' )
            {
                ++p;
                period = 1;
            }

            /* catching a border case here: "0x" followed by a non-digit should
               be parsed as the unprefixed zero.
               We have to "rewind" the parsing.
            */
            if ( memchr( _PDCLIB_digits, tolower( (unsigned char)*p ), base ) == NULL )
            {
                p -= ( 2 + period );
            }
        }
        else
        {
            --p;
        }
    }
    else
    {
        /* inf / nan(...) */
        /* Repurposing base: 0 for no match, -1 for inf, -2 for nan */
        if ( tolower( (unsigned char)p[0] ) == 'i' && tolower( (unsigned char)p[1] ) == 'n' && tolower( (unsigned char)p[2] ) == 'f' )
        {
            p += 3;
            base = -1;
        }
        else if ( tolower( (unsigned char)p[0] ) == 'n' && tolower( (unsigned char)p[1] ) == 'a' && tolower( (unsigned char)p[2] ) == 'n' )
        {
            const char * n = p + 3;
            p = n;
            base = -2;

            if ( *n == '(' )
            {
                while ( *++n && *n != ')' );

                if ( *n == ')' )
                {
                    p = n + 1;
                }
            }
        }
    }

    *endptr = (char *)p;
    return base;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    int base = 0;
    char sign = '\0';
    char test1[] = "  123";
    char test2[] = "\t+0123";
    char test3[] = "\v-0x123";
    TESTCASE( _PDCLIB_strtox_prelim( test1, &sign, &base ) == &test1[2] );
    TESTCASE( sign == '+' );
    TESTCASE( base == 10 );
    base = 0;
    sign = '\0';
    TESTCASE( _PDCLIB_strtox_prelim( test2, &sign, &base ) == &test2[2] );
    TESTCASE( sign == '+' );
    TESTCASE( base == 8 );
    base = 0;
    sign = '\0';
    TESTCASE( _PDCLIB_strtox_prelim( test3, &sign, &base ) == &test3[4] );
    TESTCASE( sign == '-' );
    TESTCASE( base == 16 );
    base = 10;
    sign = '\0';
    TESTCASE( _PDCLIB_strtox_prelim( test3, &sign, &base ) == &test3[2] );
    TESTCASE( sign == '-' );
    TESTCASE( base == 10 );
    base = 1;
    TESTCASE( _PDCLIB_strtox_prelim( test3, &sign, &base ) == NULL );
    base = 37;
    TESTCASE( _PDCLIB_strtox_prelim( test3, &sign, &base ) == NULL );
#endif
    return TEST_RESULTS;
}

#endif
