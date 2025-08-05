/* _PDCLIB_bigint_from_pow10( bigint_t *, unsigned )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

void _PDCLIB_bigint_from_pow10( _PDCLIB_bigint_t * bigint, unsigned pow )
{
    _PDCLIB_bigint_t powers_of_10[] =
    {
        {   1, { 0x0001u } },
        {   1, { 0x000au } },
        {   1, { 0x0064u } },
        {   1, { 0x03e8u } },
        {   1, { 0x2710u } },
        {   2, { 0x86a0u, 0x0001u } },
        {   2, { 0x4240u, 0x000fu } },
        {   2, { 0x9680u, 0x0098u } },
        {   2, { 0xe100u, 0x05f5u } },
        {   4, { 0x0000u, 0x6fc1u, 0x86f2u, 0x0023u } },
        {   7, { 0x0000u, 0x0000u, 0xef81u, 0x85acu,
                 0x415bu, 0x2d6du, 0x04eeu } },
        {  14, { 0x0000u, 0x0000u, 0x0000u, 0x0000u,
                 0x1f01u, 0xbf6au, 0xed64u, 0x6e38u,
                 0x97edu, 0xdaa7u, 0xf9f4u, 0xe93fu,
                 0x4f03u, 0x0018u } },
        {  27, { 0x0000u, 0x0000u, 0x0000u, 0x0000u, 
                 0x0000u, 0x0000u, 0x0000u, 0x0000u, 
                 0x3e01u, 0x2e95u, 0x9909u, 0x03dfu, 
                 0x38fdu, 0x0f15u, 0xe42fu, 0x2374u, 
                 0xf5ecu, 0xd3cfu, 0xdc08u, 0xc404u, 
                 0xb0dau, 0xbccdu, 0x7f19u, 0xa633u, 
                 0x2603u, 0xe91fu, 0x024eu } },
        {  54, { 0x0000u, 0x0000u, 0x0000u, 0x0000u, 
                 0x0000u, 0x0000u, 0x0000u, 0x0000u, 
                 0x0000u, 0x0000u, 0x0000u, 0x0000u, 
                 0x0000u, 0x0000u, 0x0000u, 0x0000u, 
                 0x7c01u, 0x982eu, 0x875bu, 0xbed3u, 
                 0x9f72u, 0xd8d9u, 0x2f87u, 0x1215u, 
                 0x50c6u, 0x6bdeu, 0x6e70u, 0xcf4au, 
                 0xd80fu, 0xd595u, 0x716eu, 0x26b2u, 
                 0x66b0u, 0xadc6u, 0x3624u, 0x1d15u, 
                 0xd35au, 0x3c42u, 0x540eu, 0x63ffu, 
                 0x73c0u, 0xcc55u, 0xef17u, 0x65f9u, 
                 0x28f2u, 0x55bcu, 0xc7f7u, 0x80dcu, 
                 0xeddcu, 0xf46eu, 0xefceu, 0x5fdcu, 
                 0x53f7u, 0x0005u } }
    };

    _PDCLIB_size_t index = 8;

    _PDCLIB_bigint_from_bigint( bigint, &powers_of_10[ pow & 7 ] );
    pow >>= 3;

    while ( pow > 0 )
    {
        if ( pow & 1 )
        {
            _PDCLIB_bigint_mul( bigint, &powers_of_10[ index ] );
        }

        pow >>= 1;
        ++index;
    }
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t bigint;

    _PDCLIB_bigint_from_pow10( &bigint, 0 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 1 );

    _PDCLIB_bigint_from_pow10( &bigint, 1 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 10 );

    _PDCLIB_bigint_from_pow10( &bigint, 2 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 100 );

    _PDCLIB_bigint_from_pow10( &bigint, 3 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 1000 );

    _PDCLIB_bigint_from_pow10( &bigint, 4 );
    TESTCASE( bigint.size == 1 );
    TESTCASE( bigint.data[0] == 10000 );

    _PDCLIB_bigint_from_pow10( &bigint, 5 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[1] == 1 );
    TESTCASE( bigint.data[0] == 34464 );

    _PDCLIB_bigint_from_pow10( &bigint, 6 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[1] == 15 );
    TESTCASE( bigint.data[0] == 16960 );

    _PDCLIB_bigint_from_pow10( &bigint, 7 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[1] == 152 );
    TESTCASE( bigint.data[0] == 38528 );

    _PDCLIB_bigint_from_pow10( &bigint, 8 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[1] == 1525 );
    TESTCASE( bigint.data[0] == 57600 );

    _PDCLIB_bigint_from_pow10( &bigint, 9 );
    TESTCASE( bigint.size == 2 );
    TESTCASE( bigint.data[1] == 15258 );
    TESTCASE( bigint.data[0] == 51712 );
#endif

    return TEST_RESULTS;
}

#endif
