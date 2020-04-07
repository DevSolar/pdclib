/* Definition guard <_PDCLIB_defguard.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_DEFGUARD_H
#define _PDCLIB_DEFGUARD_H _PDCLIB_DEFGUARD_H

#if defined( __CYGWIN__ )
/* sys/stat.h (for open()) and sys/time.h (for gettimeofday()) each include
   sys/_timespec.h, which redefines struct timespec. (sys/stat.h includes
   <time.h> itself, finding PDCLib's version, and PDCLib's time.c includes
   <time.h> as well for obvious reasons.)
   This define knocks out the sys/_timespec.h include by setting its include
   guard.
*/
#define _SYS__TIMESPEC_H_
#endif

#if defined( __MINGW32__ ) || defined ( __MINGW64__ )
#define _TIMESPEC_DEFINED
#endif

#endif
