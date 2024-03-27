/* _PDCLIB_rename( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of _PDCLIB_rename() fit for use with
   POSIX kernels.
 */

#include <stdio.h>

#ifndef REGTEST

/* Having to jump through some hoops here so including fcntl.h does
   work. Linux struggles with redefinitions of SEEK_SET et al. if
   we set _GNU_SOURCE, but Cygwin needs that to actually get to the
   AT_FDCWD definition.
*/
#ifdef __linux__
#define _ATFILE_SOURCE 1
#else
#define _GNU_SOURCE 1
#endif

#include "pdclib/_PDCLIB_glue.h"
#include "pdclib/_PDCLIB_defguard.h"

#include "/usr/include/errno.h"

/* The system calls provided for renaming are rename(), renameat()
   and renameat2(). Using rename() is not possible, since we have
   that symbol in our library and would end up with a recursive
   call. But we *can* use renameat() with default parameters!
   AT_FDCWD is declared in fcntl.h. We need to manually declare
   renameat() here as it is declared in system's <stdio.h>.
*/
#include "/usr/include/fcntl.h"

#ifdef __cplusplus
extern "C" {
#endif

int renameat( int, const char *, int, const char * );

#ifdef __cplusplus
}
#endif

int _PDCLIB_rename( const char * oldpath, const char * newpath )
{
    /* Whether existing newpath is overwritten is implementation-
       defined. This system call *does* overwrite.
    */
    if ( renameat( AT_FDCWD, oldpath, AT_FDCWD, newpath ) != 0 )
    {
        /* The 1:1 mapping in _PDCLIB_config.h ensures this works. */
        *_PDCLIB_errno_func() = errno;
        return -1;
    }
    else
    {
        return 0;
    }
}

#endif

#ifdef TEST
#include "_PDCLIB_test.h"

#include <stdlib.h>

int main( void )
{
#ifndef REGTEST
    FILE * file;
    remove( testfile1 );
    remove( testfile2 );
    /* check that neither file exists */
    TESTCASE( fopen( testfile1, "r" ) == NULL );
    TESTCASE( fopen( testfile2, "r" ) == NULL );
    /* rename file 1 to file 2 - expected to fail */
    TESTCASE( _PDCLIB_rename( testfile1, testfile2 ) == -1 );
    /* create file 1 */
    TESTCASE( ( file = fopen( testfile1, "w" ) ) != NULL );
    TESTCASE( fputc( 'x', file ) == 'x' );
    TESTCASE( fclose( file ) == 0 );
    /* check that file 1 exists */
    TESTCASE( ( file = fopen( testfile1, "r" ) ) != NULL );
    TESTCASE( fclose( file ) == 0 );
    /* rename file 1 to file 2 */
    TESTCASE( _PDCLIB_rename( testfile1, testfile2 ) == 0 );
    /* check that file 2 exists, file 1 does not */
    TESTCASE( fopen( testfile1, "r" ) == NULL );
    TESTCASE( ( file = fopen( testfile2, "r" ) ) != NULL );
    TESTCASE( fclose( file ) == 0 );
    /* create another file 1 */
    TESTCASE( ( file = fopen( testfile1, "w" ) ) != NULL );
    TESTCASE( fputc( 'x', file ) == 'x' );
    TESTCASE( fclose( file ) == 0 );
    /* check that file 1 exists */
    TESTCASE( ( file = fopen( testfile1, "r" ) ) != NULL );
    TESTCASE( fclose( file ) == 0 );
    /* Whether existing destination files are overwritten or not
       is implementation-defined.
       This implementation *does* overwrite.
    */
    TESTCASE( _PDCLIB_rename( testfile1, testfile2 ) == 0 );
    /* remove both files */
    remove( testfile1 );
    remove( testfile2 );
#endif
    return TEST_RESULTS;
}

#endif
