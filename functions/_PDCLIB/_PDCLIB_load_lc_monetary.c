/* _PDCLIB_load_lc_monetary( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pdclib/_PDCLIB_int.h"

bool _PDCLIB_load_lc_monetary( const char * path, const char * locale )
{
    bool rc = false;
    const char * extension = "_monetary.dat";
    char * file = malloc( strlen( path ) + strlen( locale ) + strlen( extension ) + 1 );

    if ( file )
    {
        FILE * fh;

        strcpy( file, path );
        strcat( file, locale );
        strcat( file, extension );

        if ( ( fh = fopen( file, "rb" ) ) != NULL )
        {
            char buffer[ 14 ];
            char * data = _PDCLIB_load_lines( fh, 7 );

            if ( data != NULL )
            {
                if ( fread( buffer, 1, 14, fh ) == 14 )
                {
                    _PDCLIB_lc_numeric_monetary.monetary_alloced = 1;
                    _PDCLIB_lc_numeric_monetary.lconv->mon_decimal_point = data;
                    data += strlen( data ) + 1;
                    _PDCLIB_lc_numeric_monetary.lconv->mon_thousands_sep = data;
                    data += strlen( data ) + 1;
                    _PDCLIB_lc_numeric_monetary.lconv->mon_grouping = data;
                    data += strlen( data ) + 1;
                    _PDCLIB_lc_numeric_monetary.lconv->positive_sign = data;
                    data += strlen( data ) + 1;
                    _PDCLIB_lc_numeric_monetary.lconv->negative_sign = data;
                    data += strlen( data ) + 1;
                    _PDCLIB_lc_numeric_monetary.lconv->currency_symbol = data;
                    data += strlen( data ) + 1;
                    _PDCLIB_lc_numeric_monetary.lconv->int_curr_symbol = data;

                    _PDCLIB_lc_numeric_monetary.lconv->frac_digits = buffer[ 0 ];
                    _PDCLIB_lc_numeric_monetary.lconv->p_cs_precedes = buffer[ 1 ];
                    _PDCLIB_lc_numeric_monetary.lconv->n_cs_precedes = buffer[ 2 ];
                    _PDCLIB_lc_numeric_monetary.lconv->p_sep_by_space = buffer[ 3 ];
                    _PDCLIB_lc_numeric_monetary.lconv->n_sep_by_space = buffer[ 4 ];
                    _PDCLIB_lc_numeric_monetary.lconv->p_sign_posn = buffer[ 5 ];
                    _PDCLIB_lc_numeric_monetary.lconv->n_sign_posn = buffer[ 6 ];
                    _PDCLIB_lc_numeric_monetary.lconv->int_frac_digits = buffer[ 7 ];
                    _PDCLIB_lc_numeric_monetary.lconv->int_p_cs_precedes = buffer[ 8 ];
                    _PDCLIB_lc_numeric_monetary.lconv->int_n_cs_precedes = buffer[ 9 ];
                    _PDCLIB_lc_numeric_monetary.lconv->int_p_sep_by_space = buffer[ 10 ];
                    _PDCLIB_lc_numeric_monetary.lconv->int_n_sep_by_space = buffer[ 11 ];
                    _PDCLIB_lc_numeric_monetary.lconv->int_p_sign_posn = buffer[ 12 ];
                    _PDCLIB_lc_numeric_monetary.lconv->int_n_sign_posn= buffer[ 13 ];

                    rc = true;
                }
                else
                {
                    free( data );
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
    FILE * fh = fopen( "test_monetary.dat", "wb" );
    struct lconv * lc;
    TESTCASE( fh != NULL );
    fprintf( fh, "%s\n", "," );    /* mon_decimal_point */
    fprintf( fh, "%s\n", "." );    /* mon_thousands_sep */
    fprintf( fh, "%s\n", "3" );    /* mon_grouping */
    fprintf( fh, "%s\n", "" );     /* positive_sign */
    fprintf( fh, "%s\n", "-" );    /* negative_sign */
    fprintf( fh, "%s\n", "\xa4" ); /* currency_symbol */
    fprintf( fh, "%s\n", "EUR" );  /* int_curr_symbol */
    fputc( 2, fh ); /* frac_digits */
    fputc( 0, fh ); /* p_cs_precedes */
    fputc( 0, fh ); /* n_cs_precedes */
    fputc( 1, fh ); /* p_sep_by_space */
    fputc( 1, fh ); /* n_sep_by_space */
    fputc( 1, fh ); /* p_sign_posn */
    fputc( 1, fh ); /* n_sign_posn */
    fputc( 2, fh ); /* int_frac_digits */
    fputc( 0, fh ); /* int_p_cs_precedes */
    fputc( 0, fh ); /* int_n_cs_precedes */
    fputc( 1, fh ); /* int_p_sep_by_space */
    fputc( 1, fh ); /* int_n_sep_by_space */
    fputc( 1, fh ); /* int_p_sign_posn */
    fputc( 1, fh ); /* int_n_sign_posn */
    fprintf( fh, "\n" );
    fclose( fh );
    TESTCASE( _PDCLIB_load_lc_monetary( "./", "test" ) );
    remove( "test_monetary.dat" );
    lc = localeconv();
    TESTCASE( strcmp( lc->mon_decimal_point, "," ) == 0 );
    TESTCASE( strcmp( lc->mon_thousands_sep, "." ) == 0 );
    TESTCASE( strcmp( lc->mon_grouping, "3" ) == 0 );
    TESTCASE( strcmp( lc->positive_sign, "" ) == 0 );
    TESTCASE( strcmp( lc->negative_sign, "-" ) == 0 );
    TESTCASE( strcmp( lc->currency_symbol, "\xa4" ) == 0 );
    TESTCASE( strcmp( lc->int_curr_symbol, "EUR" ) == 0 );

    TESTCASE( lc->frac_digits == 2 );
    TESTCASE( lc->p_cs_precedes == 0 );
    TESTCASE( lc->n_cs_precedes == 0 );
    TESTCASE( lc->p_sep_by_space == 1 );
    TESTCASE( lc->n_sep_by_space == 1 );
    TESTCASE( lc->p_sign_posn == 1 );
    TESTCASE( lc->n_sign_posn == 1 );
    TESTCASE( lc->int_frac_digits == 2 );
    TESTCASE( lc->int_p_cs_precedes == 0 );
    TESTCASE( lc->int_n_cs_precedes == 0 );
    TESTCASE( lc->int_p_sep_by_space == 1 );
    TESTCASE( lc->int_n_sep_by_space == 1 );
    TESTCASE( lc->int_p_sign_posn == 1 );
    TESTCASE( lc->int_n_sign_posn == 1 );
#endif

    return TEST_RESULTS;
}

#endif
