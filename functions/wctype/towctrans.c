/* towctrans( wint_t, wctrans_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wctype.h>
#ifndef REGTEST
#include <string.h>
#include <_PDCLIB_locale.h>

wint_t towctrans( wint_t wc, wctrans_t trans )
{
    switch( trans ) {
        case 0:                         return wc;
        case _PDCLIB_WCTRANS_TOLOWER:   return towlower( wc );
        case _PDCLIB_WCTRANS_TOUPPER:   return towupper( wc );
        default: abort();
    }
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE(towctrans(L'a', wctrans("toupper")) == L'A');
    TESTCASE(towctrans(L'B', wctrans("toupper")) == L'B');
    TESTCASE(towctrans(L'a', wctrans("tolower")) == L'a');
    TESTCASE(towctrans(L'B', wctrans("tolower")) == L'b');
    TESTCASE(towctrans(L'B', wctrans("invalid")) == L'B');
    TESTCASE(towctrans(L'B', 0)                  == L'B');
    return TEST_RESULTS;
}
#endif
