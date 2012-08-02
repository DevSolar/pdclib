#include <threads.h>

int tss_create(tss_t *key, tss_dtor_t dtor)
{
	key->self  = key;
	key->value = NULL;
	return thrd_success;
}