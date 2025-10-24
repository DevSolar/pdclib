
/* stdnoreturn.h Tests

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef __VBCC__
#include <stdnoreturn.h>
#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* Really no way to test _Noreturn */
    return TEST_RESULTS;
}

#endif
