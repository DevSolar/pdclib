PDCLib - Public Domain C Library
================================

License
-------

PDCLib is distributed unter the Creative Commons CC0 License. You
should have received a copy of the full legal text of this license
as part of this distribution (COPYING.CC0). It is also available at

https://creativecommons.org/publicdomain/zero/1.0/legalcode

The following is a human-readable summary of that license.

                       No Copyright

The person who associated a work with this deed has dedicated the
work to the public domain by waiving all of his or her rights to
the work worldwide under copyright law, including all related and
neighboring rights, to the extent allowed by law.

You can copy, modify, distribute and perform the work, even for
commercial purposes, all without asking permission. See Other
Information below.

                    Other Information

In no way are the patent or trademark rights of any person affected
by CC0, nor are the rights that other persons may have in the work
or in how the work is used, such as publicity or privacy rights.

Unless expressly stated otherwise, the person who associated a work
with this deed makes no warranties about the work, and disclaims
liability for all uses of the work, to the fullest extent permitted
by applicable law.

When using or citing the work, you should not imply endorsement by
the author or the affirmer.

What is it
----------

This is a C Standard Library. Nothing more, nothing less. No POSIX
or other extensions, just what's defined in ISO/IEC 9899.

(Well, this is what it will be when the 1.0 release comes out. See
the "Development Status" section to see what's implemented so far.)

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
6) platform-specific, optimized "overlay" implementations (optional).

The standard headers (in ./include/) only contain what they are
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

Then there are internal header files (in ./include/pdclib/), which
contain all the "black magic" and "code fu" that was kept out of the
standard headers. You should not have to touch them if you want to
adapt PDCLib to a new platform. Note that, if you *do* have to touch
them, I would consider it a serious design flaw, and would be happy
to fix it in the next PDCLib release. Any adaption work should be
covered by the steps detailed below.

For adapting PDCLib to a new platform (the trinity of CPU, operating
system, and compiler), make a copy of ./platform/example/ named
./platform/{your_platform}/, and modify the files of your copy to suit
the constraints of your platform. When you are done, copy the contents
of your platform directory over the source directory structure
of PDCLib (or link them into the appropriate places). That should be
all that is actually required to make PDCLib work for your platform.

Of course, your platform might provide more efficient replacements
for the generic implementations offered by PDCLib. The math functions
are an especially "juicy" target for optimization - while PDCLib does
provide generic implementations for each of them, there are usually
FPU opcodes that do the same job, only orders of magnitude faster. For
this, you might want to create an "optimization overlay" for PDCLib.

Optimization Overlay
--------------------

The basic idea of PDCLib is to provide a generic implementation that
is useable even on platforms I have never heard of - for example, the
OS and/or compiler *you* just wrote and now need a C library for. That
is actually what PDCLib was written for: To provide a C library for
compiler and OS builders that do not want the usual baggage of POSIX
and GNU extensions, licensing considerations etc. etc.

Thus, PDCLib provides generic implementations. They do work, and do
so correctly, but they are not very efficient when compared to hand-
crafted assembler or compiler build-ins. So I wanted to provide a
means to modify PDCLib to run more efficiently on a given platform,
without cluttering the main branch with tons of #ifdef statements and
"featureset #defines" that grow stale quickly.

The solution is the "optimization overlay". Every function has its
own implementation file, which makes it possible to replace them
piecemeal by copying a platform-specific overlay over the main PDCLib
branch to create a PDCLib adapted / optimized for the platform in
question. That overlay could be part of the PDCLib source tree (for
established platforms where maintainers won't bother with PDCLib), or
part of that platform's source tree (for under-development platforms
PDCLib maintainers won't bother with).

So, to use PDCLib on your given platform, you unpack PDCLib (as you
obviously have done already since you are reading this), and copy
the overlay for your platform over the PDCLib source tree structure.

Development Status
------------------

Note that pre-v1.0 "releases" are internal milestones only, and that
you are strongly encouraged to use the latest source snapshot at all
times.

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
