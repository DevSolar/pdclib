/* tmpfile( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#ifndef __STDC_NO_THREADS__
#include <threads.h>
extern mtx_t _PDCLIB_filelist_mtx;
#endif

#include "pdclib/_PDCLIB_glue.h"
#include "pdclib/_PDCLIB_defguard.h"

#include <stdlib.h>
#include <string.h>

#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "unistd.h"

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

/* This is an example implementation of tmpfile() fit for use with POSIX
   kernels.
*/
struct _PDCLIB_file_t * tmpfile( void )
{
    FILE * rc;
    /* This is the chosen way to get high-quality randomness. Replace as
       appropriate.
    */
    int randomsource = open( "/dev/urandom", O_RDONLY );
    /* Working under the assumption that the tempfile location is canonical
       (absolute), and does not require going through _PDCLIB_realpath().
    */
    char * filename = ( char * )malloc( L_tmpnam );
    _PDCLIB_fd_t fd;

    if ( randomsource == -1 )
    {
        return NULL;
    }

    for ( ;; )
    {
        /* Get a filename candidate. What constitutes a valid filename and
           where temporary files are usually located is platform-dependent,
           which is one reason why this function is located in the platform
           overlay. The other reason is that a *good* implementation should
           use high-quality randomness instead of a pseudo-random sequence to
           generate the filename candidate, which is *also* platform-dependent.
        */
        unsigned int random;
        read( randomsource, (void *)&random, sizeof( unsigned int ) );
        sprintf( filename, "/tmp/%u.tmp", random );
        /* Check if file of this name exists. Note that fopen() is a very weak
           check, which does not take e.g. access permissions into account
           (file might exist but not readable). Replace with something more
           appropriate.
        */
        fd = open( filename, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR );

        if ( fd != -1 )
        {
            /* Found a file that does not exist yet */
            break;
        }

        close( fd );
    }

    close( randomsource );

    /* See fopen(), which does much of the same. */

    if ( ( rc = _PDCLIB_init_file_t( NULL ) ) == NULL )
    {
        /* initializing FILE structure failed */
        close( fd );
        return NULL;
    }

    rc->status |= _PDCLIB_filemode( "wb+" ) | _IOLBF | _PDCLIB_DELONCLOSE;
    rc->handle = fd;

    /* Filename (for potential freopen()) */
    rc->filename = filename;

    /* Adding to list of open files */
    _PDCLIB_LOCK( _PDCLIB_filelist_mtx );
    rc->next = _PDCLIB_filelist;
    _PDCLIB_filelist = rc;
    _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <string.h>

int main( void )
{
    FILE * fh;
#ifndef REGTEST
    char filename[ L_tmpnam ];
    FILE * fhtest;
#endif
    TESTCASE( ( fh = tmpfile() ) != NULL );
    TESTCASE( fputc( 'x', fh ) == 'x' );
    /* Checking that file is actually there */
    TESTCASE_NOREG( strcpy( filename, fh->filename ) == filename );
    TESTCASE_NOREG( ( fhtest = fopen( filename, "r" ) ) != NULL );
    TESTCASE_NOREG( fclose( fhtest ) == 0 );
    /* Closing tmpfile */
    TESTCASE( fclose( fh ) == 0 );
    /* Checking that file was deleted */
    TESTCASE_NOREG( fopen( filename, "r" ) == NULL );
    return TEST_RESULTS;
}

#endif
