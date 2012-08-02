#ifndef _PDCLIB_STDNORETURN_H
#define _PDCLIB_STDNORETURN_H
#include <_PDCLIB_aux.h>

#ifndef __cplusplus
/* This is problematic - if we don't define it, then C code can't be compiled
 * on a C++ compiler. If we do define it, then we break all instances of C++
 * [[noreturn]]
 *
 * This does not appear well thought out...
 */
#define noreturn _PDCLIB_noreturn
#endif


#endif
