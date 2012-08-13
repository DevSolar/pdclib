/* $Id$ */

/* tmpfile( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#include <errno.h>
#include <_PDCLIB_glue.h>

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

/* This is a stub implementation of tmpfile
*/
struct _PDCLIB_file_t * tmpfile( void )
{
    errno = ENOTSUP;
    return NULL;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>
#include <string.h>

int main( void )
{
    return TEST_RESULTS;
}

#endif

