/* Internal PDCLib configuration <_PDCLIB_config.h>
   ("Example" platform target, for PDCLib development)

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_CONFIG_H
#define _PDCLIB_CONFIG_H _PDCLIB_CONFIG_H

/* -------------------------------------------------------------------------- */
/* Misc                                                                       */
/* -------------------------------------------------------------------------- */

/* Helper macros also documented in _PDCLIB_internal.h, but defined here as   */
/* they are needed in this file already.                                      */
/* _PDCLIB_cc( x, y ) concatenates two preprocessor tokens without extending. */
/* _PDCLIB_concat( x, y ) concatenates two preprocessor tokens with extending */
#define _PDCLIB_cc( x, y )     x ## y
#define _PDCLIB_concat( x, y ) _PDCLIB_cc( x, y )

/* exit() can signal success to the host environment by the value of zero or  */
/* the constant EXIT_SUCCESS. Failure is signaled by EXIT_FAILURE. Note that  */
/* any other return value is "implementation-defined", i.e. your environment  */
/* is not required to handle it gracefully. Set your definitions here.        */
#define _PDCLIB_SUCCESS 0
#define _PDCLIB_FAILURE -1

/* qsort() in <stdlib.h> requires a function that swaps two memory areas.     */
/* Below is a naive implementation that can be improved significantly for     */
/* specific platforms, e.g. by swapping int instead of char.                  */
#define _PDCLIB_memswp( i, j, size ) \
    char tmp; \
    do { \
        tmp = *i; \
        *i++ = *j; \
        *j++ = tmp; \
    } while ( --size );

/* Define this to some compiler directive that can be written after the       */
/* parameter list of a function declaration to indicate the function does     */
/* never return. If your compiler does not support such a directive, define   */
/* to nothing. (This is to avoid warnings with the exit functions under GCC   */
/* when compiling with C99/C++ settings, where C11 _Noreturn is unavailable.) */
#define _PDCLIB_NORETURN __attribute__(( noreturn ))

/* -------------------------------------------------------------------------- */
/* Symbol Visibility                                                          */
/* -------------------------------------------------------------------------- */

/* This defines _PDCLIB_PUBLIC to indicate external linkage, and _PDCLIB_LOCAL
   to indicate local linkage.
*/

#ifdef _PDCLIB_STATIC_DEFINE
  #define _PDCLIB_PUBLIC
  #define _PDCLIB_LOCAL
#else
  #if defined _WIN32 || defined __CYGWIN__
    #ifdef _PDCLIB_BUILD
      #ifdef __GNUC__
        #define _PDCLIB_PUBLIC __attribute__ ((dllexport))
      #else
        #define _PDCLIB_PUBLIC __declspec(dllexport)
      #endif
    #else
      #ifdef __GNUC__
        #define _PDCLIB_PUBLIC __attribute__ ((dllimport))
      #else
        #define _PDCLIB_PUBLIC __declspec(dllimport)
      #endif
    #endif
    #define _PDCLIB_LOCAL
  #else
    #if __GNUC__ >= 4
      #define _PDCLIB_PUBLIC __attribute__ ((visibility ("default")))
      #define _PDCLIB_LOCAL  __attribute__ ((visibility ("hidden")))
    #else
      #define _PDCLIB_PUBLIC
      #define _PDCLIB_LOCAL
    #endif
  #endif
#endif

/* -------------------------------------------------------------------------- */
/* Integers                                                                   */
/* -------------------------------------------------------------------------- */
/* The defines below make use of predefines offered by GCC and clang. If you  */
/* adapt PDCLib for a different compiler family, you will have to use what    */
/* that compiler provides, or enter actual values.                            */
/* -------------------------------------------------------------------------- */

/* At the point of writing, PDCLib makes no provisions for, nor has it been   */
/* tested, on a platform that uses signed magnitude or one's complement to    */
/* encode its integers. Most importantly, there are no guarantees that the    */
/* negative zero of those encodings is in any form handled gracefully.        */
#define _PDCLIB_TWOS_COMPLEMENT 1

/* 1234 for little endian, 4321 for big endian; other types not supported.    */
#define _PDCLIB_ENDIANESS __BYTE_ORDER__

/* Calculation of a minimum value from a given maximum for two's complement.  */
/* (For convenience only, used only in this header file below.)               */
#define _PDCLIB_MIN_CALC( max ) ( ( - max ) - 1 )

/* Now, introducting the various predefines to the _PDCLIB_* namespace, so    */
/* the rest of PDCLib can work with that and adapting to a different compiler */
/* will require changes only in this one file.                                */

/* Bits in a char */
#define _PDCLIB_CHAR_BIT __CHAR_BIT__

/* Maximum and minimum values of signed / unsigned char                       */
#define _PDCLIB_SCHAR_MAX __SCHAR_MAX__
#define _PDCLIB_SCHAR_MIN _PDCLIB_MIN_CALC( __SCHAR_MAX__ )
#define _PDCLIB_UCHAR_MAX ( __SCHAR_MAX__ * 2 + 1 )

/* Whether the 'char' type is unsigned                                        */
#ifdef __CHAR_UNSIGNED__
#define _PDCLIB_CHAR_MAX _PDCLIB_UCHAR_MAX
#define _PDCLIB_CHAR_MIN 0
#else
#define _PDCLIB_CHAR_MAX _PDCLIB_SCHAR_MAX
#define _PDCLIB_CHAR_MIN _PDCLIB_SCHAR_MIN
#endif

/* Maximum and minimum values of signed / unsigned short                      */
#define _PDCLIB_SHRT_MAX __SHRT_MAX__
#define _PDCLIB_SHRT_MIN _PDCLIB_MIN_CALC( __SHRT_MAX__ )
#define _PDCLIB_USHRT_MAX ( __SHRT_MAX__ * 2u + 1 )

/* Maximum and minimum values of signed / unsigned int                        */
#define _PDCLIB_INT_MAX __INT_MAX__
#define _PDCLIB_INT_MIN _PDCLIB_MIN_CALC( __INT_MAX__ )
#define _PDCLIB_UINT_MAX ( __INT_MAX__ * 2u + 1 )

/* Maximum and minimum values of signed / unsigned long                       */
#define _PDCLIB_LONG_MAX __LONG_MAX__
#define _PDCLIB_LONG_MIN _PDCLIB_MIN_CALC( __LONG_MAX__ )
#define _PDCLIB_ULONG_MAX ( __LONG_MAX__ * 2ul + 1 )

/* Maximum and minimum values of signed / unsigned long long                  */
#define _PDCLIB_LLONG_MAX __LONG_LONG_MAX__
#define _PDCLIB_LLONG_MIN _PDCLIB_MIN_CALC( __LONG_LONG_MAX__ )
#define _PDCLIB_ULLONG_MAX ( __LONG_LONG_MAX__ * 2ull + 1 )

/* -------------------------------------------------------------------------- */
/* <stdint.h> defines a set of integer types that are of a minimum width, and */
/* "usually fastest" on the system. (If, for example, accessing a single char */
/* requires the CPU to access a complete int and then mask out the char, the  */
/* "usually fastest" type of at least 8 bits would be int, not char.)         */
/* If you do not have information on the relative performance of the types,   */
/* the standard allows you to define any type that meets minimum width and    */
/* signedness requirements.                                                   */
/* The first define is the appropriate basic type (e.g. "long int"), second   */
/* its max value, the third its min value (both expressed in the given type). */
/* The same follows for the unsigned type (for which the minimum value is     */
/* obviously zero and need not be defined).                                   */
/* There *are* predefines provided for the printf()/scanf() length specifiers */
/* but tunneling them through here would have added many lines of repetitive  */
/* and mostly redundant defines. They are determined in <_PDCLIB_internal.h>. */
/* -------------------------------------------------------------------------- */

/* int_fast8_t / uint_fast8_t                                                 */
#define _PDCLIB_int_fast8_t        __INT_FAST8_TYPE__
#define _PDCLIB_INT_FAST8_MAX      __INT_FAST8_MAX__
#define _PDCLIB_INT_FAST8_MIN      _PDCLIB_MIN_CALC( __INT_FAST8_MAX__ )
#define _PDCLIB_uint_fast8_t       __UINT_FAST8_TYPE__
#define _PDCLIB_UINT_FAST8_MAX     __UINT_FAST8_MAX__

/* int_least8_t / uint_least8_t                                               */
#define _PDCLIB_int_least8_t       __INT_LEAST8_TYPE__
#define _PDCLIB_INT_LEAST8_MAX     __INT_LEAST8_MAX__
#define _PDCLIB_INT_LEAST8_MIN     _PDCLIB_MIN_CALC( __INT_LEAST8_MAX__ )
#define _PDCLIB_uint_least8_t      __UINT_LEAST8_TYPE__
#define _PDCLIB_UINT_LEAST8_MAX    __UINT_LEAST8_MAX__

/* int_fast16_t / uint_fast16_t                                               */
#define _PDCLIB_int_fast16_t       __INT_FAST16_TYPE__
#define _PDCLIB_INT_FAST16_MAX     __INT_FAST16_MAX__
#define _PDCLIB_INT_FAST16_MIN     _PDCLIB_MIN_CALC( __INT_FAST16_MAX__ )
#define _PDCLIB_uint_fast16_t      __UINT_FAST16_TYPE__
#define _PDCLIB_UINT_FAST16_MAX    __UINT_FAST16_MAX__

/* int_least16_t / uint_least16_t                                             */
#define _PDCLIB_int_least16_t      __INT_LEAST16_TYPE__
#define _PDCLIB_INT_LEAST16_MAX    __INT_LEAST16_MAX__
#define _PDCLIB_INT_LEAST16_MIN    _PDCLIB_MIN_CALC( __INT_LEAST16_MAX__ )
#define _PDCLIB_uint_least16_t     __UINT_LEAST16_TYPE__
#define _PDCLIB_UINT_LEAST16_MAX   __UINT_LEAST16_MAX__

/* int_fast32_t / uint_fast32_t                                               */
#define _PDCLIB_int_fast32_t       __INT_FAST32_TYPE__
#define _PDCLIB_INT_FAST32_MAX     __INT_FAST32_MAX__
#define _PDCLIB_INT_FAST32_MIN     _PDCLIB_MIN_CALC( __INT_FAST32_MAX__ )
#define _PDCLIB_uint_fast32_t      __UINT_FAST32_TYPE__
#define _PDCLIB_UINT_FAST32_MAX    __UINT_FAST32_MAX__

/* int_least32_t / uint_least32_t                                             */
#define _PDCLIB_int_least32_t      __INT_LEAST32_TYPE__
#define _PDCLIB_INT_LEAST32_MAX    __INT_LEAST32_MAX__
#define _PDCLIB_INT_LEAST32_MIN    _PDCLIB_MIN_CALC( __INT_LEAST32_MAX__ )
#define _PDCLIB_uint_least32_t     __UINT_LEAST32_TYPE__
#define _PDCLIB_UINT_LEAST32_MAX   __UINT_LEAST32_MAX__

/* int_fast64_t / uint_fast64_t                                               */
#define _PDCLIB_int_fast64_t       __INT_FAST64_TYPE__
#define _PDCLIB_INT_FAST64_MAX     __INT_FAST64_MAX__
#define _PDCLIB_INT_FAST64_MIN     _PDCLIB_MIN_CALC( __INT_FAST64_MAX__ )
#define _PDCLIB_uint_fast64_t      __UINT_FAST64_TYPE__
#define _PDCLIB_UINT_FAST64_MAX    __UINT_FAST64_MAX__

/* int_least64_t / uint_least64_t                                             */
#define _PDCLIB_int_least64_t      __INT_LEAST64_TYPE__
#define _PDCLIB_INT_LEAST64_MAX    __INT_LEAST64_MAX__
#define _PDCLIB_INT_LEAST64_MIN    _PDCLIB_MIN_CALC( __INT_LEAST64_MAX__ )
#define _PDCLIB_uint_least64_t     __UINT_LEAST64_TYPE__
#define _PDCLIB_UINT_LEAST64_MAX   __UINT_LEAST64_MAX__

/* Exact-width integer types. These are *optional*. If your platform does not */
/* support types of these exact widths in two's complement encoding, just     */
/* leave them undefined.                                                      */
#define _PDCLIB_int8_t   __INT8_TYPE__
#define _PDCLIB_int16_t  __INT16_TYPE__
#define _PDCLIB_int32_t  __INT32_TYPE__
#define _PDCLIB_int64_t  __INT64_TYPE__
#define _PDCLIB_uint8_t  __UINT8_TYPE__
#define _PDCLIB_uint16_t __UINT16_TYPE__
#define _PDCLIB_uint32_t __UINT32_TYPE__
#define _PDCLIB_uint64_t __UINT64_TYPE__

/* INTn_C / UINTn_C macros to define int_leastN_t / uint_leastN_t literals.   */
#if defined( __INT8_C )
/* GCC                                                                        */
#define _PDCLIB_INT_LEAST8_C       __INT8_C
#define _PDCLIB_UINT_LEAST8_C      __UINT8_C
#define _PDCLIB_INT_LEAST16_C      __INT16_C
#define _PDCLIB_UINT_LEAST16_C     __UINT16_C
#define _PDCLIB_INT_LEAST32_C      __INT32_C
#define _PDCLIB_UINT_LEAST32_C     __UINT32_C
#define _PDCLIB_INT_LEAST64_C      __INT64_C
#define _PDCLIB_UINT_LEAST64_C     __UINT64_C
#elif defined( __INT8_C_SUFFIX__ )
/* Clang                                                                      */
#define _PDCLIB_INT_LEAST8_C(c)    _PDCLIB_concat( c, __INT8_C_SUFFIX__ )
#define _PDCLIB_UINT_LEAST8_C(c)   _PDCLIB_concat( c, __UINT8_C_SUFFIX__ )
#define _PDCLIB_INT_LEAST16_C(c)   _PDCLIB_concat( c, __INT16_C_SUFFIX__ )
#define _PDCLIB_UINT_LEAST16_C(c)  _PDCLIB_concat( c, __UINT16_C_SUFFIX__ )
#define _PDCLIB_INT_LEAST32_C(c)   _PDCLIB_concat( c, __INT32_C_SUFFIX__ )
#define _PDCLIB_UINT_LEAST32_C(c)  _PDCLIB_concat( c, __UINT32_C_SUFFIX__ )
#define _PDCLIB_INT_LEAST64_C(c)   _PDCLIB_concat( c, __INT64_C_SUFFIX__ )
#define _PDCLIB_UINT_LEAST64_C(c)  _PDCLIB_concat( c, __UINT64_C_SUFFIX__ )
#else
#error Please create your own _PDCLIB_config.h. Using the existing one as-is will not work. (Unsupported *INTn_C macros.)
#endif

/* <stdlib.h> defines the div() function family that allows taking quotient   */
/* and remainder of an integer division in one operation. Many platforms      */
/* support this in hardware / opcode, and the standard permits ordering of    */
/* the return structure in any way to fit the hardware. That is why those     */
/* structs can be configured here.                                            */

struct _PDCLIB_div_t
{
    int quot;
    int rem;
};

struct _PDCLIB_ldiv_t
{
    long int quot;
    long int rem;
};

struct _PDCLIB_lldiv_t
{
    long long int quot;
    long long int rem;
};

/* -------------------------------------------------------------------------- */
/* What follows are a couple of "special" typedefs and their limits.          */
/* -------------------------------------------------------------------------- */

/* The result type of substracting two pointers                               */
#define _PDCLIB_ptrdiff_t   __PTRDIFF_TYPE__
#define _PDCLIB_PTRDIFF_MAX __PTRDIFF_MAX__
#define _PDCLIB_PTRDIFF_MIN _PDCLIB_MIN_CALC( __PTRDIFF_MAX__ )

/* An integer type that can be accessed as atomic entity (think asynchronous  */
/* interrupts). In a freestanding environment, the type itself need not be    */
/* defined, but its limits must. (Don't ask.) GCC is so kind to predefine it, */
/* but clang is only giving us its MAX value, so we use that to identify the  */
/* type in _PDCLIB_int.h if the type definition is unavailable.               */
#ifdef __SIG_ATOMIC_TYPE__
#define _PDCLIB_sig_atomic_t   __SIG_ATOMIC_TYPE__
#endif
#define _PDCLIB_SIG_ATOMIC_MAX __SIG_ATOMIC_MAX__
#define _PDCLIB_SIG_ATOMIC_MIN _PDCLIB_MIN_CALC( __SIG_ATOMIC_MAX__ )

/* Result type of the 'sizeof' operator (must be unsigned).                   */
/* Note: In <stdint.h>, this is taken as the base for RSIZE_MAX, the limit    */
/* for the bounds-checking interfaces of Annex K. The recommendation by the   */
/* standard is to use ( SIZE_MAX >> 1 ) when "targeting machines with large   */
/* addess spaces", whereas small address spaces should use SIZE_MAX directly. */
#define _PDCLIB_size_t   __SIZE_TYPE__
#define _PDCLIB_SIZE_MAX __SIZE_MAX__

/* Large enough an integer to hold all character codes of the widest          */
/* supported locale.                                                          */
#define _PDCLIB_wchar_t   __WCHAR_TYPE__
#define _PDCLIB_WCHAR_MAX __WCHAR_MAX__
#define _PDCLIB_WCHAR_MIN __WCHAR_MIN__

/* Large enough an integer to hold all character codes of the widest          */
/* supported locale plus WEOF (which needs not to be equal to EOF, nor needs  */
/* to be of negative value).                                                  */
#define _PDCLIB_wint_t   __WINT_TYPE__
#define _PDCLIB_WINT_MAX __WINT_MAX__
#define _PDCLIB_WINT_MIN __WINT_MIN__

/* Integer types capable of taking the (cast) value of a void *, and having   */
/* the value cast back to void *, comparing equal to the original.            */
#define _PDCLIB_intptr_t     __INTPTR_TYPE__
#define _PDCLIB_INTPTR_MAX   __INTPTR_MAX__
#define _PDCLIB_INTPTR_MIN   _PDCLIB_MIN_CALC( __INTPTR_MAX__ )
#define _PDCLIB_uintptr_t    __UINTPTR_TYPE__
#define _PDCLIB_UINTPTR_MAX  __UINTPTR_MAX__

/* Largest supported integer type. Implementation note: see _PDCLIB_atomax(). */
#define _PDCLIB_intmax_t     __INTMAX_TYPE__
#define _PDCLIB_INTMAX_MAX   __INTMAX_MAX__
#define _PDCLIB_INTMAX_MIN   _PDCLIB_MIN_CALC( __INTMAX_MAX__ )
#define _PDCLIB_INTMAX_C     __INTMAX_C
#define _PDCLIB_uintmax_t    __UINTMAX_TYPE__
#define _PDCLIB_UINTMAX_MAX  __UINTMAX_MAX__
#define _PDCLIB_UINTMAX_C    __UINTMAX_C

/* <inttypes.h> defines imaxdiv(), which is equivalent to the div() function  */
/* family (see further above) with intmax_t as basis.                         */
struct _PDCLIB_imaxdiv_t
{
    _PDCLIB_intmax_t quot;
    _PDCLIB_intmax_t rem;
};

/* -------------------------------------------------------------------------- */
/* Time types, limits, constants, and paths                                   */
/* -------------------------------------------------------------------------- */

/* _PDCLIB_time is the type for type_t; _PDCLIB_clock for clock_t. Both types */
/* are defined as "real types capable of representing times". The "range and  */
/* precision of times representable" is implementation-defined.               */

/* For clock_t, the standard defines that dividing the result of clock() by   */
/* CLOCKS_PER_SEC gives the seconds elapsed.                                  */
#ifdef __CYGWIN__
#define _PDCLIB_clock_t unsigned long
#else
#define _PDCLIB_clock_t long
#endif
#define _PDCLIB_CLOCKS_PER_SEC 1000000

/* For time_t, no such divider exists. Most implementations use a count of    */
/* seconds since a specified epoch. While PDCLib really should support other  */
/* encodings as well, for now "count of seconds" is the only supported one.   */
/* MIN / MAX values for time_t are not required by the standard (and they are */
/* not "exported" from the _PDCLIB namespace), but they are useful in support */
/* of the _tzcode implementation.                                             */
#ifdef __MINGW64__
#define _PDCLIB_time_t long long
#define _PDCLIB_TIME_MAX __LONG_LONG_MAX__
#define _PDCLIB_TIME_MIN _PDCLIB_MIN_CALC( __LONG_LONG_MAX__ )
#else
#define _PDCLIB_time_t long
#define _PDCLIB_TIME_MAX __LONG_MAX__
#define _PDCLIB_TIME_MIN _PDCLIB_MIN_CALC( __LONG_MAX__ )
#endif

/* "Unix time" uses 1970-01-01T00:00:00 as "epoch". If your system uses a     */
/* different "zero point" for its timestamps, set this to the offset between  */
/* your epoch and Unix epoch. (For example, NTP uses 1900-01-01T00:00:00 as   */
/* epoch, giving an offset of (70 * 365 + 17) * 86400 = 220898800 seconds.)   */
#define _PDCLIB_EPOCH_BIAS INT64_C( 0 )

/* Leave this alone for now.                                                  */
#define _PDCLIB_TIME_UTC 1

/* Path to TZ data.                                                           */
/* IMPORTANT: *Must* end with separator character!                            */
/* It does make it much easier for the time data handling code if this detail */
/* can be relied upon and need not be handled in code.                        */
#define _PDCLIB_TZDIR "/usr/share/zoneinfo/"

/* Path to default (local) timezone                                           */
#define _PDCLIB_TZDEFAULT "/etc/localtime"

/* -------------------------------------------------------------------------- */
/* Floating Point                                                             */
/* -------------------------------------------------------------------------- */

/* Whether the implementation rounds toward zero (0), to nearest (1), toward  */
/* positive infinity (2), or toward negative infinity (3). (-1) signifies     */
/* indeterminable rounding, any other value implementation-specific rounding. */
#define _PDCLIB_FLT_ROUNDS -1

/* Check <float.h> for explanations on each of these values.                  */
#define _PDCLIB_FLT_EVAL_METHOD   __FLT_EVAL_METHOD__

#define _PDCLIB_FLT_HAS_SUBNORM   __FLT_HAS_DENORM__
#define _PDCLIB_DBL_HAS_SUBNORM   __DBL_HAS_DENORM__
#define _PDCLIB_LDBL_HAS_SUBNORM  __LDBL_HAS_DENORM__

#define _PDCLIB_FLT_RADIX         __FLT_RADIX__

#define _PDCLIB_FLT_MANT_DIG      __FLT_MANT_DIG__
#define _PDCLIB_DBL_MANT_DIG      __DBL_MANT_DIG__
#define _PDCLIB_LDBL_MANT_DIG     __LDBL_MANT_DIG__

#define _PDCLIB_FLT_DECIMAL_DIG   __FLT_DECIMAL_DIG__
#define _PDCLIB_DBL_DECIMAL_DIG   __DBL_DECIMAL_DIG__
#define _PDCLIB_LDBL_DECIMAL_DIG  __LDBL_DECIMAL_DIG__

#define _PDCLIB_DECIMAL_DIG       __DECIMAL_DIG__

#define _PDCLIB_FLT_DIG           __FLT_DIG__
#define _PDCLIB_DBL_DIG           __DBL_DIG__
#define _PDCLIB_LDBL_DIG          __LDBL_DIG__

#define _PDCLIB_FLT_MIN_EXP       __FLT_MIN_EXP__
#define _PDCLIB_DBL_MIN_EXP       __DBL_MIN_EXP__
#define _PDCLIB_LDBL_MIN_EXP      __LDBL_MIN_EXP__

#define _PDCLIB_FLT_MIN_10_EXP    __FLT_MIN_10_EXP__
#define _PDCLIB_DBL_MIN_10_EXP    __DBL_MIN_10_EXP__
#define _PDCLIB_LDBL_MIN_10_EXP   __LDBL_MIN_10_EXP__

#define _PDCLIB_FLT_MAX_EXP       __FLT_MAX_EXP__
#define _PDCLIB_DBL_MAX_EXP       __DBL_MAX_EXP__
#define _PDCLIB_LDBL_MAX_EXP      __LDBL_MAX_EXP__

#define _PDCLIB_FLT_MAX_10_EXP    __FLT_MAX_10_EXP__
#define _PDCLIB_DBL_MAX_10_EXP    __DBL_MAX_10_EXP__
#define _PDCLIB_LDBL_MAX_10_EXP   __LDBL_MAX_10_EXP__

#define _PDCLIB_FLT_MAX           __FLT_MAX__
#define _PDCLIB_DBL_MAX           __DBL_MAX__
#define _PDCLIB_LDBL_MAX          __LDBL_MAX__

#define _PDCLIB_FLT_EPSILON       __FLT_EPSILON__
#define _PDCLIB_DBL_EPSILON       __DBL_EPSILON__
#define _PDCLIB_LDBL_EPSILON      __LDBL_EPSILON__

#define _PDCLIB_FLT_MIN           __FLT_MIN__
#define _PDCLIB_DBL_MIN           __DBL_MIN__
#define _PDCLIB_LDBL_MIN          __LDBL_MIN__

#define _PDCLIB_FLT_TRUE_MIN      __FLT_DENORM_MIN__
#define _PDCLIB_DBL_TRUE_MIN      __DBL_DENORM_MIN__
#define _PDCLIB_LDBL_TRUE_MIN     __LDBL_DENORM_MIN__

/* Macros for deconstructing floating point values                            */
#define _PDCLIB_DBL_SIGN( bytes ) ( ( (unsigned)bytes[7] & 0x80 ) >> 7 )
#define _PDCLIB_DBL_DEC( bytes ) ( ( _PDCLIB_DBL_EXP( bytes ) > 0 ) ? 1 : 0 )
#define _PDCLIB_DBL_EXP( bytes ) ( ( ( (unsigned)bytes[7] & 0x7f ) << 4 ) | ( ( (unsigned)bytes[6] & 0xf0 ) >> 4 ) )
#define _PDCLIB_DBL_BIAS 1023
#define _PDCLIB_DBL_MANT_START( bytes ) ( bytes + 6 )

/* Most platforms today use IEEE 754 single precision for 'float', and double */
/* precision for 'double'. But type 'long double' varies. We use what the     */
/* compiler states about LDBL_MANT_DIG to determine the type.                 */
#if _PDCLIB_LDBL_MANT_DIG == 64

/* Intel "Extended Precision" format, using 80 bits (64bit mantissa) */
#define _PDCLIB_LDBL_SIGN( bytes ) ( ( (unsigned)bytes[9] & 0x80 ) >> 7 )
#define _PDCLIB_LDBL_DEC( bytes ) ( ( (unsigned)bytes[7] & 0x80 ) >> 7 )
#define _PDCLIB_LDBL_EXP( bytes ) ( ( ( (unsigned)bytes[9] & 0x7f ) << 8 ) | (unsigned)bytes[8] )
#define _PDCLIB_LDBL_BIAS 16383
#define _PDCLIB_LDBL_MANT_START( bytes ) ( bytes + 7 )

#elif _PDCLIB_LDBL_MANT_DIG == 113

/* IEEE "Quadruple Precision" format, using 128 bits (113bit mantissa) */
#define _PDCLIB_LDBL_SIGN( bytes ) ( ( (unsigned)bytes[15] & 0x80 ) >> 7 )
#define _PDCLIB_LDBL_DEC( bytes ) ( ( _PDCLIB_LDBL_EXP( bytes ) > 0 ) ? 1 : 0 )
#define _PDCLIB_LDBL_EXP( bytes ) ( ( ( (unsigned)bytes[15] & 0x7f ) << 8 ) | (unsigned)bytes[14] )
#define _PDCLIB_LDBL_BIAS 16383
#define _PDCLIB_LDBL_MANT_START( bytes ) ( bytes + 13 )

#else

/* IEEE "Double Precision" format, using 64 bits (53bit mantissa,
   same as DBL above) */
#define _PDCLIB_LDBL_SIGN( bytes ) ( ( (unsigned)bytes[7] & 0x80 ) >> 7 )
#define _PDCLIB_LDBL_DEC( bytes ) ( ( _PDCLIB_LDBL_EXP( bytes ) > 0 ) ? 1 : 0 )
#define _PDCLIB_LDBL_EXP( bytes ) ( ( ( (unsigned)bytes[7] & 0x7f ) << 4 ) | ( ( (unsigned)bytes[6] & 0xf0 ) >> 4 ) )
#define _PDCLIB_LDBL_BIAS 1023
#define _PDCLIB_LDBL_MANT_START( bytes ) ( bytes + 6 )

#endif

/* Given the definitions for *_MANT_START above, which resolve to "pointer
   to most dignificant byte of mantissa", the operand to use to get at the
   less significant bytes. (That would be - for i386, x86_64, and ARM.)
*/
#define _PDCLIB_FLT_OP -

/* -------------------------------------------------------------------------- */
/* Big Integer Arithmetic                                                     */
/* -------------------------------------------------------------------------- */
/* In support of the floating point converstions required by printf() etc.,   */
/* PDCLib provides rudimentary big integer arithmetics. The _PDCLIB_bigint_t  */
/* type stores values in a sequence of integer "digits", which may be of any  */
/* uint_leastN_t type with N being 32 or 16. Note that multiplication and     */
/* division require the help of the next larger type. So set the define to    */
/* 32 if efficient 64bit integer arithmetics are available on your platform,  */
/* and to 16 otherwise.                                                       */
/* (The value range of _PDCLIB_bigint_t is not affected by this setting.)     */

#define _PDCLIB_BIGINT_DIGIT_BITS 16

/* -------------------------------------------------------------------------- */
/* Platform-dependent macros defined by the standard headers.                 */
/* -------------------------------------------------------------------------- */

/* The offsetof macro                                                         */
/* Contract: Expand to an integer constant expression of type size_t, which   */
/* represents the offset in bytes to the structure member from the beginning  */
/* of the structure. If the specified member is a bitfield, behaviour is      */
/* undefined.                                                                 */
/* There is no standard-compliant way to do this.                             */
/* This implementation casts an integer zero to 'pointer to type', and then   */
/* takes the address of member. This is undefined behaviour but should work   */
/* on most compilers.                                                         */
#define _PDCLIB_offsetof( type, member ) ( (size_t) &( ( (type *) 0 )->member ) )

/* Variable Length Parameter List Handling (<stdarg.h>)                       */
/* The macros defined by <stdarg.h> are highly dependent on the calling       */
/* conventions used, and you probably have to replace them with builtins of   */
/* your compiler.                                                             */

#if defined( __i386 )

/* The following generic implementation works only for pure stack-based       */
/* architectures, and only if arguments are aligned to pointer type. Credits  */
/* to Michael Moody, who contributed this to the Public Domain.               */

/* Internal helper macro. va_round is not part of <stdarg.h>.                 */
#define _PDCLIB_va_round( type ) ( (sizeof(type) + sizeof(void *) - 1) & ~(sizeof(void *) - 1) )

typedef char * _PDCLIB_va_list;
#define _PDCLIB_va_arg( ap, type ) ( (ap) += (_PDCLIB_va_round(type)), ( *(type*) ( (ap) - (_PDCLIB_va_round(type)) ) ) )
#define _PDCLIB_va_copy( dest, src ) ( (dest) = (src), (void)0 )
#define _PDCLIB_va_end( ap ) ( (ap) = (void *)0, (void)0 )
#define _PDCLIB_va_start( ap, parmN ) ( (ap) = (char *) &parmN + ( _PDCLIB_va_round(parmN) ), (void)0 )

#elif defined( __x86_64 ) || defined( __arm__ ) || defined( __ARM_NEON )

/* No way to cover x86_64 or arm with a generic implementation, as it uses    */
/* register-based parameter passing. Using compiler builtins here.            */
typedef __builtin_va_list _PDCLIB_va_list;
#define _PDCLIB_va_arg( ap, type ) ( __builtin_va_arg( ap, type ) )
#define _PDCLIB_va_copy( dest, src ) ( __builtin_va_copy( dest, src ) )
#define _PDCLIB_va_end( ap ) ( __builtin_va_end( ap ) )
#define _PDCLIB_va_start( ap, parmN ) ( __builtin_va_start( ap, parmN ) )

#else

#error Please create your own _PDCLIB_config.h. Using the existing one as-is will not work. (Unsupported varargs.)

#endif

/* -------------------------------------------------------------------------- */
/* OS "glue", part 1                                                          */
/* These are values and data type definitions that you would have to adapt to */
/* the capabilities and requirements of your OS.                              */
/* The actual *functions* of the OS interface are declared in _PDCLIB_glue.h. */
/* -------------------------------------------------------------------------- */

/* I/O ---------------------------------------------------------------------- */

/* The type of the file descriptor returned by _PDCLIB_open(), i.e. whatever  */
/* the underlying kernel uses for stream identification.                      */
typedef int _PDCLIB_fd_t;

/* The value of type _PDCLIB_fd_t returned by _PDCLIB_open() if the operation */
/* failed.                                                                    */
#define _PDCLIB_NOHANDLE ( (_PDCLIB_fd_t) -1 )

/* The default size for file buffers. Must be at least 256.                   */
#define _PDCLIB_BUFSIZ 1024

/* The minimum number of files the implementation guarantees can opened       */
/* simultaneously.  Must be at least 8. Depends largely on how the platform   */
/* does the bookkeeping in whatever is called by _PDCLIB_open(). PDCLib puts  */
/* no further limits on the number of open files other than available memory. */
#define _PDCLIB_FOPEN_MAX 8

/* Length of the longest filename the implementation guarantees to support.   */
#define _PDCLIB_FILENAME_MAX 128

/* Maximum length of filenames generated by tmpnam(). (See tmpfile.c.)        */
#define _PDCLIB_L_tmpnam 46

/* Number of distinct file names that can be generated by tmpnam().           */
#define _PDCLIB_TMP_MAX 50

/* The values of SEEK_SET, SEEK_CUR and SEEK_END, used by fseek().            */
/* Since at least one platform (POSIX) uses the same symbols for its own      */
/* "seek" function, you should use whatever the host defines (if it does      */
/* define them).                                                              */
#define _PDCLIB_SEEK_SET 0
#define _PDCLIB_SEEK_CUR 1
#define _PDCLIB_SEEK_END 2

/* The number of characters that can be buffered with ungetc(). The standard  */
/* guarantees only one (1); PDCLib supports larger values, but applications   */
/* relying on this would rely on implementation-defined behaviour (not good). */
#define _PDCLIB_UNGETCBUFSIZE 1

/* The number of functions that can be registered with atexit(). Needs to be  */
/* at least 33 (32 guaranteed by the standard, plus _PDCLIB_closeall() which  */
/* is used internally by PDCLib to close all open streams).                   */
/* TODO: Should expand dynamically.                                           */
#define _PDCLIB_ATEXIT_SLOTS 40

/* errno -------------------------------------------------------------------- */

/* These are the values that _PDCLIB_errno can be set to by the library.      */
/*                                                                            */
/* By keeping PDCLib's errno in the _PDCLIB_* namespace, the library is       */
/* capable of "translating" between errno values used by the hosting OS and   */
/* those used and passed out by the library.                                  */
/*                                                                            */
/* Example: In the example platform, the remove() function uses the unlink()  */
/* system call as backend. Linux sets its errno to EISDIR if you try to       */
/* unlink() a directory, but POSIX demands EPERM. Within the remove()         */
/* function, you can catch 'errno == EISDIR', and set '*_PDCLIB_errno_func()  */
/* = _PDCLIB_EPERM'. Anyone using PDCLib's <errno.h> will "see" EPERM instead */
/* of EISDIR.                                                                 */
/*                                                                            */
/* If you do not want that kind of translation, you might want to "match" the */
/* values used by PDCLib with those used by the host OS, to avoid confusion.  */
/* auxiliary/errno/errno_readout.c provides a convenience program to read     */
/* those errno values mandated by the standard from a platform's <errno.h>,   */
/* giving output that can readily be pasted here.                             */
/* Either way, note that the list below, the list in PDCLib's <errno.h>, and  */
/* the list in _PDCLIB_stdinit.h, need to be kept in sync.                    */
/*                                                                            */
/* The values below are read from a Linux system.                             */

/* Argument list too long */
#define _PDCLIB_E2BIG             7
/* Permission denied */
#define _PDCLIB_EACCES           13
/* Address in use */
#define _PDCLIB_EADDRINUSE       98
/* Address not available */
#define _PDCLIB_EADDRNOTAVAIL    99
/* Address family not supported */
#define _PDCLIB_EAFNOSUPPORT     97
/* Resource unavailable, try again */
#define _PDCLIB_EAGAIN           11
/* Connection already in progress */
#define _PDCLIB_EALREADY        114
/* Bad file descriptor */
#define _PDCLIB_EBADF             9
/* Bad message */
#define _PDCLIB_EBADMSG          74
/* Device or resource busy */
#define _PDCLIB_EBUSY            16
/* Operation canceled */
#define _PDCLIB_ECANCELED       125
/* No child processes */
#define _PDCLIB_ECHILD           10
/* Connection aborted */
#define _PDCLIB_ECONNABORTED    103
/* Connection refused */
#define _PDCLIB_ECONNREFUSED    111
/* Connection reset */
#define _PDCLIB_ECONNRESET      104
/* Resource deadlock would occur */
#define _PDCLIB_EDEADLK          35
/* Destination address required */
#define _PDCLIB_EDESTADDRREQ     89
/* Mathematics argument out of domain of function */
#define _PDCLIB_EDOM             33
/* File exists */
#define _PDCLIB_EEXIST           17
/* Bad address */
#define _PDCLIB_EFAULT           14
/* File too large */
#define _PDCLIB_EFBIG            27
/* Host is unreachable */
#define _PDCLIB_EHOSTUNREACH    113
/* Identifier removed */
#define _PDCLIB_EIDRM            43
/* Illegal byte sequence */
#define _PDCLIB_EILSEQ           84
/* Operation in progress */
#define _PDCLIB_EINPROGRESS     115
/* Interrupted function */
#define _PDCLIB_EINTR             4
/* Invalid argument */
#define _PDCLIB_EINVAL           22
/* I/O error */
#define _PDCLIB_EIO               5
/* Socket is connected */
#define _PDCLIB_EISCONN         106
/* Is a directory */
#define _PDCLIB_EISDIR           21
/* Too many levels of symbolic links */
#define _PDCLIB_ELOOP            40
/* File descriptor value too large */
#define _PDCLIB_EMFILE           24
/* Too many links */
#define _PDCLIB_EMLINK           31
/* Message too large */
#define _PDCLIB_EMSGSIZE         90
/* Filename too long */
#define _PDCLIB_ENAMETOOLONG     36
/* Network is down */
#define _PDCLIB_ENETDOWN        100
/* Connection aborted by network */
#define _PDCLIB_ENETRESET       102
/* Network unreachable */
#define _PDCLIB_ENETUNREACH     101
/* Too many files open in system */
#define _PDCLIB_ENFILE           23
/* No buffer space available */
#define _PDCLIB_ENOBUFS         105
/* No message is available on the STREAM head read queue */
#define _PDCLIB_ENODATA          61
/* No such device */
#define _PDCLIB_ENODEV           19
/* No such file or directory */
#define _PDCLIB_ENOENT            2
/* Executable file format error */
#define _PDCLIB_ENOEXEC           8
/* No locks available */
#define _PDCLIB_ENOLCK           37
/* Link has been severed */
#define _PDCLIB_ENOLINK          67
/* Not enough space */
#define _PDCLIB_ENOMEM           12
/* No message of the desired type */
#define _PDCLIB_ENOMSG           42
/* Protocol not available */
#define _PDCLIB_ENOPROTOOPT      92
/* No space left on device */
#define _PDCLIB_ENOSPC           28
/* No STREAM resources */
#define _PDCLIB_ENOSR            63
/* Not a STREAM */
#define _PDCLIB_ENOSTR           60
/* Function not supported */
#define _PDCLIB_ENOSYS           38
/* The socket is not connected */
#define _PDCLIB_ENOTCONN        107
/* Not a directory */
#define _PDCLIB_ENOTDIR          20
/* Directory not empty */
#define _PDCLIB_ENOTEMPTY        39
/* State not recoverable */
#define _PDCLIB_ENOTRECOVERABLE 131
/* Not a socket */
#define _PDCLIB_ENOTSOCK         88
/* Not supported */
#define _PDCLIB_ENOTSUP          95
/* Inappropriate I/O control operation */
#define _PDCLIB_ENOTTY           25
/* No such device or address */
#define _PDCLIB_ENXIO             6
/* Operation not supported on socket */
#define _PDCLIB_EOPNOTSUPP       95
/* Value too large to be stored in data type */
#define _PDCLIB_EOVERFLOW        75
/* Previous owner died */
#define _PDCLIB_EOWNERDEAD      130
/* Operation not permitted */
#define _PDCLIB_EPERM             1
/* Broken pipe */
#define _PDCLIB_EPIPE            32
/* Protocol error */
#define _PDCLIB_EPROTO           71
/* Protocol not supported */
#define _PDCLIB_EPROTONOSUPPORT  93
/* Protocol wrong type for socket */
#define _PDCLIB_EPROTOTYPE       91
/* Result too large */
#define _PDCLIB_ERANGE           34
/* Read-only file system */
#define _PDCLIB_EROFS            30
/* Invalid seek */
#define _PDCLIB_ESPIPE           29
/* No such process */
#define _PDCLIB_ESRCH             3
/* Stream ioctl() timeout */
#define _PDCLIB_ETIME            62
/* Connection timed out */
#define _PDCLIB_ETIMEDOUT       110
/* Text file busy */
#define _PDCLIB_ETXTBSY          26
/* Operation would block */
#define _PDCLIB_EWOULDBLOCK      11
/* Cross-device link */
#define _PDCLIB_EXDEV            18

/* The highest defined errno value, plus one. This is used to set the size    */
/* of the array in struct _PDCLIB_lc_text_t holding error messages for the    */
/* strerror() and perror() functions. (If you change this value because you   */
/* are using additional errno values, you *HAVE* to provide appropriate error */
/* messages for *ALL* locales.)                                               */
#define _PDCLIB_ERRNO_MAX 132

/* The error message used for unknown error codes (generated by errno_readout */
/* for consistency between the 'holes' in the list of defined error messages  */
/* and the text generated by e.g. strerror() for out-of-range error values.)  */
#define _PDCLIB_EUNKNOWN_TEXT (char*)"unknown error"

/* locale data -------------------------------------------------------------- */

/* The default path where PDCLib should look for its locale data.             */
/* Must end with the appropriate separator character.                         */
#define _PDCLIB_LOCALE_PATH "/usr/share/pdclib/i18n/"

/* The name of the environment variable that can be used to override that     */
/* path setting.                                                              */
#define _PDCLIB_LOCALE_PATH_ENV PDCLIB_I18N

#ifdef __CYGWIN__
typedef unsigned int wint_t;
#endif

/* threads ------------------------------------------------------------------ */

/* This is relying on underlying <pthread.h> implementation to provide thread */
/* support.                                                                   */
/* The problem here is we cannot just #include <pthread.h> and access the     */
/* original definitions. The standard library must not drag identifiers into  */
/* the user's namespace, so we have to set our own definitions in the _PDCLIB */
/* namespace. Which are, obviously, platform-specific.                        */
/* If you do NOT want to provide threads support, define __STDC_NO_THREADS__  */
/* to 1 and simply delete the threads.h header and the corresponding files in */
/* functions/threads/. This makes PDCLib non-thread-safe (obviously), as the  */
/* safeguards against race conditions (e.g. in <stdio.h>) will be omitted.    */

/* auxiliary/pthread/pthread_readout.c provides a convenience program to read */
/* appropriate definitions from a platform's <pthread.h>, giving output that  */
/* can be copy & pasted here.                                                 */

#cmakedefine __STDC_NO_THREADS__ 1

#ifndef __STDC_NO_THREADS__

typedef unsigned long int _PDCLIB_thrd_t;
typedef union { unsigned char _PDCLIB_cnd_t_data[ 48 ]; long long int _PDCLIB_cnd_t_align; } _PDCLIB_cnd_t;
#if defined( __arm__ ) || defined( __ARM_NEON )
typedef union { unsigned char _PDCLIB_mtx_t_data[ 24 ]; long int _PDCLIB_mtx_t_align; } _PDCLIB_mtx_t;
#else
typedef union { unsigned char _PDCLIB_mtx_t_data[ 40 ]; long int _PDCLIB_mtx_t_align; } _PDCLIB_mtx_t;
#endif
typedef unsigned int _PDCLIB_tss_t;
typedef int _PDCLIB_once_flag;
#define _PDCLIB_ONCE_FLAG_INIT 0
#define _PDCLIB_RECURSIVE_MUTEX_INIT PTHREAD_MUTEX_INITIALIZER
/* This one is actually hidden in <limits.h>, and only if __USE_POSIX is      */
/* defined prior to #include <limits.h> (PTHREAD_DESTRUCTOR_ITERATIONS).      */
#define _PDCLIB_TSS_DTOR_ITERATIONS 4
/* The following are not made public in any header, but used internally for   */
/* interfacing with the pthread API.                                          */
typedef union { unsigned char _PDCLIB_cnd_attr_t_data[ 4 ]; int _PDCLIB_cnd_attr_t_align; } _PDCLIB_cnd_attr_t;
typedef union { unsigned char _PDCLIB_mtx_attr_t_data[ 4 ]; int _PDCLIB_mtx_attr_t_align; } _PDCLIB_mtx_attr_t;
#if defined( __arm__ ) || defined( __ARM_NEON )
typedef union { unsigned char _PDCLIB_thrd_attr_t_data[ 36 ]; long int _PDCLIB_thrd_attr_t_align; } _PDCLIB_thrd_attr_t;
#else
typedef union { unsigned char _PDCLIB_thrd_attr_t_data[ 56 ]; long int _PDCLIB_thrd_attr_t_align; } _PDCLIB_thrd_attr_t;
#endif
/* Static initialization of recursive mutex.                                  */
#if defined( __arm__ ) || defined( __ARM_NEON )
#define _PDCLIB_MTX_RECURSIVE_INIT { {\
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
         0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,\
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }
/* Static initialization of plain / timeout mutex (identical with pthread).   */
#define _PDCLIB_MTX_PLAIN_INIT { {\
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }
#else
#define _PDCLIB_MTX_RECURSIVE_INIT { {\
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
     0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }
/* Static initialization of plain / timeout mutex (identical with pthread).   */
#define _PDCLIB_MTX_PLAIN_INIT { {\
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }
#endif

#endif

/* Termux defines atexit in crtbegin_so.o leading to a multiple definition    */
/* error from the linker. This is a crude workaround, which does NOT fix      */
/* various run-time issues on Termux likely also related to crt linkage. But  */
/* at least things compile OK, and SOME tests can be run.                     */
#if defined( __ARM_NEON )
#define atexit _PDCLIB_atexit
#endif

#endif
