/* $Id$ */

/* vsscanf( const char *, const char *, va_list arg )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST
#include <ctype.h>

int vsscanf( const char * _PDCLIB_restrict s, const char * _PDCLIB_restrict format, va_list arg )
{
    /* base, flag, n, i, current, s, width, prec, stream, arg */
    struct _PDCLIB_status_t status = { 0, 0, 0, 0, 0, (char *)s, 0, 0, NULL, NULL };
    va_copy( status.arg, arg );

    while ( *format != '\0' )
    {
        const char * rc;
        if ( ( *format != '%' ) || ( ( rc = _PDCLIB_scan( format, &status ) ) == format ) )
        {
            /* No conversion specifier, match verbatim */
            if ( isspace( *format ) )
            {
                /* Whitespace char in format string: Skip all whitespaces */
                /* No whitespaces in input do not result in matching error */
                while ( isspace( *status.s ) )
                {
                    ++status.s;
                    ++status.i;
                }
            }
            else
            {
                /* Non-whitespace char in format string: Match verbatim */
                if ( *status.s != *format )
                {
                    /* Matching error */
                    return status.n;
                }
                else
                {
                    ++status.s;
                    ++status.i;
                }
            }
            ++format;
        }
        else
        {
            /* NULL return code indicates input error */
            if ( rc == NULL )
            {
                break;
            }
            /* Continue parsing after conversion specifier */
            format = rc;
        }
    }
    va_end( status.arg );
    return status.n;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    char const * teststring1 = "abc  def";
    char const * teststring2 = "abcdef";
    char const * teststring3 = "abc%def";
    int x;
    TESTCASE( sscanf( teststring2, "abcdef%n", &x ) == 0 );
    TESTCASE( x == 6 );
    TESTCASE( sscanf( teststring1, "abc def%n", &x ) == 0 );
    TESTCASE( x == 8 );
    TESTCASE( sscanf( teststring2, "abc def%n", &x ) == 0 );
    TESTCASE( x == 6 );
    TESTCASE( sscanf( teststring3, "abc%%def%n", &x ) == 0 );
    TESTCASE( x == 7 );
    return TEST_RESULTS;
}

#endif
