/* $Id$ */

/* _PDCLIB_flushbuffer( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include <_PDCLIB_glue.h>

_PDCLIB_size_t _PDCLIB_flushbuffer( struct _PDCLIB_file_t * stream, _PDCLIB_size_t written, int retries )
{
    _PDCLIB_size_t n = stream->bufidx - written;
    int count = _PDCLIB_write( stream, stream->buffer + written, ( n <= INT_MAX ? (int)n : INT_MAX ) );
    written += count; /* if count is -1, we don't need written anyway */
    switch ( count )
    {
        case -1:
            /* write error */
            stream->status |= _PDCLIB_ERRORFLAG;
            /* FIXME: Map host errno to PDCLib errno */
            return 0;
        case 0:
            /* no characters written - retry */
            if ( retries == _PDCLIB_FLUSH_RETRIES )
            {
                /* max. number of retries without characters being written */
                stream->status |= _PDCLIB_ERRORFLAG;
                /* FIXME: Set errno */
                return 0;
            }
            _PDCLIB_FLUSH_RETRY_PREP;
            return _PDCLIB_flushbuffer( stream, written, retries + 1 );
        default:
            /* If the following assert fails, we wrote more characters than
               available in the buffer. (???)
            */
            assert( written <= stream->bufidx );
            if ( written == stream->bufidx ) 
            {
                /* write complete */
                stream->bufidx = 0;
                return written;
            }
            return _PDCLIB_flushbuffer( stream, written, 0 );
    }
}
    
#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif

