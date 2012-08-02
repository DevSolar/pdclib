#include <threads.h>

void tss_delete(tss_t key)
{
	key.self->self = NULL;
}
