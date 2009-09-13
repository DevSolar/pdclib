/* $Id$ */

/* strtoul( const char *, char * *, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <limits.h>
#include <stdlib.h>

#ifndef REGTEST

#include <stdint.h>

unsigned long int strtoul( const char * s, char ** endptr, int base )
{
    unsigned long int rc;
    char sign = '+';
    const char * p = _PDCLIB_strtox_prelim( s, &sign, &base );
    if ( base < 2 || base > 36 ) return 0;
    rc = (unsigned long int)_PDCLIB_strtox_main( &p, (unsigned)base, (uintmax_t)ULONG_MAX, (uintmax_t)( ULONG_MAX / base ), (int)( ULONG_MAX % base ), &sign );
    if ( endptr != NULL ) *endptr = ( p != NULL ) ? (char *) p : (char *) s;
    return ( sign == '+' ) ? rc : -rc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>
#include <errno.h>

int main( void )
{
    char * endptr;
    /* this, to base 36, overflows even a 256 bit integer */
    char overflow[] = "-ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ_";
    errno = 0;
    /* basic functionality */
    TESTCASE( strtoul( "123", NULL, 10 ) == 123 );
    /* proper detecting of default base 10 */
    TESTCASE( strtoul( "123", NULL, 0 ) == 123 );
    /* proper functioning to smaller base */
    TESTCASE( strtoul( "14", NULL, 8 ) == 12 );
    /* proper autodetecting of octal */
    TESTCASE( strtoul( "014", NULL, 0 ) == 12 );
    /* proper autodetecting of hexadecimal, lowercase 'x' */
    TESTCASE( strtoul( "0xFF", NULL, 0 ) == 255 );
    /* proper autodetecting of hexadecimal, uppercase 'X' */
    TESTCASE( strtoul( "0XFF", NULL, 0 ) == 255 );
    /* errno should still be 0 */
    TESTCASE( errno == 0 );
    /* overflowing subject sequence must still return proper endptr */
    TESTCASE( strtoul( overflow, &endptr, 36 ) == ULONG_MAX );
    TESTCASE( errno == ERANGE );
    TESTCASE( ( endptr - overflow ) == 53 );
    /* same for positive */
    errno = 0;
    TESTCASE( strtoul( overflow + 1, &endptr, 36 ) == ULONG_MAX );
    TESTCASE( errno == ERANGE );
    TESTCASE( ( endptr - overflow ) == 53 );
    /* testing skipping of leading whitespace */
    TESTCASE( strtoul( " \n\v\t\f123", NULL, 0 ) == 123 );
    /* testing conversion failure */
    TESTCASE( strtoul( overflow, &endptr, 10 ) == 0 );
    TESTCASE( endptr == overflow );
    endptr = NULL;
    TESTCASE( strtoul( overflow, &endptr, 0 ) == 0 );
    TESTCASE( endptr == overflow );
    return TEST_RESULTS;
}
#endif
