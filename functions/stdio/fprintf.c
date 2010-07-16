/* $Id$ */

/* fprintf( FILE *, const char *, ... )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int fprintf( struct _PDCLIB_file_t * _PDCLIB_restrict stream, const char * _PDCLIB_restrict format, ... )
{
    int rc;
    va_list ap;
    va_start( ap, format );
    rc = vfprintf( stream, format, ap );
    va_end( ap );
    return rc;
}

#endif

#ifdef TEST
#include <limits.h>
#include <string.h>
#include <_PDCLIB_test.h>

#define testprintf( stream, n, format, ... ) fprintf( stream, format, __VA_ARGS__ )

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
