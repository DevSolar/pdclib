/* $Id$ */

/* remove( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

int remove( const char * filename )
{
    /* TODO: Check open file list, flush and close file if open */
    return _PDCLIB_remove( filename );
}

#endif

#ifdef TEST
/* TODO: Work around the following undef */
#undef SEEK_SET
#include <_PDCLIB_test.h>

#include <stdlib.h>
#include <string.h>

int main( void )
{
    /* TODO: Extend to internal testing (buffer etc.) */
    char filename[] = "touch testfile";
    system( filename );
    /* file is actually readable */
    TESTCASE( fopen( filename + 6, "r" ) != NULL );
    /* remove function does not return error */
    TESTCASE( remove( filename + 6 ) == 0 );
    /* file is no longer readable */
    TESTCASE( fopen( filename + 6, "r" ) == NULL );
    /* remove function does return error */
    TESTCASE( remove( filename + 6 ) != 0 );
    memcpy( filename, "mkdir", 5 );
    /* create directory */
    system( filename );
    /* remove function does not return error */
    TESTCASE( remove( filename + 6 ) == 0 );
    /* remove function does return error */
    TESTCASE( remove( filename + 6 ) != 0 );
    return TEST_RESULTS;
}

#endif
