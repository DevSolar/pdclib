/* _Noreturn <stdnoreturn.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_STDNORETURN_H
#define _PDCLIB_STDNORETURN_H _PDCLIB_STDNORETURN_H

/* C99 does not know about 'noreturn', '_Noreturn', or <stdnoreturn.h>.
   C11 introduced '_Noreturn' as function specifier (like 'inline'),
   and the header <stdnoreturn.h> to define 'noreturn' -> '_Noreturn'.
   (The purpose, of course, to avoid invalidating existing code by
   introducing a new keyword in the client-reserved namespace.)
   C23 introduced the function attribute [[noreturn]]. '_Noreturn' as
   a function specifier was deprecated, as was including <stdnoreturn.h>.
   To keep compatibility with code that used both the new '[[noreturn]]'
   and <stdnoreturn.h>, '[[_Noreturn]]' was declared legal if undesirable.
   C++11 introduced '[[noreturn]]'.
   C++17 onward state explicitly that <stdnoreturn.h> is not part of a
   C++ implementation, and <cstdnoreturn> does not exist.

   We can therefore assume:

   C code that includes <stdnoreturn.h> knows what it's doing.

   C++ code that includes <stdnoreturn.h> does not, but it's not our
   problem.

   Hence there is no need for any version checks here.
*/


#define noreturn _Noreturn

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_STDNORETURN_H
#include _PDCLIB_EXTEND_STDNORETURN_H
#endif

#endif
