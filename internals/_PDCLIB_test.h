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

int NO_TESTDRIVER = 0;

//#define BEGIN_TESTS   unsigned int rc = 0
static unsigned int rc = 0;
#define TESTCASE( x ) if ( x ) {} \
                      else { rc += 1; printf( "FAILED: " __FILE__ ", line %d - " #x "\n", __LINE__ ); }
#define TEST_RESULTS  rc
