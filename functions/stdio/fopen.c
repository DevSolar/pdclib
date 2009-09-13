/* $Id$ */

/* fopen( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

struct _PDCLIB_file_t * fopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode )
{
    struct _PDCLIB_file_t * rc;
    if ( mode == NULL || filename == NULL || filename[0] == '\0' )
    {
        /* Mode or filename invalid */
        return NULL;
    }
    if ( ( rc = calloc( 1, sizeof( struct _PDCLIB_file_t ) ) ) == NULL )
    {
        /* no memory for another FILE */
        return NULL;
    }
    if ( ( rc->status = _PDCLIB_filemode( mode ) ) == 0 ) 
    {
        /* invalid mode */
        free( rc );
        return NULL;
    }
    rc->handle = _PDCLIB_open( filename, rc->status );
    if ( rc->handle == _PDCLIB_NOHANDLE )
    {
        /* OS open() failed */
        free( rc );
        return NULL;
    }
    /* Adding to list of open files */
    rc->next = _PDCLIB_filelist;
    _PDCLIB_filelist = rc;
    /* Setting buffer, and mark as internal. TODO: Check for unbuffered */
    if ( ( rc->buffer = malloc( BUFSIZ ) ) == NULL )
    {
        free( rc );
        return NULL;
    }
    if ( ( rc->ungetbuf = malloc( _PDCLIB_UNGETCBUFSIZE ) ) == NULL )
    {
       free( rc->buffer );
       free( rc );
       return NULL;
    }
    rc->bufsize = BUFSIZ;
    rc->bufidx = 0;
    rc->ungetidx = 0;
    /* Setting buffer to _IOLBF because "when opened, a stream is fully
       buffered if and only if it can be determined not to refer to an
       interactive device."
    */
    rc->status |= _PDCLIB_LIBBUFFER | _IOLBF;
    /* TODO: Setting mbstate */
    return rc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* Some of the tests are not executed for regression tests, as the libc on
       my system is at once less forgiving (segfaults on mode NULL) and more
       forgiving (accepts undefined modes).
    */
    remove( "testfile" );
    TESTCASE_NOREG( fopen( NULL, NULL ) == NULL );
    TESTCASE( fopen( NULL, "w" ) == NULL );
    TESTCASE_NOREG( fopen( "", NULL ) == NULL );
    TESTCASE( fopen( "", "w" ) == NULL );
    TESTCASE( fopen( "foo", "" ) == NULL );
    TESTCASE_NOREG( fopen( "testfile", "wq" ) == NULL ); /* Undefined mode */
    TESTCASE_NOREG( fopen( "testfile", "wr" ) == NULL ); /* Undefined mode */
    TESTCASE( fopen( "testfile", "w" ) != NULL );
    remove( "testfile" );
    return TEST_RESULTS;
}

#endif
