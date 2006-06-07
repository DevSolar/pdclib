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
    /* FIXME: THIS IS NOT TO BE USED OUT-OF-THE-BOX.
       It is a proof-of-concept implementation. E.g. a stream may only be fully
       buffered IF IT CAN BE DETERMINED NOT TO REFER TO AN INTERACTIVE DEVICE.
       This logic is not represented here, as this is the EXAMPLE platform, and
       actual platform overlays may differ widely. Another point is the value
       for permissions being hardcoded to 0664 for file creations.
    */
    int osmode;
    switch ( mode & ~_PDCLIB_FBIN )
    {
        case _PDCLIB_FREAD: /* "r" */
            osmode = O_RDONLY;
            break;
        case _PDCLIB_FWRITE: /* "w" */
            osmode = O_WRONLY | O_CREAT | O_TRUNC;
            break;
        case _PDCLIB_FAPPEND: /* "a" */
            osmode = O_APPEND | O_CREAT;
            break;
        case _PDCLIB_FREAD | _PDCLIB_FRW: /* "r+" */
            osmode = O_RDWR;
            break;
        case _PDCLIB_FWRITE | _PDCLIB_FRW: /* "w+" */
            osmode = O_RDWR | O_CREAT | O_TRUNC;
            break;
        case _PDCLIB_FAPPEND | _PDCLIB_FRW: /* "a+" */
            osmode = O_RDWR | O_APPEND | O_CREAT;
            break;
        default: /* Invalid mode */
            return -1;
    }
    if ( osmode & O_CREAT )
    {
        return open( filename, osmode, S_IRUSR | S_IWUSR );
    }
    else
    {
        return open( filename, osmode );
    }
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <stdlib.h>

int main( void )
{
    /* This testdriver assumes POSIX, i.e. _PDCLIB_fd_t being int and being
       incremented by one on each successful open.
    */
    _PDCLIB_fd_t fh;
    TESTCASE( _PDCLIB_open( "testfile2", _PDCLIB_FREAD ) == _PDCLIB_NOHANDLE );
    TESTCASE( ( fh = _PDCLIB_open( "testfile1", _PDCLIB_FWRITE ) ) != _PDCLIB_NOHANDLE );
    TESTCASE( write( fh, "test", 4 ) == 4 );
    TESTCASE( close( fh ) == 0 );
    TESTCASE( _PDCLIB_open( "testfile1", _PDCLIB_FREAD ) != _PDCLIB_NOHANDLE );
    system( "rm testfile1" );
    return TEST_RESULTS;
}

#endif
