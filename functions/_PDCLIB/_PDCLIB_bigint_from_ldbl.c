/* _PDCLIB_bigint_from_ldbl( _PDCLIB_bigint_t *, long double )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

#include <string.h>

void _PDCLIB_bigint_from_ldbl( _PDCLIB_bigint_t * fp, long double ld )
{
    int exp;
    int sign;

    memcpy( fp->data, &ld, sizeof( long double ) );
    sign = _PDCLIB_LDBL_SIGN( fp->data );
    exp = _PDCLIB_LDBL_EXP( fp->data );
    fp->size = _PDCLIB_LDBL_SIZE( fp->data );
    fp->data[ fp->size ] = exp;
    fp->data[ fp->size + 1 ] = sign;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdio.h>
#include <string.h>

int main( void )
{
    _PDCLIB_bigint_t fp;
    _PDCLIB_bigint_t testdata[] =
    {
        { 4, { 0x3000u, 0x3333u, 0x3333u, 0x7b33u, 0x4003u, 0x0001u } }
    };

    _PDCLIB_bigint_from_ldbl( &fp, -31.4 );
    TESTCASE( _PDCLIB_bigint_cmp( &fp, &testdata[0] ) == 0 );
    TESTCASE( fp.data[4] == testdata[0].data[4] );
    TESTCASE( fp.data[5] == testdata[0].data[5] );

    return TEST_RESULTS;
}

#endif
