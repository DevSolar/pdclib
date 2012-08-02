#include <threads.h>
#include <assert.h>

int mtx_lock(mtx_t *mtx)
{
	if(*mtx == 0) {
		*mtx = 1;
		return thrd_success;
	} else return thrd_error;
}