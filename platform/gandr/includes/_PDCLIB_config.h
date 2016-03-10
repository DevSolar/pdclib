#ifndef _PDCLIB_CONFIG_H
#define _PDCLIB_CONFIG_H
/* Internal PDCLib configuration <_PDCLIB_config.h>
   (Gandr platform)

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/



/* end of line */
#define _PDCLIB_endl "\n"

/* exit() */
#define _PDCLIB_SUCCESS 0
#define _PDCLIB_FAILURE -1

/* trivial memswp */
#define _PDCLIB_memswp( i, j, size ) char tmp; do { tmp = *i; *i++ = *j; *j++ = tmp; } while ( --size );


#if defined(__arm__)
  #define _PDCLIB_CHAR_SIGNED 0
#else
  #define _PDCLIB_CHAR_SIGNED 1
#endif

/* Width of the integer types short, int, long, and long long, in bytes.      */
/* SHRT == 2, INT >= SHRT, LONG >= INT >= 4, LLONG >= LONG - check your       */
/* compiler manuals.                                                          */
#define _PDCLIB_SHRT_BYTES  2
#define _PDCLIB_INT_BYTES 4
#if defined(__LP64__)
  #define _PDCLIB_LONG_BYTES 8
#else
  #define _PDCLIB_LONG_BYTES 4
#endif
#define _PDCLIB_LLONG_BYTES 8

/* layout of div_t, ldiv_t, lldiv_t */
struct _PDCLIB_div_t   { int quot;            int rem; };
struct _PDCLIB_ldiv_t  { long int quot;       long int rem; };
struct _PDCLIB_lldiv_t { long long int quot;  long long int rem; };

/* fast* datatypes. This is a bit of a blunt instrument. */
#define _PDCLIB_FAST8 CHAR
#define _PDCLIB_fast8 char
#define _PDCLIB_FAST8_CONV hh

#define _PDCLIB_FAST16 SHRT
#define _PDCLIB_fast16 short
#define _PDCLIB_FAST16_CONV h

#define _PDCLIB_FAST32 INT
#define _PDCLIB_fast32 int
#define _PDCLIB_FAST32_CONV

#define _PDCLIB_FAST64 LLONG
#define _PDCLIB_fast64 long long
#define _PDCLIB_FAST64_CONV ll

/* ptrdiff_t */
#define _PDCLIB_ptrdiff long
#define _PDCLIB_PTRDIFF LONG
#define _PDCLIB_PTR_CONV l

/* Result type of the 'sizeof' operator (must be unsigned) */
#define _PDCLIB_size unsigned long
#define _PDCLIB_SIZE ULONG

/* intptr_t */
#define _PDCLIB_intptr long
#define _PDCLIB_INTPTR LONG

/* sig_atomic_t */
#define _PDCLIB_sig_atomic char
#define _PDCLIB_SIG_ATOMIC CHAR

/* wint_t, wchar_t */
#define _PDCLIB_wint  signed int
#define _PDCLIB_wchar unsigned int
#define _PDCLIB_WCHAR UINT


/* Largest supported integer type */
#define _PDCLIB_intmax long long int
#define _PDCLIB_INTMAX LLONG
#define _PDCLIB_MAX_CONV ll
#define _PDCLIB_INTMAX_LITERAL ll

struct _PDCLIB_imaxdiv_t { _PDCLIB_intmax quot; _PDCLIB_intmax rem; };

/* time_t */
#define _PDCLIB_time  unsigned long long

/* clock_t */
#define _PDCLIB_clock unsigned
#define _PDCLIB_CLOCKS_PER_SEC 1000000

/* timespec_get */
#define _PDCLIB_TIME_UTC 1

/* -------------------------------------------------------------------------- */
/* Floating Point                                                             */
/* -------------------------------------------------------------------------- */

/* Whether the implementation rounds toward zero (0), to nearest (1), toward
   positive infinity (2), or toward negative infinity (3). (-1) signifies
   indeterminable rounding, any other value implementation-specific rounding.
*/
#define _PDCLIB_FLT_ROUNDS -1

/* Whether the implementation uses exact-width precision (0), promotes float
   to double (1), or promotes float and double to long double (2). (-1)
   signifies indeterminable behaviour, any other value implementation-specific
   behaviour.
*/
#define _PDCLIB_FLT_EVAL_METHOD -1

/* "Number of the decimal digits (n), such that any floating-point number in the
   widest supported floating type with p(max) radix (b) digits can be rounded to
   a floating-point number with (n) decimal digits and back again without change
   to the value p(max) log(10)b if (b) is a power of 10, [1 + p(max) log(10)b]
   otherwise."
   64bit IEC 60559 double format (53bit mantissa) is DECIMAL_DIG 17.
   80bit IEC 60559 double-extended format (64bit mantissa) is DECIMAL_DIG 21.
*/
#define _PDCLIB_DECIMAL_DIG 17

/* Floating point types
 *
 * PDCLib (at present) assumes IEEE 754 floating point formats
 * The following names are used:
 *    SINGLE:   IEEE 754 single precision (32-bit)
 *    DOUBLE:   IEEE 754 double precision (64-bit)
 *    EXTENDED: IEEE 754 extended precision (80-bit, as x87)
 */
#define _PDCLIB_FLOAT_TYPE   SINGLE
#define _PDCLIB_DOUBLE_TYPE  DOUBLE
#if defined(__i386__) || defined(__amd64__)
  #define _PDCLIB_LDOUBLE_TYPE EXTENDED
#else
  #define _PDCLIB_LDOUBLE_TYPE DOUBLE
#endif

/* -------------------------------------------------------------------------- */
/* Platform-dependent macros defined by the standard headers.                 */
/* -------------------------------------------------------------------------- */

/* offsetof */
#define _PDCLIB_offsetof( type, member ) __builtin_offsetof( type, member )

/* stdarg.h */
typedef __builtin_va_list _PDCLIB_va_list;
#define _PDCLIB_va_arg( ap, type ) (__builtin_va_arg( (ap), type ))
#define _PDCLIB_va_copy( dest, src ) (__builtin_va_copy( (dest), (src) ))
#define _PDCLIB_va_end( ap ) (__builtin_va_end( ap ) )
#define _PDCLIB_va_start( ap, parmN ) (__builtin_va_start( (ap), (parmN) ))

/* "OS glue" */

/* Memory management -------------------------------------------------------- */

#define _PDCLIB_MALLOC_PAGESIZE 4096
#define _PDCLIB_MALLOC_ALIGN 16
#define _PDCLIB_MALLOC_GRANULARITY 4096
#define _PDCLIB_MALLOC_TRIM_THRESHOLD 2*1024*1024
#define _PDCLIB_MALLOC_MMAP_THRESHOLD 256*1024
#define _PDCLIB_MALLOC_RELEASE_CHECK_RATE 4095

/* Locale --------------------------------------------------------------------*/

/* Locale method. See _PDCLIB_locale.h. If undefined, POSIX per-thread locales
 * will be disabled
 */
/* #define _PDCLIB_LOCALE_METHOD _PDCLIB_LOCALE_METHOD_TSS */

/* wchar_t encoding */
#define _PDCLIB_WCHAR_ENCODING _PDCLIB_WCHAR_ENCODING_UCS4

/* I/O ---------------------------------------------------------------------- */

/* The default size for file buffers. Must be at least 256. */
#define _PDCLIB_BUFSIZ 1024

/* We need \n -> \r\n translation for text files */
#define _PDCLIB_NEED_EOL_TRANSLATION 1

/* Minimum number of files we can open simultaneously. C says this must be >= 8,
 * so we say that. May actually be a lie in some cases...
 */
#define _PDCLIB_FOPEN_MAX 8

/* Length of the longest filename the implementation guarantees to support. */
#define _PDCLIB_FILENAME_MAX 260

/* Maximum length of filenames generated by tmpnam(). (See tmpfile.c.) */
#define _PDCLIB_L_tmpnam 260

/* Number of distinct file names that can be generated by tmpnam(). */
#define _PDCLIB_TMP_MAX 50

/* SEEK_SET, CUR, END */
#define _PDCLIB_SEEK_SET 0
#define _PDCLIB_SEEK_CUR 1
#define _PDCLIB_SEEK_END 2

/* How much can you ungetc? Not much, thankfully */
#define _PDCLIB_UNGETCBUFSIZE 1

/* errno -------------------------------------------------------------------- */

/* errno values as per C++11 */
#define _PDCLIB_ERANGE             1
#define _PDCLIB_EDOM               2
#define _PDCLIB_EILSEQ             3
#define _PDCLIB_E2BIG              4
#define _PDCLIB_ECONNRESET         5
#define _PDCLIB_EISCONN            6
#define _PDCLIB_ENOENT             7
#define _PDCLIB_ENOTRECOVERABLE    8
#define _PDCLIB_EROFS              9
#define _PDCLIB_EACCES            10
#define _PDCLIB_EDEADLK           11
#define _PDCLIB_EISDIR            12
#define _PDCLIB_ENOEXEC           13
#define _PDCLIB_ENOTSOCK          14
#define _PDCLIB_ESPIPE            15
#define _PDCLIB_EADDRINUSE        16
#define _PDCLIB_EDESTADDRREQ      17
#define _PDCLIB_ELOOP             18
#define _PDCLIB_ENOLCK            19
#define _PDCLIB_ENOTSUP           20
#define _PDCLIB_ESRCH             21
#define _PDCLIB_EADDRNOTAVAIL     22
#define _PDCLIB_EMFILE            23
#define _PDCLIB_ENOLINK           24
#define _PDCLIB_ENOTTY            25
#define _PDCLIB_ETIME             26
#define _PDCLIB_EAFNOSUPPORT      27
#define _PDCLIB_EEXIST            28
#define _PDCLIB_EMLINK            29
#define _PDCLIB_ENOMEM            30
#define _PDCLIB_ENXIO             31
#define _PDCLIB_ETIMEDOUT         32
#define _PDCLIB_EAGAIN            33
#define _PDCLIB_EFAULT            34
#define _PDCLIB_EMSGSIZE          35
#define _PDCLIB_ENOMSG            36
#define _PDCLIB_EOPNOTSUPP        37
#define _PDCLIB_ETXTBSY           38
#define _PDCLIB_EALREADY          39
#define _PDCLIB_EFBIG             40
#define _PDCLIB_ENAMETOOLONG      41
#define _PDCLIB_ENOPROTOOPT       42
#define _PDCLIB_EOVERFLOW         43
#define _PDCLIB_EWOULDBLOCK       _PDCLIB_EAGAIN
#define _PDCLIB_EBADF             44
#define _PDCLIB_EHOSTUNREACH      45
#define _PDCLIB_ENETDOWN          46
#define _PDCLIB_ENOSPC            47
#define _PDCLIB_EOWNERDEAD        48
#define _PDCLIB_EXDEV             49
#define _PDCLIB_EBADMSG           50
#define _PDCLIB_EIDRM             51
#define _PDCLIB_ENETRESET         52
#define _PDCLIB_ENOSR             53
#define _PDCLIB_EPERM             54
#define _PDCLIB_EBUSY             55
#define _PDCLIB_ENETUNREACH       56
#define _PDCLIB_ENOSTR            57
#define _PDCLIB_EPIPE             58
#define _PDCLIB_ECANCELED         59
#define _PDCLIB_EINPROGRESS       60
#define _PDCLIB_ENFILE            61
#define _PDCLIB_ENOSYS            62
#define _PDCLIB_EPROTO            63
#define _PDCLIB_ECHILD            64
#define _PDCLIB_EINTR             65
#define _PDCLIB_ENOBUFS           66
#define _PDCLIB_ENOTCONN          67
#define _PDCLIB_EPROTONOSUPPORT   68
#define _PDCLIB_ECONNABORTED      69
#define _PDCLIB_EINVAL            70
#define _PDCLIB_ENODATA           71
#define _PDCLIB_ENOTDIR           72
#define _PDCLIB_EPROTOTYPE        73
#define _PDCLIB_EIO               74
#define _PDCLIB_ECONNREFUSED      75
#define _PDCLIB_ENODEV            76
#define _PDCLIB_ENOTEMPTY         77

/* This is used to set the size of the array in struct lconv (<locale.h>)     */
/* holding the error messages for the strerror() and perror() fuctions. If    */
/* you change this value because you are using additional errno values, you   */
/* *HAVE* to provide appropriate error messages for *ALL* locales.            */
/* Needs to be one higher than the highest errno value above.                 */
#define _PDCLIB_ERRNO_MAX 78

#endif
