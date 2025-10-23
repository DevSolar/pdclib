/* limits.h Tests

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <limits.h>

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* The tests are actually much more restrictive / less portable than
       PDCLib's setup of limits.h, since they assume 8-bit chars and two's
       complement encoding.
       At least the tests failing on an exotic hardware will remind you
       PDCLib has not been tested like that before.
    */
    TESTEQUAL( 8, CHAR_BIT );

    TESTEQUAL( 127, SCHAR_MAX );
    TESTEQUAL( -128, SCHAR_MIN );
    TESTEQUAL( 255, UCHAR_MAX );

#if CHAR_MIN < 0
    TESTEQUAL( 127, CHAR_MAX );
    TESTEQUAL( -128, CHAR_MIN );
#else
    TESTEQUAL( 255, CHAR_MAX );
    TESTEQUAL( 0, CHAR_MIN );
#endif

    TESTEQUAL( 32767, SHRT_MAX );
    TESTEQUAL( -32768, SHRT_MIN );
    TESTEQUAL( 65535U, USHRT_MAX );

#if INT_MAX == SHRT_MAX
    TESTEQUAL( 32767, INT_MAX );
    TESTEQUAL( -32768, INT_MIN );
    TESTEQUAL( 65535U, UINT_MAX );
#else
    TESTEQUAL( 2147483647, INT_MAX );
    TESTEQUAL( -2147483648, INT_MIN );
    TESTEQUAL( 4294967295U, UINT_MAX );
#endif

#if LONG_MAX == INT_MAX
    TESTEQUAL( 2147483647, LONG_MAX );
    TESTEQUAL( -2147483648, LONG_MIN );
    TESTEQUALU( 4294967295U, ULONG_MAX );
#else
    TESTEQUAL( 9223372036854775807L, LONG_MAX );
    TESTEQUAL( -9223372036854775807L - 1, LONG_MIN );
    TESTEQUALU( 18446744073709551615UL, ULONG_MAX );
#endif

    TESTEQUAL( 9223372036854775807LL, LLONG_MAX );
    TESTEQUAL( -9223372036854775807LL - 1, LLONG_MIN );
    TESTEQUALU( 18446744073709551615ULL, ULLONG_MAX );

    return TEST_RESULTS;
}

#endif
