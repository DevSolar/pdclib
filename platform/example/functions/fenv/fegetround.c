/* int fegetround( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdint.h>
#include <fenv.h>

#ifndef REGTEST

int fegetround( void )
{
#ifdef __x86_64__
    uint16_t fpu_control;
    __asm__ ( "fnstcw %0" : "=m" (fpu_control) );
    return ( fpu_control & UINT16_C( 0x0c00 ) ) >> 10;
#elif __aarch64__
    uint32_t fpu_control;
    __asm__ __volatile__ ( "mrs %0, fpcr" : "=r" (fpu_control) );
    return ( fpu_control & UINT32_C( 0x00c00000 ) ) >> 22;
#else
#error Platform not supported.
#endif
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
