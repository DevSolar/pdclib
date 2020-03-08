/* freopen( const char *, const char *, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <errno.h>
#include <limits.h>
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

struct _PDCLIB_file_t * freopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    unsigned int filemode = _PDCLIB_filemode( mode );

    if ( stream == NULL )
    {
        errno = EBADF;
        return NULL;
    }

    _PDCLIB_LOCK( _PDCLIB_filelist_mtx );

    if ( _PDCLIB_isstream( stream, NULL ) )
    {
        /* May lock only after established that stream is valid */
        _PDCLIB_LOCK( stream->mtx );

        /* Flush buffer */
        if ( stream->status & _PDCLIB_FWRITE )
        {
            _PDCLIB_flushbuffer( stream );
        }

        if ( filename == NULL )
        {
            /* Attempt to change mode without closing stream */
            switch ( _PDCLIB_changemode( stream, filemode ) )
            {
                case INT_MIN:
                    /* fail completely */
                    _PDCLIB_UNLOCK( stream->mtx );
                    _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
                    return NULL;

                case 0:
                    /* fail; try close / reopen */
                    filename = stream->filename;
                    /* Setting to NULL to make the free() below a non-op. */
                    stream->filename = NULL;
                    break;

                default:
                    /* success */
                    _PDCLIB_UNLOCK( stream->mtx );
                    _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
                    return stream;
            }
        }

        /* Close handle */
        _PDCLIB_close( stream->handle );

        /* Remove stream from list */
        _PDCLIB_getstream( stream );

        /* Delete tmpfile() */
        if ( stream->status & _PDCLIB_DELONCLOSE )
        {
            /* Have to switch here; stream->filename may have moved to
               filename after failed in-place mode change above.
            */
            _PDCLIB_remove( ( stream->filename == NULL ) ? filename : stream->filename );
            stream->status &= ~_PDCLIB_DELONCLOSE;
        }

        /* Free buffer */
        if ( stream->status & _PDCLIB_FREEBUFFER )
        {
            free( stream->buffer );
        }

        if ( filename == NULL )
        {
            /* Input was filename NULL, stream->filename NULL.
               No filename means there is nothing to reopen. In-place
               mode change was already attempted (and failed) above.
            */
            return NULL;
        }
        else
        {
            /* We have a filename, either from input or (if filename
               was NULL) from stream. We will attempt the re-open with
               that, and will retrieve _PDCLIB_realpath() from that.
               So stream->filename is no longer needed.
            */
            free( stream->filename );
        }
    }
    else
    {
        /* Not a valid stream. As _PDCLIB_init_file_t() cannot tell the
           difference, only knows that it has been called by freopen()
           (by the non-NULL parameter), we need to initialize the mutex
           here (so that either way, _PDCLIB_init_file_t() gets a pre-
           initialized mutex).
        */
#ifndef __STDC_NO_THREADS__
        if ( mtx_init( &stream->mtx, mtx_plain | mtx_recursive ) != thrd_success )
        {
            /* Could not initialize stream mutex */
            _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
            return NULL;
        }

#endif

        /* Locking the mutex, so we come out of the if-else with a locked
           mutex either way.
        */
        _PDCLIB_LOCK( stream->mtx );
    }

    /* Stream is closed, or never was open (even though its mutex exists
       and is locked) at this point.
       Now we check if we have the whereabouts to open it.
    */

    if ( filemode == 0 )
    {
        /* Mode invalid */
        _PDCLIB_UNLOCK( stream->mtx );
#ifndef __STDC_NO_THREADS__
        mtx_destroy( &stream->mtx );
#endif
        free( stream->filename );
        free( stream );
        _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
        return NULL;
    }

    if ( filename == NULL || filename[0] == '\0' )
    {
        /* No filename available (standard stream?) */
        _PDCLIB_UNLOCK( stream->mtx );
#ifndef __STDC_NO_THREADS__
        mtx_destroy( &stream->mtx );
#endif
        free( stream->filename );
        free( stream );
        _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
        return NULL;
    }

    /* (Re-)initializing the structure. */
    if ( _PDCLIB_init_file_t( stream ) == NULL )
    {
        /* Re-init failed. */
        _PDCLIB_UNLOCK( stream->mtx );
#ifndef __STDC_NO_THREADS__
        mtx_destroy( &stream->mtx );
#endif
        free( stream->filename );
        free( stream );
        _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
        return NULL;
    }

    /* Resetting buffer mode and filemode */
    stream->status |= filemode | _IOLBF;

    /* Attempt open */
    if ( ( stream->handle = _PDCLIB_open( filename, stream->status ) ) == _PDCLIB_NOHANDLE )
    {
        /* OS open() failed */
        _PDCLIB_UNLOCK( stream->mtx );
#ifndef __STDC_NO_THREADS__
        mtx_destroy( &stream->mtx );
#endif
        free( stream->filename );
        free( stream->buffer );
        free( stream );
        _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
        return NULL;
    }

    /* Getting absolute filename */
    stream->filename = _PDCLIB_realpath( filename );

    /* Adding to list of open files */
    stream->next = _PDCLIB_filelist;
    _PDCLIB_filelist = stream;

    _PDCLIB_UNLOCK( stream->mtx );
    _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );

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
