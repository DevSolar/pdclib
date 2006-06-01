/* $Id$ */

/* rename( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

int rename( const char * old, const char * new )
{
    /* TODO: Search open file list, flush and close file */
    return _PDCLIB_rename( old, new );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
#ifndef REGTEST
    TESTCASE( NO_TESTDRIVER );
#else
    puts( "No testing of rename() - test driver does not know internals of system function." );
#endif
    return TEST_RESULTS;
}

#endif
