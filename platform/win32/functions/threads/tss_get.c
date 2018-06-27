#ifndef REGTEST
#include <threads.h>
#include <windows.h>

void *tss_get(tss_t key)
{
    return TlsGetValue(key->_Key);
}
#endif

#ifdef TEST
#include "_PDCLIB_test.h"

#ifndef REGTEST
static tss_t key;
static char v;
#endif

// Todo: make a thread and test destruction!

int main( void )
{
#ifndef REGTEST
    TESTCASE(tss_create(&key, NULL) == thrd_success);
    TESTCASE(tss_get(key) == NULL);
    TESTCASE(tss_set(key, &v) == thrd_success);
    TESTCASE(tss_get(key) == &v);
    tss_delete(key);
#endif
    return TEST_RESULTS;
}

#endif