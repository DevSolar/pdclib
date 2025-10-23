/* Internal PDCLib configuration <_PDCLIB_config.h>
   (x86_64-linux-gcc)

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_CONFIG_H
#define _PDCLIB_CONFIG_H _PDCLIB_CONFIG_H

/* -------------------------------------------------------------------------- */
/* Integers                                                                   */
/* -------------------------------------------------------------------------- */

/* Bits in a char */
#define _PDCLIB_CHAR_WIDTH 8

/* Whether the 'char' type is unsigned                                        */
#define _PDCLIB_CHAR_SIGNED 1

/* Encoding of signed values - (2) two's complement, (1) one's complement,    */
/* (0) signed magnitude                                                       */
#define _PDCLIB_SIGNED_ENCODING 2

/* Maximum values of base types                                               */
#define _PDCLIB_CHAR_MAX 0x7f
#define _PDCLIB_SHRT_MAX 0x7fff
#define _PDCLIB_INT_MAX 0x7fffffff
#define _PDCLIB_LONG_MAX 0x7fffffffffffffffL
#define _PDCLIB_LLONG_MAX 0x7fffffffffffffffLL

#endif
