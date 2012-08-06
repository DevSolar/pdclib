/* $Id$ */

/* _PDCLIB_flushbuffer( struct _PDCLIB_file_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is a stub implementation of _PDCLIB_flushbuffer
*/

#include <stdio.h>
#include <string.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>
#include <errno.h>

int _PDCLIB_flushbuffer( struct _PDCLIB_file_t * stream )
{
    errno = ENOTSUP;
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

