/* tmpfile_s( FILE * * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef REGTEST

errno_t tmpfile_s( FILE * _PDCLIB_restrict * _PDCLIB_restrict streamptr )
{
    if ( streamptr == NULL )
    {
        _PDCLIB_constraint_handler( _PDCLIB_CONSTRAINT_VIOLATION( _PDCLIB_EINVAL ) );
        return _PDCLIB_EINVAL;
    }

    *streamptr = tmpfile();

    if ( *streamptr == NULL )
    {
        assert( *_PDCLIB_errno_func() != 0 );
        return *_PDCLIB_errno_func();
    }

    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <string.h>

#if ! defined( REGTEST ) || defined( __STDC_LIB_EXT1__ )

static int HANDLER_CALLS = 0;

static void test_handler( const char * _PDCLIB_restrict msg, void * _PDCLIB_restrict ptr, errno_t error )
{
    ++HANDLER_CALLS;
}

#endif

int main( void )
{
#if ! defined( REGTEST ) || defined( __STDC_LIB_EXT1__ )
    FILE * fh;
    char filename[ L_tmpnam ];
    FILE * fhtest;
    set_constraint_handler_s( test_handler );

    TESTCASE( ( tmpfile_s( &fh ) ) == 0 );
    TESTCASE( fputc( 'x', fh ) == 'x' );
    /* Checking that file is actually there */
    TESTCASE_NOREG( strcpy( filename, fh->filename ) == filename );
    TESTCASE_NOREG( ( fhtest = fopen( filename, "r" ) ) != NULL );
    TESTCASE_NOREG( fclose( fhtest ) == 0 );
    /* Closing tmpfile */
    TESTCASE( fclose( fh ) == 0 );
    /* Checking that file was deleted */
    TESTCASE_NOREG( fopen( filename, "r" ) == NULL );

    /* Constraint violation */
    TESTCASE( ( tmpfile_s( NULL ) ) != 0 );

    TESTCASE( HANDLER_CALLS == 1 );
#endif
    return TEST_RESULTS;
}

#endif
