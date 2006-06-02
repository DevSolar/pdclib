/* $Id$ */

/* _PDCLIB_rename( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST
#include <unistd.h>
#include <_PDCLIB_glue.h>

int _PDCLIB_rename( const char * old, const char * new )
{
    /* Note that the behaviour if new file exists is implementation-defined.
       There is nothing wrong with either overwriting it or failing the
       operation, but you might want to document whichever you chose.
       This example fails if new file exists.
    */
    if ( link( old, new ) == 0 )
    {
        return unlink( old );
    }
    else
    {
        return -1;
    }
}

#endif

#ifdef TEST
/* TODO: Work around the following undef */
#undef SEEK_SET
#include <_PDCLIB_test.h>

#include <stdlib.h>

int main( void )
{
    char filename1[] = "touch testfile1";
    char filename2[] = "testfile2";
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
