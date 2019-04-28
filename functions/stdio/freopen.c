/* freopen( const char *, const char *, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
extern mtx_t _PDCLIB_filelist_mtx;
#endif

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

/* ISO/IEC 9899:2011
The freopen function opens the file whose name is the string pointed to by filename
and associates the stream pointed to by stream with it. The mode argument is used just
as in the fopen function. 272)
If filename is a null pointer, the freopen function attempts to change the mode of
the stream to that specified by mode, as if the name of the file currently associated with
the stream had been used. It is implementation-defined which changes of mode are
permitted (if any), and under what circumstances.
The freopen function first attempts to close any file that is associated with the specified
stream. Failure to close the file is ignored. The error and end-of-file indicators for the
stream are cleared.
The freopen function returns a null pointer if the open operation fails. Otherwise,
freopen returns the value of stream.

272) The primary use of the freopen function is to change the file associated with a standard text stream
(stderr, stdin, or stdout), as those identifiers need not be modifiable lvalues to which the value
returned by the fopen function may be assigned.
*/

/* IEEE Std 1003.1, 2004 Edition
The freopen() function shall first attempt to flush the stream and close any
file descriptor associated with stream. Failure to flush or close the file
descriptor successfully shall be ignored. The error and end-of-file indicators
for the stream shall be cleared.
The freopen() function shall open the file whose pathname is the string pointed
to by filename and associate the stream pointed to by stream with it. The mode
argument shall be used just as in fopen().
The original stream shall be closed regardless of whether the subsequent open
succeeds.
If filename is a null pointer, the freopen() function shall attempt to change
the mode of the stream to that specified by mode, as if the name of the file
currently associated with the stream had been used. In this case, the file
descriptor associated with the stream need not be closed if the call to freopen()
succeeds. It is implementation-defined which changes of mode are permitted (if
any), and under what circumstances.
After a successful call to the freopen() function, the orientation of the stream
shall be cleared, the encoding rule shall be cleared, and the assocuated mbstate_t
object shall be set to describe an initial conversion state.
The largest value that can be represented correctly in an object of type off_t
shall be established as the offset maximum in the open file description.
Upon successful completion, freopen() shall return the value of stream.
Otherwise, a null pointer shall be returned, and errno shall be set to indicate
the error.
EBADF The file descriptor underlying the stream is not a valid file descriptor
      when filename is a null pointer.
ENAMETOOLONG ...FILENAME_MAX...
ENFILE ...FOPEN_MAX...
ENOENT A component of filename does not name an existing file or filename is
       an empty string.
EOVERFLOW The named file is a regular file and the size of the file cannot be
          represented correctly in an object of type off_t.
EBADF The mode with which the file descriptor underlying the stream was opened
      does not support the requested mode when filename is a null pointer.
EINVAL The value of the mode argument is not valid.
*/

struct _PDCLIB_file_t * freopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    unsigned int status = stream->status & ( _IONBF | _IOLBF | _IOFBF | _PDCLIB_FREEBUFFER | _PDCLIB_DELONCLOSE | _PDCLIB_STATIC );

    /* TODO: This function can change wide orientation of a stream */
    /* FIXME: While adding the mutex locks, the function seemed suspicious.
       For one, it does not remove the FILE * from the filelist if the
       reopening fails, leaving a closed file in the list of opened files.
       Probably other broken paths as well. Have another look ASAP.
    */

    if ( ( filename == NULL ) && ( stream->filename == NULL ) )
    {
        /* TODO: Special handling for mode changes on std-streams */
        /* Requires flushing (see next block), but as we do not actually do
           anything, we shouldn't flush either, so this block was moved up.
           Once functionality is added here, the block should move back
           down below the _PDCLIB_flushbuffer (and the mutex lock!).
        */
        return NULL;
    }

    _PDCLIB_LOCK( stream->mtx );

    if ( stream->status & _PDCLIB_FWRITE )
    {
        _PDCLIB_flushbuffer( stream );
    }

    _PDCLIB_close( stream->handle );

    /* TODO: It is not nice to do this on a stream we just closed.
       It does not matter with the current implementation of clearerr(),
       but it might start to matter if someone replaced that implementation.
    */
    clearerr( stream );

    /* The new filename might not fit the old buffer */
    if ( filename == NULL )
    {
        /* Use previous filename */
        filename = stream->filename;
    }
    else if ( ( stream->filename != NULL ) && ( strlen( stream->filename ) >= strlen( filename ) ) )
    {
        /* Copy new filename into existing buffer */
        strcpy( stream->filename, filename );
    }
    else
    {
        /* Allocate new buffer */
        if ( ( stream->filename = (char *)malloc( strlen( filename ) ) ) == NULL )
        {
            _PDCLIB_UNLOCK( stream->mtx );
            return NULL;
        }
        strcpy( stream->filename, filename );
    }
    if ( ( mode == NULL ) || ( filename[0] == '\0' ) )
    {
        _PDCLIB_UNLOCK( stream->mtx );
        return NULL;
    }
    if ( ( stream->status = _PDCLIB_filemode( mode ) ) == 0 )
    {
        _PDCLIB_UNLOCK( stream->mtx );
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
        _PDCLIB_UNLOCK( stream->mtx );
        return NULL;
    }
    _PDCLIB_UNLOCK( stream->mtx );
    return stream;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    FILE * fin;
    FILE * fout;
    TESTCASE( ( fin = fopen( testfile1, "wb+" ) ) != NULL );
    TESTCASE( fputc( 'x', fin ) == 'x' );
    TESTCASE( fclose( fin ) == 0 );
    TESTCASE( ( fin = freopen( testfile1, "rb", stdin ) ) != NULL );
    TESTCASE( getchar() == 'x' );

    TESTCASE( ( fout = freopen( testfile2, "wb+", stdout ) ) != NULL );
    TESTCASE( putchar( 'x' ) == 'x' );
    rewind( fout );
    TESTCASE( fgetc( fout ) == 'x' );

    TESTCASE( fclose( fin ) == 0 );
    TESTCASE( fclose( fout ) == 0 );
    TESTCASE( remove( testfile1 ) == 0 );
    TESTCASE( remove( testfile2 ) == 0 );

    return TEST_RESULTS;
}

#endif
