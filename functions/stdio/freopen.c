/* $Id$ */

/* freopen( const char *, const char *, FILE * )

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
   This implementation allows any mode changes.
   (Primary use of this function is to redirect stdin, stdout, and stderr.)
*/
struct _PDCLIB_file_t * freopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    unsigned int status = stream->status & ( _IONBF | _IOLBF | _IOFBF | _PDCLIB_FREEBUFFER | _PDCLIB_DELONCLOSE );
    /* TODO: This function can change wide orientation of a stream */
    if ( stream->status & _PDCLIB_FWRITE )
    {
        _PDCLIB_flushbuffer( stream );
    }
    _PDCLIB_close( stream->handle );
    clearerr( stream );
    /* FIXME: Copy filename into the FILE structure. */
    /* FIXME: filename cannot reside in "big block" memory */
    if ( filename == NULL )
    {
        filename = stream->filename;
    }
    if ( ( mode == NULL ) || ( filename[0] == '\0' ) )
    {
        return NULL;
    }
    if ( ( stream->status = _PDCLIB_filemode( mode ) ) == 0 )
    {
        return NULL;
    }
    /* Re-add the flags we saved above */
    stream->status |= status;
    stream->bufidx = 0;
    stream->bufend = 0;
    stream->ungetidx = 0;
    /* TODO: Setting mbstate */
    if ( ( stream->handle = _PDCLIB_open( filename, stream->status ) ) == _PDCLIB_NOHANDLE )
    {
        return NULL;
    }
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
