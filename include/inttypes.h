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

#if _PDCLIB_INT_LEAST8_MAX > _PDCLIB_INT_MAX
#define PRIdLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, d ) )
#define PRIiLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, i ) )
#define PRIoLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, o ) )
#define PRIuLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, u ) )
#define PRIxLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, x ) )
#define PRIXLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, X ) )
#else
#define PRIdLEAST8  "d"
#define PRIiLEAST8  "i"
#define PRIoLEAST8  "o"
#define PRIuLEAST8  "u"
#define PRIxLEAST8  "x"
#define PRIXLEAST8  "X"
#endif

#if _PDCLIB_INT_FAST8_MAX > _PDCLIB_INT_MAX
#define PRIdFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, d ) )
#define PRIiFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, i ) )
#define PRIoFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, o ) )
#define PRIuFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, u ) )
#define PRIxFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, x ) )
#define PRIXFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, X ) )
#else
#define PRIdFAST8  "d"
#define PRIiFAST8  "i"
#define PRIoFAST8  "o"
#define PRIuFAST8  "u"
#define PRIxFAST8  "x"
#define PRIXFAST8  "X"
#endif

#if _PDCLIB_INT_LEAST16_MAX > _PDCLIB_INT_MAX
#define PRIdLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, d ) )
#define PRIiLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, i ) )
#define PRIoLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, o ) )
#define PRIuLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, u ) )
#define PRIxLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, x ) )
#define PRIXLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, X ) )
#else
#define PRIdLEAST16  "d"
#define PRIiLEAST16  "i"
#define PRIoLEAST16  "o"
#define PRIuLEAST16  "u"
#define PRIxLEAST16  "x"
#define PRIXLEAST16  "X"
#endif

#if _PDCLIB_INT_FAST16_MAX > _PDCLIB_INT_MAX
#define PRIdFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, d ) )
#define PRIiFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, i ) )
#define PRIoFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, o ) )
#define PRIuFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, u ) )
#define PRIxFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, x ) )
#define PRIXFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, X ) )
#else
#define PRIdFAST16  "d"
#define PRIiFAST16  "i"
#define PRIoFAST16  "o"
#define PRIuFAST16  "u"
#define PRIxFAST16  "x"
#define PRIXFAST16  "X"
#endif

#if _PDCLIB_INT_LEAST32_MAX > _PDCLIB_INT_MAX
#define PRIdLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, d ) )
#define PRIiLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, i ) )
#define PRIoLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, o ) )
#define PRIuLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, u ) )
#define PRIxLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, x ) )
#define PRIXLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, X ) )
#else
#define PRIdLEAST32  "d"
#define PRIiLEAST32  "i"
#define PRIoLEAST32  "o"
#define PRIuLEAST32  "u"
#define PRIxLEAST32  "x"
#define PRIXLEAST32  "X"
#endif

#if _PDCLIB_INT_FAST32_MAX > _PDCLIB_INT_MAX
#define PRIdFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, d ) )
#define PRIiFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, i ) )
#define PRIoFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, o ) )
#define PRIuFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, u ) )
#define PRIxFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, x ) )
#define PRIXFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, X ) )
#else
#define PRIdFAST32  "d"
#define PRIiFAST32  "i"
#define PRIoFAST32  "o"
#define PRIuFAST32  "u"
#define PRIxFAST32  "x"
#define PRIXFAST32  "X"
#endif

#if _PDCLIB_INT_LEAST64_MAX > _PDCLIB_INT_MAX
#define PRIdLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, d ) )
#define PRIiLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, i ) )
#define PRIoLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, o ) )
#define PRIuLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, u ) )
#define PRIxLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, x ) )
#define PRIXLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, X ) )
#else
#define PRIdLEAST64  "d"
#define PRIiLEAST64  "i"
#define PRIoLEAST64  "o"
#define PRIuLEAST64  "u"
#define PRIxLEAST64  "x"
#define PRIXLEAST64  "X"
#endif

#if _PDCLIB_INT_FAST64_MAX > _PDCLIB_INT_MAX
#define PRIdFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, d ) )
#define PRIiFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, i ) )
#define PRIoFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, o ) )
#define PRIuFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, u ) )
#define PRIxFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, x ) )
#define PRIXFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, X ) )
#else
#define PRIdFAST64  "d"
#define PRIiFAST64  "i"
#define PRIoFAST64  "o"
#define PRIuFAST64  "u"
#define PRIxFAST64  "x"
#define PRIXFAST64  "X"
#endif

#if _PDCLIB_INTMAX_MAX > _PDCLIB_INT_MAX
#define PRIdMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, d ) )
#define PRIiMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, i ) )
#define PRIoMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, o ) )
#define PRIuMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, u ) )
#define PRIxMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, x ) )
#define PRIXMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, X ) )
#else
#define PRIdMAX  "d"
#define PRIiMAX  "i"
#define PRIoMAX  "o"
#define PRIuMAX  "u"
#define PRIxMAX  "x"
#define PRIXMAX  "X"
#endif

#if _PDCLIB_INTPTR_MAX > _PDCLIB_INT_MAX
#define PRIdPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, d ) )
#define PRIiPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, i ) )
#define PRIoPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, o ) )
#define PRIuPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, u ) )
#define PRIxPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, x ) )
#define PRIXPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, X ) )
#else
#define PRIdPTR  "d"
#define PRIiPTR  "i"
#define PRIoPTR  "o"
#define PRIuPTR  "u"
#define PRIxPTR  "x"
#define PRIXPTR  "X"
#endif

#define SCNdLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, d ) )
#define SCNiLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, i ) )
#define SCNoLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, o ) )
#define SCNuLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, u ) )
#define SCNxLEAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, x ) )

#define SCNdFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, d ) )
#define SCNiFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, i ) )
#define SCNoFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, o ) )
#define SCNuFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, u ) )
#define SCNxFAST8  _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST8_PREFIX, x ) )

#define SCNdLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, d ) )
#define SCNiLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, i ) )
#define SCNoLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, o ) )
#define SCNuLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, u ) )
#define SCNxLEAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, x ) )

#define SCNdFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, d ) )
#define SCNiFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, i ) )
#define SCNoFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, o ) )
#define SCNuFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, u ) )
#define SCNxFAST16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST16_PREFIX, x ) )

#define SCNdLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, d ) )
#define SCNiLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, i ) )
#define SCNoLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, o ) )
#define SCNuLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, u ) )
#define SCNxLEAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, x ) )

#define SCNdFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, d ) )
#define SCNiFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, i ) )
#define SCNoFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, o ) )
#define SCNuFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, u ) )
#define SCNxFAST32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST32_PREFIX, x ) )

#define SCNdLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, d ) )
#define SCNiLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, i ) )
#define SCNoLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, o ) )
#define SCNuLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, u ) )
#define SCNxLEAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, x ) )

#define SCNdFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, d ) )
#define SCNiFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, i ) )
#define SCNoFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, o ) )
#define SCNuFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, u ) )
#define SCNxFAST64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_FAST64_PREFIX, x ) )

#define SCNdMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, d ) )
#define SCNiMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, i ) )
#define SCNoMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, o ) )
#define SCNuMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, u ) )
#define SCNxMAX _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTMAX_PREFIX, x ) )

#define SCNdPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, d ) )
#define SCNiPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, i ) )
#define SCNoPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, o ) )
#define SCNuPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, u ) )
#define SCNxPTR _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INTPTR_PREFIX, x ) )

/* The exact-width types (int8_t, int16_t, ...) are *optional*, as not all
   architectures support the necessary 8-bits-per-byte two's complement
   native types.
*/

#if _PDCLIB_TWOS_COMPLEMENT == 1

#if _PDCLIB_INT_LEAST8_MAX == 0x7f
#if _PDCLIB_INT_LEAST8_MAX > _PDCLIB_INT_MAX
#define PRId8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, d ) )
#define PRIi8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, i ) )
#define PRIo8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, o ) )
#define PRIu8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, u ) )
#define PRIx8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, x ) )
#define PRIX8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, X ) )
#endif
#define SCNd8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, d ) )
#define SCNi8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, i ) )
#define SCNo8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, o ) )
#define SCNu8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, u ) )
#define SCNx8 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST8_PREFIX, x ) )
#endif

#if _PDCLIB_INT_LEAST16_MAX == 0x7fff
#if _PDCLIB_INT_LEAST16_MAX > _PDCLIB_INT_MAX
#define PRId16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, d ) )
#define PRIi16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, i ) )
#define PRIo16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, o ) )
#define PRIu16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, u ) )
#define PRIx16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, x ) )
#define PRIX16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, X ) )
#endif
#define SCNd16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, d ) )
#define SCNi16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, i ) )
#define SCNo16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, o ) )
#define SCNu16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, u ) )
#define SCNx16 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST16_PREFIX, x ) )
#endif

#if _PDCLIB_INT_LEAST32_MAX == 0x7fffffffl
#if _PDCLIB_INT_LEAST32_MAX > _PDCLIB_INT_MAX
#define PRId32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, d ) )
#define PRIi32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, i ) )
#define PRIo32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, o ) )
#define PRIu32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, u ) )
#define PRIx32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, x ) )
#define PRIX32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, X ) )
#endif
#define SCNd32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, d ) )
#define SCNi32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, i ) )
#define SCNo32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, o ) )
#define SCNu32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, u ) )
#define SCNx32 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST32_PREFIX, x ) )
#endif

#if _PDCLIB_INT_LEAST64_MAX == 0x7fffffffffffffffll
#if _PDCLIB_INT_LEAST64_MAX > _PDCLIB_INT_MAX
#define PRId64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, d ) )
#define PRIi64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, i ) )
#define PRIo64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, o ) )
#define PRIu64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, u ) )
#define PRIx64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, x ) )
#define PRIX64 _PDCLIB_value2string( _PDCLIB_concat( _PDCLIB_INT_LEAST64_PREFIX, X ) )
#endif
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
