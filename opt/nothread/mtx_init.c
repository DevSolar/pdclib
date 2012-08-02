#include <threads.h>

int mtx_init(mtx_t *mtx, int type)
{
	*mtx = 0;
	return thrd_success;
}
