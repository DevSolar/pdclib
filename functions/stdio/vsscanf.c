/* $Id$ */

/* vsscanf( const char *, const char *, va_list arg )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int vsscanf( const char * _PDCLIB_restrict s, const char * _PDCLIB_restrict format, va_list arg )
{
    struct _PDCLIB_status_t status;
    status.base = 0;
    status.flags = 0;
    /* In _PDCLIB_print, status.n holds the maximum number of characters to be
       written. As we don't need that for the scanf() functions, we (ab)use
       this field to hold the number of matching conversion specifiers.
    */
    status.n = 0; 
    status.i = 0;
    status.this = 0;
    /* In _PDCLIB_print, status.s is the string *printed to*. In the scanf()
       functions, we (ab)use this field to hold the string *scanned from*.
    */
    status.s = (char *)s;
    status.width = 0;
    status.prec = 0;
    status.stream = NULL;
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
