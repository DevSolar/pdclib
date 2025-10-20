
/* stdalign.h Tests

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdalign.h>

#ifdef TEST

#include "_PDCLIB_test.h"

struct test_struct
{
    char c;
    long long l;
    long double f;
};

#define LARGE_ALIGNMENT 128

int main( void )
{
    /* alignof must be a power of two */
    TESTNEQ( 0, alignof( int ) );
    TESTEQUAL( 0, ( alignof( int ) & ( alignof( int ) - 1 ) ) );

    /* alignment of struct must be the maximum alignment of its members */
    TESTEQUAL( alignof( long double ), alignof( struct test_struct ) );

    /* max_align_t must have the largest alignment requirement */
#if ( __STDC_VERSION__ + 0 ) >= 201112L
    TESTCASE( alignof( max_align_t ) >= alignof( struct test_struct ) );
    TESTCASE( alignof( max_align_t ) >= alignof( long long ) );
    TESTCASE( alignof( max_align_t ) >= alignof( long double ) );
#endif

    {
    /* large alignment */
    alignas( LARGE_ALIGNMENT ) struct test_struct aligned_struct;
    TESTEQUAL( LARGE_ALIGNMENT, alignof( aligned_struct ) );
    }

    {
    /* using alignof() as input to alignas() */
    alignas( alignof( double ) ) char aligned_char;
    TESTEQUAL( alignof( double ), alignof( aligned_char ) );
    }

    return TEST_RESULTS;
}

#endif
