/* _PDCLIB_load_lc_time( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pdclib/_PDCLIB_internal.h"

struct _PDCLIB_lc_time_t * _PDCLIB_load_lc_time( const char * path, const char * locale )
{
    struct _PDCLIB_lc_time_t * rc = NULL;
    const char * extension = "_time.dat";
    char * file = (char *)malloc( strlen( path ) + strlen( locale ) + strlen( extension ) + 1 );

    if ( file )
    {
        FILE * fh;

        strcpy( file, path );
        strcat( file, locale );
        strcat( file, extension );

        if ( ( fh = fopen( file, "rb" ) ) != NULL )
        {
            if ( ( rc = (struct _PDCLIB_lc_time_t *)malloc( sizeof( struct _PDCLIB_lc_time_t ) ) ) != NULL )
            {
                char * data = _PDCLIB_load_lines( fh, 44 );

                if ( data != NULL )
                {
                    size_t i;

                    for ( i = 0; i < 12; ++i )
                    {
                        rc->month_name_abbr[ i ] = data;
                        data += strlen( data ) + 1;
                    }

                    for ( i = 0; i < 12; ++i )
                    {
                        rc->month_name_full[ i ] = data;
                        data += strlen( data ) + 1;
                    }

                    for ( i = 0; i < 7; ++i )
                    {
                        rc->day_name_abbr[ i ] = data;
                        data += strlen( data ) + 1;
                    }

                    for ( i = 0; i < 7; ++i )
                    {
                        rc->day_name_full[ i ] = data;
                        data += strlen( data ) + 1;
                    }

                    rc->alloced = 1;
                }
                else
                {
                    free( rc );
                    rc = NULL;
                }
            }

            fclose( fh );
        }

        free( file );
    }

    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    FILE * fh = fopen( "test_time.dat", "wb" );
    struct _PDCLIB_lc_time_t * lc;

    TESTCASE( fh != NULL );

    /* month name abbreviation */
    TESTCASE( fprintf( fh, "%s\n", "Jan" ) == 4 );
    TESTCASE( fprintf( fh, "%s\n", "Feb" ) == 4 );
    TESTCASE( fprintf( fh, "%s\n", "M\xe4r" ) == 4 );
    TESTCASE( fprintf( fh, "%s\n", "Apr" ) == 4 );
    TESTCASE( fprintf( fh, "%s\n", "Mai" ) == 4 );
    TESTCASE( fprintf( fh, "%s\n", "Jun" ) == 4 );
    TESTCASE( fprintf( fh, "%s\n", "Jul" ) == 4 );
    TESTCASE( fprintf( fh, "%s\n", "Aug" ) == 4 );
    TESTCASE( fprintf( fh, "%s\n", "Sep" ) == 4 );
    TESTCASE( fprintf( fh, "%s\n", "Okt" ) == 4 );
    TESTCASE( fprintf( fh, "%s\n", "Nov" ) == 4 );
    TESTCASE( fprintf( fh, "%s\n", "Dez" ) == 4 );
    /* month name full */
    TESTCASE( fprintf( fh, "%s\n", "Januar" ) == 7 );
    TESTCASE( fprintf( fh, "%s\n", "Februar" ) == 8 );
    TESTCASE( fprintf( fh, "%s\n", "M\xe4rz" ) == 5 );
    TESTCASE( fprintf( fh, "%s\n", "April" ) == 6 );
    TESTCASE( fprintf( fh, "%s\n", "Mai" ) == 4 );
    TESTCASE( fprintf( fh, "%s\n", "Juni" ) == 5 );
    TESTCASE( fprintf( fh, "%s\n", "Juli" ) == 5 );
    TESTCASE( fprintf( fh, "%s\n", "August" ) == 7 );
    TESTCASE( fprintf( fh, "%s\n", "September" ) == 10 );
    TESTCASE( fprintf( fh, "%s\n", "Oktober" ) == 8 );
    TESTCASE( fprintf( fh, "%s\n", "November" ) == 9 );
    TESTCASE( fprintf( fh, "%s\n", "Dezember" ) == 9 );
    /* day name abbreviation */
    TESTCASE( fprintf( fh, "%s\n", "So" ) == 3 );
    TESTCASE( fprintf( fh, "%s\n", "Mo" ) == 3 );
    TESTCASE( fprintf( fh, "%s\n", "Di" ) == 3 );
    TESTCASE( fprintf( fh, "%s\n", "Mi" ) == 3 );
    TESTCASE( fprintf( fh, "%s\n", "Do" ) == 3 );
    TESTCASE( fprintf( fh, "%s\n", "Fr" ) == 3 );
    TESTCASE( fprintf( fh, "%s\n", "Sa" ) == 3 );
    /* day name full */
    TESTCASE( fprintf( fh, "%s\n", "Sonntag" ) == 8 );
    TESTCASE( fprintf( fh, "%s\n", "Montag" ) == 7 );
    TESTCASE( fprintf( fh, "%s\n", "Dienstag" ) == 9 );
    TESTCASE( fprintf( fh, "%s\n", "Mittwoch" ) == 9 );
    TESTCASE( fprintf( fh, "%s\n", "Donnerstag" ) == 11 );
    TESTCASE( fprintf( fh, "%s\n", "Freitag" ) == 8 );
    TESTCASE( fprintf( fh, "%s\n", "Samstag" ) == 8 );

    TESTCASE( fprintf( fh, "%s\n", "%a %d %b %Y %T %Z" ) == 18 ); /* date time format (%c) */
    TESTCASE( fprintf( fh, "%s\n", "%I:%M:%S" ) == 9 ); /* 12-hour time format (%r) */
    TESTCASE( fprintf( fh, "%s\n", "%d.%m.%Y" ) == 9 ); /* date format (%x) */
    TESTCASE( fprintf( fh, "%s\n", "%H:%M:%S" ) == 9 ); /* time format (%X) */

    TESTCASE( fprintf( fh, "%s\n", "" ) == 1 ); /* AM */
    TESTCASE( fprintf( fh, "%s\n", "" ) == 1 ); /* PM */
    fclose( fh );
    TESTCASE( ( lc = _PDCLIB_load_lc_time( "./", "test" ) ) );
    remove( "test_time.dat" );

    TESTCASE( strcmp( lc->month_name_abbr[ 0 ], "Jan" ) == 0 );
    TESTCASE( strcmp( lc->month_name_abbr[ 11 ], "Dez" ) == 0 );
    TESTCASE( strcmp( lc->month_name_full[ 0 ], "Januar" ) == 0 );
    TESTCASE( strcmp( lc->month_name_full[ 11 ], "Dezember" ) == 0 );
    TESTCASE( strcmp( lc->day_name_abbr[ 0 ], "So" ) == 0 );
    TESTCASE( strcmp( lc->day_name_abbr[ 6 ], "Sa" ) == 0 );
    TESTCASE( strcmp( lc->day_name_full[ 0 ], "Sonntag" ) == 0 );
    TESTCASE( strcmp( lc->day_name_full[ 6 ], "Samstag" ) == 0 );

#endif

    return TEST_RESULTS;
}

#endif
