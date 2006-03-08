/* $Id$ */

/* _PDCLIB_rename( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST
#include <unistd.h>
#include <_PDCLIB_glue.h>

int _PDCLIB_rename( const char * old, const char * new )
{
    /* Note that the behaviour if new file exists is implementation-defined.
       There is nothing wrong with either overwriting it or failing the
       operation, but you might want to document whichever you chose.
       This example fails if new file exists.
    */
    if ( link( old, new ) == 0 )
    {
        return unlink( old );
    }
    else
    {
        return -1;
    }
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
