#ifndef REGTEST
#define _POSIX_C_SOURCE 2008098L
#include <threads.h>
#include <pthread.h>

int mtx_init(mtx_t *mtx, int type)
{
    if(type == mtx_plain || type == mtx_timed) {
        if(pthread_mutex_init(mtx, NULL) == 0)
            return thrd_success;
        else
            return thrd_error;

    } else if (type == mtx_recursive || type == (mtx_recursive | mtx_timed)) {
        int rc = thrd_error;
        pthread_mutexattr_t attr;

        if(pthread_mutexattr_init(&attr))
            goto cleanup1;

        if(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE))
            goto cleanup2;

        if(pthread_mutex_init(mtx, &attr) == 0)
            rc = thrd_success;

    cleanup2:
        pthread_mutexattr_destroy(&attr);
    cleanup1:
        return rc;
    } else {
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
