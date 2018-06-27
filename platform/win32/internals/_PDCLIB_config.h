#ifndef _PDCLIB_CONFIG_H
#define _PDCLIB_CONFIG_H

/* Internal PDCLib configuration <_PDCLIB_config.h>
   (Win32 platform)

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* Misc                                                                       */
/* -------------------------------------------------------------------------- */

/* The character (sequence) your platform uses as newline.                    */
#define _PDCLIB_endl "\r\n"

/* exit() can signal success to the host environment by the value of zero or  */
/* the constant EXIT_SUCCESS. Failure is signaled by EXIT_FAILURE. Note that  */
/* any other return value is "implementation-defined", i.e. your environment  */
/* is not required to handle it gracefully. Set your definitions here.        */
#define _PDCLIB_SUCCESS 0
#define _PDCLIB_FAILURE -1

/* qsort() in <stdlib.h> requires a function that swaps two memory areas.     */
/* Below is a naive implementation that can be improved significantly for     */
/* specific platforms, e.g. by swapping int instead of char.                  */
#define _PDCLIB_memswp( i, j, size ) char tmp; do { tmp = *i; *i++ = *j; *j++ = tmp; } while ( --size );

/* -------------------------------------------------------------------------- */
/* Integers                                                                   */
/* -------------------------------------------------------------------------- */
/* Assuming 8-bit char, two's-complement architecture here. 'short' being     */
/* 16 bit, 'int' being either 16, 32 or 64 bit, 'long' being either 32 or 64  */
/* bit (but 64 bit only if 'int' is 32 bit), and 'long long' being 64 bit if  */
/* 'long' is not, 64 or 128 bit otherwise.                                    */
/* Author is quite willing to support other systems but would like to hear of */
/* interest in such support and details on the to-be-supported architecture   */
/* first, before going to lengths about it.                                   */
/* -------------------------------------------------------------------------- */

/* Set to 0 if your 'char' type is unsigned.                                  */
#define _PDCLIB_CHAR_SIGNED 1

/* Width of the integer types short, int, long, and long long, in bytes.      */
/* SHRT == 2, INT >= SHRT, LONG >= INT >= 4, LLONG >= LONG - check your       */
/* compiler manuals.                                                          */
#define _PDCLIB_SHRT_BYTES  2
#define _PDCLIB_INT_BYTES   4
#define _PDCLIB_LONG_BYTES  4
#define _PDCLIB_LLONG_BYTES 8

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
/* <stdint.h> defines a set of integer types that are of a minimum width, and */
/* "usually fastest" on the system. (If, for example, accessing a single char */
/* requires the CPU to access a complete int and then mask out the char, the  */
/* "usually fastest" type of at least 8 bits would be int, not char.)         */
/* If you do not have information on the relative performance of the types,   */
/* the standard allows you to define any type that meets minimum width and    */
/* signedness requirements.                                                   */
/* The defines below are just configuration for the real typedefs and limit   */
/* definitions done in <_PDCLIB_int.h>. The uppercase define shall be either  */
/* SHRT, INT, LONG, or LLONG (telling which values to use for the *_MIN and   */
/* *_MAX limits); the lowercase define either short, int, long, or long long  */
/* (telling the actual type to use).                                          */
/* The third define is the length modifier used for the type in printf() and  */
/* scanf() functions (used in <inttypes.h>).                                  */
/* If you require a non-standard datatype to define the "usually fastest"     */
/* types, PDCLib as-is doesn't support that. Please contact the author with   */
/* details on your platform in that case, so support can be added.            */
/* -------------------------------------------------------------------------- */

#define _PDCLIB_FAST8 INT
#define _PDCLIB_fast8 int
#define _PDCLIB_FAST8_CONV

#define _PDCLIB_FAST16 INT
#define _PDCLIB_fast16 int
#define _PDCLIB_FAST16_CONV

#define _PDCLIB_FAST32 INT
#define _PDCLIB_fast32 int
#define _PDCLIB_FAST32_CONV

#define _PDCLIB_FAST64 LLONG
#define _PDCLIB_fast64 long long
#define _PDCLIB_FAST64_CONV ll

/* -------------------------------------------------------------------------- */
/* What follows are a couple of "special" typedefs and their limits. Again,   */
/* the actual definition of the limits is done in <_PDCLIB_int.h>, and the    */
/* defines here are merely "configuration". See above for details.            */
/* -------------------------------------------------------------------------- */

/* The types used for size_t and ptrdiff_t should not have an integer conversion
   rank greater than that of signed long int unless the implementation supports
   objects large enough to make this necessary.
*/

/* Result type of substracting two pointers (must be signed) */
#if defined(__amd64__) || defined(_M_AMD64)
#define _PDCLIB_ptrdiff long long
#define _PDCLIB_PTRDIFF LLONG
#define _PDCLIB_PTR_CONV ll
#else
#define _PDCLIB_ptrdiff int
#define _PDCLIB_PTRDIFF INT
#define _PDCLIB_PTR_CONV
#endif

/* Result type of the 'sizeof' operator (must be unsigned) */
#if defined(__amd64__) || defined(_M_AMD64)
#define _PDCLIB_size unsigned long long
#define _PDCLIB_SIZE ULLONG
#else
#define _PDCLIB_size unsigned int
#define _PDCLIB_SIZE UINT
#endif

/* An integer type that can be accessed as atomic entity (think asynchronous
   interrupts). The type itself is not defined in a freestanding environment,
   but its limits are. (Don't ask.)
*/
#define _PDCLIB_sig_atomic int
#define _PDCLIB_SIG_ATOMIC INT

/* Object type whose alignment is as great as supported by implementation
   in all contexts.
*/
#define _PDCLIB_max_align long double

/* Integer type whose range of values can represent distinct codes for
   all members of the largest extended character set specified among the
   supported locales.
   Note that the definition of this type must agree with the type used
   by the compiler for L"" string and L'' character literals.
*/
#define _PDCLIB_wchar unsigned short
#define _PDCLIB_WCHAR USHRT

/* Each member of the basic character set shall have a code value equal
   to its value when used as the lone character in an integer character
   constant. If that is not the case, uncomment the following line.
#define __STDC_MB_MIGHT_NEQ_WC__
*/

/* Integer type unchanged by default argument promotions that can hold any
   value corresponding to characters of the extended character set, as well
   as at least one value that does not correspond to any member of the
   extended character set (WEOF).
*/
#define _PDCLIB_wint  signed int

#if defined(__amd64__) || defined(_M_AMD64)
#define _PDCLIB_intptr long long
#define _PDCLIB_INTPTR LLONG
#else
#define _PDCLIB_intptr int
#define _PDCLIB_INTPTR INT
#endif

/* Largest supported integer type. Implementation note: see _PDCLIB_atomax(). */
#define _PDCLIB_intmax long long int
#define _PDCLIB_INTMAX LLONG
#define _PDCLIB_MAX_CONV ll
/* You are also required to state the literal suffix for the intmax type      */
#define _PDCLIB_INTMAX_LITERAL ll

/* <inttypes.h> defines imaxdiv(), which is equivalent to the div() function  */
/* family (see further above) with intmax_t as basis.                         */

struct _PDCLIB_imaxdiv_t
{
    _PDCLIB_intmax quot;
    _PDCLIB_intmax rem;
};

/* <time.h>: time_t
 * The C standard doesn't define what representation of time is stored in
 * time_t when returned by time() , but POSIX defines it to be seconds since the
 * UNIX epoch and most appplications expect that.
 *
 * time_t is also used as the tv_sec member of struct timespec, which *is*
 * defined as a linear count of seconds.
 *
 * time_t is defined as a "real type", so may be a floating point type, but with
 * the presence of the nanosecond accurate struct timespec, and with the lack of
 * any functions for manipulating more accurate values of time_t, this is
 * probably not useful.
 */
#define _PDCLIB_time unsigned long long

/* <time.h>: clock_t
 *
 * A count of "clock ticks", where the length of a clock tick is unspecified by
 * the standard. The implementation is required to provide a macro,
 * CLOCKS_PER_SEC, which is the number of "clock ticks" which corresponds to one
 * second.
 *
 * clock_t may be any real type (i.e. integral or floating), and its type on
 * various systems differs.
 *
 * On XSI systems, CLOCKS_PER_SEC must be defined to 1000000
 */
#define _PDCLIB_clock double
#define _PDCLIB_CLOCKS_PER_SEC 1000000

/* <time.h>: TIME_UTC
 *
 * The TIME_UTC parameter is passed to the timespec_get function in order to get
 * the system time in UTC since an implementation defined epoch (not necessarily
 * the same as that used for time_t). That said, on POSIX the obvious
 * implementation of timespec_get for TIME_UTC is to wrap
 * clock_gettime(CLOCK_REALTIME, ...), which is defined as time in UTC since the
 * same epoch.
 *
 * This may be any non-zero integer value.
 */
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
#define _PDCLIB_LDOUBLE_TYPE EXTENDED

/* -------------------------------------------------------------------------- */
/* Platform-dependent macros defined by the standard headers.                 */
/* -------------------------------------------------------------------------- */

/* The offsetof macro
   Contract: Expand to an integer constant expression of type size_t, which
   represents the offset in bytes to the structure member from the beginning
   of the structure. If the specified member is a bitfield, behaviour is
   undefined.
   There is no standard-compliant way to do this.
   This implementation casts an integer zero to 'pointer to type', and then
   takes the address of member. This is undefined behaviour but should work on
   most compilers.
*/
#ifdef __GNUC__
#define _PDCLIB_offsetof( type, member ) __builtin_offsetof( type, member )
#else
#define _PDCLIB_offsetof( type, member ) ( (size_t) &( ( (type *) 0 )->member ) )
#endif

/* Variable Length Parameter List Handling (<stdarg.h>)
   The macros defined by <stdarg.h> are highly dependent on the calling
   conventions used, and you probably have to replace them with builtins of
   your compiler.
*/

#ifdef __GNUC__
typedef __builtin_va_list _PDCLIB_va_list;
#define _PDCLIB_va_arg( ap, type ) (__builtin_va_arg( (ap), type ))
#define _PDCLIB_va_copy( dest, src ) (__builtin_va_copy( (dest), (src) ))
#define _PDCLIB_va_end( ap ) (__builtin_va_end( ap ) )
#define _PDCLIB_va_start( ap, parmN ) (__builtin_va_start( (ap), (parmN) ))
#elif (defined(__i386__) || defined(__i386) || defined(_M_IX86)) && !(defined(__amd64__) || defined(__x86_64__) || defined(_M_AMD64))
/* Internal helper macro. va_round is not part of <stdarg.h>. */
#define _PDCLIB_va_round( type ) ( (sizeof(type) + sizeof(void *) - 1) & ~(sizeof(void *) - 1) )
typedef char * _PDCLIB_va_list;
#define _PDCLIB_va_arg( ap, type ) ( (ap) += (_PDCLIB_va_round(type)), ( *(type*) ( (ap) - (_PDCLIB_va_round(type)) ) ) )
#define _PDCLIB_va_copy( dest, src ) ( (dest) = (src), (void)0 )
#define _PDCLIB_va_end( ap ) ( (ap) = (void *)0, (void)0 )
#define _PDCLIB_va_start( ap, parmN ) ( (ap) = (char *) &parmN + ( _PDCLIB_va_round(parmN) ), (void)0 )
#else
#error Compiler/Architecture support please
#endif

/* -------------------------------------------------------------------------- */
/* OS "glue", part 1                                                          */
/* These are values and data type definitions that you would have to adapt to */
/* the capabilities and requirements of your OS.                              */
/* The actual *functions* of the OS interface are declared in _PDCLIB_glue.h. */
/* -------------------------------------------------------------------------- */

/* Memory management -------------------------------------------------------- */

/* Set this to the page size of your OS. If your OS does not support paging, set
   to an appropriate value. (Too small, and malloc() will call the kernel too
   often. Too large, and you will waste memory.)
*/
#define _PDCLIB_MALLOC_PAGESIZE 4096
#define _PDCLIB_MALLOC_ALIGN 16
#define _PDCLIB_MALLOC_GRANULARITY 64*1024
#define _PDCLIB_MALLOC_TRIM_THRESHOLD 2*1024*1024
#define _PDCLIB_MALLOC_MMAP_THRESHOLD 256*1024
#define _PDCLIB_MALLOC_RELEASE_CHECK_RATE 4095

/* TODO: Better document these */

/* Locale --------------------------------------------------------------------*/

/* Locale method. See _PDCLIB_locale.h. If undefined, POSIX per-thread locales
   will be disabled.
*/
#define _PDCLIB_LOCALE_METHOD _PDCLIB_LOCALE_METHOD_TSS

/* wchar_t encoding */
#define _PDCLIB_WCHAR_ENCODING _PDCLIB_WCHAR_ENCODING_UTF16

/* I/O ---------------------------------------------------------------------- */

/* The default size for file buffers. Must be at least 256. */
#define _PDCLIB_BUFSIZ 1024

/* The minimum number of files the implementation can open simultaneously. Must
   be at least 8. Depends largely on how the bookkeeping is done by fopen() /
   freopen() / fclose(). The example implementation limits the number of open
   files only by available memory.
*/
#define _PDCLIB_FOPEN_MAX 8

/* Length of the longest filename the implementation guarantees to support. */
#define _PDCLIB_FILENAME_MAX 260

/* Maximum length of filenames generated by tmpnam(). (See tmpfile.c.) */
#define _PDCLIB_L_tmpnam 260

/* Number of distinct file names that can be generated by tmpnam(). */
#define _PDCLIB_TMP_MAX 50

/* The values of SEEK_SET, SEEK_CUR and SEEK_END, used by fseek().
   Since at least one platform (POSIX) uses the same symbols for its own "seek"
   function, we use whatever the host defines (if it does define them).

   Win32 note: Must match Win32 API values (FILE_BEGIN/FILE_CURRENT/FILE_END)
*/
#define _PDCLIB_SEEK_SET 0
#define _PDCLIB_SEEK_CUR 1
#define _PDCLIB_SEEK_END 2

/* The number of characters that can be buffered with ungetc(). The standard
   guarantees only one (1); anything larger would make applications relying on
   this capability dependent on implementation-defined behaviour (not good).
*/
#define _PDCLIB_UNGETCBUFSIZE 1

/* errno -------------------------------------------------------------------- */

/* These are the values that _PDCLIB_errno can be set to by the library.

   By keeping PDCLib's errno in the _PDCLIB_* namespace, the library is capable
   to "translate" between errno values used by the hosting operating system and
   those used and passed out by the library.

   Example: In the example platform, the remove() function uses the unlink()
   system call as backend. Linux sets its errno to EISDIR if you try to unlink()
   a directory, but POSIX demands EPERM. Within the remove() function, you can
   catch the 'errno == EISDIR', and set '_PDCLIB_errno = _PDCLIB_EPERM'. Anyone
   using PDCLib's <errno.h> will "see" EPERM instead of EISDIR (the _PDCLIB_*
   prefix removed by <errno.h> mechanics).

   If you do not want that kind of translation, you might want to "match" the
   values used by PDCLib with those used by the host OS, as to avoid confusion.

   The C standard only defines three distinct errno values: ERANGE, EDOM, and
   EILSEQ. The standard leaves it up to "the implementation" whether there are
   any more beyond those three.

   However, C++11 introduced the whole list of POSIX errno values into the
   standard, so PDCLib might as well define those as well.

   Sometimes the standard says to set errno to indicate an error, but does not
   prescribe a value. We will use a value from the following list. If POSIX
   defines a value, we use that; otherwise, we use as seems suitable.
*/

/* These values were taken from Windows 7, MSVC 2010. */
#define _PDCLIB_E2BIG              7
#define _PDCLIB_EACCES            13
#define _PDCLIB_EADDRINUSE       100
#define _PDCLIB_EADDRNOTAVAIL    101
#define _PDCLIB_EAFNOSUPPORT     102
#define _PDCLIB_EAGAIN            11
#define _PDCLIB_EALREADY         103
#define _PDCLIB_EBADF              9
#define _PDCLIB_EBADMSG          104
#define _PDCLIB_EBUSY             16
#define _PDCLIB_ECANCELED        105
#define _PDCLIB_ECHILD            10
#define _PDCLIB_ECONNABORTED     106
#define _PDCLIB_ECONNREFUSED     107
#define _PDCLIB_ECONNRESET       108
#define _PDCLIB_EDEADLK           36
#define _PDCLIB_EDESTADDRREQ     109
#define _PDCLIB_EDOM              33
#define _PDCLIB_EEXIST            17
#define _PDCLIB_EFAULT            14
#define _PDCLIB_EFBIG             27
#define _PDCLIB_EHOSTUNREACH     110
#define _PDCLIB_EIDRM            111
#define _PDCLIB_EILSEQ            42
#define _PDCLIB_EINPROGRESS      112
#define _PDCLIB_EINTR              4
#define _PDCLIB_EINVAL            22
#define _PDCLIB_EIO                5
#define _PDCLIB_EISCONN          113
#define _PDCLIB_EISDIR            21
#define _PDCLIB_ELOOP            114
#define _PDCLIB_EMFILE            24
#define _PDCLIB_EMLINK            31
#define _PDCLIB_EMSGSIZE         115
#define _PDCLIB_ENAMETOOLONG      38
#define _PDCLIB_ENETDOWN         116
#define _PDCLIB_ENETRESET        117
#define _PDCLIB_ENETUNREACH      118
#define _PDCLIB_ENFILE            23
#define _PDCLIB_ENOBUFS          119
#define _PDCLIB_ENODATA          120
#define _PDCLIB_ENODEV            19
#define _PDCLIB_ENOENT             2
#define _PDCLIB_ENOEXEC            8
#define _PDCLIB_ENOLCK            39
#define _PDCLIB_ENOLINK          121
#define _PDCLIB_ENOMEM            12
#define _PDCLIB_ENOMSG           122
#define _PDCLIB_ENOPROTOOPT      123
#define _PDCLIB_ENOSPC            28
#define _PDCLIB_ENOSR            124
#define _PDCLIB_ENOSTR           125
#define _PDCLIB_ENOSYS            40
#define _PDCLIB_ENOTCONN         126
#define _PDCLIB_ENOTDIR           20
#define _PDCLIB_ENOTEMPTY         41
#define _PDCLIB_ENOTRECOVERABLE  127
#define _PDCLIB_ENOTSOCK         128
#define _PDCLIB_ENOTSUP          129
#define _PDCLIB_ENOTTY            25
#define _PDCLIB_ENXIO              6
#define _PDCLIB_EOPNOTSUPP       130
#define _PDCLIB_EOVERFLOW        132
#define _PDCLIB_EOWNERDEAD       133
#define _PDCLIB_EPERM              1
#define _PDCLIB_EPIPE             32
#define _PDCLIB_EPROTO           134
#define _PDCLIB_EPROTONOSUPPORT  135
#define _PDCLIB_EPROTOTYPE       136
#define _PDCLIB_ERANGE            34
#define _PDCLIB_EROFS             30
#define _PDCLIB_ESPIPE            29
#define _PDCLIB_ESRCH              3
#define _PDCLIB_ETIME            137
#define _PDCLIB_ETIMEDOUT        138
#define _PDCLIB_ETXTBSY          139
#define _PDCLIB_EWOULDBLOCK      140
#define _PDCLIB_EXDEV             18

/* This is used to set the size of the array in struct lconv (<locale.h>)     */
/* holding the error messages for the strerror() and perror() fuctions. If    */
/* you change this value because you are using additional errno values, you   */
/* *HAVE* to provide appropriate error messages for *ALL* locales.            */
/* Needs to be one higher than the highest errno value above.                 */
#define _PDCLIB_ERRNO_MAX 141

#endif
