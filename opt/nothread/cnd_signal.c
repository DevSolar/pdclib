#include <threads.h>

int cnd_signal(cnd_t *cond)
{
	return thrd_success;
}

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    return TEST_RESULTS;
}

#endif