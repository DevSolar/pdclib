PDCLib - Public Domain C Library
================================

License
-------

Permission is granted to use, modify, and / or redistribute at will.

This includes removing authorship notices, re-use of code parts in
other software (with or without giving credit), and / or creating a
commercial product based on it.

This software is provided as-is. Use it at your own risk. There is
no warranty whatsoever, neither expressed nor implied, and by using
this software you accept that the author(s) shall not be held liable
for any loss of data, loss of service, or other damages, be they
incidential or consequential. Your only option other than accepting
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

What is it
----------

This is a C Standard Library. Nothing more, nothing less. No POSIX
or other extensions, just what's defined in ISO/IEC 9899.

(Well, this is what it will be when the 1.0 release comes out. See
the "Development Status" section to see what's implemented so far.)

Internals
---------

As a namespace convention, everything (files, typedefs, functions,
macros) not defined in ISO/IEC 9899 is prefixed with _PDCLIB_*.
As identifiers starting with '_' and a capital letter are reserved
for the implementation, and the chances of you compiler using an
identifier in the _PDCLIB_* range are slim, any strictly conforming
application should work with PDCLib.

PDCLib consists of several parts:

1) standard headers;
2) implementation files for standard functions;
3) internal header files keeping complex stuff out of the standard
   headers;
4) the central, platform-specific file _PDCLIB_config.h;
5) optimization overlay implementation files (optional).

The standard headers only contain what they are defined to contain.
Where additional logic or macro magic is necessary, that is deferred
to the internal files. This has been done so that the headers are
actually educational as to what they provide (as opposed to how the
library does it).

There is a seperate implementation file for every function defined
by the standard, named {function}.c. Not only does this avoid linking
in huge amounts of unused code when you use but a single function,
it also allows the optimization overlay to work (see below).

Then there are internal header files, which contain all the "black
magic" and "code fu" that were kept out of the standard headers. You
should not have to touch them if you want to adapt PDCLib to a new
platform. If you do, note that the PDCLib author would consider it
a serious design flaw, and would be happy to fix it in the next PDCLib
release. Any adaption work should be covered by the config header
(and, possibly, the optimization overlay).

For adapting PDCLib to a new platform (the trinity of CPU, operating
system, and compiler), open _PDCLIB_config.h in your favourite text
editor, have a look at the comments, and modify it as appropriate for
your platform. That should be all that is actually required for such
an adaption (see previous paragraph).

Of course, your platform might provide more efficient replacements
for the generic implementations offered by PDCLib. The math functions
are an especially "juicy" target for optimization - while PDCLib does
provide generic implementations for each of them, there are usually
FPU opcodes that do the same job, only orders of magnitude faster. For
this, you might want to create an "optimization overlay" for PDCLib.

Optimization Overlay
--------------------

The idea is to provide a generic implementation that is useable even
on platforms the author never heard of - for example, the OS and/or
compiler *you* just wrote and now need a C library for. That is
actually what PDCLib was written for: To provide a C library for
compiler and OS builders that do not want the usual baggage of POSIX
and GNU extensions, licensing considerations etc. etc.

Thus, PDCLib provides generic implementations. They do work, and do
so correctly, but they are not very efficient when compared to hand-
crafted assembler or compiler build-ins. So the author wanted to
provide a means to modify PDCLib to run more efficiently on a given
platform, without cluttering the main branch with tons of #ifdef
statements and "featureset defines" that grow stale quickly.

The solution is the "optimization overlay". Every function has its
own implementation file, and _PDCLIB_config.h should be the only
header that must be modified. So, a platform-specific overlay is
copied over the main PDCLib branch - replacing _PDCLIB_config.h and
any number of implementation files - to create a PDCLib adapted /
optimized for the platform in question. That overlay could be part
of the PDCLib source tree (for established platforms where maintainers
won't bother with PDCLib), or part of that platform's source tree
(for under-development platforms PDCLib maintainers won't bother with).

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

Future releases:

v0.2 - will (hopefully) add the INTN_C() / UINTN_C() macros, at least
one overlay for GCC / x86, and implementations for <string.h> as well
as parts of <stdlib.h>. I will also add a test driver to make at least
some basic tests for syntax.

