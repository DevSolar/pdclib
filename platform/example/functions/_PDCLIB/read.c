/* $Id$ */

/* _PDCLIB_read( _PDCLIB_fd_t, char *, _PDCLIB_size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <_PDCLIB_glue.h>

#ifndef REGTEST

int read(int, void *, unsigned int);

_PDCLIB_size_t _PDCLIB_read( _PDCLIB_fd_t fd, char * buffer, _PDCLIB_size_t n )
{
    return read( fd, buffer, n );
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
