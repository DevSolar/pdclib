/* _PDCLIB_print_fp_deci( _PDCLIB_bigint_t *, struct _PDCLIB_status_t *, char )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <assert.h>

void _PDCLIB_print_fp_deci( _PDCLIB_bigint_t * fp,
                            struct _PDCLIB_status_t * status,
                            char sign )
{
    if ( fp->size == 0 )
    {
        /* mant-in-buffer zero, exp10 zero, go format */
    }

    /*
    if ( status->prec < 0 )
    {
        assert( "Dragon 4 not yet implemented!" );
    }
    else...
    */
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( int argc, char * argv[] )
{
    /* Tested by _PDCLIB_print testdriver */
#ifndef REGTEST
#endif
    return TEST_RESULTS;
}

#endif
