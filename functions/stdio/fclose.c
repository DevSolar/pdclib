/* fclose( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
extern mtx_t _PDCLIB_filelist_mtx;
#endif

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

int fclose( struct _PDCLIB_file_t * stream )
{
    struct _PDCLIB_file_t * current;
    struct _PDCLIB_file_t * previous = NULL;

    _PDCLIB_LOCK( stream->mtx );

    /* Remove stream from list */
    _PDCLIB_LOCK( _PDCLIB_filelist_mtx );

    current = _PDCLIB_filelist;

    while ( ( current != NULL ) && ( current != stream ) )
    {
        previous = current;
        current = current->next;
    }

    if ( current == NULL )
    {
        *_PDCLIB_errno_func() = _PDCLIB_EBADF;
        _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
        _PDCLIB_UNLOCK( stream->mtx );
        return EOF;
    }

    if ( previous != NULL )
    {
        previous->next = stream->next;
    }
    else
    {
        _PDCLIB_filelist = stream->next;
    }

    _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );

    /* Flush buffer */
    if ( stream->status & _PDCLIB_FWRITE )
    {
        if ( _PDCLIB_flushbuffer( stream ) == EOF )
        {
            /* Flush failed, errno already set */
            _PDCLIB_UNLOCK( stream->mtx );
            return EOF;
        }
    }

    /* Close handle */
    _PDCLIB_close( stream->handle );

    /* Delete tmpfile() */
    if ( stream->status & _PDCLIB_DELONCLOSE )
    {
        remove( stream->filename );
    }

    /* Free user buffer (setvbuf allocated) */
    if ( stream->status & _PDCLIB_FREEBUFFER )
    {
        free( stream->buffer );
    }

    /* Free filename (freopen allocated) */
    if ( stream->status & _PDCLIB_FREENAME )
    {
        free( stream->filename );
    }

    _PDCLIB_UNLOCK( stream->mtx );

    /* Free stream */
    if ( ! ( stream->status & _PDCLIB_STATIC ) )
    {
        free( stream );
    }

    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    struct _PDCLIB_file_t * file1;
    struct _PDCLIB_file_t * file2;
    remove( testfile1 );
    remove( testfile2 );
    TESTCASE( _PDCLIB_filelist == stdin );
    TESTCASE( ( file1 = fopen( testfile1, "w" ) ) != NULL );
    TESTCASE( _PDCLIB_filelist == file1 );
    TESTCASE( ( file2 = fopen( testfile2, "w" ) ) != NULL );
    TESTCASE( _PDCLIB_filelist == file2 );
    TESTCASE( fclose( file2 ) == 0 );
    TESTCASE( _PDCLIB_filelist == file1 );
    TESTCASE( ( file2 = fopen( testfile2, "w" ) ) != NULL );
    TESTCASE( _PDCLIB_filelist == file2 );
    TESTCASE( fclose( file1 ) == 0 );
    TESTCASE( _PDCLIB_filelist == file2 );
    TESTCASE( fclose( file2 ) == 0 );
    TESTCASE( _PDCLIB_filelist == stdin );
    TESTCASE( remove( testfile1 ) == 0 );
    TESTCASE( remove( testfile2 ) == 0 );
#else
    puts( " NOTEST fclose() test driver is PDCLib-specific." );
#endif
    return TEST_RESULTS;
}

#endif
