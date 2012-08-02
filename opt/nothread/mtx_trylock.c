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
