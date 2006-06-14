/* $Id$ */

/* fopen( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

/* FIXME: This approach is a possible attack vector. */
struct _PDCLIB_file_t * _PDCLIB_filelist = NULL;

/* Helper function that parses the C-style mode string passed to fopen() into
   the PDCLib flags FREAD, FWRITE, FAPPEND, FRW (read-write) and FBIN (binary
   mode).
*/
static unsigned int filemode( char const * const mode )
{
    int rc = 0;
    switch ( mode[0] )
    {
        case 'r':
            rc |= _PDCLIB_FREAD;
            break;
        case 'w':
            rc |= _PDCLIB_FWRITE;
            break;
        case 'a':
            rc |= _PDCLIB_FAPPEND;
            break;
        default:
            /* Other than read, write, or append - invalid */
            return 0;
    }
    for ( size_t i = 1; i < 4; ++i )
    {
        switch ( mode[i] )
        {
            case '+':
                if ( rc & _PDCLIB_FRW ) return 0; /* Duplicates are invalid */
                rc |= _PDCLIB_FRW;
                break;
            case 'b':
                if ( rc & _PDCLIB_FBIN ) return 0; /* Duplicates are invalid */
                rc |= _PDCLIB_FBIN;
                break;
            case '\0':
                /* End of mode */
                return rc;
            default:
                /* Other than read/write or binary - invalid. */
                return 0;
        }
    }
    /* Longer than three chars - invalid. */
    return 0;
}

struct _PDCLIB_file_t * fopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode )
{
    struct _PDCLIB_file_t * rc;
    if ( mode == NULL || filename == NULL || filename[0] == '\0' )
    {
        /* Mode or filename invalid */
        return NULL;
    }
    if ( ( rc = calloc( 1, sizeof( struct _PDCLIB_file_t ) ) ) == NULL )
    {
        /* no memory for another FILE */
        return NULL;
    }
    if ( ( rc->status = filemode( mode ) ) == 0 ) goto fail; /* invalid mode */
    rc->handle = _PDCLIB_open( filename, rc->status );
    if ( rc->handle == _PDCLIB_NOHANDLE ) goto fail; /* OS open() failed */
    /* Adding to list of open files */
    rc->next = _PDCLIB_filelist;
    _PDCLIB_filelist = rc;
    /* Setting buffer, and mark as internal. TODO: Check for unbuffered? */
    if ( ( rc->buffer = malloc( BUFSIZ ) ) == NULL ) goto fail;
    rc->bufsize = BUFSIZ;
    rc->status |= ( _PDCLIB_LIBBUFFER | _PDCLIB_VIRGINSTR );
    /* TODO: Setting mbstate */
    return rc;
fail:
    free( rc );
    return NULL;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
#ifndef REGTEST
    TESTCASE( filemode( "r" ) == _PDCLIB_FREAD );
    TESTCASE( filemode( "w" ) == _PDCLIB_FWRITE );
    TESTCASE( filemode( "a" ) == _PDCLIB_FAPPEND );
    TESTCASE( filemode( "r+" ) == ( _PDCLIB_FREAD | _PDCLIB_FRW ) );
    TESTCASE( filemode( "w+" ) == ( _PDCLIB_FWRITE | _PDCLIB_FRW ) );
    TESTCASE( filemode( "a+" ) == ( _PDCLIB_FAPPEND | _PDCLIB_FRW ) );
    TESTCASE( filemode( "rb" ) == ( _PDCLIB_FREAD | _PDCLIB_FBIN ) );
    TESTCASE( filemode( "wb" ) == ( _PDCLIB_FWRITE | _PDCLIB_FBIN ) );
    TESTCASE( filemode( "ab" ) == ( _PDCLIB_FAPPEND | _PDCLIB_FBIN ) );
    TESTCASE( filemode( "r+b" ) == ( _PDCLIB_FREAD | _PDCLIB_FRW | _PDCLIB_FBIN ) );
    TESTCASE( filemode( "w+b" ) == ( _PDCLIB_FWRITE | _PDCLIB_FRW | _PDCLIB_FBIN ) );
    TESTCASE( filemode( "a+b" ) == ( _PDCLIB_FAPPEND | _PDCLIB_FRW | _PDCLIB_FBIN ) );
    TESTCASE( filemode( "rb+" ) == ( _PDCLIB_FREAD | _PDCLIB_FRW | _PDCLIB_FBIN ) );
    TESTCASE( filemode( "wb+" ) == ( _PDCLIB_FWRITE | _PDCLIB_FRW | _PDCLIB_FBIN ) );
    TESTCASE( filemode( "ab+" ) == ( _PDCLIB_FAPPEND | _PDCLIB_FRW | _PDCLIB_FBIN ) );
    TESTCASE( fopen( NULL, NULL ) == NULL );
    TESTCASE( fopen( NULL, "w" ) == NULL );
    TESTCASE( fopen( "", NULL ) == NULL );
    TESTCASE( fopen( "", "w" ) == NULL );
    TESTCASE( fopen( "foo", "" ) == NULL );
    TESTCASE( fopen( "testfile", "wq" ) == NULL ); /* Illegal mode */
    TESTCASE( fopen( "testfile", "wr" ) == NULL ); /* Illegal mode */
    TESTCASE( fopen( "testfile", "w" ) != NULL );
    system( "rm testfile" );
#else
    puts( " NOTEST fopen() test driver is PDCLib-specific." );
#endif
    return TEST_RESULTS;
}

#endif
