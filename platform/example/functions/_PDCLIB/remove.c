/* $Id$ */

/* _PDCLIB_remove( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of _PDCLIB_remove() (declared in
   _PDCLIB_glue.h), fit for use in POSIX kernels.
   NOTE: Linux is *not* POSIX-compliant in this, as it sets EISDIR instead of
   EPERM if you try to unlink a directory. Check the manpage for unlink(2).
*/

#ifndef REGTEST
#include <_PDCLIB_glue.h>
#include <errno.h>
#include <unistd.h>

int _PDCLIB_remove( const char * filename )
{
    int prev_errno = errno;
    int rc;
    errno = 0;
    if ( ( ( rc = unlink( filename ) ) != 0 ) && ( errno == EPERM ) )
    {
        rc = rmdir( filename );
    }
    errno = prev_errno;
    return rc;
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
