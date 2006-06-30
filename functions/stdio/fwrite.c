/* $Id$ */

/* fwrite( const void *, size_t, size_t, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <_PDCLIB_glue.h>

#ifndef REGTEST

size_t fwrite( const void * _PDCLIB_restrict ptr, size_t size, size_t nmemb, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    return _PDCLIB_write( stream->handle, ptr, size * nmemb );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    FILE * fh;
    TESTCASE( ( fh = fopen( "testfile", "w" ) ) != NULL );
    TESTCASE( fwrite( "SUCCESS testing fwrite()\n", 1, 25, fh ) == 25 );
    TESTCASE( fclose( fh ) == 0 );
    /* TODO: Add readback test. */
    TESTCASE( remove( "testfile" ) == 0 );
    return TEST_RESULTS;
}

#endif
