/* $Id$ */

/* rename( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

int rename( const char * old, const char * new )
{
    /* TODO: Search open file list, flush and close file */
    return _PDCLIB_rename( old, new );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <stdlib.h>

int main( void )
{
    /* TODO: Extend to internal testing (buffer etc.) */
    char filename1[] = "touch testfile1";
    char filename2[] = "testfile2";
    remove( filename1 + 6 );
    remove( filename2 );
    /* make sure that neither file exists */
    TESTCASE( fopen( filename1 + 6, "r" ) == NULL );
    TESTCASE( fopen( filename2, "r" ) == NULL );
    /* rename file 1 to file 2 - expected to fail */
    TESTCASE( rename( filename1 + 6, filename2 ) == -1 );
    /* create file 1 */
    system( filename1 );
    /* check that file 1 exists */
    TESTCASE( fopen( filename1 + 6, "r" ) != NULL );
    /* rename file 1 to file 2 */
    TESTCASE( rename( filename1 + 6, filename2 ) == 0 );
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
#ifndef REGTEST
    TESTCASE( rename( filename1 + 6, filename2 ) == -1 );
#else
    /* glibc rename() overwrites existing destination file. */
    TESTCASE( rename( filename1 + 6, filename2 ) == 0 );
#endif
    /* remove both files */
    remove( filename1 + 6 );
    remove( filename2 );
    /* check that they're gone */
    TESTCASE( fopen( filename1 + 6, "r" ) == NULL );
    TESTCASE( fopen( filename2, "r" ) == NULL );
    return TEST_RESULTS;
}

#endif

