/* _PDCLIB_strtod_main( const char *, char ** )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <limits.h>
#include <stdlib.h>

#ifndef REGTEST

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* This is a work in progress; this function will later serve as backend
   for strtof(), strtod() and strtold(), but is currently being implemented
   in terms of strtod() alone.
*/
static double _PDCLIB_strtod_main( const char * nptr, char ** endptr )
{
    double value = 0.0;
    int base = 0;
    char sign = '+';
    const char * dec_end;
    const char * frac_end;
    const char * exp_end;
    const char * p = _PDCLIB_strtox_prelim( nptr, &sign, &base );

    if ( endptr != NULL )
    {
        *endptr = (char *)nptr;
    }

    _PDCLIB_strtod_scan( p, &dec_end, &frac_end, &exp_end, base );

    //printf( "p: %s   base: %d   dec_end: %s   frac_end: %s   exp_end: %s\n", p, base, dec_end, frac_end, exp_end );

    switch ( base )
    {
        case 10:
            {
                uint64_t significand = 0;
                int exponent = 0;
                int exponent_shift = 0;
                int exponent_sign = 1;

                /* Infinity */
                if ( tolower( p[0] ) == 'i' && tolower( p[1] ) == 'n' && tolower( p[2] ) == 'f' )
                {
                    value = 1.0 / 0.0;

                    if ( sign == '-' )
                    {
                        value *= -1;
                    }

                    if ( endptr != NULL )
                    {
                        if ( tolower( p[3] ) == 'i' &&
                             tolower( p[4] ) == 'n' &&
                             tolower( p[5] ) == 'i' &&
                             tolower( p[6] ) == 't' &&
                             tolower( p[7] ) == 'y' )
                        {
                            *endptr = (char *)p + 8;
                        }
                        else
                        {
                            *endptr = (char *)p + 3;
                        }
                    }

                    return value;
                }

                /* Not a number */
                if ( tolower( p[0] ) == 'n' && tolower( p[1] ) == 'a' && tolower( p[2] ) == 'n' )
                {
                    value = 0.0 / 0.0;

                    if ( endptr != NULL )
                    {
                        p += 3;
                        *endptr = (char *)p;

                        if ( *p++ == '(' )
                        {
                            while ( isalnum( *p ) )
                            {
                                ++p;
                            }

                            if ( *p == ')' )
                            {
                                *endptr = (char *)p + 1;
                            }
                        }
                    }

                    return value;
                }

                /* TODO: out-of-range error handling */
                for ( const char * it = p; it != dec_end; ++it )
                {
                    significand = significand * 10 + (*it - '0');
                    if ( significand >= ((UINT64_MAX - 9) / 10) )
                    {
                        /* skip non-significant significand digits
                        ** (increase exponent by d to shift decimal left) */
                        exponent_shift += (int)( dec_end - it );
                        break;
                    }
                }

                /* if decimal point is present */
                if ( frac_end != dec_end )
                {
                    /* copy digits from after decimal to significand
                    ** (decrease exponent by d to shift decimal right) */
                    for ( const char * it = dec_end + 1; it != frac_end; ++it )
                    {
                        if ( significand < ((UINT64_MAX - 9) / 10) )
                        {
                            significand = significand * 10 + (*it - '0');
                            --exponent_shift;
                        }
                    }
                }

                /* if exponent is present */
                if ( exp_end != frac_end )
                {
                    const char * it = frac_end + 1;
                    if (*it == '-')
                    {
                        exponent_sign = -1;
                        ++it;
                    }
                    else if (*it == '+')
                    {
                        ++it;
                    }
                    for ( ; it != exp_end; ++it )
                    {
                        exponent = exponent < 10000 ? (exponent * 10 + (*it - '0')) : 10000;
                    }
                }

                if ( endptr != NULL )
                {
                    *endptr = (char *)exp_end;
                }

                if ( significand == 0 )
                {
                    return sign < 0 ? -0.0 : +0.0;
                }

                exponent = (exponent * exponent_sign) + exponent_shift;
                while ( exponent > 0 && significand < (UINT64_MAX / 10) )
                {
                    significand *= 10;
                    --exponent;
                }
                while ( exponent < 0 && (significand % 10) == 0 )
                {
                    significand /= 10;
                    ++exponent;
                }

                if ( exponent == 0 )
                {
                    value = significand;
                }
                else
                {
                    long double r = (long double)significand;
                    if ( exponent > 0 )
                    {
                        while ( exponent >= 100  ) { exponent -= 100; r *= 1.0e+100L; }
                        while ( exponent >= 10   ) { exponent -= 10;  r *= 1.0e+10L;  }
                        while ( exponent >= 1    ) { exponent -= 1;   r *= 1.0e+01L;  }
                    }
                    else
                    {
                        while ( exponent <= -100 ) { exponent += 100; r *= 1.0e-100L; }
                        while ( exponent <= -10  ) { exponent += 10;  r *= 1.0e-10L;  }
                        while ( exponent <= -1   ) { exponent += 1;   r *= 1.0e-01L;  }
                    }
                    if ( r > +1.7976931348623157081452742373e+308L )
                    {
                        value = 1.0e308*10.0; /* INFINITY */
                    }
                    else
                    {
                        value = (double)r;
                    }
                }

                if ( sign == '-' ) value = -value;

                return value;
            }
        case 16:
            {
                /* TODO: base-16 conversion */
            }
        default:
            {
                if ( endptr != NULL )
                {
                    *endptr = (char *)exp_end;
                }

                return 0.0;
            }
    }
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stddef.h>

#ifndef REGTEST
#define strtod _PDCLIB_strtod_main
#endif

int main( void )
{
    char * endptr;
    unsigned i;
    char const * tests[] =
    {
        "0.0", "+0.0", "-0.0",
        "0", "+0", "-0",
        "inf", "+inf", "-inf",
        "3.14", "+3.14", "-3.14",
        "45.1237e6", "+45.1237e+6", "-45.1237e-6",
        "0xa.bcdp+6", "+0x000.001p-1", "-0x12p4", "0x.123p-6", "0x123.p-5",
        ".123e-4", "123.e-4",
        ".e", ".", "",
        "foo",
        "0.5", "-0.5",
        "10", "20",
        "10.5"
    };
    double expected_doubles[] =
    {
        0x0p+0, 0x0p+0, -0x0p+0,
        0.0, 0.0, 0.0,
        ( 1.0 / 0.0 ), ( 1.0 / 0.0 ), ( -1.0 / 0.0 ),
        0x1.91eb851eb851fp+1, 0x1.91eb851eb851fp+1, -0x1.91eb851eb851fp+1,
        0x1.58443ap+25, 0x1.58443ap+25, -0x1.7a86686b4c9fep-15,
        0x1.579ap+9, 0x1p-13, -0x1.2p+8, 0x1.23p-10, 0x1.23p+3,
        0x1.9cb8320b1507p-17, 0x1.930be0ded288dp-7,
        0x0p+0, 0x0p+0, 0x0p+0,
        0.0,
        0.5, -0.5,
        10, 20,
        10.5,
    };
    ptrdiff_t expected_endptr[] =
    {
        3, 4, 4,
        1, 2, 2,
        3, 4, 4,
        4, 5, 5,
        9, 11, 11,
        10, 13, 7, 9, 9,
        7, 7,
        0, 0, 0,
        0,
        3, 4,
        2, 2,
        4,
    };
    char const * nan_tests[] =
    {
        "nan", "+nan", "-nan",
        "nan(foo)", "nan(foo", "nan(foo42bar)",
        "nan()", "nan(42)", "nan( )"
    };
    ptrdiff_t nan_expected_endptr[] =
    {
        3, 4, 4,
        8, 3, 13,
        5, 7, 3
    };

    for ( i = 0; i < sizeof( tests ) / sizeof( tests[0] ); ++i )
    {
        double d = strtod( tests[i], &endptr );
        TESTCASE( d == expected_doubles[i] );
        TESTCASE( ( endptr - tests[i] ) == expected_endptr[i] );
    }

    for ( i = 0; i < sizeof( nan_tests ) / sizeof( nan_tests[0] ); ++i )
    {
        double d = strtod( nan_tests[i], &endptr );
        TESTCASE( d != d );
        TESTCASE( ( endptr - nan_tests[i] ) == nan_expected_endptr[i] );
    }

    return TEST_RESULTS;
}

#endif
