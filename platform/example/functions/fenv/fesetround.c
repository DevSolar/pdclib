/* fesetround( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <fenv.h>
#include <stdint.h>

#ifndef REGTEST

int fesetround( int round )
{
    switch ( round )
    {
#ifdef FE_TONEAREST
        case FE_TONEAREST:
#endif
#ifdef FE_UPWARD
        case FE_UPWARD:
#endif
#ifdef FE_DOWNWARD
        case FE_DOWNWARD:
#endif
#ifdef FE_TRUNCATE
        case FE_TRUNCATE:
#endif
#ifdef __x86_64__
            {
                uint16_t fpu_control;
                __asm__ ( "fnstcw %0" : "=m" ( fpu_control ) );
                fpu_control &= UINT16_C( 3 ) << 10;
                fpu_control |= round << 10;
                __asm__ ( "fldcw %0" : : "m" ( fpu_control ) );
            }
            {
                uint32_t sse_control;
                __asm__ ( "stmxcsr %0" : "=m" ( sse_control ) );
                sse_control &= UINT32_C( 3 ) << 13;
                sse_control |= round << 13;
                __asm__ ( "ldmxcsr %0" : : "m" ( sse_control ) );
            }
#elif __aarch64__
            {
                uint32_t fpu_control;
                __asm__ ( "mrs %0, fpcr" : "=r" ( fpu_control ) );
                fpu_control &= UINT32_C( 3 ) << 22;
                fpu_control |= round << 22;
                __asm__ ( "msr fpcr, %0" : : "r" ( fpu_control ) );
            }
#else
#error Platform not supported.
#endif
            return 0;
        default:
            // Invalid argument
            return -1;
    }
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
