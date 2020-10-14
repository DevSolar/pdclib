/* General utilities <stdlib.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_STDLIB_H
#define _PDCLIB_STDLIB_H _PDCLIB_STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_lib_ext1.h"
#include "pdclib/_PDCLIB_internal.h"

#ifndef _PDCLIB_SIZE_T_DEFINED
#define _PDCLIB_SIZE_T_DEFINED _PDCLIB_SIZE_T_DEFINED
typedef _PDCLIB_size_t size_t;
#endif

#ifndef _PDCLIB_NULL_DEFINED
#define _PDCLIB_NULL_DEFINED _PDCLIB_NULL_DEFINED
#define NULL _PDCLIB_NULL
#endif

/* Numeric conversion functions */

/* TODO: atof(), strtof(), strtod(), strtold() */

_PDCLIB_PUBLIC double atof( const char * nptr );
_PDCLIB_PUBLIC double strtod( const char * _PDCLIB_restrict nptr, char ** _PDCLIB_restrict endptr );
_PDCLIB_PUBLIC float strtof( const char * _PDCLIB_restrict nptr, char ** _PDCLIB_restrict endptr );
_PDCLIB_PUBLIC long double strtold( const char * _PDCLIB_restrict nptr, char ** _PDCLIB_restrict endptr );

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
   the return type, the functions return LONG_MIN, LONG_MAX, ULONG_MAX,
   LLONG_MIN, LLONG_MAX, or ULLONG_MAX respectively, depending on the sign of
   the integer representation and the return type, and errno is set to ERANGE.
*/
/* There is strtoimax() and strtoumax() in <inttypes.h> operating on intmax_t /
   uintmax_t, if the long long versions do not suit your needs.
*/
_PDCLIB_PUBLIC long int strtol( const char * _PDCLIB_restrict nptr, char ** _PDCLIB_restrict endptr, int base );
_PDCLIB_PUBLIC long long int strtoll( const char * _PDCLIB_restrict nptr, char ** _PDCLIB_restrict endptr, int base );
_PDCLIB_PUBLIC unsigned long int strtoul( const char * _PDCLIB_restrict nptr, char ** _PDCLIB_restrict endptr, int base );
_PDCLIB_PUBLIC unsigned long long int strtoull( const char * _PDCLIB_restrict nptr, char ** _PDCLIB_restrict endptr, int base );

/* These functions are the equivalent of (int)strtol( nptr, NULL, 10 ),
   strtol( nptr, NULL, 10 ) and strtoll(nptr, NULL, 10 ) respectively, with the
   exception that they do not have to handle overflow situations in any defined
   way.
   (PDCLib does not simply forward these to their strtox() equivalents, but
   provides a simpler atox() function that saves a couple of tests and simply
   continues with the conversion in case of overflow.)
*/
_PDCLIB_PUBLIC int atoi( const char * nptr );
_PDCLIB_PUBLIC long int atol( const char * nptr );
_PDCLIB_PUBLIC long long int atoll( const char * nptr );

/* Pseudo-random sequence generation functions */

extern unsigned long int _PDCLIB_seed;

#define RAND_MAX 32767

/* Returns the next number in a pseudo-random sequence, which is between 0 and
   RAND_MAX.
   (PDCLib uses the implementation suggested by the standard document, which is
   next = next * 1103515245 + 12345; return (unsigned int)(next/65536) % 32768;)
*/
_PDCLIB_PUBLIC int rand( void );

/* Initialize a new pseudo-random sequence with the starting seed. Same seeds
   result in the same pseudo-random sequence. The default seed is 1.
*/
_PDCLIB_PUBLIC void srand( unsigned int seed );

/* Memory management functions */

/* Allocate a chunk of heap memory of given size. If request could not be
   satisfied, return NULL. Otherwise, return a pointer to the allocated
   memory. Memory contents are undefined.
*/
_PDCLIB_PUBLIC void * malloc( size_t size );

/* Allocate a chunk of heap memory that is large enough to hold nmemb elements
   of the given size, and zero-initialize that memory. If request could not be
   satisfied, return NULL. Otherwise, return a pointer to the allocated
   memory.
*/
_PDCLIB_PUBLIC void * calloc( size_t nmemb, size_t size );

/* De-allocate a chunk of heap memory previously allocated using malloc(),
   calloc(), or realloc(), and pointed to by ptr. If ptr does not match a
   pointer previously returned by the mentioned allocation functions, or
   free() has already been called for this ptr, behaviour is undefined.
*/
_PDCLIB_PUBLIC void free( void * ptr );

/* Resize a chunk of memory previously allocated with malloc() and pointed to
   by ptr to the given size (which might be larger or smaller than the original
   size). Returns a pointer to the reallocated memory, or NULL if the request
   could not be satisfied. Note that the resizing might include a memcpy()
   from the original location to a different one, so the return value might or
   might not equal ptr. If size is larger than the original size, the value of
   memory beyond the original size is undefined. If ptr is NULL, realloc()
   behaves like malloc().
*/
_PDCLIB_PUBLIC void * realloc( void * ptr, size_t size );

/* Communication with the environment */

/* These two can be passed to exit() or _Exit() as status values, to signal
   successful and unsuccessful program termination, respectively. EXIT_SUCCESS
   can be replaced by 0. How successful or unsuccessful program termination are
   signaled to the environment, and what happens if exit() or _Exit() are being
   called with a value that is neither of the three, is defined by the hosting
   OS and its glue function.
*/
#define EXIT_SUCCESS _PDCLIB_SUCCESS
#define EXIT_FAILURE _PDCLIB_FAILURE

/* Initiate abnormal process termination, unless programm catches SIGABRT and
   does not return from the signal handler.
   This implementantion flushes all streams, closes all files, and removes any
   temporary files before exiting with EXIT_FAILURE.
   abort() does not return.
*/
_PDCLIB_PUBLIC _PDCLIB_Noreturn void abort( void ) _PDCLIB_NORETURN;

/* Register a function that will be called on quick_exit().
   At least 32 functions can be registered this way, and will be called in
   reverse order of registration (last-in, first-out).
   Returns zero if registration is successfull, nonzero if it failed.
*/
_PDCLIB_PUBLIC int at_quick_exit( void ( *func )( void ) );

/* Register a function that will be called on exit(), or when main() returns.
   At least 32 functions can be registered this way, and will be called in
   reverse order of registration (last-in, first-out).
   Returns zero if registration is successfull, nonzero if it failed.
*/
_PDCLIB_PUBLIC int atexit( void ( *func )( void ) );

/* Normal process termination. Functions registered by atexit() (see above) are
   called, streams flushed, files closed and temporary files removed before the
   program is terminated with the given status. (See comment for EXIT_SUCCESS
   and EXIT_FAILURE above.)
   exit() does not return.
*/
_PDCLIB_PUBLIC _PDCLIB_Noreturn void exit( int status ) _PDCLIB_NORETURN;

/* Normal process termination. Functions registered by at_quick_exit() (see
   above) are called, streams flushed, files closed and temporary files removed
   before the program is terminated with the given status. (See comment for
   EXIT_SUCCESS and EXIT_FAILURE above.)
   quick_exit() does not return.
*/
_PDCLIB_PUBLIC _PDCLIB_Noreturn void quick_exit( int status ) _PDCLIB_NORETURN;

/* Normal process termination. Functions registered by atexit()/at_quick_exit()
   (see above) are NOT CALLED. This implementation DOES flush streams, close
   files and removes temporary files before the program is teminated with the
   given status. (See comment for EXIT_SUCCESS and EXIT_FAILURE above.)
   _Exit() does not return.
*/
_PDCLIB_PUBLIC _PDCLIB_Noreturn void _Exit( int status ) _PDCLIB_NORETURN;

/* Search an environment-provided key-value map for the given key name, and
   return a pointer to the associated value string (or NULL if key name cannot
   be found). The value string pointed to might be overwritten by a subsequent
   call to getenv(). The library never calls getenv() itself.
   Details on the provided keys and how to set / change them are determined by
   the hosting OS and its glue function.
*/
_PDCLIB_PUBLIC char * getenv( const char * name );

/* If string is a NULL pointer, system() returns nonzero if a command processor
   is available, and zero otherwise. If string is not a NULL pointer, it is
   passed to the command processor. If system() returns, it does so with a
   value that is determined by the hosting OS and its glue function.
*/
_PDCLIB_PUBLIC int system( const char * string );

/* Searching and sorting */

/* Do a binary search for a given key in the array with a given base pointer,
   which consists of nmemb elements that are of the given size each. To compare
   the given key with an element from the array, the given function compar is
   called (with key as first parameter and a pointer to the array member as
   second parameter); the function should return a value less than, equal to,
   or greater than 0 if the key is considered to be less than, equal to, or
   greater than the array element, respectively.
   The function returns a pointer to a matching element found, or NULL if no
   match is found.
*/
_PDCLIB_PUBLIC void * bsearch( const void * key, const void * base, size_t nmemb, size_t size, int ( *compar )( const void *, const void * ) );

/* Do a quicksort on an array with a given base pointer, which consists of
   nmemb elements that are of the given size each. To compare two elements from
   the array, the given function compar is called, which should return a value
   less than, equal to, or greater than 0 if the first argument is considered
   to be less than, equal to, or greater than the second argument, respectively.
   If two elements are compared equal, their order in the sorted array is not
   specified.
*/
_PDCLIB_PUBLIC void qsort( void * base, size_t nmemb, size_t size, int ( *compar )( const void *, const void * ) );

/* Integer arithmetic functions */

/* Return the absolute value of the argument. Note that on machines using two-
   complement's notation (most modern CPUs), the largest negative value cannot
   be represented as positive value. In this case, behaviour is unspecified.
*/
_PDCLIB_PUBLIC int abs( int j );
_PDCLIB_PUBLIC long int labs( long int j );
_PDCLIB_PUBLIC long long int llabs( long long int j );

/* These structures each have a member quot and a member rem, of type int (for
   div_t), long int (for ldiv_t) and long long it (for lldiv_t) respectively.
   The order of the members is platform-defined to allow the div() functions
   below to be implemented efficiently.
*/
typedef struct _PDCLIB_div_t     div_t;
typedef struct _PDCLIB_ldiv_t   ldiv_t;
typedef struct _PDCLIB_lldiv_t lldiv_t;

/* Return quotient (quot) and remainder (rem) of an integer division in one of
   the structs above.
*/
_PDCLIB_PUBLIC div_t div( int numer, int denom );
_PDCLIB_PUBLIC ldiv_t ldiv( long int numer, long int denom );
_PDCLIB_PUBLIC lldiv_t lldiv( long long int numer, long long int denom );

/* TODO: Multibyte / wide character conversion functions */

/* TODO: Macro MB_CUR_MAX */

/*
_PDCLIB_PUBLIC int mblen( const char * s, size_t n );
_PDCLIB_PUBLIC int mbtowc( wchar_t * _PDCLIB_restrict pwc, const char * _PDCLIB_restrict s, size_t n );
_PDCLIB_PUBLIC int wctomb( char * s, wchar_t wc );
_PDCLIB_PUBLIC size_t mbstowcs( wchar_t * _PDCLIB_restrict pwcs, const char * _PDCLIB_restrict s, size_t n );
_PDCLIB_PUBLIC size_t wcstombs( char * _PDCLIB_restrict s, const wchar_t * _PDCLIB_restrict pwcs, size_t n );
*/

/* Annex K -- Bounds-checking interfaces */

#if ( __STDC_WANT_LIB_EXT1__ + 0 ) != 0

#ifndef _PDCLIB_ERRNO_T_DEFINED
#define _PDCLIB_ERRNO_T_DEFINED _PDCLIB_ERRNO_T_DEFINED
typedef int errno_t;
#endif

#ifndef _PDCLIB_RSIZE_T_DEFINED
#define _PDCLIB_RSIZE_T_DEFINED _PDCLIB_RSIZE_T_DEFINED
typedef size_t rsize_t;
#endif

/* A function type that can serve as a constraint handler (see below). The
   first parameter is an error message on the constraint violation, the
   second parameter a pointer to an implementation-defined object, the
   third an error code related to the constraint violation.
   If the function calling the constraint handler is defined to return
   errno_t, the third parameter will be identical to the return value of
   that function.
   This implementation sets the second parameter of the constraint handler
   call to NULL.
*/
typedef void ( *constraint_handler_t )( const char * _PDCLIB_restrict msg, void * _PDCLIB_restrict ptr, errno_t error );

/* The currently active constraint violation handler. This implementation
   sets abort_handler_s as the default constraint violation handler.
*/
extern constraint_handler_t _PDCLIB_constraint_handler;

/* Set the given function as the new constraint violation handler. */
_PDCLIB_PUBLIC constraint_handler_t set_constraint_handler_s( constraint_handler_t handler );

/* One of two predefined constraint violation handlers. When called, it will
   print an error message (including the message passed as the first
   parameter to the handler function) and call abort().
*/
_PDCLIB_PUBLIC void abort_handler_s( const char * _PDCLIB_restrict msg, void * _PDCLIB_restrict ptr, errno_t error );

/* One of two predefined constraint violation handlers. Simply returns,
   ignoring the constraint violation.
*/
_PDCLIB_PUBLIC void ignore_handler_s( const char * _PDCLIB_restrict msg, void * _PDCLIB_restrict ptr, errno_t error );

/* Search an environment-provided key-value map for the given key name.
   If the name is found,
   - if len is not NULL, the length of the associated value string is stored
     in that location.
   - if len < maxsize, the value string is copied to the indicated location.
   If the name is not found,
   - if len is not NULL, a zero is stored in that location.
   - if maxsize > 0, value[0] is set to the null character.
   Details on the provided keys and how to set / change them are determined by
   the hosting OS and its glue function.
   The following conditions will be considered runtime constraint violations:
   - value being a NULL pointer.
   - maxsize == 0 or maxsize > RSIZE_MAX.
   In case of a constraint violation, if len is not NULL a zero will be
   stored at that location, and the environment key-value map not searched.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC errno_t getenv_s( size_t * _PDCLIB_restrict len, char * _PDCLIB_restrict value, rsize_t maxsize, const char * _PDCLIB_restrict name );

/* Do a binary search for a given key in the array with a given base pointer,
   which consists of nmemb elements that are of the given size each. To compare
   the given key with an element from the array, the given function compar is
   called (with key as first parameter, a pointer to the array member as
   second parameter, and the context parameter passed to bsearch_s() as third
   parameter); the function should return a value less than, equal to,
   or greater than 0 if the key is considered to be less than, equal to, or
   greater than the array element, respectively.
   The function returns a pointer to a matching element found, or NULL if no
   match is found.
   The following conditions will be considered runtime constraint violations:
   - nmemb or size > RSIZE_MAX.
   - nmemb > 0 and either of key, base, or compar being a null pointer.
   In case of a constraint violation, the array will not be searched.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC void * bsearch_s( const void * key, const void * base, rsize_t nmemb, rsize_t size, int ( *compar )( const void * k, const void * y, void * context ), void * context );

/* Do a quicksort on an array with a given base pointer, which consists of
   nmemb elements that are of the given size each. To compare two elements from
   the array, the given function compar is called, with the first two arguments
   being pointers to the two objects to be compared, and the third argument
   being the context parameter passed to qsort_s. The compar function should
   return a value less than, equal to, or greater than 0 if the first argument
   is considered to be less than, equal to, or greater than the second argument,
   respectively. If two elements are compared equal, their order in the sorted
   array is not specified.
   The following conditions will be considered runtime constraint violations:
   - nmemb or size > RSIZE_MAX.
   - nmemb > 0 and either of base or compar being a null pointer.
   In case of a constraint violation, the array will not be sorted.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC errno_t qsort_s( void * base, rsize_t nmemb, rsize_t size, int ( *compar )( const void * x, const void * y, void * context ), void * context );

/* TODO: Multibyte / wide character functions */

#endif

#ifdef __cplusplus
}
#endif

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_STDLIB_H
#include _PDCLIB_EXTEND_STDLIB_H
#endif

#endif
