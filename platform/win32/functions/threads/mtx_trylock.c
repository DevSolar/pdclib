#ifndef REGTEST
#include <threads.h>
#include <windows.h>

int mtx_trylock(mtx_t *mtx)
{
    DWORD myId = GetCurrentThreadId();

    if(mtx->_ThreadId == (long) myId) {
        mtx->_NestCount++;
        return thrd_success;
    }

    if(mtx->_ThreadId != 0)
        return thrd_busy;

    LONG prev = InterlockedCompareExchange(&mtx->_ThreadId, myId, 0);
    if(prev == 0)
        return thrd_success;
    else
        return thrd_busy;
}
#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    return TEST_RESULTS;
}

#endif