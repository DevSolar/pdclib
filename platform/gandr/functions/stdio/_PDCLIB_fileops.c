/* _PDCLIB_fileops

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST
#include <stdio.h>
#include <stdint.h>
#include "_PDCLIB_glue.h"
#include <errno.h>
#include <gd_bal.h>

static bool readf( _PDCLIB_fd_t fd, void * buf, size_t length,
                   size_t * numBytesRead )
{
    int rv = gd_read(fd.pointer, buf, length, numBytesRead );

    return rv >= 0;
}

static bool writef( _PDCLIB_fd_t fd, const void * buf, size_t length,
                   size_t * numBytesWritten )
{
    int rv = gd_write(fd.pointer, buf, length, numBytesWritten );

    return rv >= 0;
}

static bool seekf( _PDCLIB_fd_t fd, int_fast64_t offset, int whence,
    int_fast64_t* newPos )
{
    int rv = gd_seek( fd.pointer, offset, whence, newPos );

    return rv >= 0;
}

static void closef( _PDCLIB_fd_t self )
{
    gd_close( self.pointer );
}

const _PDCLIB_fileops_t _PDCLIB_fileops = {
    .read  = readf,
    .write = writef,
    .seek  = seekf,
    .close = closef,
};

#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    // Tested by stdio test cases
    return TEST_RESULTS;
}

#endif
