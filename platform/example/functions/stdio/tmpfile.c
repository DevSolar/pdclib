/* $Id$ */

/* tmpfile( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include <_PDCLIB_glue.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
    FILE * randomsource = fopen( "/proc/sys/kernel/random/uuid", "rb" );
    char filename[ L_tmpnam ];
    _PDCLIB_fd_t fd;
    if ( randomsource == NULL )
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
        fscanf( randomsource, "%u", &random ); 
        sprintf( filename, "/tmp/%u.tmp", random );
        /* Check if file of this name exists. Note that fopen() is a very weak
           check, which does not take e.g. access permissions into account
           (file might exist but not readable). Replace with something more
           appropriate.
        */
        fd = open( filename, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR );
        if ( fd != -1 )
        {
            break;
        }
        close( fd );
    }
    fclose( randomsource );
    /* See fopen(). */
    if ( ( rc = calloc( 1, sizeof( struct _PDCLIB_file_t ) + _PDCLIB_UNGETCBUFSIZE + L_tmpnam + BUFSIZ ) ) == NULL )
    {
        /* No memory to set up FILE structure */
        close( fd );
        return NULL;
    }
    rc->status = _PDCLIB_filemode( "wb+" ) | _IOLBF | _PDCLIB_DELONCLOSE;
    rc->handle = fd;
    rc->ungetbuf = (unsigned char *)rc + sizeof( struct _PDCLIB_file_t );
    rc->filename = (char *)rc->ungetbuf + _PDCLIB_UNGETCBUFSIZE;
    rc->buffer   = rc->filename + L_tmpnam;
    strcpy( rc->filename, filename );
    rc->bufsize = BUFSIZ;
    rc->bufidx = 0;
    rc->ungetidx = 0;
    rc->next = _PDCLIB_filelist;
    _PDCLIB_filelist = rc;
    return rc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>
#include <string.h>

int main()
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

