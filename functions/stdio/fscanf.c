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

#include <limits.h>
#include <string.h>

int main( void )
{
    char teststring1[] = "  1 23\045\0\067 ";
    char buffer[15];
    FILE * fh;
    TESTCASE( ( fh = fopen( "testfile", "w+" ) ) != NULL );
    TESTCASE( fwrite( teststring1, 15, 1, fh ) == 1 );
    rewind( fh );
    /* */
    TESTCASE( memset( buffer, CHAR_MAX, 15 ) == buffer ); \
    TESTCASE( fseek( fh, 0, SEEK_SET ) == 0 ); \
    TESTCASE( fscanf( fh, "%14c", buffer ) == 1 ); \
    TESTCASE( memcmp( buffer, teststring1 + 0, 14 ) == 0 ); \
    TESTCASE( buffer[ 14 ] == CHAR_MAX ); \
    TESTCASE( memset( buffer, CHAR_MAX, 15 ) == buffer ); \
    TESTCASE( sscanf( teststring1 + 14, "%14c", buffer ) ); \
    TESTCASE( memcmp( buffer, teststring1 + 0, 14 ) == 0 ); \
    TESTCASE( buffer[ 14 ] == CHAR_MAX );
    return TEST_RESULTS;
}

#endif
