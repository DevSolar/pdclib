#include <threads.h>

int mtx_unlock(mtx_t *mtx)
{
	if(*mtx) {
		*mtx = 0;
		return thrd_success;
	} else return thrd_error;
}