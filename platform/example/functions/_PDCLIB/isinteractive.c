/* $Id$ */

/* _PDCLIB_isinteractive( _PDCLIB_fd_t fd )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of _PDCLIB_isinteractive() (declared in
   _PDCLIB_glue.h), fit for use in POSIX kernels.
   If you do not have an equivalent function, replace this with a return (1)
   and you will have all streams line-buffered by default.
*/

#ifndef REGTEST
#include <_PDCLIB_glue.h>

int isatty( int );

int _PDCLIB_isinteractive( int fd )
{
    return isatty( fd );
}

#endif

#ifdef TEST
/* TODO: Work around the following undef */
#undef SEEK_SET
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
