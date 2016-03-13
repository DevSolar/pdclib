#ifndef REGTEST
#include <threads.h>
#include <windows.h>

extern void _PDCLIB_w32errno( void );
int mtx_unlock(mtx_t *mtx)
{
    if(mtx->_NestCount) {
        mtx->_NestCount--;
        return thrd_success;
    }

    mtx->_ThreadId = 0;
    DWORD rv = SetEvent(mtx->_WaitEvHandle);
    if(rv == 0) {
        _PDCLIB_w32errno();
        return thrd_error;
    }
    return thrd_success;
}
#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    return TEST_RESULTS;
}

#endif