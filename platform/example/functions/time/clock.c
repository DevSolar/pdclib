/* clock( void )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>

#ifndef REGTEST

#include "sys/times.h"

clock_t clock( void )
{
    struct tms buf;

    if ( times( &buf ) != ( clock_t )-1 )
    {
        return buf.tms_utime + buf.tms_stime;
    }

    return -1;
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
