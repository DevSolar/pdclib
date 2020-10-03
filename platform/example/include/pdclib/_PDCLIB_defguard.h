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

/* Linux defines its own version of struct timespec (from <time.h>) in
   some internal header (depending on clib implementation), which leads
   to problems when accessing e.g. sys/time.h (type redefinition).
   The solution is to set the Linux header's include guard (to avoid
   Linux' definition), and to include PDCLib's <time.h> to define the
   type unambiguously.
*/

#define _TIMESPEC_DEFINED
#define _SYS__TIMESPEC_H_
#define _STRUCT_TIMESPEC

#include <time.h>

#endif
