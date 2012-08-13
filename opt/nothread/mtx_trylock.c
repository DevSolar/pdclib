#ifndef REGTEST
#include <threads.h>

int mtx_trylock(mtx_t *mtx)
{
	if(*mtx) {
		return thrd_error;
	} else {
		*mtx = 1;
		return thrd_success;
	}
}
#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    return TEST_RESULTS;
}

#endif