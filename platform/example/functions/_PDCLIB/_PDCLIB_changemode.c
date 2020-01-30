/* _PDCLIB_changemode( FILE * stream, int mode )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of _PDCLIB_open() fit for use with POSIX
   kernels.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

int _PDCLIB_changemode( struct _PDCLIB_file_t * stream, unsigned int mode )
{
    /* This is a utility function used by freopen, to allow for a rather
       specific bit of trickery.
       ISO/IEC 9899:2011 (i.e., the ISO C standard) is ambiguous in the
       case of the filename argument being NULL. It states that the mode
       of the open stream could be _changed_ in implementation-defined
       circumstances. While it goes on to state that freopen will "first
       attempt to close any file that is associated with the specified
       stream", it is not quite clear if the "implementation-defined
       circumstances" mentioned earlier would include changing the mode
       without actually closing the file.
       IEEE Std 1003.1, 2004 Edition (POSIX) on the other hand is less
       ambiguous, as it states that "the file descriptor associated with
       the stream need not be closed if the call to freopen() succeeds"
       for the same case (filename being NULL).
       This function gets called by PDCLib's freopen() in just that case,
       allowing you to perform whatever mode changes YOUR implementation
       decides to support. Return zero if the change requested is not
       supported; freopen will then attempt the close-and-open-again way.
       Return non-zero if the requested mode change was supported and
       successful.
    */
    /* The example implementation does not support any mode changes without
       closing the stream.
    */
    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* No test drivers. */
    return TEST_RESULTS;
}

#endif
