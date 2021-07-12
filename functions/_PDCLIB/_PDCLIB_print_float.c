/* _PDCLIB_print_float

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

void _PDCLIB_print_float( long double value, struct _PDCLIB_status_t * status )
{
    /* TODO */
}

#endif

#ifdef TEST

#include <stddef.h>

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
#endif
    return TEST_RESULTS;
}

#endif

