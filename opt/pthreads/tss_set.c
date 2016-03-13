#ifndef REGTEST
#include <threads.h>
#include <pthread.h>

int tss_set(tss_t key, void *val)
{
    switch(pthread_setspecific(key, val)) {
    case 0:
        return thrd_success;
    default:
        return thrd_error;
    }
}
#endif

#ifdef TEST
#include "_PDCLIB_test.h"

/* Tested in tss_get.c */
int main( void )
{
    return TEST_RESULTS;
}

#endif
