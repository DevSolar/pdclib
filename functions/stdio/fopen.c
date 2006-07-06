/* $Id$ */

/* fopen( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

/* FIXME: This approach is a possible attack vector. */
struct _PDCLIB_file_t * _PDCLIB_filelist = NULL;

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
    if ( ( rc->status = _PDCLIB_filemode( mode ) ) == 0 ) goto fail; /* invalid mode */
    rc->handle = _PDCLIB_open( filename, rc->status );
    if ( rc->handle == _PDCLIB_NOHANDLE ) goto fail; /* OS open() failed */
    /* Adding to list of open files */
    rc->next = _PDCLIB_filelist;
    _PDCLIB_filelist = rc;
    /* Setting buffer, and mark as internal. TODO: Check for unbuffered */
    if ( ( rc->buffer = malloc( BUFSIZ ) ) == NULL ) goto fail;
    rc->bufsize = BUFSIZ;
    rc->bufidx = 0;
    rc->status |= ( _PDCLIB_LIBBUFFER | _PDCLIB_VIRGINSTR );
    /* TODO: Setting mbstate */
    return rc;
fail:
    free( rc );
    return NULL;
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
#ifndef REGTEST
    TESTCASE( fopen( NULL, NULL ) == NULL );
#endif
    TESTCASE( fopen( NULL, "w" ) == NULL );
#ifndef REGTEST
    TESTCASE( fopen( "", NULL ) == NULL );
#endif
    TESTCASE( fopen( "", "w" ) == NULL );
    TESTCASE( fopen( "foo", "" ) == NULL );
#ifndef REGTEST
    TESTCASE( fopen( "testfile", "wq" ) == NULL ); /* Undefined mode */
    TESTCASE( fopen( "testfile", "wr" ) == NULL ); /* Undefined mode */
#endif
    TESTCASE( fopen( "testfile", "w" ) != NULL );
    system( "rm testfile" );
    return TEST_RESULTS;
}

#endif
