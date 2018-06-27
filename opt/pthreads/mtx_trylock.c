#ifndef REGTEST
#include <threads.h>
#include <pthread.h>
#include <errno.h>

int mtx_trylock(mtx_t *mtx)
{
    switch(pthread_mutex_trylock(mtx)) {
        case 0:
            return thrd_success;
        case EBUSY:
            return thrd_busy;
        default:
            return thrd_error;
    }
}
#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    return TEST_RESULTS;
}

#endif
