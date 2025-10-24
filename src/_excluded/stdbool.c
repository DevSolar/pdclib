/* stdbool.h Tests

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef __VBCC__
#include <stdbool.h>
#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef __VBCC__
    bool b;

    b = true;
    TESTCASE( b );
    b = false;
    TESTCASE( !b );

    TESTCASE( true );
    TESTCASE( !false );

    TESTEQUAL( 1, __bool_true_false_are_defined );
#endif

    return TEST_RESULTS;
}

#endif
