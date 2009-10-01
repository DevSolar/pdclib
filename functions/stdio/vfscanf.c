/* $Id$ */

/* vfscanf( FILE *, const char *, va_list )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef REGTEST

int vfscanf( FILE * _PDCLIB_restrict stream, const char * _PDCLIB_restrict format, va_list arg )
{
    struct _PDCLIB_status_t status;
    status.base = 0;
    status.flags = 0;
    status.n = 0; 
    status.i = 0;
    status.this = 0;
    status.s = NULL;
    status.width = 0;
    status.prec = 0;
    status.stream = stream;
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
            /* NULL return code indicates matching error */
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
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
