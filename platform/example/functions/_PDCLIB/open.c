/* $Id$ */

/* _PDCLIB_open( char const * const, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of _PDCLIB_open() fit for use with POSIX
   kernels.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

_PDCLIB_fd_t _PDCLIB_open( char const * const filename, unsigned int mode )
{
    int osmode = 0;
    if ( mode & _PDCLIB_FRW ) osmode |= O_RDWR;
    if ( mode & ( _PDCLIB_FWRITE | _PDCLIB_FAPPEND ) ) osmode |= O_CREAT;
    if ( mode & _PDCLIB_FWRITE ) osmode |= O_TRUNC;
    if ( mode & _PDCLIB_FAPPEND ) osmode |= O_APPEND;
    if ( ( mode & _PDCLIB_FREAD ) && ! ( mode & _PDCLIB_FRW ) ) osmode |= O_RDONLY;
    return open( filename, osmode );
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
