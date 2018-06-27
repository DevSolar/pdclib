#ifndef REGTEST
#include <threads.h>
#include <pthread.h>

void mtx_destroy(mtx_t *mtx)
{
    pthread_mutex_destroy(mtx);
}
#endif

#ifdef TEST
#include "_PDCLIB_test.h"

int main( void )
{
    return TEST_RESULTS;
}

#endif
