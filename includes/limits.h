// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Sizes of integer types
// ----------------------------------------------------------------------------

#ifndef __LIMITS_H
#define __LIMITS_H __LIMITS_H

// ISO/IEC 9899:1999, §5.2.4.2.1
// The values given below shall be replaced by constant expressions suitable
// for use in #if preprocessing directives. Moreover, except for CHAR_BIT and
// MB_LEN_MAX, the following shall be replaced by expressions that have the
// same type as would an expression that is an object of the corresponding type
// converted according to the integer promotions. Their implementation-defined
// values shall be equal or greater in magnitude (absolute value) to those
// shown, with the same sign.

// This file is part of the platform personality (see personality.txt).

// Limits of type 'char'
#define CHAR_BIT   //    8
#define CHAR_MAX   // SCHAR_MAX / UCHAR_MAX
#define CHAR_MIN   // SCHAR_MIN / 0
#define SCHAR_MAX  // +127
#define SCHAR_MIN  // -127
#define UCHAR_MAX  //  255 (2^CHAR_BIT - 1)

// Multibyte characters
#define MB_LEN_MAX //    1

// Limits of type 'short int'
#define SHRT_MAX   // +32767
#define SHRT_MIN   // -32767
#define USHRT_MAX  //  65535

// Limits of type 'int'
#define INT_MAX    // +32767
#define INT_MIN    // -32767
#define UINT_MAX   //  65535

// Limits of type 'long int'
#define LONG_MAX   // +2147483647
#define LONG_MIN   // -2147483647
#define ULONG_MAX  //  4294967295

// Limits of type 'long long int'
#define LLONG_MAX  // +9223372036854775807
#define LLONG_MIN  // -9223372036854775807
#define ULLONG_MAX // 18446744073709551615

#endif // __LIMITS_H
