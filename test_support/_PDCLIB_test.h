/* PDCLib testing suite <_PDCLIB_test.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* Helper macros for test drivers                                             */
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

/* Some strings used for <string.h> and <stdlib.h> testing. */
static const char abcde[] = "abcde";
static const char abcdx[] = "abcdx";
static const char teststring[] = "1234567890\nABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n";

/* Temporary file names */
static const char testfile[] = "test_support/testfile";
static const char testfile1[] = "test_support/testfile1";
static const char testfile2[] = "test_support/testfile2";

#ifndef NO_TESTDRIVER
#define NO_TESTDRIVER 0
#endif

static int TEST_RESULTS = 0;

/* TESTCASE() - generic test */
#define TESTCASE( x ) \
    if ( x ) \
    { \
        /* EMPTY */ \
    } \
    else \
    { \
       TEST_RESULTS += 1; \
       printf( "FAILED: " __FILE__ ", line %d - %s\n", __LINE__, #x ); \
    }

/* TESTCASE_NOREG() - PDCLib-only test */
#ifndef REGTEST
    #define TESTCASE_NOREG( x ) TESTCASE( x )
#else
    #define TESTCASE_NOREG( x )
#endif

/* Include printf() / scanf() test macros if required */

#if defined( _PDCLIB_FILEIO ) || defined( _PDCLIB_STRINGIO )
#include "_PDCLIB_iotest.h"
#endif

/* Helper macro to fill a struct tm */
#define MKTIME( tm, sec, min, hour, day, month, year, wday, yday ) tm.tm_sec = sec; tm.tm_min = min; tm.tm_hour = hour; tm.tm_mday = day; tm.tm_mon = month; tm.tm_year = year; tm.tm_wday = wday; tm.tm_yday = yday; tm.tm_isdst = -1;

