/* localeconv( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <locale.h>

#ifndef REGTEST

struct lconv * localeconv( void )
{
    return _PDCLIB_lc_numeric_monetary.lconv;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    struct lconv * lconv;
    TESTCASE( ( lconv = localeconv() ) != NULL );
    TESTCASE( strcmp( lconv->decimal_point, "." ) == 0 );
    TESTCASE( strcmp( lconv->thousands_sep, "" ) == 0 );
    printf( "lconv->grouping: \"%s\" (%02hhx %02hhx)\n", lconv->grouping, lconv->grouping[0], lconv->grouping[1] );
    TESTCASE( ( strlen( lconv->grouping ) == 0 ) || ( ( strlen( lconv->grouping ) == 1 ) && ( lconv->grouping[0] == CHAR_MAX ) ) );
    return TEST_RESULTS;
}

#endif
