/* cnd_destroy( cnd_t * cond )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <threads.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Implicitly casting the parameter. */
extern int pthread_cond_destroy( cnd_t * );

#ifdef __cplusplus
}
#endif

void cnd_destroy( cnd_t * cond )
{
    /* Could return EBUsY */
    pthread_cond_destroy( cond );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    TESTCASE( NO_TESTDRIVER );
#endif
    return TEST_RESULTS;
}

#endif
