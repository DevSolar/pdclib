#include <threads.h>

int mtx_timedlock(mtx_t *restrict mtx, const struct timespec *restrict ts)
{
	return mtx_lock(mtx);
}