#include <threads.h>

void *tss_get(tss_t key)
{
	return key.value;
}

#ifdef TEST
#include <_PDCLIB_test.h>

static tss_t key;
static char v;

int main( void )
{
    TESTCASE(tss_create(&key, NULL) == thrd_success);
    TESTCASE(tss_get(key) == NULL);
    TESTCASE(tss_set(key, &v) == thrd_success);
    TESTCASE(tss_get(key) == &v);
    tss_delete(key);
    return TEST_RESULTS;
}

#endif