#ifndef REGTEST
#include <threads.h>
#include <windows.h>

int mtx_init(mtx_t *mtx, int type)
{
    mtx->_WaitEvHandle = CreateEvent(NULL, 
        /* bManualReset*/   FALSE, 
        /* bInitialState*/  FALSE, 
        /* name*/           NULL);
    if(mtx->_WaitEvHandle == NULL)
        return thrd_error;
    
    mtx->_ThreadId     = 0;
    mtx->_NestCount    = 0;;

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