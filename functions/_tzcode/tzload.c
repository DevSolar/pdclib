/* tzload( char const *, struct state *, bool )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define _DEFAULT_SOURCE

#include "_PDCLIB_config.h"

#include "_PDCLIB_tzcode.h"

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE * tzopen( char const * name )
{
    char * fullname;
    FILE * rc;

    if ( name == NULL )
    {
        name = _PDCLIB_TZDEFAULT;

        if ( name == NULL )
        {
            errno = EINVAL;
            return NULL;
        }
    }

    if ( name[0] == ':' )
    {
        ++name;
    }

    if ( name[0] == '/' )
    {
        fullname = (char *)name;
    }
    else
    {
        if ( ( fullname = (char *)malloc( strlen( name ) + sizeof( _PDCLIB_TZDIR ) + 1 ) ) == NULL )
        {
            errno = ENOMEM;
            return NULL;
        }

        strcpy( fullname, _PDCLIB_TZDIR );
        strcat( fullname, name );
    }

    rc = fopen( fullname, "rb" );

    if ( fullname != name )
    {
        free( fullname );
    }

    return rc;
}

int_fast32_t tzread32( FILE * tzfile )
{
    int_fast32_t rc = 0;
    char in[4];

    if ( fread( in, 1, 4, tzfile ) == 4 )
    {
        int i;

        rc = in[0] & 0x7f;

        for ( i = 1; i < 4; ++i )
        {
            rc = ( rc << 8 ) | ( in[i] & 0xff );
        }

        if ( in[0] & 0x80 )
        {
            /* Do two's complement negation even on non-two's-complement
               machines. If the result would be minval - 1, return minval.
            */
            int_fast32_t minval = 1;
            minval <<= (32 - 2);           /* 1/2 maxval */
            minval = minval - 1 + minval;  /* maxval */
            minval = -1 - minval;          /* minval */

            rc -= ! _PDCLIB_TWOS_COMPLEMENT && rc != 0;
            rc += minval;
        }
    }

    return rc;
}

int_fast64_t tzread64( FILE * tzfile )
{
    int_fast64_t rc = 0;
    char in[8];

    if ( fread( in, 1, 8, tzfile ) == 8 )
    {
        int i;

        rc = in[0] & 0x7f;

        for ( i = 1; i < 8; ++i )
        {
            rc = ( rc << 8 ) | ( in[i] & 0xff );
        }

        if ( in[0] & 0x80 )
        {
            /* Do two's complement negation even on non-two's-complement
               machines. If the result would be minval - 1, return minval.
            */
            int_fast64_t minval = 1;
            minval <<= (64 - 2);           /* 1/2 maxval */
            minval = minval - 1 + minval;  /* maxval */
            minval = -1 - minval;          /* minval */

            rc -= ! _PDCLIB_TWOS_COMPLEMENT && rc != 0;
            rc += minval;
        }
    }

    return rc;
}


/* Load tz data from the named file into the given structure. Read extended
   format if doextend is set. Return 0 on success, an errno value on failure.
*/
int tzload( char const * name, struct state * sp, bool doextend )
{
    FILE * tzfile = tzopen( name );

    if ( tzfile == NULL )
    {
        return errno;
    }

    /* TODO */

    fclose( tzfile );
    return 0;
}

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    char * path = "testfile";
    FILE * fh = fopen( path, "wb+" );
    TESTCASE( fh != NULL );
    TESTCASE( fwrite( "\x00\x00\x00\x00", 1, 4, fh ) == 4 );
    TESTCASE( fwrite( "\x7f\xff\xff\xff", 1, 4, fh ) == 4 );
    TESTCASE( fwrite( "\x80\x00\x00\x00", 1, 4, fh ) == 4 );
    TESTCASE( fwrite( "\xff\xff\xff\xff", 1, 4, fh ) == 4 );
    TESTCASE( fwrite( "\x00\x00\x00\x00\x00\x00\x00\x00", 1, 8, fh ) == 8 );
    TESTCASE( fwrite( "\x7f\xff\xff\xff\xff\xff\xff\xff", 1, 8, fh ) == 8 );
    TESTCASE( fwrite( "\x80\x00\x00\x00\x00\x00\x00\x00", 1, 8, fh ) == 8 );
    TESTCASE( fwrite( "\xff\xff\xff\xff\xff\xff\xff\xff", 1, 8, fh ) == 8 );
    fclose( fh );

    TESTCASE( ( path = realpath( path, NULL ) ) != NULL );
    fh = tzopen( path );
    TESTCASE( tzread32( fh ) == INT32_C(           0 ) );
    TESTCASE( tzread32( fh ) == INT32_C(  2147483647 ) );
    TESTCASE( tzread32( fh ) == INT32_C( -2147483648 ) );
    TESTCASE( tzread32( fh ) == INT32_C(          -1 ) );
    TESTCASE( tzread64( fh ) == INT64_C(                    0 ) );
    TESTCASE( tzread64( fh ) == INT64_C(  9223372036854775807 ) );
    TESTCASE( tzread64( fh ) == INT64_C( -9223372036854775807 ) - 1 );
    TESTCASE( tzread64( fh ) == INT64_C(                   -1 ) );
    fclose( fh );
    remove( path );
    free( path );
    return TEST_RESULTS;
}

#endif
