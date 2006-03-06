/* $Id$ */

/* Release $Name$ */

/* setvbuf( FILE *, char *, int, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST

int setvbuf( FILE * _PDCLIB_restrict stream, char * _PDCLIB_restrict buf, int mode, size_t size )
{
    /* TODO: Only allowed on a "virgin" stream; add check. */
    if ( ( stream->status & ( _IOFBF | _IOLBF | _IONBF ) ) /* Only allowed on "virgin" stream */
      || ( ( mode != _IOFBF ) && ( mode != _IOLBF ) && ( mode != _IONBF ) ) /* invalid mode */
      || ( ( buf == NULL ) && ( ( buf = malloc( size ) ) == NULL ) ) /* no memory available */
    )
    {
        return -1;
    }
    stream->status |= mode;
    stream->buffer  = buf;
    stream->bufsize = size;
    return 0;
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
