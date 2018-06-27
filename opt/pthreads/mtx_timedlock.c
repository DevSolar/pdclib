#ifndef REGTEST
#define _POSIX_C_SOURCE 2008098L
#include <threads.h>
// On Mac OS X, supress system definition of struct timespec
#ifdef __APPLE__
    #define _STRUCT_TIMESPEC struct timespec
#endif
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

/* Can only implement if timeouts are supported.
 *
 * Namely, Mac OS X does not implement timeouts
 */
#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS - 200112L) >= 0L
int mtx_timedlock(mtx_t *restrict mtx, const struct timespec *restrict ts)
{
    switch(pthread_mutex_timedlock(mtx, ts)) {
        case 0:
            return thrd_success;
        case ETIMEDOUT:
            return thrd_timeout;
        default:
            return thrd_error;
    }
}
#endif

#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    return TEST_RESULTS;
}

#endif
