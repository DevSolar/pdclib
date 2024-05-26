/* fesetround( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#if ! defined( __GNUC__ ) || defined( __clang__ )
/* GCC does not support #pragma STDC */
#pragma STDC FENV_ACCESS ON
#endif

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
                uint64_t fpu_control;
                __asm__ ( "mrs %0, fpcr" : "=r" ( fpu_control ) );
                fpu_control &= UINT64_C( 3 ) << 22;
                fpu_control |= round << 22;
                __asm__ ( "msr fpcr, %0" : : "r" ( fpu_control ) );
            }
#else
#error Platform not supported. Please add own port.
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

#include <float.h>

int main( void )
{
    TESTCASE( FLT_ROUNDS == 1 );
    TESTCASE( fegetround() == FE_TONEAREST );

    TESTCASE( fesetround( FE_TOWARDZERO ) == 0 );
    TESTCASE( fegetround() == FE_TOWARDZERO );
#if ! defined( __GNUC__ ) || defined( __clang__ )
    /* GCC Bug 30569 */
    /* https://stackoverflow.com/a/78533054/60281 */
    TESTCASE( FLT_ROUNDS == 0 );
#endif

    TESTCASE( fesetround( FE_UPWARD ) == 0 );
    TESTCASE( fegetround() == FE_UPWARD );
#if ! defined( __GNUC__ ) || defined( __clang__ )
    TESTCASE( FLT_ROUNDS == 2 );
#endif

    TESTCASE( fesetround( FE_DOWNWARD ) == 0 );
    TESTCASE( fegetround() == FE_DOWNWARD );
#if ! defined( __GNUC__ ) || defined( __clang__ )
    TESTCASE( FLT_ROUNDS == 3 );
#endif

    return TEST_RESULTS;
}

#endif
