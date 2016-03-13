#ifndef REGTEST
#include <threads.h>
#include <pthread.h>

int tss_create(tss_t *key, tss_dtor_t dtor)
{
    switch(pthread_key_create(key, dtor)) {
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
