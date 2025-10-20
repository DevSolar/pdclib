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

(Well, this is what it will be when the 1.0 release comes out. Check
http://pdclib.rootdirectory.de to see what is implemented so far.)

Rebuild branch
--------------

As the master branch gradually nears completion, I decided to create
the 'rebuild' branch to do a review and clean-up of the work done so
far, and to shift from a layout primarily aimed at making development
easier for me toward making deployment easier for you.

I also extended the testing platforms by Classic AmigaOS, to have one
platform that is big endian and decidedly non-POSIX.

And finally, I hope to iron out the issues I have with debugging my
code on aarch64/Android by migrating it step by step into the new
structure.
