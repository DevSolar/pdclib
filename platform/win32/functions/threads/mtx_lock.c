#ifndef REGTEST
#include <threads.h>
#include <windows.h>

int mtx_lock(mtx_t *mtx)
{
    DWORD myId = GetCurrentThreadId();

    if(mtx->_ThreadId == myId) {
        mtx->_NestCount++;
        return thrd_success;
    }

    DWORD res = InterlockedIncrement(&mtx->_State);
    if(res == 0) {
        mtx->_ThreadId = myId;
        return thrd_success;
    }

    // If that increment didn't leave the state == 0, then we have contention
    //  -> block on the wait event handle
    DWORD rv = WaitForSingleObject(mtx->_WaitEvHandle, INFINITE);
    if(rv != WAIT_OBJECT_0) 
        return thrd_error;

    // We now own the mutex - so set it up for our use
    mtx->_ThreadId = myId;
    return thrd_success;
}
#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    return TEST_RESULTS;
}

#endif