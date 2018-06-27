#ifndef REGTEST
#include <threads.h>
#include <windows.h>

int tss_set(tss_t key, void *val)
{
    if(TlsSetValue(key->_Key, val))
        return thrd_success;
    return thrd_error;
}
#endif

#ifdef TEST
#include "_PDCLIB_test.h"

/* Tested in tss_get.c */
int main( void )
{
    return TEST_RESULTS;
}

#endif