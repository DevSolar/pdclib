/* ftell( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <limits.h>

#ifndef REGTEST

#ifndef __STDC_NO_THREADS__
#include <threads.h>
#endif

long int ftell( struct _PDCLIB_file_t * stream )
{
    /* ftell() must take into account:
       - the actual *physical* offset of the file, i.e. the offset as recognized
         by the operating system (and stored in stream->pos.offset); and
       - any buffers held by PDCLib, which
         - in case of unwritten buffers, count in *addition* to the offset; or
         - in case of unprocessed pre-read buffers, count in *substraction* to
           the offset. (Remember to count ungetidx into this number.)
       Conveniently, the calculation ( ( bufend - bufidx ) + ungetidx ) results
       in just the right number in both cases:
         - in case of unwritten buffers, ( ( 0 - unwritten ) + 0 )
           i.e. unwritten bytes as negative number
         - in case of unprocessed pre-read, ( ( preread - processed ) + unget )
           i.e. unprocessed bytes as positive number.
       That is how the somewhat obscure return-value calculation works.
    */
    /*  If offset is too large for return type, report error instead of wrong
        offset value.
    */
    long int rc;
    _PDCLIB_LOCK( stream->mtx );

    if ( ( stream->pos.offset - stream->bufend ) > ( LONG_MAX - ( stream->bufidx - stream->ungetidx ) ) )
    {
        /* integer overflow */
        _PDCLIB_UNLOCK( stream->mtx );
        *_PDCLIB_errno_func() = _PDCLIB_ERANGE;
        return -1;
    }

    rc = ( stream->pos.offset - ( ( ( int )stream->bufend - ( int )stream->bufidx ) + stream->ungetidx ) );
    _PDCLIB_UNLOCK( stream->mtx );
    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdlib.h>

int main( void )
{
    /* Testing all the basic I/O functions individually would result in lots
       of duplicated code, so I took the liberty of lumping it all together
       here.
    */
    /* The following functions delegate their tests to here:
       fgetc fflush rewind fputc ungetc fseek
       flushbuffer seek fillbuffer prepread prepwrite
    */
    char buffer[4];
    FILE * fh;
    TESTCASE( ( fh = tmpfile() ) != NULL );
    TESTCASE( setvbuf( fh, buffer, _IOLBF, 4 ) == 0 );
    /* Testing ungetc() at offset 0 */
    rewind( fh );
    TESTCASE( ungetc( 'x', fh ) == 'x' );
    TESTCASE( ftell( fh ) == -1l );
    rewind( fh );
    TESTCASE( ftell( fh ) == 0l );
    /* Commence "normal" tests */
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
    /* Check that SEEK_CUR actually uses internal position */
    TESTCASE( fseek( fh, 1l, SEEK_CUR ) == 0 );
    TESTCASE( ftell( fh ) == 2l );
    /* TODO: t.b.c. */
    TESTCASE( fclose( fh ) == 0 );
    return TEST_RESULTS;
}

#endif
