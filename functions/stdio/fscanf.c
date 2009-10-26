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

#include <string.h>

char scanstring[] = "  1 23\00045\000\00067 ";

void scantest( int testnr, FILE * fh, size_t position, char const * format, 
               int expected_fscan_rc, char const * expected_fscan_output, size_t expected_fscan_length, 
               int expected_sscan_rc, char const * expected_sscan_output, size_t expected_sscan_length )
{
    char buffer[15];
    printf( "Test %d\n", testnr );
    TESTCASE( memset( buffer, -1, 15 ) == buffer );
    TESTCASE( fseek( fh, position, SEEK_SET ) == 0 );
    TESTCASE( fscanf( fh, format, buffer ) == expected_fscan_rc );
    TESTCASE( memcmp( buffer, expected_fscan_output, expected_fscan_length ) == 0 );
    TESTCASE( memset( buffer, -1, 15 ) == buffer );
    TESTCASE( sscanf( scanstring + position, format, buffer ) == expected_sscan_rc );
    TESTCASE( memcmp( buffer, expected_sscan_output, expected_sscan_length ) == 0 );
}

int main( void )
{
    FILE * fh;
    TESTCASE( ( fh = fopen( "testfile", "w+" ) ) != NULL );
    TESTCASE( fwrite( scanstring, 14, 1, fh ) == 1 );
    rewind( fh );

    /* %14c - full scan */
    scantest( 1, fh, 0, "%14c",
              1, "  1 23\00045\000\00067 \377", 15,
              1, "  1 23\377", 7 );

    /* %c - default to one, reading whitespace */
    scantest( 2, fh, 0, "%c",
              1, " \377", 2,
              1, " \377", 2 );

    /* %1c - reading zero byte */
    scantest( 3, fh, 9, "%1c",
              1, "\000\377", 2,
              -1, "\377", 1 );

    /* %0c - NOT reading EOF */
    scantest( 4, fh, 13, "%0c",
              0, "\377", 1,
              0, "\377", 1 );
              
    TESTCASE( fclose( fh ) == 0 );
    //TESTCASE( remove( "testfile" ) == 0 );

    return TEST_RESULTS;
}

#endif
