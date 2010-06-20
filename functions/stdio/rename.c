/* $Id$ */

/* rename( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

#include <string.h>

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

int rename( const char * old, const char * new )
{
    struct _PDCLIB_file_t * current = _PDCLIB_filelist;
    while ( current != NULL )
    {
        if ( ( current->filename != NULL ) && ( strcmp( current->filename, old ) == 0 ) )
        {
            /* File of that name currently open. Do not rename. */
            return EOF;
        }
        current = current->next;
    }
    return _PDCLIB_rename( old, new );
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <stdlib.h>

int main( void )
{
    char filename1[] = "touch testfile1";
    char filename2[] = "testfile2";
    FILE * file;
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
    TESTCASE( ( file = fopen( filename1 + 6, "r" ) ) != NULL );
    TESTCASE( fclose( file ) == 0 );
    /* rename file 1 to file 2 */
    TESTCASE( rename( filename1 + 6, filename2 ) == 0 );
    /* check that file 2 exists, file 1 does not */
    TESTCASE( fopen( filename1 + 6, "r" ) == NULL );
    TESTCASE( ( file = fopen( filename2, "r" ) ) != NULL );
    TESTCASE( fclose( file ) == 0 );
    /* create another file 1 */
    system( filename1 );
    /* check that file 1 exists */
    TESTCASE( ( file = fopen( filename1 + 6, "r" ) ) != NULL );
    TESTCASE( fclose( file ) == 0 );
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

