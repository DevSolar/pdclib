/* $Id$ */

/* PDCLib testing suite <_PDCLIB_test.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* Helper macros for test drivers                                             */
/* -------------------------------------------------------------------------- */

#include <stdio.h>

/* Some strings used for <string.h> and <stdlib.h> testing. */
static char const abcde[] = "abcde";
static char const abcdx[] = "abcdx";
static char const teststring[] = "1234567890\nABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n";

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

/* ...printf() tests */
#if defined( FPRINTF_FUNCTION )
static char result_buffer[ 1000 ];
#define RESULT_MISMATCH( act, exp ) \
    rewind( act ), \
    result_buffer[ fread( result_buffer, 1, strlen( exp ) + 1, act ) ] = '\0', \
    rewind( act ), \
    memcmp( result_buffer, exp, strlen( exp ) )
#define RESULT_STRING( tgt ) result_buffer
#elif defined( SPRINTF_FUNCTION )
#define RESULT_MISMATCH( act, exp ) strcmp( act, exp ) != 0
#define RESULT_STRING( tgt ) tgt
#endif

#define PRINTF_TEST( expected_rc, expected_string, format, ... ) { \
        int actual_rc = testprintf( target, format, __VA_ARGS__ ); \
        if ( ( actual_rc != expected_rc ) || \
             ( RESULT_MISMATCH( target, expected_string ) ) ) \
        { \
            ++TEST_RESULTS; \
            fprintf( stderr, "FAILED: " __FILE__ " (" _PDCLIB_FILEID "), line %d\n        expected %2d, \"%s\"\n        actual   %2d, \"%s\"\n", __LINE__, expected_rc, expected_string, actual_rc, RESULT_STRING( target ) ); \
        } \
    } while ( 0 )

/* ...scanf() tests */
/* TODO: t.b.d. */
