/* $Id$ */

/* vsnprintf( char *, size_t, const char *, va_list ap )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int vsnprintf( char * s, size_t n, const char * format, _PDCLIB_va_list arg )
{
    /* TODO: This function should interpret format as multibyte characters.  */
    /* Members: base, flags, n, i, this, s, width, prec, stream, arg         */
    struct _PDCLIB_status_t status = { 0, 0, n, 0, 0, s, 0, 0, NULL, arg };
    while ( *format != '\0' )
    {
        const char * rc;
        if ( ( *format != '%' ) || ( ( rc = _PDCLIB_print( format, &status ) ) == format ) )
        {
            /* No conversion specifier, print verbatim */
            s[ status.i++ ] = *(format++);
        }
        else
        {
            /* Continue parsing after conversion specifier */
            format = rc;
        }
    }
    s[ status.i ] = '\0';
    return status.i;
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
