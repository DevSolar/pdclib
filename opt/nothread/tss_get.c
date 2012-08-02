#include <threads.h>

void *tss_get(tss_t key)
{
	return key.value;
}