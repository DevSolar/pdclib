/* $Id$ */

/* _PDCLIB_write( _PDCLIB_fd_t, char const *, _PDCLIB_size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <_PDCLIB_glue.h>
#include <unistd.h>

#ifndef REGTEST

int _PDCLIB_write( struct _PDCLIB_file_t * stream, char const * buffer, int n )
{
    /* CAUTION: We assume ssize_t <=> int here. We do so implicitly so a smart
       compiler can throw a warning in case it does not (and you missed this
       note). Somewhere we have to cast the return value of write() to that of
       _PDCLIB_write() (since the latter cannot use a return type not defined
       by the standard). It would perhaps have been syntactically cleaner to
       use ssize_t here and make the cast in the return statement, but this
       way we don't have to include yet another non-standard header.
    */
    int rc;
    if ( ( rc = write( stream->handle, buffer, (size_t)n ) ) == -1 )
    {
        /* Error encountered */
        stream->status |= _PDCLIB_ERRORFLAG;
        /* FIXME: Map the errno of the OS to PDCLib's errno */
    }
    return rc;
}

#endif

#ifdef TEST
/* TODO: Work around the following undef */
#undef SEEK_SET
#include <_PDCLIB_test.h>

#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

/* TODO: This uses POSIX system calls for now, should use standard calls
   once they are in place. Clumsy sunny-path testing.
*/
int main( void )
{
    /* See the code comment at the functions' return statement above. */
    int fd, r;
    char * buffer = malloc( 13 );
    TESTCASE( buffer != NULL );
    strcpy( buffer, "Test output\n" );
    /* Writing string to file */
    TESTCASE( ( fd = open( "testfile", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU ) ) != -1 );
    struct _PDCLIB_file_t file = { fd, { 0, 0 }, buffer, BUFSIZ, 12, 0, 0, NULL, NULL };
    TESTCASE( _PDCLIB_write( &file, file.buffer, 12 ) == 12 );
    TESTCASE( close( file.handle ) != -1 );
    /* Reading file back in */
    TESTCASE( ( fd = open( "testfile", O_RDONLY ) ) != -1 );
    memset( buffer, '\0', 13 );
    TESTCASE( ( r = read( file.handle, (void *)buffer, 12 ) ) == 12 );
    TESTCASE( strcmp( buffer, "Test output\n" ) == 0 );
    TESTCASE( close( fd ) != -1 );
    TESTCASE( unlink( "testfile" ) != -1 );
    return TEST_RESULTS;
}

#endif

