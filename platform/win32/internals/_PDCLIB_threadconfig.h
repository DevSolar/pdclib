#ifndef _PDCLIB_THREADCONFIG_H
#define _PDCLIB_THREADCONFIG_H
#include "_PDCLIB_aux.h"
#include "_PDCLIB_int.h"

#ifdef __cplusplus
extern "C" {
#endif
#define _PDCLIB_TSS_DTOR_ITERATIONS 3
#define _PDCLIB_ONCE_FLAG_INIT { -1, 0 }
#define _PDCLIB_ONCE_FLAG_IS_DONE( _f ) ((_f)->_State == 0)
typedef struct {
    long  _State;
    void *_Handle;
} _PDCLIB_once_flag;

void _PDCLIB_call_once(_PDCLIB_once_flag *flag, void (*func)(void));

//#define _PDCLIB_THRD_HAVE_MISC
//#define _PDCLIB_CND_T char
#define _PDCLIB_MTX_T struct _PDCLIB_mtx 

struct _PDCLIB_mtx {
    void                   * _WaitEvHandle;
    volatile          long   _ThreadId; 
    volatile unsigned  int   _NestCount;
};

#define _PDCLIB_TSS_T struct _PDCLIB_tss *

struct _PDCLIB_tss {
    void    (*_Destructor)(void*);
    struct _PDCLIB_tss * _Next;
    unsigned int _Key;
};

#ifdef __cplusplus
}
#endif
#endif
