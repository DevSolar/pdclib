/* _PDCLIB_runTlsCallbacks( void *, DWORD, PVOID )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stddef.h>
#include <windows.h>

#ifndef REGTEST
extern PIMAGE_TLS_CALLBACK __crt_xl_start__;
#ifdef __GNUC__
__attribute__((section(".CRT$XLZZZ")))
#else
__declspec(allocate(".CRT$XLZZZ")) 
#endif
PIMAGE_TLS_CALLBACK __crt_xl_end__ = NULL;

/* Runs all TLS callbacks registered in the executable
 */

void NTAPI _PDCLIB_runTlsCallbacks(void * image, DWORD reason, PVOID pv);
void NTAPI _PDCLIB_runTlsCallbacks(void * image, DWORD reason, PVOID pv)
{
    PIMAGE_TLS_CALLBACK * pcb = &__crt_xl_start__;

    while(*pcb) (*(pcb++))(image, reason, pv);
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
