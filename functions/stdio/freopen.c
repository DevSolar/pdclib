/* $Id$ */

/* freopen( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#include <_PDCLIB_glue.h>
#include <stdlib.h>

/* Close any file currently associated with the given stream. Open the file
   identified by the given filename with the given mode (equivalent to fopen()),
   and associate it with the given stream. If filename is a NULL pointer,
   attempt to change the mode of the given stream.
   This implementation allows the following mode changes: TODO
   (Primary use of this function is to redirect stdin, stdout, and stderr.)
*/

struct _PDCLIB_file_t * freopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode, struct _PDCLIB_file_t * stream )
{
    /* FIXME: This is ad-hoc (to make the vprintf() testdriver work), and must be checked. */
    /* FIXME: If filename is NULL, change mode. */
    /* TODO: This function can change wide orientation of a stream */
    if ( filename == NULL ) return NULL;
    if ( stream->status & _PDCLIB_FWRITE ) fflush( stream );
    if ( stream->status & _PDCLIB_LIBBUFFER ) free( stream->buffer );
    _PDCLIB_close( stream->handle );
    clearerr( stream );
    if ( ( mode == NULL ) || ( filename[0] == '\0' ) ) return NULL;
    if ( ( stream->status = _PDCLIB_filemode( mode ) ) == 0 ) return NULL;
    stream->handle = _PDCLIB_open( filename, stream->status );
    if ( ( stream->buffer = malloc( BUFSIZ ) ) == NULL ) return NULL;
    stream->bufsize = BUFSIZ;
    stream->bufidx = 0;
    stream->status |= _PDCLIB_LIBBUFFER;
    /* TODO: Setting mbstate */
    return stream;
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
