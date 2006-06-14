/* $Id$ */

/* setbuf( FILE *, char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

void setbuf( struct _PDCLIB_file_t * _PDCLIB_restrict stream, char * _PDCLIB_restrict buf )
{
    /* TODO: Only allowed on a "virgin" stream; add check. */
    if ( buf == NULL )
    {
        setvbuf( stream, buf, _IONBF, BUFSIZ );
    }
    else
    {
        setvbuf( stream, buf, _IOFBF, BUFSIZ );
    }
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* TODO: Extend testing once setvbuf() is finished. */
#ifndef REGTEST
    char const * const filename = "testfile";
    char buffer[ 100 ];
    struct _PDCLIB_file_t * fh;
    /* full buffered */
    TESTCASE( ( fh = fopen( filename, "w" ) ) != NULL );
    TESTCASE( fh->status & _PDCLIB_LIBBUFFER );
    TESTCASE( fh->bufsize == BUFSIZ );
    setbuf( fh, buffer );
#if 0
    TESTCASE( fh->buffer == buffer );
    TESTCASE( fh->bufsize == BUFFERSIZE );
#endif
    TESTCASE( ( fh->status & ( _IOFBF | _IONBF | _IOLBF ) ) == _IOFBF );
    TESTCASE( fclose( fh ) == 0 );
    /* not buffered */
    TESTCASE( ( fh = fopen( filename, "w" ) ) != NULL );
    setbuf( fh, NULL );
#if 0
    TESTCASE( fh->buffer == NULL );
    TESTCASE( fh->bufsize == 0 );
#endif
    TESTCASE( ( fh->status & ( _IOFBF | _IONBF | _IOLBF ) ) == _IONBF );
    TESTCASE( fclose( fh ) == 0 );
#else
    puts( " NOTEST setbuf() test driver is PDCLib-specific." );
#endif
    return TEST_RESULTS;
}

#endif
