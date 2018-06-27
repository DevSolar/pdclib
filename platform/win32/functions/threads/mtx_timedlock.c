#ifndef REGTEST
#include <threads.h>
#include <windows.h>
#include <stdint.h>

int mtx_timedlock(mtx_t *_PDCLIB_restrict mtx, 
                  const struct timespec *_PDCLIB_restrict until)
{
    DWORD myId = GetCurrentThreadId();

    if(mtx->_ThreadId == (long) myId) {
        mtx->_NestCount++;
        return thrd_success;
    }


    for(;;) {
        LONG prev = InterlockedCompareExchange(&mtx->_ThreadId, myId, 0);
        if(prev == 0)
            return thrd_success;

        struct timespec now;
        int32_t msToWait = 0;
        if(timespec_get(&now, TIME_UTC) != TIME_UTC) {
            // timespec_get must work!
            return thrd_error;
        } else {
            int64_t deltaSec  = (int64_t)until->tv_sec  - now.tv_sec;
            long    deltaNsec = (long)until->tv_nsec - now.tv_nsec;

            if(INT32_MAX / 2000U < deltaSec) {
                // Risk of overflow - do a shorter timeout on this iteration
                msToWait = INT32_MAX / 2;
            } else {
                msToWait = deltaSec * 1000 + deltaNsec / 1000;
            }
        }

        if(msToWait < 0) {
            return thrd_timeout;
        }

        DWORD rv = WaitForSingleObject(mtx->_WaitEvHandle, msToWait);
        if(rv != WAIT_OBJECT_0 && rv != WAIT_TIMEOUT)
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