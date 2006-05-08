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

/* TODO: Initialize stdin, stdout, stderr */

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
