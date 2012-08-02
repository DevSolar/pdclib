#include <threads.h>

int tss_set(tss_t key, void *val)
{
	key.self->value = val;
	return thrd_success;
}