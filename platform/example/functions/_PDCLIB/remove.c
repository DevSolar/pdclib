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
    if ( ( ( rc = unlink( filename ) ) != 0 ) && ( errno == EISDIR ) )
    {
        rc = rmdir( filename );
    }
    errno = prev_errno;
    return rc;
}

#endif

#ifdef TEST
/* TODO: Work around the following undef */
#undef SEEK_SET
#include <_PDCLIB_test.h>

#include <stdlib.h>
#include <string.h>

int main( void )
{
    char filename[] = "touch testfile";
    system( filename );
    /* file is actually readable */
    TESTCASE( fopen( filename + 6, "r" ) != NULL );
    /* remove function does not return error */
    TESTCASE( _PDCLIB_remove( filename + 6 ) == 0 );
    /* file is no longer readable */
    TESTCASE( fopen( filename + 6, "r" ) == NULL );
    /* remove function does return error */
    TESTCASE( _PDCLIB_remove( filename + 6 ) != 0 );
    memcpy( filename, "mkdir", 5 );
    /* create directory */
    system( filename );
    /* remove function does not return error */
    TESTCASE( _PDCLIB_remove( filename + 6 ) == 0 );
    /* remove function does return error */
    TESTCASE( _PDCLIB_remove( filename + 6 ) != 0 );
    return TEST_RESULTS;
}

#endif
