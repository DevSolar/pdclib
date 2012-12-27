#ifndef _PDCLIB_THREADCONFIG_H
#define _PDCLIB_THREADCONFIG_H
#include <_PDCLIB_aux.h>
#include <_PDCLIB_config.h>

#ifdef __APPLE__
#include <_types.h>
#define _PDCLIB_THR_T __darwin_pthread_t
#define _PDCLIB_CND_T __darwin_pthread_cond_t
#define _PDCLIB_MTX_T __darwin_pthread_mutex_t

#define _PDCLIB_TSS_DTOR_ITERATIONS 5
#define _PDCLIB_TSS_T __darwin_pthread_key_t

typedef __darwin_pthread_once_t _PDCLIB_once_flag;
#define _PDCLIB_ONCE_FLAG_INIT {_PTHREAD_ONCE_SIG_init, {0}}

#else
#error Need to interrogate the C library headers for your platform
#endif

_PDCLIB_END_EXTERN_C
#endif
