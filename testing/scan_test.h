/* $Id$ */

/* scan test header

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <string.h>
#include <limits.h>

#define CHECK_FEQUAL( a, b, T, F ) do { T x = a; T y = b; TESTCASE( x == y ); } while ( 0 )

