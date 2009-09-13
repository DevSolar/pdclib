/* $Id$ */

/* ftell( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <limits.h>

#ifndef REGTEST

long int ftell( struct _PDCLIB_file_t * stream )
{
    /* TODO: A bit too fuzzy in the head now. stream->ungetidx should be in here
             somewhere.
    */
    if ( stream->pos.offset > ( LONG_MAX - stream->bufidx ) )
    {
        /* integer overflow */
        _PDCLIB_errno = _PDCLIB_EINVAL;
        return -1;
    }
    /* Position of start-of-buffer, plus:
       - buffered, unwritten content (for output streams), or
       - already-parsed content from buffer (for input streams)
    */
    return (long int)( stream->pos.offset + stream->bufidx - stream->ungetidx );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <stdlib.h>

int main( void )
{
    /* Testing all the basic I/O functions individually would result in lots
       of duplicated code, so I took the liberty of lumping it all together
       here.
    */
    /* The following functions delegate their tests to here:
       fgetc fflush rewind fputc ungetc fseek
       flushbuffer seek fillbuffer
    */
    char * buffer = (char*)malloc( 4 );
    FILE * fh;
    remove( "testfile" );
    TESTCASE( ( fh = fopen( "testfile", "w+" ) ) != NULL );
    TESTCASE( setvbuf( fh, buffer, _IOLBF, 4 ) == 0 );
    TESTCASE( fputc( '1', fh ) == '1' );
    TESTCASE( fputc( '2', fh ) == '2' );
    TESTCASE( fputc( '3', fh ) == '3' );
    /* Positions incrementing as expected? */
    TESTCASE( ftell( fh ) == 3l );
    TESTCASE_NOREG( fh->pos.offset == 0l );
    TESTCASE_NOREG( fh->bufidx == 3l );
    /* Buffer properly flushed when full? */
    TESTCASE( fputc( '4', fh ) == '4' );
    TESTCASE_NOREG( fh->pos.offset == 4l );
    TESTCASE_NOREG( fh->bufidx == 0 );
    /* fflush() resetting positions as expected? */
    TESTCASE( fputc( '5', fh ) == '5' );
    TESTCASE( fflush( fh ) == 0 );
    TESTCASE( ftell( fh ) == 5l );
    TESTCASE_NOREG( fh->pos.offset == 5l );
    TESTCASE_NOREG( fh->bufidx == 0l );
    /* rewind() resetting positions as expected? */
    rewind( fh );
    TESTCASE( ftell( fh ) == 0l );
    TESTCASE_NOREG( fh->pos.offset == 0 );
    TESTCASE_NOREG( fh->bufidx == 0 );
    /* Reading back first character after rewind for basic read check */
    TESTCASE( fgetc( fh ) == '1' );
    TESTCASE( fclose( fh ) == 0 );
    /* TODO: t.b.c. */
    remove( "testfile" );
    return TEST_RESULTS;
}

#endif

