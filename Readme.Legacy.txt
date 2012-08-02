$Id$

PDCLib - Public Domain C Library
================================

License
-------

Permission is granted to use, modify, and / or redistribute at will.

This includes removing authorship notices, re-use of code parts in
other software (with or without giving credit), and / or creating a
commercial product based on it.

This permission is not revocable by the author.

This software is provided as-is. Use it at your own risk. There is
no warranty whatsoever, neither expressed nor implied, and by using
this software you accept that the author(s) shall not be held liable
for any loss of data, loss of service, or other damages, be they
incidental or consequential. Your only option other than accepting
this is not to use the software at all.

A case for Public Domain
------------------------

There was a time when you could just post a piece of code to usenet
and say, "I give it away for free; perhaps it's useful for you."

Then came the lawyers.

There are building blocks in software engineering that are so basic
that everyone should have free access to them without having to
employ a complete legal department for advice. They should be FREE.
Available for free, free of licensing implications, free of attached
propaganda, free of everything but their useful self.

Today, even the term "free" has to be defined by several paragraphs
of legal blah-blah.

Sick and tired of it, the author brought you this piece of software
under a "license" that should not be neccessary in the first place:
"Free" should have been enough.

Unfortunately, German law does not even *allow* to declare a work to
be "in the Public Domain", so the "free for all" license I intended
had to be made expressively.

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

The standard headers (in ./includes/) only contain what they are
defined to contain. Where additional logic or macro magic is
necessary, that is deferred to the internal files. This has been done
so that the headers are actually educational as to what they provide
(as opposed to how the library does it).

Note that there *might* be some feature to remove this additional
level of indirection for a production release, to ease the workload
put on the preprocessor.

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


A WORD ON THE v0.5 RELEASE
==========================

The v0.5 release is not well-tested. There are several things in it done
in a way that I would never label "release quality". Some things are not
even in the *structure* I would like them to be. An example for this is
the current handling of errno values: It needlessly introduces dependency
on PDCLib (because I use non-standard values), and the values are placed
in the wrong header (_PDCLIB_int.h instead of _PDCLIB_glue.h where they
would be more appropriate).

But at some point during the development toward the v0.5 release, I found
that my current PDCLib work schedule simply does not allow me to wait
until every piece of <stdio.h> is as I would like it to be. It would
probably take another year or two, and my patience is UP.

I want this released, and I want to think about something else but
<stdio.h> for some time.

So, expect significant change to how stdio is done in upcoming releases.
Everything *WILL* be stable by the time v1.0 comes around, but until then
you will have to accept that I can only deliver "hobby quality" for now.

