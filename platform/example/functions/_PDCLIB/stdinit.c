/* $Id$ */

/* _PDCLIB_stdinit

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example initialization of stdin, stdout and stderr to the integer
   file descriptors 0, 1, and 2, respectively. This applies for a great variety
   of operating systems, including POSIX compliant ones.
*/

#include <stdio.h>

#ifndef REGTEST

/* In a POSIX system, stdin / stdout / stderr are equivalent to the (int) file
   descriptors 0, 1, and 2 respectively.
*/
/* TODO: This is proof-of-concept, requires finetuning. */
static char _PDCLIB_sin_buffer[BUFSIZ];
static char _PDCLIB_sout_buffer[BUFSIZ];
static char _PDCLIB_serr_buffer[BUFSIZ];

static unsigned char _PDCLIB_sin_ungetbuf[_PDCLIB_UNGETCBUFSIZE];
static unsigned char _PDCLIB_sout_ungetbuf[_PDCLIB_UNGETCBUFSIZE];
static unsigned char _PDCLIB_serr_ungetbuf[_PDCLIB_UNGETCBUFSIZE];

/* FIXME: serr should handle one character. Buffering on out / in? */
static struct _PDCLIB_file_t _PDCLIB_serr = { 2, _PDCLIB_serr_buffer, BUFSIZ, 0, 0, { 0, 0 }, 0, _PDCLIB_serr_ungetbuf, _IONBF | _PDCLIB_FWRITE, NULL, NULL };
static struct _PDCLIB_file_t _PDCLIB_sout = { 1, _PDCLIB_sout_buffer, BUFSIZ, 0, 0, { 0, 0 }, 0, _PDCLIB_sout_ungetbuf, _IOLBF | _PDCLIB_FWRITE, NULL, &_PDCLIB_serr };
static struct _PDCLIB_file_t _PDCLIB_sin  = { 0, _PDCLIB_sin_buffer, BUFSIZ, 0, 0, { 0, 0 }, 0, _PDCLIB_sin_ungetbuf, _IOLBF | _PDCLIB_FREAD, NULL, &_PDCLIB_sout };

struct _PDCLIB_file_t * stdin  = &_PDCLIB_sin;
struct _PDCLIB_file_t * stdout = &_PDCLIB_sout;
struct _PDCLIB_file_t * stderr = &_PDCLIB_serr;

/* FIXME: This approach is a possible attack vector. */
struct _PDCLIB_file_t * _PDCLIB_filelist = &_PDCLIB_sin;

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* Testing covered by several other testdrivers using stdin / stdout / 
       stderr.
    */
    return TEST_RESULTS;
}

#endif
