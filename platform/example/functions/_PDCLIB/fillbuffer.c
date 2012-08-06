/* $Id$ */

/* _PDCLIB_fillbuffer( struct _PDCLIB_file_t * stream )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is a stub version of _PDCLIB_fillbuffer
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>
#include <errno.h>

int _PDCLIB_fillbuffer( struct _PDCLIB_file_t * stream )
{
    errno = ENOTSUP; 
    stream->status |= _PDCLIB_EOFFLAG;
    return EOF;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* Testing covered by ftell.c */
    return TEST_RESULTS;
}

#endif

