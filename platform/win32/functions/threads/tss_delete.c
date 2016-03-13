#ifndef REGTEST
#include <windows.h>
#include <threads.h>
#include <stdlib.h>

extern struct _PDCLIB_tss * _PDCLIB_tss_first;
void tss_delete( tss_t key )
{
    struct _PDCLIB_tss * prev = NULL;
    struct _PDCLIB_tss * cur  = _PDCLIB_tss_first;
    while(cur) {
        if(cur == key) {
            if(prev) {
                prev->_Next = key->_Next;
            } else {
                _PDCLIB_tss_first = key->_Next;
            }

            TlsFree(key->_Key);
            free(key);
            return;
        }
    }

    // Not actually a TSS key
    abort();
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