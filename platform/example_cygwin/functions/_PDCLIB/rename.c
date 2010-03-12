/* $Id$ */

/* _PDCLIB_rename( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

#include </usr/include/errno.h>

extern int unlink( const char * pathname );
extern int link( const char * old, const char * new );

int _PDCLIB_rename( const char * old, const char * new )
{
    /* Note that the behaviour if new file exists is implementation-defined.
       There is nothing wrong with either overwriting it or failing the
       operation, but you might want to document whichever you chose.
       This example fails if new file exists.
    */
    if ( link( old, new ) == 0 )
    {
        if ( unlink( old ) == EOF )
        {
            switch ( errno )
            {
                case EACCES:
                case EFAULT:
                case EIO:
                case EISDIR:
                case ELOOP:
                case ENAMETOOLONG:
                case ENOENT:
                case ENOMEM:
                case ENOTDIR:
                case EPERM:
                case EROFS:
                    _PDCLIB_errno = _PDCLIB_EIO;
                    break;
                default:
                    _PDCLIB_errno = _PDCLIB_EUNKNOWN;
                    break;
            }
            return -1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        switch ( errno )
        {
            case EACCES:
            case EEXIST:
            case EFAULT:
            case EIO:
            case ELOOP:
            case EMLINK:
            case ENAMETOOLONG:
            case ENOENT:
            case ENOMEM:
            case ENOSPC:
            case ENOTDIR:
            case EPERM:
            case EROFS:
            case EXDEV:
                _PDCLIB_errno = _PDCLIB_EIO;
                break;
            default:
                _PDCLIB_errno = _PDCLIB_EUNKNOWN;
                break;
        }
        return EOF;
    }
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <stdlib.h>

int main( void )
{
    char filename1[] = "touch testfile1";
    char filename2[] = "testfile2";
    remove( filename1 + 6 );
    remove( filename2 );
    /* check that neither file exists */
    TESTCASE( fopen( filename1 + 6, "r" ) == NULL );
    TESTCASE( fopen( filename2, "r" ) == NULL );
    /* rename file 1 to file 2 - expected to fail */
    TESTCASE( _PDCLIB_rename( filename1 + 6, filename2 ) == -1 );
    /* create file 1 */
    system( filename1 );
    /* check that file 1 exists */
    TESTCASE( fopen( filename1 + 6, "r" ) != NULL );
    /* rename file 1 to file 2 */
    TESTCASE( _PDCLIB_rename( filename1 + 6, filename2 ) == 0 );
    /* check that file 2 exists, file 1 does not */
    TESTCASE( fopen( filename1 + 6, "r" ) == NULL );
    TESTCASE( fopen( filename2, "r" ) != NULL );
    /* create another file 1 */
    system( filename1 );
    /* check that file 1 exists */
    TESTCASE( fopen( filename1 + 6, "r" ) != NULL );
    /* rename file 1 to file 2 - expected to fail, see comment in
       _PDCLIB_rename() itself.
    */
    TESTCASE( _PDCLIB_rename( filename1 + 6, filename2 ) == -1 );
    /* remove both files */
    remove( filename1 + 6 );
    remove( filename2 );
    /* check that they're gone */
    TESTCASE( fopen( filename1 + 6, "r" ) == NULL );
    TESTCASE( fopen( filename2, "r" ) == NULL );
    return TEST_RESULTS;
}

#endif
