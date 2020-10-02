/* Definition guard <_PDCLIB_defguard.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_DEFGUARD_H
#define _PDCLIB_DEFGUARD_H _PDCLIB_DEFGUARD_H

#if defined( __ANDROID__ )
/* typedef sigset_t */
#include "bits/signal_types.h"
#endif

#define _TIMESPEC_DEFINED
#define _SYS__TIMESPEC_H_
#define _STRUCT_TIMESPEC

#include <time.h>

#endif
