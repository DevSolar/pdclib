/* $Id$ */

/* vfprintf( FILE *, const char *, va_list )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits.h>

#ifndef REGTEST
#include <_PDCLIB_io.h>

int _PDCLIB_vfprintf_unlocked( FILE * _PDCLIB_restrict stream, 
                       const char * _PDCLIB_restrict format, 
                       va_list arg )
{
    /* TODO: This function should interpret format as multibyte characters.  */
    struct _PDCLIB_status_t status;
    status.base = 0;
    status.flags = 0;
    status.n = UINT_MAX;
    status.i = 0;
    status.current = 0;
    status.s = NULL;
    status.width = 0;
    status.prec = 0;
    status.stream = stream;
    va_copy( status.arg, arg );

    while ( *format != '\0' )
    {
        const char * rc;
        if ( ( *format != '%' ) || ( ( rc = _PDCLIB_print( format, &status ) ) == format ) )
        {
            /* No conversion specifier, print verbatim */
            _PDCLIB_putc_unlocked( *(format++), stream );
            status.i++;
        }
        else
        {
            /* Continue parsing after conversion specifier */
            format = rc;
        }
    }
    va_end( status.arg );
    return status.i;
}

int vfprintf( FILE * _PDCLIB_restrict stream, 
              const char * _PDCLIB_restrict format, 
              va_list arg )
{
    _PDCLIB_flockfile( stream );
    int r = _PDCLIB_vfprintf_unlocked( stream, format, arg );
    _PDCLIB_funlockfile( stream );
    return r;
}

#endif

#ifdef TEST
#define _PDCLIB_FILEID "stdio/vfprintf.c"
#define _PDCLIB_FILEIO
#include <stddef.h>
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
    FILE * target;
    TESTCASE( ( target = tmpfile() ) != NULL );
#include "printf_testcases.h"
    TESTCASE( fclose( target ) == 0 );
    return TEST_RESULTS;
}

#endif
