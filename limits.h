#ifndef _PDCLIB_LIMITS_H
#define _PDCLIB_LIMITS_H _PDCLIB_LIMITS_H

/* $Id$ */

/* 7.10 Sizes of integer types <limits.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* Defined to 1 as multibyte characters are not supported yet. */
#define MB_LEN_MAX 1

#define LLONG_MIN  (-0x7fffffffffffffff - 1)
#define LLONG_MAX  0x7fffffffffffffff
#define ULLONG_MAX 0xffffffffffffffff

/* Produced by enquire version 5.1a, CWI, Amsterdam
   http://www.cwi.nl/~steven/enquire.html  */

   /* Number of bits in a storage unit */
#define CHAR_BIT 8
   /* Maximum char */
#define CHAR_MAX 127
   /* Minimum char */
#define CHAR_MIN (-128)
   /* Maximum signed char */
#define SCHAR_MAX 127
   /* Minimum signed char */
#define SCHAR_MIN (-128)
   /* Maximum unsigned char (minimum is always 0) */
#define UCHAR_MAX 255
   /* Maximum short */
#define SHRT_MAX 32767
   /* Minimum short */
#define SHRT_MIN (-32768)
   /* Maximum int */
#define INT_MAX 2147483647
   /* Minimum int */
#define INT_MIN (-2147483647-1)
   /* Maximum long */
#define LONG_MAX 2147483647L
   /* Minimum long */
#define LONG_MIN (-2147483647L-1L)
   /* Maximum unsigned short (minimum is always 0) */
#define USHRT_MAX 65535
   /* Maximum unsigned int (minimum is always 0) */
#define UINT_MAX 4294967295U
   /* Maximum unsigned long (minimum is always 0) */
#define ULONG_MAX 4294967295UL

#endif
