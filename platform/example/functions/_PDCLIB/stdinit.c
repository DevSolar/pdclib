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

/* FIXME: serr should handle one character. Buffering on out / in? */
static struct _PDCLIB_file_t _PDCLIB_serr = { 2, { 0, 0 }, _PDCLIB_serr_buffer, BUFSIZ, 0, 0, _IONBF, NULL };
static struct _PDCLIB_file_t _PDCLIB_sout = { 1, { 0, 0 }, _PDCLIB_sout_buffer, BUFSIZ, 0, 0, _IOLBF, &_PDCLIB_serr };
static struct _PDCLIB_file_t _PDCLIB_sin  = { 0, { 0, 0 }, _PDCLIB_sin_buffer, BUFSIZ, 0, 0, _IOLBF, &_PDCLIB_sout };

struct _PDCLIB_file_t * stdin  = &_PDCLIB_sin;
struct _PDCLIB_file_t * stdout = &_PDCLIB_sout;
struct _PDCLIB_file_t * stderr = &_PDCLIB_serr;

#endif

#ifdef TEST
/* TODO: Necessity of this undef should probably be circumvented. */
#undef SEEK_SET
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
