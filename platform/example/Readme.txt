"Example" Platform Overlay
==========================

This is an example platform overlay, as described in the main Readme.txt of
this archive. For ease of development, it applies (and tests) correctly on the
machine of the author; no other guarantees can be given.
It should give you a good idea of what is REQUIRED to make a copy of PDCLib
work. There is a lot more you could do, and even some things you SHOULD do, in
order to experience anything but abysmal performance:

- Read / write operations on binary streams, and even on text streams for
  machines that do not do any text conversion, can be made much more efficient
  by using some sort of page buffer instead of the linear buffer implemented
  here. It requires some special and platform-dependent manipulations, though,
  which is why it is not done by default.

- Anything relating to floating point logic is written in generic C. While
  this is (hopefully) highly portable and should get you started on your
  platform of choice, it is also highly inefficient and should be replaced by
  inline assembly. Just make sure that your assembly keeps all the promises
  the C library makes.
