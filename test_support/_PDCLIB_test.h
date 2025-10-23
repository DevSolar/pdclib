
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
        long long observed = (long long)(x); \
        if ( observed != (long long)expected ) \
        { \
            TEST_RESULTS += 1; \
            printf( "    FAILED: " __FILE__ ", line %d (%s) - expected %lld, got %lld\n", __LINE__, #x, (long long)expected, observed ); \
        } \
    } while ( 0 )

#define TESTEQUALU( expected, x ) \
    do \
    { \
        unsigned long long observed = (unsigned long long)(x); \
        if ( observed != (unsigned long long)expected ) \
        { \
            TEST_RESULTS += 1; \
            printf( "    FAILED: " __FILE__ ", line %d (%s) - expected %llu, got %llu\n", __LINE__, #x, (unsigned long long)expected, observed ); \
        } \
    } while ( 0 )

#define TESTNEQ( unexpected, x ) \
    do \
    { \
        if ( (long long)(x) == unexpected ) \
        { \
            TEST_RESULTS += 1; \
            printf( "    FAILED: " __FILE__ ", line %d (%s) - got (unexpected) %lld\n", __LINE__, #x, (long long)unexpected ); \
        } \
    } while ( 0 )

#define TESTNEQU( unexpected, x ) \
    do \
    { \
        if ( (unsigned long long)(x) == unexpected ) \
        { \
            TEST_RESULTS += 1; \
            printf( "    FAILED: " __FILE__ ", line %d (%s) - got (unexpected) %llu\n", __LINE__, #x, (unsigned long long)unexpected ); \
        } \
    } while ( 0 )
