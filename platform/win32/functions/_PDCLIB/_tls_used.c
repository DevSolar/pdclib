/* _tls_used

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST
#include <stddef.h>
#include <stdint.h>
#include <windows.h>

/* Win32 TLS support
 *
 * Components which depend upon TLS must express a dependency on the symbol 
 * _tls_used. This will cause said symbol to be emitted.
 *
 * The linker (in the case of both Microsoft's linker and Binutils, at least)
 * will point the TLS directory entry in the PE header to _tls_used.
 *
 * NOTE: On Windows versions < NT 6.0, the TLS support _only_ works for 
 *       the main executable and any DLLs loaded as dependencies of it
 */

extern char __tls_start__[], __tls_end__[];
ULONG _tls_index = TLS_OUT_OF_INDEXES;

extern void NTAPI _PDCLIB_runTlsCallbacks(void * image, DWORD reason, PVOID pv);
static PIMAGE_TLS_CALLBACK tlsCallbacks[] = {
    &_PDCLIB_runTlsCallbacks,
    NULL,
};

#ifdef __GNUC__
__attribute__((__section__(".rdata$T")))
#else
__declspec(allocate(".rdata$T"))
#endif
#ifdef _WIN64
const IMAGE_TLS_DIRECTORY64 _tls_used = {
#else
const IMAGE_TLS_DIRECTORY _tls_used = {
#endif
        (uintptr_t) &__tls_start__,
        (uintptr_t) &__tls_end__,
        (uintptr_t) &_tls_index,        // TLS index
        (uintptr_t) &tlsCallbacks[0],   // TLS callback array
        (ULONG) 0,                      // Size of zero fill
        (ULONG) 0                       // Characteristics
};
#endif

#ifdef TEST
#include "_PDCLIB_test.h"

/* Tested in tss_get.c */
int main( void )
{
    return TEST_RESULTS;
}

#endif
