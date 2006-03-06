/* $Id$ */

/* Release $Name$ */

/* fopen( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

static const FILE * _PDCLIB_filelist = NULL;

static int filemode( char const * const mode )
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
            return -1;
    }
    for ( size_t i = 1; i < 4; ++i )
    {
        switch ( mode[1] )
        {
            case '+':
                if ( rc & _PDCLIB_FRW ) return -1;
                rc |= _PDCLIB_FRW;
                break;
            case 'b':
                if ( rc & _PDCLIB_FBIN ) return -1;
                rc |= _PDCLIB_FBIN;
                break;
            case '\0':
                return rc;
            default:
                return -1;
        }
    }
    return -1;
}

FILE * fopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode )
{
    FILE * rc;
    if ( mode == NULL || filename == NULL || filename[0] == '\0' )
    {
        return NULL;
    }
    if ( ( rc = calloc( 1, sizeof( FILE ) ) ) == NULL ) return rc; /* no space for another FILE */
    if ( ( rc->status = filemode( mode ) ) == -1 ) goto fail; /* invalid mode given */
    if ( ( rc->handle = _PDCLIB_open( filename, rc->status ) ) == -1 ) goto fail; /* OS "open" failed */
    rc->next = _PDCLIB_filelist;
    _PDCLIB_filelist = rc;
    /* TODO: Continue here: Set up PDCLib FILE contents */
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
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
