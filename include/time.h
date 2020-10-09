/* Date and time <time.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_TIME_H
#define _PDCLIB_TIME_H _PDCLIB_TIMEH

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

/* See comments in _PDCLIB_config.h on the semantics of time_t and clock_t. */

typedef _PDCLIB_time_t time_t;
typedef _PDCLIB_clock_t clock_t;

#define CLOCKS_PER_SEC _PDCLIB_CLOCKS_PER_SEC
#define TIME_UTC _PDCLIB_TIME_UTC

/* Implementor's note: If you change this structure, and are using Pthread
   threading support, check auxiliary/pthread/pthread_readout.c for its
   twin. It is imperative that Pthread and PDCLib use identical layouts for
   struct timespec, as they are implicitly cast from one to the other. This
   cannot be checked for in this header (as we may not include host system
   headers here), so the assert()s are in pthread_readout.c (which, in turn,
   cannot include *this* header, which is why this admonishment to keep the
   definitions in sync exists...).
*/
struct timespec
{
    time_t tv_sec;
    long tv_nsec;
};

struct tm
{
    int tm_sec;   /* 0-60 */
    int tm_min;   /* 0-59 */
    int tm_hour;  /* 0-23 */
    int tm_mday;  /* 1-31 */
    int tm_mon;   /* 0-11 */
    int tm_year;  /* years since 1900 */
    int tm_wday;  /* 0-6 */
    int tm_yday;  /* 0-365 */
    int tm_isdst; /* >0 DST, 0 no DST, <0 information unavailable */
};

/* Returns the number of "clocks" in processor time since the invocation
   of the program. Divide by CLOCKS_PER_SEC to get the value in seconds.
   Returns -1 if the value cannot be represented in the return type or is
   not available.
*/
_PDCLIB_PUBLIC clock_t clock( void );

/* Returns the difference between two calendar times in seconds. */
_PDCLIB_PUBLIC double difftime( time_t time1, time_t time0 );

/* Normalizes the values in the broken-down time pointed to by timeptr.
   Returns the calender time specified by the broken-down time.
*/
_PDCLIB_PUBLIC time_t mktime( struct tm * timeptr );

/* Returns the current calender time. If timer is not a NULL pointer, stores
   the current calender time at that address as well.
*/
_PDCLIB_PUBLIC time_t time( time_t * timer );

/* Sets the interval pointed to by ts to the current calender time, based
   on the specified base.
   Returns base, if successful, otherwise zero.
*/
_PDCLIB_PUBLIC int timespec_get( struct timespec * ts, int base );

/* Converts the broken-down time pointed to by timeptr into a string in the
   form "Sun Sep 16 01:03:52 1973\n\0".
*/
_PDCLIB_PUBLIC char * asctime( const struct tm * timeptr );

/* Equivalent to asctime( localtime( timer ) ). */
_PDCLIB_PUBLIC char * ctime( const time_t * timer );

/* Converts the calender time pointed to by timer into a broken-down time
   expressed as UTC.
   Returns a pointer to the broken-down time, or a NULL pointer if it
   cannot be represented.
*/
_PDCLIB_PUBLIC struct tm * gmtime( const time_t * timer );

/* Converts the calender time pointed to by timer into a broken-down time
   expressed as local time.
   Returns a pointer to the broken-down time, or a NULL pointer if if
   cannot be represented.
*/
_PDCLIB_PUBLIC struct tm * localtime( const time_t * timer );

/* Writes the broken-down time pointed to by timeptr into the character
   array pointed to by s. The string pointed to by format controls the
   exact output. No more than maxsize charactrs will be written.
   Returns the number of characters written (excluding the terminating
   null character), or zero on failure.
*/
_PDCLIB_PUBLIC size_t strftime( char * _PDCLIB_restrict s, size_t maxsize, const char * _PDCLIB_restrict format, const struct tm * _PDCLIB_restrict timeptr );

/* Annex K -- Bounds-checking interfaces */

#if ( __STDC_WANT_LIB_EXT1__ + 0 ) != 0

#ifndef _PDCLIB_ERRNO_T_DEFINED
#define _PDCLIB_ERRNO_T_DEFINED _PDCLIB_ERRNO_T_DEFINED
typedef int errno_t;
#endif

#ifndef _PDCLIB_RSIZE_T_DEFINED
#define _PDCLIB_RSIZE_T_DEFINED _PDCLIB_RSIZE_T_DEFINED
typedef _PDCLIB_size_t rsize_t;
#endif

/* Converts the broken-down time pointed to by timeptr into a string in the
   form "Sun Sep 16 01:03:52 1973\n\0", which is stored in buffer s of maxsize.
   Returns zero if the time was successfully converted and stored, non-zero
   otherwise.
   The following conditions will be considered runtime constraint violations:
   - s or timeptr being NULL.
   - maxsize being < 26 or > RSIZE_MAX.
   - the broken-down time pointed to by timeptr not being normalized.
   - the year represented by the broken-down time pointed to by timeptr
     being < 0 or > 9999.
   In case of a constraint violation, the time will not be converted. If
   s is not NULL and maxsize is neither zero nor > RSIZE_MAX, s[0] will be
   set to '\0'.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC errno_t asctime_s( char * s, rsize_t maxsize, const struct tm * timeptr );

/* Equivalent to asctime_s( s, maxsize, localtime( timer ) ). */
_PDCLIB_PUBLIC errno_t ctime_s( char * s, rsize_t maxsize, const time_t * timer );

/* Converts the calender time pointed to by timer into a broken-down time
   expressed as UTC, which gets stored in the result struct.
   Returns a pointer to the broken-down time, or a NULL pointer if if
   cannot be represented or stored.
   The following conditions will be considered runtime constraint violations:
   - timer or result being NULL.
   In case of a constraint violation, the time will not be converted.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC struct tm * gmtime_s( const time_t * _PDCLIB_restrict timer, struct tm * _PDCLIB_restrict result );

/* Converts the calender time pointed to by timer into a broken-down time
   expressed as local time, which gets stored in the result struct.
   Returns a pointer to the broken-down time, or a NULL pointer if if
   cannot be represented or stored.
   The following conditions will be considered runtime constraint violations:
   - timer or result being NULL.
   In case of a constraint violation, the time will not be converted.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC struct tm * localtime_s( const time_t * _PDCLIB_restrict timer, struct tm * _PDCLIB_restrict result );

#endif

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_TIME_H
#include _PDCLIB_EXTEND_TIME_H
#endif

#ifdef __cplusplus
}
#endif

#endif
