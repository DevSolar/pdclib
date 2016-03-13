#ifndef REGTEST
#include <threads.h>
#include <windows.h>

int mtx_lock(mtx_t *mtx)
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

        DWORD rv = WaitForSingleObject(mtx->_WaitEvHandle, INFINITE);
        if(rv != WAIT_OBJECT_0)
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