/* Format conversion of integer types <inttypes.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_INTTYPES_H
#define _PDCLIB_INTTYPES_H _PDCLIB_INTTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct _PDCLIB_imaxdiv_t imaxdiv_t;

/* 7.8.1 Macros for format specifiers */

/* The various leastN_t, fastN_t, intmax_t, and intptr_t types are typedefs
   to native types. But the user does not know which ones, which gives some
   problems when trying to *printf() / *scanf() those types. The various
   macros defined below allow to give the correct conversion specifiers
   without knowing the actual native type they represent.
*/

#define PRIdLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, d ) )
#define PRIdLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, d ) )
#define PRIdLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, d ) )
#define PRIdLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, d ) )

#define PRIdFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, d ) )
#define PRIdFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, d ) )
#define PRIdFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, d ) )
#define PRIdFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, d ) )

#define PRIdMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, d ) )
#define PRIdPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, d ) )

#define PRIiLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, i ) )
#define PRIiLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, i ) )
#define PRIiLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, i ) )
#define PRIiLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, i ) )

#define PRIiFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, i ) )
#define PRIiFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, i ) )
#define PRIiFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, i ) )
#define PRIiFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, i ) )

#define PRIiMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, i ) )
#define PRIiPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, i ) )

#define PRIoLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, o ) )
#define PRIoLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, o ) )
#define PRIoLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, o ) )
#define PRIoLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, o ) )

#define PRIoFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, o ) )
#define PRIoFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, o ) )
#define PRIoFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, o ) )
#define PRIoFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, o ) )

#define PRIoMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, o ) )
#define PRIoPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, o ) )

#define PRIuLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, u ) )
#define PRIuLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, u ) )
#define PRIuLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, u ) )
#define PRIuLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, u ) )

#define PRIuFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, u ) )
#define PRIuFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, u ) )
#define PRIuFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, u ) )
#define PRIuFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, u ) )

#define PRIuMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, u ) )
#define PRIuPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, u ) )

#define PRIxLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, x ) )
#define PRIxLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, x ) )
#define PRIxLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, x ) )
#define PRIxLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, x ) )

#define PRIxFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, x ) )
#define PRIxFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, x ) )
#define PRIxFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, x ) )
#define PRIxFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, x ) )

#define PRIxMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, x ) )
#define PRIxPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, x ) )

#define PRIXLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, X ) )
#define PRIXLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, X ) )
#define PRIXLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, X ) )
#define PRIXLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, X ) )

#define PRIXFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, X ) )
#define PRIXFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, X ) )
#define PRIXFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, X ) )
#define PRIXFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, X ) )

#define PRIXMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, X ) )
#define PRIXPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, X ) )

#define SCNdLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, d ) )
#define SCNdLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, d ) )
#define SCNdLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, d ) )
#define SCNdLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, d ) )

#define SCNdFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, d ) )
#define SCNdFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, d ) )
#define SCNdFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, d ) )
#define SCNdFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, d ) )

#define SCNdMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, d ) )
#define SCNdPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, d ) )

#define SCNiLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, i ) )
#define SCNiLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, i ) )
#define SCNiLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, i ) )
#define SCNiLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, i ) )

#define SCNiFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, i ) )
#define SCNiFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, i ) )
#define SCNiFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, i ) )
#define SCNiFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, i ) )

#define SCNiMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, i ) )
#define SCNiPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, i ) )

#define SCNoLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, o ) )
#define SCNoLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, o ) )
#define SCNoLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, o ) )
#define SCNoLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, o ) )

#define SCNoFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, o ) )
#define SCNoFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, o ) )
#define SCNoFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, o ) )
#define SCNoFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, o ) )

#define SCNoMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, o ) )
#define SCNoPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, o ) )

#define SCNuLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, u ) )
#define SCNuLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, u ) )
#define SCNuLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, u ) )
#define SCNuLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, u ) )

#define SCNuFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, u ) )
#define SCNuFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, u ) )
#define SCNuFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, u ) )
#define SCNuFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, u ) )

#define SCNuMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, u ) )
#define SCNuPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, u ) )

#define SCNxLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, x ) )
#define SCNxLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, x ) )
#define SCNxLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, x ) )
#define SCNxLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, x ) )

#define SCNxFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, x ) )
#define SCNxFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, x ) )
#define SCNxFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, x ) )
#define SCNxFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, x ) )

#define SCNxMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, x ) )
#define SCNxPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, x ) )

/* The exact-width types (int8_t, int16_t, ...) are *optional*, as not all
   architectures support the necessary 8-bits-per-byte two's complement
   native types.
*/

#if _PDCLIB_TWOS_COMPLEMENT == 1

#if _PDCLIB_INT_LEAST8_MAX == 0x7f
#define PRId8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, d ) )
#define PRIi8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, i ) )
#define PRIo8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, o ) )
#define PRIu8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, u ) )
#define PRIx8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, x ) )
#define PRIX8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, X ) )
#define SCNd8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, d ) )
#define SCNi8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, i ) )
#define SCNo8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, o ) )
#define SCNu8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, u ) )
#define SCNx8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, x ) )
#endif

#if _PDCLIB_INT_LEAST16_MAX == 0x7fff
#define PRId16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, d ) )
#define PRIi16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, i ) )
#define PRIo16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, o ) )
#define PRIu16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, u ) )
#define PRIx16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, x ) )
#define PRIX16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, X ) )
#define SCNd16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, d ) )
#define SCNi16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, i ) )
#define SCNo16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, o ) )
#define SCNu16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, u ) )
#define SCNx16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, x ) )
#endif

#if _PDCLIB_INT_LEAST32_MAX == 0x7fffffffl
#define PRId32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, d ) )
#define PRIi32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, i ) )
#define PRIo32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, o ) )
#define PRIu32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, u ) )
#define PRIx32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, x ) )
#define PRIX32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, X ) )
#define SCNd32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, d ) )
#define SCNi32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, i ) )
#define SCNo32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, o ) )
#define SCNu32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, u ) )
#define SCNx32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, x ) )
#endif

#if _PDCLIB_INT_LEAST64_MAX == 0x7fffffffffffffffll
#define PRId64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, d ) )
#define PRIi64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, i ) )
#define PRIo64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, o ) )
#define PRIu64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, u ) )
#define PRIx64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, x ) )
#define PRIX64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, X ) )
#define SCNd64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, d ) )
#define SCNi64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, i ) )
#define SCNo64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, o ) )
#define SCNu64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, u ) )
#define SCNx64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, x ) )
#endif

#endif

/* 7.8.2 Functions for greatest-width integer types */

/* Calculate the absolute value of j */
_PDCLIB_PUBLIC intmax_t imaxabs( intmax_t j );

/* Return quotient (quot) and remainder (rem) of an integer division in the
   imaxdiv_t struct.
*/
_PDCLIB_PUBLIC imaxdiv_t imaxdiv( intmax_t numer, intmax_t denom );

/* Separate the character array nptr into three parts: A (possibly empty)
   sequence of whitespace characters, a character representation of an integer
   to the given base, and trailing invalid characters (including the terminating
   null character). If base is 0, assume it to be 10, unless the integer
   representation starts with 0x / 0X (setting base to 16) or 0 (setting base to
   8). If given, base can be anything from 0 to 36, using the 26 letters of the
   base alphabet (both lowercase and uppercase) as digits 10 through 35.
   The integer representation is then converted into the return type of the
   function. It can start with a '+' or '-' sign. If the sign is '-', the result
   of the conversion is negated.
   If the conversion is successful, the converted value is returned. If endptr
   is not a NULL pointer, a pointer to the first trailing invalid character is
   returned in *endptr.
   If no conversion could be performed, zero is returned (and nptr in *endptr,
   if endptr is not a NULL pointer). If the converted value does not fit into
   the return type, the functions return INTMAX_MIN, INTMAX_MAX, or UINTMAX_MAX,
   respectively, depending on the sign of the integer representation and the
   return type, and errno is set to ERANGE.
*/
/* This function is equivalent to strtol() / strtoul() in <stdlib.h>, but on
   the potentially larger type.
*/
_PDCLIB_PUBLIC intmax_t strtoimax( const char * _PDCLIB_restrict nptr, char ** _PDCLIB_restrict endptr, int base );
_PDCLIB_PUBLIC uintmax_t strtoumax( const char * _PDCLIB_restrict nptr, char ** _PDCLIB_restrict endptr, int base );

/* TODO: wcstoimax(), wcstoumax() */

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_INTTYPES_H
#include _PDCLIB_EXTEND_INTTYPES_H
#endif

#ifdef __cplusplus
}
#endif

#endif
