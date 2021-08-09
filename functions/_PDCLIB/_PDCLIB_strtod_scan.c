/* _PDCLIB_strtod_scan( const char *, const char **, const char **, const char **, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <locale.h>
#include <stdlib.h>

/* This function scans a (potential) floating point input, determining
   where each part (decimal, fractional, exponent) ends. The actual
   values are discarded, as they need to be interpreted in floating
   point context, not integer.
*/
void _PDCLIB_strtod_scan( const char * s, const char ** dec, const char ** frac, const char ** exp, int base )
{
    char decimal_point = '.';
    struct lconv * lconv;

    if ( ( lconv = localeconv() ) != NULL )
    {
        decimal_point = *lconv->decimal_point;
    }

    strtol( (char *)s, (char **)dec, base );

    if ( **dec == decimal_point )
    {
        strtol( (char *)( *dec + 1 ), (char **)frac, base );

        if ( *dec == s && *frac == s + 1 )
        {
            *frac = s;
            *exp = s;
            return;
        }
    }
    else
    {
        /* no fractional part */
        *frac = *dec;
    }

    if ( base == 10 && ( **frac == 'e' || **frac == 'E' ) )
    {
        strtol( (char *)( *frac + 1 ), (char **)exp, base );
    }
    else if ( base == 16 && ( **frac == 'p' || **frac == 'P' ) )
    {
        strtol( (char *)( *frac + 1 ), (char **)exp, 10 );
    }
    else
    {
        /* no exponent part */
        *exp = *frac;
    }

    if ( *exp == *frac + 1 )
    {
        /* exponent "lead" ('e', 'p') but no digits */
        *exp = *frac;
    }

    return;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    const char * dec;
    const char * frac;
    const char * exp;
    const char * s[] =
        { "12.34e56", ".12e34", "98e76", "12.34", ".34", "18",
          "1.2e3", ".1e2", "1e2", "1.2", ".1", "1",
          ".", ".e", "e", "1.e", ".1e"
        };

    _PDCLIB_strtod_scan( s[0], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[0] + 2 );
    TESTCASE( frac == s[0] + 5 );
    TESTCASE( exp == s[0] + 8 );

    _PDCLIB_strtod_scan( s[1], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[1] );
    TESTCASE( frac == s[1] + 3 );
    TESTCASE( exp == s[1] + 6 );

    _PDCLIB_strtod_scan( s[2], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[2] + 2 );
    TESTCASE( frac == dec );
    TESTCASE( exp == s[2] + 5 );

    _PDCLIB_strtod_scan( s[3], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[3] + 2 );
    TESTCASE( frac == s[3] + 5 );
    TESTCASE( exp == s[3] + 5 );

    _PDCLIB_strtod_scan( s[4], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[4] );
    TESTCASE( frac == s[4] + 3 );
    TESTCASE( exp == s[4] + 3 );

    _PDCLIB_strtod_scan( s[5], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[5] + 2 );
    TESTCASE( frac == s[5] + 2 );
    TESTCASE( exp == s[5] + 2 );

    _PDCLIB_strtod_scan( s[6], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[6] + 1 );
    TESTCASE( frac == s[6] + 3 );
    TESTCASE( exp == s[6] + 5 );

    _PDCLIB_strtod_scan( s[7], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[7] );
    TESTCASE( frac == s[7] + 2 );
    TESTCASE( exp == s[7] + 4 );

    _PDCLIB_strtod_scan( s[8], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[8] + 1 );
    TESTCASE( frac == s[8] + 1 );
    TESTCASE( exp == s[8] + 3 );

    _PDCLIB_strtod_scan( s[9], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[9] + 1 );
    TESTCASE( frac == s[9] + 3 );
    TESTCASE( exp == s[9] + 3 );

    _PDCLIB_strtod_scan( s[10], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[10] );
    TESTCASE( frac == s[10] + 2 );
    TESTCASE( exp == s[10] + 2 );

    _PDCLIB_strtod_scan( s[11], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[11] + 1 );
    TESTCASE( frac == s[11] + 1 );
    TESTCASE( exp == s[11] + 1 );

    _PDCLIB_strtod_scan( s[12], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[12] );
    TESTCASE( frac == s[12] );
    TESTCASE( exp == s[12] );

    _PDCLIB_strtod_scan( s[13], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[13] );
    TESTCASE( frac == s[13] );
    TESTCASE( exp == s[13] );

    _PDCLIB_strtod_scan( s[14], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[14] );
    TESTCASE( frac == s[14] );
    TESTCASE( exp == s[14] );

    _PDCLIB_strtod_scan( s[15], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[15] + 1 );
    TESTCASE( frac == s[15] + 2 );
    TESTCASE( exp == s[15] + 2 );

    _PDCLIB_strtod_scan( s[16], &dec, &frac, &exp, 10 );
    TESTCASE( dec == s[16] );
    TESTCASE( frac == s[16] + 2 );
    TESTCASE( exp == s[16] + 2 );
#endif

    return TEST_RESULTS;
}

#endif
