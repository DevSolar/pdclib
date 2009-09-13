/* $Id$ */

/* PDCLib testing suite <_PDCLIB_test.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* Helper macros for test drivers                                             */
/* -------------------------------------------------------------------------- */

#include <stdio.h>

char const abcde[] = "abcde";
char const abcdx[] = "abcdx";
char const * teststring = "1234567890\nABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n";

int NO_TESTDRIVER = 0;

static int rc = 0;

#define TESTCASE( x ) if ( x ) {} \
                      else { rc += 1; printf( "FAILED: " __FILE__ ", line %d - " #x "\n", __LINE__ ); }

#ifndef REGTEST
#define TESTCASE_NOREG( x ) TESTCASE( x )
#else
#define TESTCASE_NOREG( x )
#endif

#define TEST_RESULTS  rc

