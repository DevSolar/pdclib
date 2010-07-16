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
    struct _PDCLIB_status_t status;
    status.base = 0;
    status.flags = 0;
    status.n = SIZE_MAX;
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
            putc( *(format++), stream );
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

#endif

#ifdef TEST
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <_PDCLIB_test.h>

static int testprintf( FILE * stream, size_t n, const char * format, ... )
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
    FILE * buffer;
    TESTCASE( ( buffer = fopen( "testfile", "w" ) ) != NULL );
#include "printf_testcases.incl"
    TESTCASE( fclose( buffer ) == 0 );
    char readbuffer[1000];
    TESTCASE( ( buffer = fopen( "testfile", "r" ) ) != NULL );
    TESTCASE( fread( readbuffer, 1, 1000, buffer ) == 985 );
    TESTCASE( fclose( buffer ) == 0 );
    TESTCASE( remove( "testfile" ) == 0 );
    TESTCASE( memcmp( readbuffer, "-1281270-32768327670-214748364821474836470-214748364821474836470-922337203685477580892233720368547758070255255655356553542949672954294967295429496729542949672951844674407370955161518446744073709551615FFFFFFFF0XFFFFFFFFffffffff0xffffffff37777777777037777777777%.0#o-2147483648+2147483647+042949672954294967295-2147483648 2147483647 042949672954294967295-21474836482147483647-21474836482147483647-2147483648 2147483647 -2147483648  2147483647-21474836482147483647-21474836482147483647-21474836482147483647 -2147483648 2147483647  -21474836482147483647-21474836482147483647-214748364802147483647-02147483648002147483647-21474836482147483647-21474836482147483647-21474836482147483647 -2147483648 2147483647            00000000002147483647ffffffff0xffffffff0xffffffff-2147483648-2147483648-21474836480xffffffff0xffffffff0xffffffff214748364721474836472147483647+2147483647+2147483647+2147483647+2147483647+2147483647+2147483647- 2147483647- 2147483647 % -2147483648xabcdef0xdeadbeef123456789", 985 ) == 0 );
    return TEST_RESULTS;
}

#endif
