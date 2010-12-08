/* $Id$ */

/* freopen( const char *, const char *, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#include <_PDCLIB_glue.h>
#include <stdlib.h>
#include <string.h>

struct _PDCLIB_file_t * freopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    unsigned int status = stream->status & ( _IONBF | _IOLBF | _IOFBF | _PDCLIB_FREEBUFFER | _PDCLIB_DELONCLOSE );
    /* TODO: This function can change wide orientation of a stream */
    if ( stream->status & _PDCLIB_FWRITE )
    {
        _PDCLIB_flushbuffer( stream );
    }
    if ( ( filename == NULL ) && ( stream->filename == NULL ) )
    {
        /* TODO: Special handling for mode changes on std-streams */
        return NULL;
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
            return NULL;
        }
        strcpy( stream->filename, filename );
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
