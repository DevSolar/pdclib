/* _PDCLIB_bigint_from_dbl( _PDCLIB_bigint_t *, double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <string.h>

void _PDCLIB_bigint_from_dbl( _PDCLIB_bigint_t * fp, double d )
{
    int exp;
    int sign;

    memcpy( fp->data, &d, sizeof( double ) );
    sign = _PDCLIB_DBL_SIGN( fp->data );
    exp = _PDCLIB_DBL_EXP( fp->data );
    fp->size = _PDCLIB_DBL_SIZE( fp->data );
    fp->data[ fp->size ] = exp;
    fp->data[ fp->size + 1 ] = sign;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdio.h>

int main( void )
{
    _PDCLIB_bigint_t fp;
    _PDCLIB_bigint_t testdata[] =
    {
        { 4, { 0x6666u, 0x6666u, 0x6666u, 0x000fu, 0x0403u, 0x0000u } }
    };

    _PDCLIB_bigint_from_dbl( &fp, 31.4 );
    TESTCASE( _PDCLIB_bigint_cmp( &fp, &testdata[0] ) == 0 );
    TESTCASE( fp.data[4] == testdata[0].data[4] );
    TESTCASE( fp.data[5] == testdata[0].data[5] );

    return TEST_RESULTS;
}

#endif
