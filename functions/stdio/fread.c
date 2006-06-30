/* $Id$ */

/* fread( void *, size_t, size_t, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <_PDCLIB_glue.h>

#ifndef REGTEST

size_t fread( void * _PDCLIB_restrict ptr, size_t size, size_t nmemb, struct _PDCLIB_file_t * _PDCLIB_restrict stream )
{
    return _PDCLIB_read( stream->handle, ptr, size * nmemb );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* Testing handled by fwrite(). */
    return TEST_RESULTS;
}

#endif
