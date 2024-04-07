/* PDCLib internal logic <_PDCLIB_internal.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_INTERNAL_H
#define _PDCLIB_INTERNAL_H _PDCLIB_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------- */
/* You should not have to edit anything in this file; if you DO have to, it   */
/* would be considered a bug / missing feature: notify the author(s).         */
/* -------------------------------------------------------------------------- */

#include "pdclib/_PDCLIB_config.h"

/* -------------------------------------------------------------------------- */
/* Standard Version                                                           */
/* -------------------------------------------------------------------------- */

/* Many a compiler gets this wrong, so you might have to hardcode it instead. */

#if __STDC__ != 1
#error Compiler does not define _ _STDC_ _ to 1 (not standard-compliant)!
#endif

#ifndef __STDC_HOSTED__
#error Compiler does not define _ _STDC_HOSTED_ _ (not standard-compliant)!
#elif __STDC_HOSTED__ != 0 && __STDC_HOSTED__ != 1
#error Compiler does not define _ _STDC_HOSTED_ _ to 0 or 1 (not standard-compliant)!
#endif

/* null pointer constant -- ((void *)0) in C, 0 in C++98, nullptr since C++11 */
#ifdef __cplusplus
#if __cplusplus >= 201103L
#define _PDCLIB_NULL nullptr
#else
#define _PDCLIB_NULL 0
#endif
#else
#define _PDCLIB_NULL ((void *)0)
#endif

/* restrict / inline enabled for C99 onward only */
#if defined( __cplusplus ) || ! defined( __STDC_VERSION ) ||  __STDC_VERSION__ < 199901L
#define _PDCLIB_restrict
#define _PDCLIB_inline
#else
#define _PDCLIB_restrict restrict
#define _PDCLIB_inline inline
#endif

/* noreturn enabled for C11 onward only */
#if defined( __cplusplus ) && __cplusplus >= 201103L
#define _PDCLIB_Noreturn [[noreturn]]
#else
#if defined( __STDC_VERSION__ ) >= 201112L
#define _PDCLIB_Noreturn _Noreturn
#else
#define _PDCLIB_Noreturn
#endif
#endif

/* -------------------------------------------------------------------------- */
/* Helper macros:                                                             */
/*                                                                            */
/* (defined in _PDCLIB_config.h)                                              */
/* _PDCLIB_cc( x, y ) concatenates two preprocessor tokens without extending. */
/* _PDCLIB_concat( x, y ) concatenates two preprocessor tokens with extending */
/*                                                                            */
/* (defined below)                                                            */
/* _PDCLIB_static_assert( e, m ) does a compile-time assertion of expression  */
/*                               e, with m as the failure message.            */
/* _PDCLIB_symbol2string( x ) turn symbol into string literal (by adding ""). */
/* _PDCLIB_value2string( x ) expands a preprocessor token and turns it into a */
/*                           string literal (by adding "").                   */
/* _PDCLIB_TYPE_SIGNED( type ) resolves to true if type is signed.            */
/* _PDCLIB_LOCK( mtx ) lock a mutex if library has threads support.           */
/* _PDCLIB_UNLOCK( mtx ) unlock a mutex if library has threads support.       */
/* _PDCLIB_CONSTRAINT_VIOLATION( e ) expand errno number e to parameter list  */
/*                                   fit for Annex K constraint violation     */
/*                                   handler.                                 */
/* -------------------------------------------------------------------------- */

#define _PDCLIB_static_assert( e, m ) enum { _PDCLIB_concat( _PDCLIB_assert_, __LINE__ ) = 1 / ( !!(e) ) }

#define _PDCLIB_TYPE_SIGNED( type ) (((type) -1) < 0)

#define _PDCLIB_symbol2string( x ) #x
#define _PDCLIB_value2string( x ) _PDCLIB_symbol2string( x )

#ifndef __STDC_NO_THREADS__
#define _PDCLIB_LOCK( mtx ) mtx_lock( &mtx )
#define _PDCLIB_UNLOCK( mtx ) mtx_unlock( &mtx )
#else
#define _PDCLIB_LOCK( mtx )
#define _PDCLIB_UNLOCK( mtx )
#endif

#define _PDCLIB_CONSTRAINT_VIOLATION( e ) _PDCLIB_lc_messages->errno_texts[e], NULL, e

#define _PDCLIB_GETC( fh ) ( ( fh->ungetidx == 0 ) ? ( unsigned char )fh->buffer[ fh->bufidx++ ] : ( unsigned char )fh->ungetbuf[ --fh->ungetidx ] )

#define _PDCLIB_CHECKBUFFER( fh ) ( ( ( fh->bufidx == fh->bufend ) && ( fh->ungetidx == 0 ) ) ? _PDCLIB_fillbuffer( fh ) : 0 )

/* -------------------------------------------------------------------------- */
/* Preparing the length modifiers used in <inttypes.h>.                       */
/* -------------------------------------------------------------------------- */

/* We use the _MAX value as a proxy for the actual type here. That is crude
   but the best we can do, cross-platform wise.
   Identifying which type the leastN_t / fastN_t / intmax_t / intptr_t are
   and providing the appropriate printf()/scanf() length modifier.
*/

#if _PDCLIB_INT_FAST8_MAX == _PDCLIB_SCHAR_MAX
#define _PDCLIB_INT_FAST8_PREFIX hh
#elif _PDCLIB_INT_FAST8_MAX == _PDCLIB_SHRT_MAX
#define _PDCLIB_INT_FAST8_PREFIX h
#elif _PDCLIB_INT_FAST8_MAX == _PDCLIB_INT_MAX
#define _PDCLIB_INT_FAST8_PREFIX
#elif _PDCLIB_INT_FAST8_MAX == _PDCLIB_LONG_MAX
#define _PDCLIB_INT_FAST8_PREFIX l
#elif _PDCLIB_INT_FAST8_MAX == _PDCLIB_LLONG_MAX
#define _PDCLIB_INT_FAST8_PREFIX ll
#else
#error No matching native type for int_fast8_t. Please check your setup.
#endif

#if _PDCLIB_INT_FAST16_MAX == _PDCLIB_SCHAR_MAX
#define _PDCLIB_INT_FAST16_PREFIX hh
#elif _PDCLIB_INT_FAST16_MAX == _PDCLIB_SHRT_MAX
#define _PDCLIB_INT_FAST16_PREFIX h
#elif _PDCLIB_INT_FAST16_MAX == _PDCLIB_INT_MAX
#define _PDCLIB_INT_FAST16_PREFIX
#elif _PDCLIB_INT_FAST16_MAX == _PDCLIB_LONG_MAX
#define _PDCLIB_INT_FAST16_PREFIX l
#elif _PDCLIB_INT_FAST16_MAX == _PDCLIB_LLONG_MAX
#define _PDCLIB_INT_FAST16_PREFIX ll
#else
#error No matching native type for int_fast16_t. Please check your setup.
#endif

#if _PDCLIB_INT_FAST32_MAX == _PDCLIB_SCHAR_MAX
#define _PDCLIB_INT_FAST32_PREFIX hh
#elif _PDCLIB_INT_FAST32_MAX == _PDCLIB_SHRT_MAX
#define _PDCLIB_INT_FAST32_PREFIX h
#elif _PDCLIB_INT_FAST32_MAX == _PDCLIB_INT_MAX
#define _PDCLIB_INT_FAST32_PREFIX
#elif _PDCLIB_INT_FAST32_MAX == _PDCLIB_LONG_MAX
#define _PDCLIB_INT_FAST32_PREFIX l
#elif _PDCLIB_INT_FAST32_MAX == _PDCLIB_LLONG_MAX
#define _PDCLIB_INT_FAST32_PREFIX ll
#else
#error No matching native type for int_fast32_t. Please check your setup.
#endif

#if _PDCLIB_INT_FAST64_MAX == _PDCLIB_SCHAR_MAX
#define _PDCLIB_INT_FAST64_PREFIX hh
#elif _PDCLIB_INT_FAST64_MAX == _PDCLIB_SHRT_MAX
#define _PDCLIB_INT_FAST64_PREFIX h
#elif _PDCLIB_INT_FAST64_MAX == _PDCLIB_INT_MAX
#define _PDCLIB_INT_FAST64_PREFIX
#elif _PDCLIB_INT_FAST64_MAX == _PDCLIB_LONG_MAX
#define _PDCLIB_INT_FAST64_PREFIX l
#elif _PDCLIB_INT_FAST64_MAX == _PDCLIB_LLONG_MAX
#define _PDCLIB_INT_FAST64_PREFIX ll
#else
#error No matching native type for int_fast64_t. Please check your setup.
#endif

/* Many of the combinations below can very likely be ruled out logically.
   All combinations are still listed for simplicity's sake (and to not fall
   into the trap of false assumptions).
*/

#if _PDCLIB_INT_LEAST8_MAX == _PDCLIB_SCHAR_MAX
#define _PDCLIB_INT_LEAST8_PREFIX hh
#elif _PDCLIB_INT_LEAST8_MAX == _PDCLIB_SHRT_MAX
#define _PDCLIB_INT_LEAST8_PREFIX h
#elif _PDCLIB_INT_LEAST8_MAX == _PDCLIB_INT_MAX
#define _PDCLIB_INT_LEAST8_PREFIX
#elif _PDCLIB_INT_LEAST8_MAX == _PDCLIB_LONG_MAX
#define _PDCLIB_INT_LEAST8_PREFIX l
#elif _PDCLIB_INT_LEAST8_MAX == _PDCLIB_LLONG_MAX
#define _PDCLIB_INT_LEAST8_PREFIX ll
#else
#error No matching native type for int_least8_t. Please check your setup.
#endif

#if _PDCLIB_INT_LEAST16_MAX == _PDCLIB_SCHAR_MAX
#define _PDCLIB_INT_LEAST16_PREFIX hh
#elif _PDCLIB_INT_LEAST16_MAX == _PDCLIB_SHRT_MAX
#define _PDCLIB_INT_LEAST16_PREFIX h
#elif _PDCLIB_INT_LEAST16_MAX == _PDCLIB_INT_MAX
#define _PDCLIB_INT_LEAST16_PREFIX
#elif _PDCLIB_INT_LEAST16_MAX == _PDCLIB_LONG_MAX
#define _PDCLIB_INT_LEAST16_PREFIX l
#elif _PDCLIB_INT_LEAST16_MAX == _PDCLIB_LLONG_MAX
#define _PDCLIB_INT_LEAST16_PREFIX ll
#else
#error No matching native type for int_least16_t. Please check your setup.
#endif

#if _PDCLIB_INT_LEAST32_MAX == _PDCLIB_SCHAR_MAX
#define _PDCLIB_INT_LEAST32_PREFIX hh
#elif _PDCLIB_INT_LEAST32_MAX == _PDCLIB_SHRT_MAX
#define _PDCLIB_INT_LEAST32_PREFIX h
#elif _PDCLIB_INT_LEAST32_MAX == _PDCLIB_INT_MAX
#define _PDCLIB_INT_LEAST32_PREFIX
#elif _PDCLIB_INT_LEAST32_MAX == _PDCLIB_LONG_MAX
#define _PDCLIB_INT_LEAST32_PREFIX l
#elif _PDCLIB_INT_LEAST32_MAX == _PDCLIB_LLONG_MAX
#define _PDCLIB_INT_LEAST32_PREFIX ll
#else
#error No matching native type for int_least32_t. Please check your setup.
#endif

#if _PDCLIB_INT_LEAST64_MAX == _PDCLIB_SCHAR_MAX
#define _PDCLIB_INT_LEAST64_PREFIX hh
#elif _PDCLIB_INT_LEAST64_MAX == _PDCLIB_SHRT_MAX
#define _PDCLIB_INT_LEAST64_PREFIX h
#elif _PDCLIB_INT_LEAST64_MAX == _PDCLIB_INT_MAX
#define _PDCLIB_INT_LEAST64_PREFIX
#elif _PDCLIB_INT_LEAST64_MAX == _PDCLIB_LONG_MAX
#define _PDCLIB_INT_LEAST64_PREFIX l
#elif _PDCLIB_INT_LEAST64_MAX == _PDCLIB_LLONG_MAX
#define _PDCLIB_INT_LEAST64_PREFIX ll
#else
#error No matching native type for int_least64_t. Please check your setup.
#endif

#if _PDCLIB_INTMAX_MAX == _PDCLIB_SCHAR_MAX
#define _PDCLIB_INTMAX_PREFIX hh
#elif _PDCLIB_INTMAX_MAX == _PDCLIB_SHRT_MAX
#define _PDCLIB_INTMAX_PREFIX h
#elif _PDCLIB_INTMAX_MAX == _PDCLIB_INT_MAX
#define _PDCLIB_INTMAX_PREFIX
#elif _PDCLIB_INTMAX_MAX == _PDCLIB_LONG_MAX
#define _PDCLIB_INTMAX_PREFIX l
#elif _PDCLIB_INTMAX_MAX == _PDCLIB_LLONG_MAX
#define _PDCLIB_INTMAX_PREFIX ll
#else
#error No matching native type for intmax_t. Please check your setup.
#endif

#if _PDCLIB_INTPTR_MAX == _PDCLIB_SCHAR_MAX
#define _PDCLIB_INTPTR_PREFIX hh
#elif _PDCLIB_INTPTR_MAX == _PDCLIB_SHRT_MAX
#define _PDCLIB_INTPTR_PREFIX h
#elif _PDCLIB_INTPTR_MAX == _PDCLIB_INT_MAX
#define _PDCLIB_INTPTR_PREFIX
#elif _PDCLIB_INTPTR_MAX == _PDCLIB_LONG_MAX
#define _PDCLIB_INTPTR_PREFIX l
#elif _PDCLIB_INTPTR_MAX == _PDCLIB_LLONG_MAX
#define _PDCLIB_INTPTR_PREFIX ll
#else
#error No matching native type for intptr_t. Please check your setup.
#endif

/* We might not have a type definition for sig_atomic_t at this point. The    */
/* clang compiler does not provide an appropriate predefine for it. So if we  */
/* do not have _PDCLIB_sig_atomic_t, identify the type trough its MAX value.  */

#ifndef _PDCLIB_sig_atomic_t

#if _PDCLIB_SIG_ATOMIC_MAX == _PDCLIB_SCHAR_MAX
#define _PDCLIB_sig_atomic_t char
#elif _PDCLIB_SIG_ATOMIC_MAX == _PDCLIB_SHRT_MAX
#define _PDCLIB_sig_atomic_t short
#elif _PDCLIB_SIG_ATOMIC_MAX == _PDCLIB_INT_MAX
#define _PDCLIB_sig_atomic_t int
#elif _PDCLIB_SIG_ATOMIC_MAX == _PDCLIB_LONG_MAX
#define _PDCLIB_sig_atomic_t long
#elif _PDCLIB_SIG_ATOMIC_MAX == _PDCLIB_LLONG_MAX
#define _PDCLIB_sig_atomic_t long long
#else
#error No matching native type for sig_atomic_t. Please check your setup.
#endif

#endif

/* -------------------------------------------------------------------------- */
/* Various <stdio.h> internals                                                */
/* -------------------------------------------------------------------------- */

/* Flags for representing mode (see fopen()). Note these must fit the same
   status field as the _IO?BF flags in <stdio.h> and the internal flags below.
*/
#define _PDCLIB_FREAD   (1u<<3)
#define _PDCLIB_FWRITE  (1u<<4)
#define _PDCLIB_FAPPEND (1u<<5)
#define _PDCLIB_FRW     (1u<<6)
#define _PDCLIB_FBIN    (1u<<7)

/* Internal flags, made to fit the same status field as the flags above. */
/* -------------------------------------------------------------------------- */
/* free() the buffer memory on closing (setvbuf()) */
#define _PDCLIB_FREEBUFFER  (1u<<8)
/* stream has encountered error / EOF */
#define _PDCLIB_ERRORFLAG   (1u<<9)
#define _PDCLIB_EOFFLAG     (1u<<10)
/* stream is wide-oriented */
#define _PDCLIB_WIDESTREAM  (1u<<11)
/* stream is byte-oriented */
#define _PDCLIB_BYTESTREAM  (1u<<12)
/* file associated with stream should be remove()d on closing (tmpfile()) */
#define _PDCLIB_DELONCLOSE  (1u<<13)

/* Position / status structure for getpos() / fsetpos(). */
struct _PDCLIB_fpos_t
{
    _PDCLIB_uint_least64_t offset; /* File position offset */
    int                    status; /* Multibyte parsing state (unused, reserved) */
};

/* FILE structure */
struct _PDCLIB_file_t
{
    _PDCLIB_fd_t            handle;   /* OS file handle */
    char *                  buffer;   /* Pointer to buffer memory */
    _PDCLIB_size_t          bufsize;  /* Size of buffer */
    _PDCLIB_size_t          bufidx;   /* Index of current position in buffer */
    _PDCLIB_size_t          bufend;   /* Index of last pre-read character in buffer */
    struct _PDCLIB_fpos_t   pos;      /* Offset and multibyte parsing state */
    _PDCLIB_size_t          ungetidx; /* Number of ungetc()'ed characters */
    unsigned char           ungetbuf[_PDCLIB_UNGETCBUFSIZE]; /* ungetc() buffer */
    unsigned int            status;   /* Status flags; see above */
    /* multibyte parsing status to be added later */
#ifndef __STDC_NO_THREADS__
    _PDCLIB_mtx_t           mtx;      /* Multithreading safety */
#endif
    char *                  filename; /* Name the current stream has been opened with */
    struct _PDCLIB_file_t * next;     /* Pointer to next struct (internal) */
};

/* -------------------------------------------------------------------------- */
/* Internal data types                                                        */
/* -------------------------------------------------------------------------- */

/* Structure required by both atexit() and exit() for handling atexit functions */
struct _PDCLIB_exitfunc_t
{
    struct _PDCLIB_exitfunc_t * next;
    void ( *func )( void );
};

/* Status structure required by _PDCLIB_print(). */
struct _PDCLIB_status_t
{
    int              base;   /* base to which the value shall be converted   */
    _PDCLIB_int_fast32_t flags; /* flags and length modifiers                */
    _PDCLIB_size_t   n;      /* print: maximum characters to be written      */
                             /* scan:  number matched conversion specifiers  */
    _PDCLIB_size_t   i;      /* number of characters read/written            */
    _PDCLIB_size_t   current;/* chars read/written in the CURRENT conversion */
    char *           s;      /* *sprintf(): target buffer                    */
                             /* *sscanf():  source string                    */
    _PDCLIB_size_t   width;  /* specified field width                        */
    int              prec;   /* specified field precision                    */
    struct _PDCLIB_file_t * stream; /* *fprintf() / *fscanf() stream         */
    _PDCLIB_va_list  arg;    /* argument stack                               */
};

/* -------------------------------------------------------------------------- */
/* Declaration of helper functions (implemented in functions/_PDCLIB).        */
/* -------------------------------------------------------------------------- */

/* This is the main function called by atoi(), atol() and atoll().            */
_PDCLIB_LOCAL _PDCLIB_intmax_t _PDCLIB_atomax( const char * s );

/* Two helper functions used by strtol(), strtoul() and long long variants.   */
_PDCLIB_LOCAL const char * _PDCLIB_strtox_prelim( const char * p, char * sign, int * base );
_PDCLIB_LOCAL _PDCLIB_uintmax_t _PDCLIB_strtox_main( const char ** p, unsigned int base, _PDCLIB_uintmax_t error, _PDCLIB_uintmax_t limval, int limdigit, char * sign );

/* A helper function used by strtof(), strtod(), and strtold().               */
_PDCLIB_LOCAL void _PDCLIB_strtod_scan( const char * s, const char ** dec, const char ** frac, const char ** exp, int base );

/* Digits arrays used by various integer conversion functions */
extern const char _PDCLIB_digits[];
extern const char _PDCLIB_Xdigits[];

/* The worker for all printf() type of functions. The pointer spec should point
   to the introducing '%' of a conversion specifier. The status structure is to
   be that of the current printf() function, of which the members n, s, stream
   and arg will be preserved; i will be updated; and all others will be trashed
   by the function.
   Returns a pointer to the first character not parsed as conversion specifier.
*/
_PDCLIB_LOCAL const char * _PDCLIB_print( const char * spec, struct _PDCLIB_status_t * status );

/* The worker for all scanf() type of functions. The pointer spec should point
   to the introducing '%' of a conversion specifier. The status structure is to
   be that of the current scanf() function, of which the member stream will be
   preserved; n, i, and s will be updated; and all others will be trashed by
   the function.
   Returns a pointer to the first character not parsed as conversion specifier,
   or NULL in case of error.
   FIXME: Should distinguish between matching and input error
*/
_PDCLIB_LOCAL const char * _PDCLIB_scan( const char * spec, struct _PDCLIB_status_t * status );

/* Parsing any fopen() style filemode string into a number of flags. */
_PDCLIB_LOCAL unsigned int _PDCLIB_filemode( const char * mode );

/* Initialize a FILE structure. If the parameter is NULL, a new FILE structure
   is malloc'ed. Returns a pointer to the stream if successful, NULL otherwise.
*/
_PDCLIB_LOCAL struct _PDCLIB_file_t * _PDCLIB_init_file_t( struct _PDCLIB_file_t * stream );

/* Sanity checking and preparing of read buffer, should be called first thing
   by any stdio read-data function.
   Returns 0 on success, EOF on error.
   On error, EOF / error flags and errno are set appropriately.
*/
_PDCLIB_LOCAL int _PDCLIB_prepread( struct _PDCLIB_file_t * stream );

/* Sanity checking, should be called first thing by any stdio write-data
   function.
   Returns 0 on success, EOF on error.
   On error, error flags and errno are set appropriately.
*/
_PDCLIB_LOCAL int _PDCLIB_prepwrite( struct _PDCLIB_file_t * stream );

/* Closing all streams on program exit */
_PDCLIB_LOCAL void _PDCLIB_closeall( void );

/* Check if a given year is a leap year. Parameter is offset to 1900. */
_PDCLIB_LOCAL int _PDCLIB_is_leap( int year_offset );

/* Read a specified number of lines from a file stream; return a pointer to
   allocated memory holding the lines (newlines replaced with zero terminators)
   or NULL in case of error.
*/
_PDCLIB_LOCAL char * _PDCLIB_load_lines( struct _PDCLIB_file_t * stream, _PDCLIB_size_t lines );

/* Returns the (locale dependent) error message associated with the argument
   errno value.
*/
_PDCLIB_LOCAL char * _PDCLIB_geterrtext( int errnum );

/* Returns non-zero if the given stream is on the internal list of open files,
   zero otherwise. Sets the second paramenter (if not NULL) to the previous
   stream on the list (or NULL if the given stream is the first on the list).
   This function does not lock _PDCLIB_filelist_mtx, this needs to be done by
   the calling function (_PDCLIB_getstream() or freopen()).
*/
_PDCLIB_LOCAL int _PDCLIB_isstream( struct _PDCLIB_file_t * stream, struct _PDCLIB_file_t ** previous );

/* Removes the given stream from the internal list of open files. Returns zero
   if successful, non-zero otherwise. In case of error, sets errno to EBADF.
   This function does not lock _PDCLIB_filelist_mtx, this needs to be done by
   the calling function (fclose()).
*/
_PDCLIB_LOCAL int _PDCLIB_getstream( struct _PDCLIB_file_t * stream );

/* Backend for strtok and strtok_s (plus potential extensions like strtok_r). */
_PDCLIB_LOCAL char * _PDCLIB_strtok( char * _PDCLIB_restrict s1, _PDCLIB_size_t * _PDCLIB_restrict s1max, const char * _PDCLIB_restrict s2, char ** _PDCLIB_restrict ptr );

/* -------------------------------------------------------------------------- */
/* Declaration of helper functions (implemented in functions/_dtoa).          */
/* -------------------------------------------------------------------------- */

_PDCLIB_LOCAL void _PDCLIB_freedtoa( char * s );
_PDCLIB_LOCAL char * _PDCLIB_dtoa( double dd, int mode, int ndigits, int * decpt, int * sign, char ** rve );

/* -------------------------------------------------------------------------- */
/* errno                                                                      */
/* -------------------------------------------------------------------------- */

/* A mechanism for delayed evaluation.
   If PDCLib would call its error number "errno" directly, there would be no way
   to catch its value from underlying system calls that also use it (i.e., POSIX
   operating systems). That is why we use an internal name, providing a means to
   access it through <errno.h>.
*/
_PDCLIB_PUBLIC int * _PDCLIB_errno_func( void );

/* -------------------------------------------------------------------------- */
/* <locale.h> support                                                         */
/* -------------------------------------------------------------------------- */

#define _PDCLIB_LC_ALL        0
#define _PDCLIB_LC_COLLATE    1
#define _PDCLIB_LC_CTYPE      2
#define _PDCLIB_LC_MONETARY   3
#define _PDCLIB_LC_NUMERIC    4
#define _PDCLIB_LC_TIME       5
#define _PDCLIB_LC_MESSAGES   6
#define _PDCLIB_LC_COUNT      7

#define _PDCLIB_CTYPE_ALPHA   1
#define _PDCLIB_CTYPE_BLANK   2
#define _PDCLIB_CTYPE_CNTRL   4
#define _PDCLIB_CTYPE_GRAPH   8
#define _PDCLIB_CTYPE_PUNCT  16
#define _PDCLIB_CTYPE_SPACE  32
#define _PDCLIB_CTYPE_LOWER  64
#define _PDCLIB_CTYPE_UPPER 128

#define _PDCLIB_CHARSET_SIZE ( 1 << _PDCLIB_CHAR_BIT )

struct _PDCLIB_lc_lconv_numeric_t
{
    char * decimal_point;
    char * thousands_sep;
    char * grouping;
};

struct _PDCLIB_lc_lconv_monetary_t
{
    char * mon_decimal_point;
    char * mon_thousands_sep;
    char * mon_grouping;
    char * positive_sign;
    char * negative_sign;
    char * currency_symbol;
    char * int_curr_symbol;
    char frac_digits;
    char p_cs_precedes;
    char n_cs_precedes;
    char p_sep_by_space;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;
    char int_frac_digits;
    char int_p_cs_precedes;
    char int_n_cs_precedes;
    char int_p_sep_by_space;
    char int_n_sep_by_space;
    char int_p_sign_posn;
    char int_n_sign_posn;
};

struct _PDCLIB_lc_numeric_monetary_t
{
    struct lconv * lconv;
    int numeric_alloced;
    int monetary_alloced;
};

extern struct _PDCLIB_lc_numeric_monetary_t _PDCLIB_lc_numeric_monetary;

struct _PDCLIB_lc_collate_t
{
    int alloced;
    /* 1..3 code points */
    /* 1..8, 18 collation elements of 3 16-bit integers */
};

extern struct _PDCLIB_lc_collate_t _PDCLIB_lc_collate_C;
extern struct _PDCLIB_lc_collate_t * _PDCLIB_lc_collate;

/* One entry to the _PDCLIB_lc_ctype_t.entry data table */
struct _PDCLIB_lc_ctype_entry_t
{
    _PDCLIB_uint_least16_t flags;  /* Whether a character is of a given CTYPE */
    unsigned char upper;           /* Result for toupper() */
    unsigned char lower;           /* Result for tolower() */
};

struct _PDCLIB_lc_ctype_t
{
    int alloced;                             /* .entry dynamically allocated? */
    int digits_low;                          /* Where decimal digits start */
    int digits_high;                         /* Where decimal digits end */
    int Xdigits_low;                         /* Where A..F start */
    int Xdigits_high;                        /* Where A..F end */
    int xdigits_low;                         /* Where a..f start */
    int xdigits_high;                        /* Where a..f end */
    struct _PDCLIB_lc_ctype_entry_t * entry; /* The data table */
};

extern struct _PDCLIB_lc_ctype_t _PDCLIB_lc_ctype_C;
extern struct _PDCLIB_lc_ctype_t * _PDCLIB_lc_ctype;

struct _PDCLIB_lc_messages_t
{
    int alloced;
    char * errno_texts[_PDCLIB_ERRNO_MAX]; /* strerror() / perror()   */
};

extern struct _PDCLIB_lc_messages_t _PDCLIB_lc_messages_C;
extern struct _PDCLIB_lc_messages_t * _PDCLIB_lc_messages;

struct _PDCLIB_lc_time_t
{
    int alloced;
    char * month_name_abbr[12]; /* month names, abbreviated                   */
    char * month_name_full[12]; /* month names, full                          */
    char * day_name_abbr[7];    /* weekday names, abbreviated                 */
    char * day_name_full[7];    /* weekday names, full                        */
    char * date_time_format;    /* date / time format for strftime( "%c" )    */
    char * time_format_12h;     /* 12-hour time format for strftime( "%r" )   */
    char * date_format;         /* date format for strftime( "%x" )           */
    char * time_format;         /* time format for strftime( "%X" )           */
    char * am_pm[2];            /* AM / PM designation                        */
};

extern struct _PDCLIB_lc_time_t _PDCLIB_lc_time_C;
extern struct _PDCLIB_lc_time_t * _PDCLIB_lc_time;

_PDCLIB_LOCAL struct _PDCLIB_lc_lconv_numeric_t * _PDCLIB_load_lc_numeric( const char * path, const char * locale );
_PDCLIB_LOCAL struct _PDCLIB_lc_lconv_monetary_t * _PDCLIB_load_lc_monetary( const char * path, const char * locale );
_PDCLIB_LOCAL struct _PDCLIB_lc_collate_t * _PDCLIB_load_lc_collate( const char * path, const char * locale );
_PDCLIB_LOCAL struct _PDCLIB_lc_ctype_t * _PDCLIB_load_lc_ctype( const char * path, const char * locale );
_PDCLIB_LOCAL struct _PDCLIB_lc_time_t * _PDCLIB_load_lc_time( const char * path, const char * locale );
_PDCLIB_LOCAL struct _PDCLIB_lc_messages_t * _PDCLIB_load_lc_messages( const char * path, const char * locale );

/* -------------------------------------------------------------------------- */
/* _PDCLIB_bigint_t support (required for floating point conversions)         */
/* -------------------------------------------------------------------------- */

/* Must be divisible by 32.                                                   */
#define _PDCLIB_BIGINT_BITS 1024

#if _PDCLIB_BIGINT_DIGIT_BITS == 32
#define _PDCLIB_BIGINT_DIGIT_MAX UINT32_C( 0xFFFFFFFF )
#define _PDCLIB_BIGINT_BASE ( UINT64_C(1) << _PDCLIB_BIGINT_DIGIT_BITS )
typedef _PDCLIB_uint_least32_t _PDCLIB_bigint_digit_t;
typedef _PDCLIB_uint_least64_t _PDCLIB_bigint_arith_t;
typedef _PDCLIB_int_least64_t _PDCLIB_bigint_sarith_t;
#elif _PDCLIB_BIGINT_DIGIT_BITS == 16
#define _PDCLIB_BIGINT_DIGIT_MAX UINT16_C( 0xFFFF )
#define _PDCLIB_BIGINT_BASE ( UINT32_C(1) << _PDCLIB_BIGINT_DIGIT_BITS )
typedef _PDCLIB_uint_least16_t _PDCLIB_bigint_digit_t;
typedef _PDCLIB_uint_least32_t _PDCLIB_bigint_arith_t;
typedef _PDCLIB_int_least32_t _PDCLIB_bigint_sarith_t;
#elif _PDCLIB_BIGINT_DIGIT_BITS == 8
/* For testing purposes only. */
#define _PDCLIB_BIGINT_DIGIT_MAX UINT8_C( 0xFF )
#define _PDCLIB_BIGINT_BASE ( UINT16_C(1) << _PDCLIB_BIGINT_DIGIT_BITS )
typedef _PDCLIB_uint_least8_t  _PDCLIB_bigint_digit_t;
typedef _PDCLIB_uint_least16_t _PDCLIB_bigint_arith_t;
typedef _PDCLIB_int_least16_t _PDCLIB_bigint_sarith_t;
#else
#error Only 16 or 32 supported for _PDCLIB_BIGINT_DIGIT_BITS.
#endif

/* How many "digits" a _PDCLIB_bigint_t holds.                                */
#define _PDCLIB_BIGINT_DIGITS _PDCLIB_BIGINT_BITS / _PDCLIB_BIGINT_DIGIT_BITS

/* Maximum number of characters needed for _PDCLIB_bigint_tostring()          */
#define _PDCLIB_BIGINT_CHARS ( _PDCLIB_BIGINT_BITS / 4 + _PDCLIB_BIGINT_DIGITS + 2 )

/* Type */
/* ---- */

typedef struct
{
    /* Least significant digit first */
    _PDCLIB_bigint_digit_t data[ _PDCLIB_BIGINT_DIGITS ];
    /* Number of digits used; zero value == zero size */
    _PDCLIB_size_t size;
} _PDCLIB_bigint_t;

/* Initializer */
/* ----------- */

/* Sets a bigint to pow2( n ) */
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint2( _PDCLIB_bigint_t * bigint, unsigned n );

/* Sets a bigint to pow10( n ) */
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint10( _PDCLIB_bigint_t * bigint, unsigned n );

/* Sets a bigint from a 32bit input value. */
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint32( _PDCLIB_bigint_t * bigint, _PDCLIB_uint_least32_t value );

/* Sets a bigint from two 32bit input values. */
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint64( _PDCLIB_bigint_t * bigint, _PDCLIB_uint_least32_t high, _PDCLIB_uint_least32_t low );

/* Sets a bigint to the mantissa of a floating point value, as used rather
   specifically in _PDCLIB_print_fp.c.
*/
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint_mant( _PDCLIB_bigint_t * bigint, unsigned char const * mant, _PDCLIB_size_t mant_dig );

/* Sets a bigint from another bigint. (Copies only value->size digits, so it is
   faster than a POD copy of a _PDCLIB_bigint_t in most cases.)
*/
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint( _PDCLIB_bigint_t * _PDCLIB_restrict bigint, _PDCLIB_bigint_t const * _PDCLIB_restrict value );

/* Comparison, Output */
/* ------------------ */

/* Compares two given bigint values. Returns 0 if lhs == rhs, a negative number
   if lhs < rhs, and a positive number if lhs > rhs.
*/
_PDCLIB_LOCAL int _PDCLIB_bigint_cmp( _PDCLIB_bigint_t const * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs );

/* Writes a hexadecimal representation of the given bigint into the given buffer.
   Buffer should be at least _PDCLIB_BIGINT_CHARS in size.
*/
_PDCLIB_LOCAL char * _PDCLIB_bigint_tostring( _PDCLIB_bigint_t const * _PDCLIB_restrict value, char * _PDCLIB_restrict buffer );

/* Operations (in-place) */
/* --------------------- */

/* Adds to a given bigint another given bigint. */
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint_add( _PDCLIB_bigint_t * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs );

/* Substracts from a given bigint another given bigint. */
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint_sub( _PDCLIB_bigint_t * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs );

/* Multiplies a given bigint with a given 32bit value. */
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint_mul_dig( _PDCLIB_bigint_t * lhs, _PDCLIB_bigint_digit_t rhs );

/* Divides a given bigint by a given 32bit value. */
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint_div_dig( _PDCLIB_bigint_t * lhs, _PDCLIB_bigint_digit_t rhs );

/* Shifts a given bigint left by a given count of bits. */
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint_shl( _PDCLIB_bigint_t * lhs, unsigned rhs );

/* Operations (into new bigint) */
/* ---------------------------- */

/* Multiplies a given bigint with another given bigint. */
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint_mul( _PDCLIB_bigint_t * _PDCLIB_restrict result, _PDCLIB_bigint_t const * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs );

/* Divides a given bigint by another given bigint. */
_PDCLIB_LOCAL _PDCLIB_bigint_t * _PDCLIB_bigint_div( _PDCLIB_bigint_t * _PDCLIB_restrict result, _PDCLIB_bigint_t const * _PDCLIB_restrict lhs, _PDCLIB_bigint_t const * _PDCLIB_restrict rhs );

/* Queries */
/* ------- */

/* Returns the log2() of a given bigint, i.e. the offset of the highest
   bit set.
*/
_PDCLIB_LOCAL unsigned _PDCLIB_bigint_log2( _PDCLIB_bigint_t const * bigint );

/* Returns the "inverse" log2() of a given bigint, i.e. the offset of the
   lowest bit set.
*/
_PDCLIB_LOCAL unsigned _PDCLIB_bigint_invlog2( _PDCLIB_bigint_t const * bigint );

/* FP Conversions */
/* -------------- */

/* Split a float into its integral components.
   Returns 1 if value is negative, zero otherwise.
*/
_PDCLIB_LOCAL int _PDCLIB_float_split( float value, unsigned * exponent, _PDCLIB_bigint_t * significand );

/* Split a double into its integral components.
   Returns 1 if value is negative, zero otherwise.
*/
_PDCLIB_LOCAL int _PDCLIB_double_split( double value, unsigned * exponent, _PDCLIB_bigint_t * significand );

/* Split a long double into its integral components.
   Returns 1 if value is negative, zero otherwise.
*/
_PDCLIB_LOCAL int _PDCLIB_long_double_split( long double value, unsigned * exponent, _PDCLIB_bigint_t * significand );

/* -------------------------------------------------------------------------- */
/* Sanity checks                                                              */
/* -------------------------------------------------------------------------- */

/* signed-ness of char */
_PDCLIB_static_assert( _PDCLIB_CHAR_MIN == ((((char) -1) < 0) ? _PDCLIB_SCHAR_MIN : 0), "Compiler disagrees on signed-ness of 'char'." );

/* two's complement */
#if _PDCLIB_TWOS_COMPLEMENT == 1
#if _PDCLIB_CHAR_MIN < 0
_PDCLIB_static_assert( ((char) ~ (char) 0 < 0), "Not two's complement on 'char'." );
#endif
_PDCLIB_static_assert( ((short) ~ (short) 0 < 0), "Not two's complement on 'short'." );
_PDCLIB_static_assert( ((int) ~ (int) 0 < 0), "Not two's complement on 'int'." );
_PDCLIB_static_assert( ((long) ~ (long) 0 < 0), "Not two's complement on 'long'." );
_PDCLIB_static_assert( ((long long) ~ (long long) 0 < 0), "Not two's complement on 'long long'." );
#endif

/* size_t as the result of sizeof */
_PDCLIB_static_assert( sizeof( sizeof( int ) ) == sizeof( _PDCLIB_size_t ), "Compiler disagrees on size_t." );

/* wchar_t as the type of wide character literals */
_PDCLIB_static_assert( sizeof( _PDCLIB_wchar_t ) == sizeof( L'x' ), "Compiler disagrees on wchar_t." );
#ifdef __cplusplus
_PDCLIB_static_assert( sizeof( _PDCLIB_wchar_t ) == sizeof( wchar_t ), "Compiler disagrees on wchar_t (C++)." );
#endif

/* intptr_t/uintptr_t being wide enough to store the value of a pointer */
_PDCLIB_static_assert( sizeof( void * ) == sizeof( _PDCLIB_intptr_t ), "Compiler disagrees on intptr_t." );
_PDCLIB_static_assert( sizeof( void * ) == sizeof( _PDCLIB_uintptr_t ), "Compiler disagrees on uintptr_t." );

/* ptrdiff_t as the result of pointer arithmetic */
_PDCLIB_static_assert( sizeof( &_PDCLIB_digits[1] - &_PDCLIB_digits[0] ) == sizeof( _PDCLIB_ptrdiff_t ), "Compiler disagrees on ptrdiff_t." );

#ifdef __cplusplus
}
#endif

#endif
