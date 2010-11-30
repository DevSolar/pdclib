/* $Id$ */

/* PDCLib testing suite <_PDCLIB_test.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* Helper macros for test drivers                                             */
/* -------------------------------------------------------------------------- */

#include <stdio.h>

static char const abcde[] = "abcde";
static char const abcdx[] = "abcdx";
static char const teststring[] = "1234567890\nABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n";
static char const testfile[]="testing/testfile";
static char const testfile1[]="testing/testfile1";
static char const testfile2[]="testing/testfile2";

#define NO_TESTDRIVER 0

static int TEST_RESULTS = 0;

#define TESTCASE( x ) if ( x ) {} \
                      else { TEST_RESULTS += 1; printf( "FAILED: " __FILE__ ", line %d - %s\n", __LINE__, #x ); }

#define TESTCASE_SPRINTF( x ) if ( strcmp( target, x ) == 0 ) {} \
                              else { TEST_RESULTS += 1; printf( "FAILED: " __FILE__ " (" _PDCLIB_FILEID "), line %d - \"%s\" != \"%s\"\n", __LINE__, target, x ); }

#ifndef REGTEST
#define TESTCASE_NOREG( x ) TESTCASE( x )
#else
#define TESTCASE_NOREG( x )
#endif
