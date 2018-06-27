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
#include <wchar.h>

/* Some strings used for <string.h> and <stdlib.h> testing. */
static char const abcde[] = "abcde";
static char const abcdx[] = "abcdx";
static char const teststring[] = "1234567890\nABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n";

static wchar_t const wabcde[] = L"abcde";
static wchar_t const wabcdx[] = L"abcdx";
static wchar_t const wteststring[] = L"1234567890\nABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n";

/* Temporary file names */
static char const testfile[]="testing/testfile";
static char const testfile1[]="testing/testfile1";
static char const testfile2[]="testing/testfile2";

#define NO_TESTDRIVER 0

static int TEST_RESULTS = 0;

/* TESTCASE() - generic test */
#define TESTCASE( x ) if ( x ) {} \
                      else { TEST_RESULTS += 1; printf( "FAILED: " __FILE__ ", line %d - %s\n", __LINE__, #x ); }

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

