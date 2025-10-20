
/* PDCLib testing suite <_PDCLIB_test.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* Helper macros for test drivers                                             */
/* -------------------------------------------------------------------------- */

#ifndef NO_TESTDRIVER
#define NO_TESTDRIVER 0
#endif

static int TEST_RESULTS = 0;

extern int printf( char const *, ... );

#define TESTCASE( x ) \
    do \
    if ( ! ( x ) ) \
    { \
        TEST_RESULTS += 1; \
        printf( "    FAILED: " __FILE__ ", line %d (%s) - evaluated false\n", __LINE__, #x ); \
    } while( 0 )

#define TESTEQUAL( expected, x ) \
    do \
    { \
        int observed = (int)(x); \
        if ( observed != expected ) \
        { \
            TEST_RESULTS += 1; \
            printf( "    FAILED: " __FILE__ ", line %d (%s) - expected %d, got %d\n", __LINE__, #x, (int)expected, (int)observed ); \
        } \
    } while ( 0 )

#define TESTNEQ( unexpected, x ) \
    do \
    { \
        if ( (int)(x) == unexpected ) \
        { \
            TEST_RESULTS += 1; \
            printf( "    FAILED: " __FILE__ ", line %d (%s) - got (unexpected) %d\n", __LINE__, #x, (int)unexpected ); \
        } \
    } while ( 0 )
