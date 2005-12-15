/* $Id$ */

/* Release $Name$ */

/* _PDCLIB_strtox_main( const char * *, int, _PDCLIB_uintmax_t, _PDCLIB_uintmax_t, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define _PDCLIB_INT_H _PDCLIB_INT_H
#include <_PDCLIB_int.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

_PDCLIB_uintmax_t _PDCLIB_strtox_main( const char ** p, int base, _PDCLIB_uintmax_t error, _PDCLIB_uintmax_t limval, _PDCLIB_uintmax_t limdigit, char * sign )
{
    _PDCLIB_uintmax_t rc = 0;
    int digit = -1;
    const char * x;
    while ( ( x = memchr( _PDCLIB_digits, toupper(**p), base ) ) != NULL )
    {
        digit = x - _PDCLIB_digits;
        if ( ( rc < limval ) || ( ( rc == limval ) && ( digit <= limdigit ) ) )
        {
            rc = rc * base + ( x - _PDCLIB_digits );
            ++(*p);
        }
        else
        {
            errno = ERANGE;
            /* TODO: Only if endptr != NULL - but do we really want *another* parameter? */
            while ( memchr( _PDCLIB_digits, **p, base ) != NULL ) ++(*p);
            /* TODO: This is ugly, but keeps caller from negating the error value */
            *sign = '+';
            return error;
        }
    }
    if ( digit == -1 )
    {
        *p = NULL;
        return 0;
    }
    return rc;
}

#ifdef TEST
#include <_PDCLIB_test.h>
#include <errno.h>

int main()
{
    const char * p;
    char test[] = "123_";
    char fail[] = "xxx";
    char sign = '-';
    BEGIN_TESTS;
    /* basic functionality */
    p = test;
    errno = 0;
    TESTCASE( _PDCLIB_strtox_main( &p, 10, 999, 12, 3, &sign ) == 123 );
    TESTCASE( errno == 0 );
    TESTCASE( p == &test[3] );
    /* proper functioning to smaller base */
    p = test;
    TESTCASE( _PDCLIB_strtox_main( &p, 8, 999, 12, 3, &sign ) == 0123 );
    TESTCASE( errno == 0 );
    TESTCASE( p == &test[3] );
    /* overflowing subject sequence must still return proper endptr */
    p = test;
    TESTCASE( _PDCLIB_strtox_main( &p, 4, 999, 1, 2, &sign ) == 999 );
    TESTCASE( errno == ERANGE );
    TESTCASE( p == &test[3] );
    TESTCASE( sign == '+' );
    /* testing conversion failure */
    errno = 0;
    p = fail;
    sign = '-';
    TESTCASE( _PDCLIB_strtox_main( &p, 10, 999, 99, 8, &sign ) == 0 );
    TESTCASE( p == NULL );
    return TEST_RESULTS;
}

#endif
