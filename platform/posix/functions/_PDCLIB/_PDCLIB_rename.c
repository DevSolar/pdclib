/* _PDCLIB_rename( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include "_PDCLIB_glue.h"

#include <errno.h>

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
            return -1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return EOF;
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
    /* rename file 1 to file 2 - expected to fail, see comment in
       _PDCLIB_rename() itself.
    */
    TESTCASE( _PDCLIB_rename( testfile1, testfile2 ) == -1 );
    /* remove both files */
    remove( testfile1 );
    remove( testfile2 );
#endif
    return TEST_RESULTS;
}

#endif
