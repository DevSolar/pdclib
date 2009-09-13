/* $Id$ */

/* fgetpos( FILE * , fpos_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

int fgetpos( struct _PDCLIB_file_t * _PDCLIB_restrict stream, struct _PDCLIB_fpos_t * _PDCLIB_restrict pos )
{
    pos->offset = stream->pos.offset + stream->bufidx - stream->ungetidx;
    pos->status = stream->pos.status;
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
