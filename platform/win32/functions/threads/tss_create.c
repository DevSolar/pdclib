#ifndef REGTEST
#include <threads.h>
#include <stdbool.h>
#include <windows.h>

/* Pull in TLS support */
extern char _tls_used[];

struct _PDCLIB_tss * _PDCLIB_tss_first = NULL;

int tss_create( tss_t *key, tss_dtor_t dtor )
{
    *key = malloc( sizeof *key );
    if( !*key ) {
        return thrd_nomem;
    }

    (*key)->_Key = TlsAlloc();
    if((*key)->_Key == TLS_OUT_OF_INDEXES) {
        return thrd_error;
    }
    (*key)->_Destructor = dtor;
    (*key)->_Next = _PDCLIB_tss_first;

    // TODO: make this atomic (& validate no other TLS blocks have been 
    // simultaneously allocated)
    _PDCLIB_tss_first = *key;

    return thrd_success;
}

static void NTAPI runTlsDestructors( void * image, DWORD reason, PVOID pv )
{
    if( reason == DLL_THREAD_DETACH ) {
        for(unsigned i = 0; i < TSS_DTOR_ITERATIONS; i++) {
            struct _PDCLIB_tss * tss = _PDCLIB_tss_first;
            bool destructorsRan = false;
            while( tss ) {
                void * val = TlsGetValue( tss->_Key );
                if( val ) {
                    TlsSetValue( tss->_Key, NULL );
                    if( tss->_Destructor ) {
                        tss->_Destructor( val );
                        destructorsRan = true;
                    }
                }

                tss = tss->_Next;
            }
            if(!destructorsRan) break;
        }
    }
}

#ifdef __GNUC__
__attribute__((__section__(".CRT$XLC")))
#else
__declspec(allocate(".CRT$XLC")) 
#endif
PIMAGE_TLS_CALLBACK _PDCLIB_runTlsDestructors = runTlsDestructors;

#endif

#ifdef TEST
#include "_PDCLIB_test.h"

/* Tested in tss_get.c */
int main( void )
{
    return TEST_RESULTS;
}

#endif