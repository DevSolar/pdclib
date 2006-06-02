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
#include <_PDCLIB_test.h>

int main( void )
{
#ifndef REGTEST
    TESTCASE( NO_TESTDRIVER );
#else
    puts( " NOTEST remove() test driver is PDCLib-specific." );
#endif
    return TEST_RESULTS;
}

#endif
