/* $Id$ */

/* vfprintf( FILE *, const char *, va_list )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#ifndef REGTEST

int vfprintf( struct _PDCLIB_file_t * _PDCLIB_restrict stream, const char * _PDCLIB_restrict format, va_list arg )
{
    /* TODO: This function should interpret format as multibyte characters.  */
    /* Members: base, flags, n, i, this, s, width, prec, stream, arg         */
    struct _PDCLIB_status_t status = { 0, 0, SIZE_MAX, 0, 0, NULL, 0, 0, stream, arg };
    while ( *format != '\0' )
    {
        const char * rc;
        if ( ( *format != '%' ) || ( ( rc = _PDCLIB_print( format, &status ) ) == format ) )
        {
            /* No conversion specifier, print verbatim */
            putc( *(format++), stream );
        }
        else
        {
            /* Continue parsing after conversion specifier */
            format = rc;
        }
    }
    return status.i;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

static int testprintf( FILE * stream, const char * format, ... )
{
    int i;
    va_list arg;
    va_start( arg, format );
    i = vfprintf( stream, format, arg );
    va_end( arg );
    return i;
}

int main( void )
{
    FILE * fh;
    TESTCASE( testprintf( stdout, "Hallo\n" ) == 6 );
#if 0
    TESTCASE( ( fh = fopen( "testfile", "w" ) ) != NULL );
    TESTCASE( testprintf( fh, "Hallo\n" ) );
    TESTCASE( fclose( fh ) == 0 );
    TESTCASE( remove( "testfile" ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
