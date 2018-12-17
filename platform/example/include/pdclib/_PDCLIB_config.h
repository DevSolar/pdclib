/* Internal PDCLib configuration <_PDCLIB_config.h>
   (Generic Template)

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_CONFIG_H
#define _PDCLIB_CONFIG_H _PDCLIB_CONFIG_H

/* -------------------------------------------------------------------------- */
/* Misc                                                                       */
/* -------------------------------------------------------------------------- */

/* The character (sequence) your platform uses as newline.                    */
#define _PDCLIB_endl "\n"

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

/* Define this to some compiler directive that can be written after the       */
/* parameter list of a function declaration to indicate the function does     */
/* never return. If your compiler does not support such a directive, define   */
/* to nothing. (This is to avoid warnings with the exit functions under GCC.) */
#define _PDCLIB_NORETURN __attribute__(( noreturn ))

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
#ifdef __CHAR_UNSIGNED__
#define _PDCLIB_CHAR_SIGNED 0
#else
#define _PDCLIB_CHAR_SIGNED 1
#endif

/* Width of the integer types short, int, long, and long long, in bytes.      */
/* SHRT == 2, INT >= SHRT, LONG >= INT >= 4, LLONG >= LONG - check your       */
/* compiler manuals.                                                          */
#define _PDCLIB_SHRT_BYTES  2
#define _PDCLIB_INT_BYTES   4
#ifdef __LP64__
#define _PDCLIB_LONG_BYTES  8
#else
#define _PDCLIB_LONG_BYTES  4
#endif
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

#define _PDCLIB_FAST64 LONG
#define _PDCLIB_fast64 long
#define _PDCLIB_FAST64_CONV l

/* -------------------------------------------------------------------------- */
/* What follows are a couple of "special" typedefs and their limits. Again,   */
/* the actual definition of the limits is done in <_PDCLIB_int.h>, and the    */
/* defines here are merely "configuration". See above for details.            */
/* -------------------------------------------------------------------------- */

/* The result type of substracting two pointers */
#define _PDCLIB_ptrdiff long
#define _PDCLIB_PTRDIFF LONG
#define _PDCLIB_PTR_CONV l

/* An integer type that can be accessed as atomic entity (think asynchronous
   interrupts). The type itself is not defined in a freestanding environment,
   but its limits are. (Don't ask.)
*/
#define _PDCLIB_sig_atomic int
#define _PDCLIB_SIG_ATOMIC INT

/* Result type of the 'sizeof' operator (must be unsigned) */
#define _PDCLIB_size unsigned long
#define _PDCLIB_SIZE ULONG

/* Large enough an integer to hold all character codes of the largest supported
   locale.
*/
#define _PDCLIB_wchar unsigned int
#define _PDCLIB_WCHAR UINT

/* Large enough an integer to hold all character codes of the largest supported
   locale plus WEOF (which needs not to be equal to EOF, nor needs to be of
   negative value).
*/
#define _PDCLIB_wint unsigned int
#define _PDCLIB_WINT UINT

/* (Signed) integer type capable of taking the (cast) value of a void *, and
   having the value cast back to void *, comparing equal to the original.
*/
#define _PDCLIB_intptr long
#define _PDCLIB_INTPTR LONG

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

/* -------------------------------------------------------------------------- */
/* Time types                                                                 */
/* -------------------------------------------------------------------------- */

/* See <time.h> for a couple of comments on these types and their semantics. */

#define _PDCLIB_time long

#define _PDCLIB_clock long
#define _PDCLIB_CLOCKS_PER_SEC 1000000

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
#define _PDCLIB_offsetof( type, member ) ( (size_t) &( ( (type *) 0 )->member ) )

/* Variable Length Parameter List Handling (<stdarg.h>)
   The macros defined by <stdarg.h> are highly dependent on the calling
   conventions used, and you probably have to replace them with builtins of
   your compiler.
*/

#if defined( __i386 )

/* The following generic implementation works only for pure
   stack-based architectures, and only if arguments are aligned to pointer
   type. Credits to Michael Moody, who contributed this to the Public Domain.
*/

/* Internal helper macro. va_round is not part of <stdarg.h>. */
#define _PDCLIB_va_round( type ) ( (sizeof(type) + sizeof(void *) - 1) & ~(sizeof(void *) - 1) )

typedef char * _PDCLIB_va_list;
#define _PDCLIB_va_arg( ap, type ) ( (ap) += (_PDCLIB_va_round(type)), ( *(type*) ( (ap) - (_PDCLIB_va_round(type)) ) ) )
#define _PDCLIB_va_copy( dest, src ) ( (dest) = (src), (void)0 )
#define _PDCLIB_va_end( ap ) ( (ap) = (void *)0, (void)0 )
#define _PDCLIB_va_start( ap, parmN ) ( (ap) = (char *) &parmN + ( _PDCLIB_va_round(parmN) ), (void)0 )

#elif defined( __x86_64 ) || defined( __arm__ ) || defined( __ARM_NEON )

/* No way to cover x86_64 or arm with a generic implementation, as it uses
    register-based parameter passing. Using compiler builtins here.
*/
typedef __builtin_va_list _PDCLIB_va_list;
#define _PDCLIB_va_arg( ap, type ) ( __builtin_va_arg( ap, type ) )
#define _PDCLIB_va_copy( dest, src ) ( __builtin_va_copy( dest, src ) )
#define _PDCLIB_va_end( ap ) ( __builtin_va_end( ap ) )
#define _PDCLIB_va_start( ap, parmN ) ( __builtin_va_start( ap, parmN ) )

#else

#error Please create your own _PDCLIB_config.h. Using the existing one as-is will not work.

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
#define _PDCLIB_PAGESIZE 4096

/* Set this to the minimum memory node size. Any malloc() for a smaller size
   will be satisfied by a malloc() of this size instead (to avoid excessive
   fragmentation).
*/
#define _PDCLIB_MINALLOC 8

/* I/O ---------------------------------------------------------------------- */

/* The type of the file descriptor returned by _PDCLIB_open(). */
typedef int _PDCLIB_fd_t;

/* The value (of type _PDCLIB_fd_t) returned by _PDCLIB_open() if the operation
   failed.
*/
#define _PDCLIB_NOHANDLE ( (_PDCLIB_fd_t) -1 )

/* The default size for file buffers. Must be at least 256. */
#define _PDCLIB_BUFSIZ 1024

/* The minimum number of files the implementation can open simultaneously. Must
   be at least 8. Depends largely on how the bookkeeping is done by fopen() /
   freopen() / fclose(). The example implementation limits the number of open
   files only by available memory.
*/
#define _PDCLIB_FOPEN_MAX 8

/* Length of the longest filename the implementation guarantees to support. */
#define _PDCLIB_FILENAME_MAX 128

/* Maximum length of filenames generated by tmpnam(). (See tmpfile.c.) */
#define _PDCLIB_L_tmpnam 46

/* Number of distinct file names that can be generated by tmpnam(). */
#define _PDCLIB_TMP_MAX 50

/* The values of SEEK_SET, SEEK_CUR and SEEK_END, used by fseek().
   Since at least one platform (POSIX) uses the same symbols for its own "seek"
   function, we use whatever the host defines (if it does define them).
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

   The standard only defines three distinct errno values: ERANGE, EDOM, and
   EILSEQ. The standard leaves it up to "the implementation" whether there are
   any more beyond those three. There is some controversy as to whether errno is
   such a good idea at all, so you might want to come up with a different error
   reporting facility for your platform.
*/

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

/* The maximum value that errno can be set to. This is used to set the size   */
/* of the array in struct _PDCLIB_lc_text_t holding error messages for the    */
/* strerror() and perror() functions. (If you change this value because you   */
/* are using additional errno values, you *HAVE* to provide appropriate error */
/* messages for *ALL* locales.)                                               */
/* Default is 4 (0, ERANGE, EDOM, EILSEQ).                                    */
#define _PDCLIB_ERRNO_MAX 132

/* locale data -------------------------------------------------------------- */

/* The default path where PDCLib should look for its locale data.             */
/* Must end with the appropriate separator character.                         */
#define _PDCLIB_LOCALE_PATH "/usr/share/pdclib/i18n"

/* The name of the environment variable that can be used to override that     */
/* path setting.                                                              */
#define _PDCLIB_LOCALE_PATH_ENV PDCLIB_I18N

#ifdef __CYGWIN__
typedef unsigned int wint_t;
#endif


#endif
