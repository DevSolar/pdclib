/* $Id$ */

/* _PDCLIB_close( _PDCLIB_fd_t fd )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is a stub example implementation of _PDCLIB_close()
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>
#include <errno.h>

int _PDCLIB_close( int fd )
{
    errno = ENOTSUP;
    return 1;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* No testdriver; tested in driver for _PDCLIB_open(). */
    return TEST_RESULTS;
}

#endif
