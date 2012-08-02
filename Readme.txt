PDCLib - Public Domain C Library
================================

License
-------

Written in 2003-2012 by Martin "Solar" Baute,
           2012-     by Erin Shepherd

To the extent possible under law, the author(s) have dedicated all copyright 
and related and neighboring rights to this software to the public domain 
worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with 
this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

NOTE: Some configuration options may include components under non-public domain
      conditions. In particular, selecting ptmalloc3 as the malloc 
      implementation will cause the incorporation of elements under the BSD 
      license.

What is it
----------

This is a C Standard Library - what's defined in ISO/IEC 9899 "Information 
technology — Programming languages — C" or extensions to the above defined in
ISO/IEC 14882 "Information technology — Programming languages — C++". A few 
extensions may optionally be provided.

Terms for extensions
--------------------
Extensions are permitted where their inclusion is reasonable, they are widely
used, in  keeping with the spirit of the standard, and do not convey 
additional requirements upon the target system, and do not needlessly duplicate
functionality already contained within the standard.

As an example: strdup is in, because (a) it can be implemented entirely in 
terms of existing standard C functions and (b) is very widely used. Something
like open, write or close would not be considered, because it implies POSIXy 
assumptions.

Internals
---------

As a namespace convention, everything (files, typedefs, functions,
macros) not defined in ISO/IEC 9899 is prefixed with _PDCLIB.
The standard defines any identifiers starting with '_' and a capital
letter as reserved for the implementation, and since the chances of
your compiler using an identifier in the _PDCLIB range are slim,
any strictly conforming application should work with this library.

PDCLib consists of several parts:

1) standard headers;
2) implementation files for standard functions;
3) internal header files keeping complex stuff out of the standard
   headers;
4) the central, platform-specific file _PDCLIB_config.h;
5) platform-specific implementation files;

The standard headers (in ./includes/) only contain what they are
defined to contain. Where additional logic or macro magic is
necessary, that is deferred to the internal files. This has been done
so that the headers are actually educational as to what they provide
(as opposed to how the library does it).

There is a seperate implementation file (in ./function/{header}/) for
every function defined by the standard, named {function}.c. Not only
does this avoid linking in huge amounts of unused code when you use
but a single function, it also allows the optimization overlay to work
(see below).

(The directory ./functions/_PDCLIB/ contains internal and helper
functions that are not part of the standard.)

Then there are internal header files (in ./internal/), which contain
all the "black magic" and "code fu" that was kept out of the standard
headers. You should not have to touch them if you want to adapt PDCLib
to a new platform. Note that, if you *do* have to touch them, I would
consider it a serious design flaw, and would be happy to fix it in the
next PDCLib release. Any adaption work should be covered by the steps
detailed below.

For adapting PDCLib to a new platform (the trinity of CPU, operating
system, and compiler), make a copy of ./platform/example/ named
./platform/{your_platform}/, and modify the files of your copy to suit
the constraints of your platform. When you are done, copy the contents
of your platform directory over the source directory structure
of PDCLib (or link them into the appropriate places). That should be
all that is actually required to make PDCLib work for your platform.

Future directions
-----------------
Obviously, full C89, C99 and C11 conformance; and full support for the 
applicable portions of C++98, C++03 and C++11.

Support for "optimization overlays." These would allow efficient 
implementations of certain functions on individual platforms, for example 
memcpy, strcpy and memset. This requires further work to only compile in one
version of a given function.

Development Status
------------------

v0.1 - 2004-12-12
Freestanding-only C99 implementation without any overlay, and missing
the INTN_C() / UINTN_C() macros. <float.h> still has the enquire.c
values hardcoded into it; not sure whether to include enquire.c in the
package, to leave <float.h> to the overlay, or devise some parameterized
macro magic as for <limits.h> / <stdint.h>. Not thoroughly tested, but
I had to make the 0.1 release sometime so why not now.

v0.2 - 2005-01-12
Adds implementations for <string.h> (excluding strerror()), INTN_C() /
UINTN_C() macros, and some improvements in the internal headers.
Test drivers still missing, but added warnings about that.

v0.3 - 2005-11-21
Adds test drivers, fixes some bugs in <string.h>.

v0.4 - 2005-02-06
Implementations for parts of <stdlib.h>. Still missing are the floating
point conversions, and the wide-/multibyte-character functions.

v0.4.1 - 2006-11-16
With v0.5 (<stdio.h>) taking longer than expected, v0.4.1 was set up as
a backport of bugfixes in the current development code.
- #1  realloc( NULL, size ) fails           (fixed)
- #2  stdlib.h - insufficient documentation (fixed)
- #4  Misspelled name in credits            (fixed)
- #5  malloc() splits off too-small nodes   (fixed)
- #6  qsort() stack overflow                (fixed)
- #7  malloc() bug in list handling         (fixed)
- #8  strncmp() does not terminate at '\0'  (fixed)
- #9  stdint.h dysfunctional                (fixed)
- #10 NULL redefinition warnings            (fixed)

v0.5 - 2010-12-22
Implementations for <inttypes.h>, <errno.h>, most parts of <stdio.h>,
and strerror() from <string.h>.
Still no locale / wide-char support. Enabled all GCC compiler warnings I
could find, and fixed everything that threw a warning. (You see this,
maintainers of Open Source software? No warnings whatsoever. Stop telling
me it cannot be done.) Fixed all known bugs in the v0.4 release.

Near Future
-----------
Current development directions are:

Implement portions of the C11 standard that have a direct impact on the way 
that PDCLib itself is built. For example, in order to support multithreading,
PDCLib needs a threading abstraction; therefore, C11's thread library is being
implemented to provide the backing for this (as there is no purpose in 
implementing two abstractions)

Cleanup portions of <stdio.h>, particularly the backend. _PDCLIB_fillbuffer and
_PDCLIB_flushbuffer in particular do not feel 'well' factored and need to know
too much about FILE's internals. 

Modularize the library somewhat. This can already be seen with components under 
"opt/". This structure is preliminary; it will likely change as the process 
continues.
