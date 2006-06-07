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
            osmode = O_WRONLY | O_APPEND | O_CREAT;
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
#include <string.h>

#include <errno.h>

int main( void )
{
    /* This testdriver assumes POSIX, i.e. _PDCLIB_fd_t being int and being
       incremented by one on each successful open.
    */
    _PDCLIB_fd_t fh;
    char buffer[ 10 ];
    /* Trying to read non-existent file. */
    TESTCASE( _PDCLIB_open( "testfile", _PDCLIB_FREAD ) == _PDCLIB_NOHANDLE );
    /* Writing to file, trying to read from it. */
    TESTCASE( ( fh = _PDCLIB_open( "testfile", _PDCLIB_FWRITE ) ) != _PDCLIB_NOHANDLE );
    TESTCASE( write( fh, "test", 4 ) == 4 );
    TESTCASE( lseek( fh, 0, SEEK_SET ) == 0 );
    TESTCASE( read( fh, buffer, 4 ) == -1 );
    TESTCASE( close( fh ) == 0 );
    /* Reading from file, trying to write to it. */
    TESTCASE( ( fh = _PDCLIB_open( "testfile", _PDCLIB_FREAD ) ) != _PDCLIB_NOHANDLE );
    TESTCASE( write( fh, "test", 4 ) == -1 );
    TESTCASE( close( fh ) == 0 );
    /* Appending to file, trying to read from it. */
    TESTCASE( ( fh = _PDCLIB_open( "testfile", _PDCLIB_FAPPEND ) ) != _PDCLIB_NOHANDLE );
    TESTCASE( write( fh, "app", 3 ) == 3 );
    TESTCASE( lseek( fh, 0, SEEK_SET ) == 0 );
    TESTCASE( read( fh, buffer, 10 ) == -1 );
    TESTCASE( write( fh, "end", 3 ) == 3 );
    TESTCASE( close( fh ) == 0 );
    /* Reading and writing from file ("r+"). */
    TESTCASE( ( fh = _PDCLIB_open( "testfile", _PDCLIB_FREAD | _PDCLIB_FRW ) ) != _PDCLIB_NOHANDLE );
    TESTCASE( read( fh, buffer, 10 ) == 10 );
    TESTCASE( memcmp( buffer, "testappend", 10 ) == 0 );
    TESTCASE( lseek( fh, 0, SEEK_SET ) == 0 );
    TESTCASE( write( fh, "wedo", 4 ) == 4 );
    TESTCASE( lseek( fh, 0, SEEK_SET ) == 0 );
    TESTCASE( read( fh, buffer, 10 ) == 10 );
    TESTCASE( memcmp( buffer, "wedoappend", 10 ) == 0 );
    TESTCASE( close( fh ) == 0 );
    /* Writing and reading from file ("w+"). */
    TESTCASE( ( fh = _PDCLIB_open( "testfile", _PDCLIB_FWRITE | _PDCLIB_FRW ) ) != _PDCLIB_NOHANDLE );
    TESTCASE( write( fh, "test", 4 ) == 4 );
    TESTCASE( lseek( fh, 1, SEEK_SET ) == 1 );
    TESTCASE( read( fh, buffer, 2 ) == 2 );
    TESTCASE( memcmp( buffer, "es", 2 ) == 0 );
    TESTCASE( write( fh, "sie", 3 ) == 3 );
    TESTCASE( lseek( fh, 0, SEEK_SET ) == 0 );
    TESTCASE( read( fh, buffer, 6 ) == 6 );
    TESTCASE( memcmp( buffer, "tessie", 6 ) == 0 );
    TESTCASE( close( fh ) == 0 );
    /* Appending and reading from file ("a+"). */
    TESTCASE( ( fh = _PDCLIB_open( "testfile", _PDCLIB_FAPPEND | _PDCLIB_FRW ) ) != _PDCLIB_NOHANDLE );
    TESTCASE( write( fh, "baby", 4 ) == 4 );
    TESTCASE( lseek( fh, 0, SEEK_SET ) == 0 );
    TESTCASE( read( fh, buffer, 10 ) == 10 );
    TESTCASE( memcmp( buffer, "tessiebaby", 10 ) == 0 );
    TESTCASE( close( fh ) == 0 );
    /* Cleaning up. */
    system( "rm testfile" );
    return TEST_RESULTS;
}

#endif
