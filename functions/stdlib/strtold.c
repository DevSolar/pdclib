/* strtold( const char *, char ** )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <float.h>

long double strtold( const char * s, char ** endptr )
{
    long double rc = 0;
    char sign = '+';
    int base = _PDCLIB_strtod_prelim( s, &sign, endptr );

    s = *endptr;

    switch ( base )
    {
        case -2:
            rc = 0.0/0.0 * -1;
            break;
        case -1:
            /* INF */
            rc = LDBL_MAX * 2;
            break;
        case 0:
            /* No match */
            break;
        case 10:
            rc = (long double)_PDCLIB_naive_etod( s, endptr );
            break;
        case 16:
            rc = (long double)_PDCLIB_naive_ptod( s, endptr );
            break;
    }

    if ( sign == '-' )
    {
        rc *= -1.0;
    }

    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <errno.h>
#include <float.h>
#include <stddef.h>

typedef struct
{
    const char * s;
    long double d;
    ptrdiff_t l;
} testdata_t;

int main( void )
{
    long double d;
    char * s;
    testdata_t testdata[] =
    {
        { "123", 123.0, 3 },
        { "123.45", 123.45, 6 },
        { ".45", 0.45, 3 },
        { "123.", 123, 4 },
        { "  -0123f", -123.0, 7 },
        { " -.45", -0.45, 5 },
        { " 0.a", 0.0, 3 },
        { "1.23e2", 123.0, 6 },
        { "1.23e-2", 0.0123, 7 },
        { "-0.000123e+6", -123.0, 12 },
        { "-123000e-3", -123, 10 },
        { "-123e-003", -0.123, 9 },
        { " infx", LDBL_MAX * 2, 4 },
        { " nanx", 0.0 / 0.0 * -1, 4 },
        { " -infx", LDBL_MAX * 2 * -1, 5 },
        { " -nanx", 0.0 / 0.0, 5 },
        { " nan(foo)", 0.0 / 0.0 * -1, 9 },
        { " nan(foo", 0.0 / 0.0 * -1, 4 }
    };

    d = strtod( testdata[0].s, &s );
    TESTCASE( d == testdata[0].d );
    TESTCASE( (s - testdata[0].s) == testdata[0].l );

    d = strtod( testdata[1].s, &s );
    TESTCASE( d == testdata[1].d );
    TESTCASE( (s - testdata[1].s) == testdata[1].l );

    d = strtod( testdata[2].s, &s );
    TESTCASE( d == testdata[2].d );
    TESTCASE( (s - testdata[2].s) == testdata[2].l );

    d = strtod( testdata[3].s, &s );
    TESTCASE( d == testdata[3].d );
    TESTCASE( (s - testdata[3].s) == testdata[3].l );

    d = strtod( testdata[4].s, &s );
    TESTCASE( d == testdata[4].d );
    TESTCASE( (s - testdata[4].s) == testdata[4].l );

    d = strtod( testdata[5].s, &s );
    TESTCASE( d == testdata[5].d );
    TESTCASE( (s - testdata[5].s) == testdata[5].l );

    d = strtod( testdata[6].s, &s );
    TESTCASE( d == testdata[6].d );
    TESTCASE( (s - testdata[6].s) == testdata[6].l );

    d = strtod( testdata[7].s, &s );
    TESTCASE( d == testdata[7].d );
    TESTCASE( (s - testdata[7].s) == testdata[7].l );

    d = strtod( testdata[8].s, &s );
    TESTCASE( d == testdata[8].d );
    TESTCASE( (s - testdata[8].s) == testdata[8].l );

    d = strtod( testdata[9].s, &s );
    TESTCASE( d == testdata[9].d );
    TESTCASE( (s - testdata[9].s) == testdata[9].l );

    d = strtod( testdata[10].s, &s );
    TESTCASE( d == testdata[10].d );
    TESTCASE( (s - testdata[10].s) == testdata[10].l );

    d = strtod( testdata[11].s, &s );
    TESTCASE( d == testdata[11].d );
    TESTCASE( (s - testdata[11].s) == testdata[11].l );

    d = strtod( testdata[12].s, &s );
    TESTCASE( d == testdata[12].d );
    TESTCASE( (s - testdata[12].s) == testdata[12].l );

    d = strtod( testdata[13].s, &s );
    TESTCASE( d != d );
    TESTCASE( (s - testdata[13].s) == testdata[13].l );

    d = strtod( testdata[14].s, &s );
    TESTCASE( d == testdata[14].d );
    TESTCASE( (s - testdata[14].s) == testdata[14].l );

    d = strtod( testdata[15].s, &s );
    TESTCASE( d != d );
    TESTCASE( (s - testdata[15].s) == testdata[15].l );

    d = strtod( testdata[16].s, &s );
    TESTCASE( d != d );
    TESTCASE( (s - testdata[16].s) == testdata[16].l );

    d = strtod( testdata[17].s, &s );
    TESTCASE( d != d );
    TESTCASE( (s - testdata[17].s) == testdata[17].l );

    return TEST_RESULTS;
}

#endif
