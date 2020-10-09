/* String handling <string.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_STRING_H
#define _PDCLIB_STRING_H _PDCLIB_STRING_H

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

/* String function conventions */

/*
   In any of the following functions taking a size_t n to specify the length of
   an array or size of a memory region, n may be 0, but the pointer arguments to
   the call shall still be valid unless otherwise stated.
*/

/* Copying functions */

/* Copy a number of n characters from the memory area pointed to by s2 to the
   area pointed to by s1. If the two areas overlap, behaviour is undefined.
   Returns the value of s1.
*/
_PDCLIB_PUBLIC void * memcpy( void * _PDCLIB_restrict s1, const void * _PDCLIB_restrict s2, size_t n );

/* Copy a number of n characters from the memory area pointed to by s2 to the
   area pointed to by s1. The two areas may overlap.
   Returns the value of s1.
*/
_PDCLIB_PUBLIC void * memmove( void * _PDCLIB_restrict s1, const void * _PDCLIB_restrict s2, size_t n );

/* Copy the character array s2 (including terminating '\0' byte) into the
   character array s1.
   Returns the value of s1.
*/
_PDCLIB_PUBLIC char * strcpy( char * _PDCLIB_restrict s1, const char * _PDCLIB_restrict s2 );

/* Copy a maximum of n characters from the character array s2 into the character
   array s1. If s2 is shorter than n characters, '\0' bytes will be appended to
   the copy in s1 until n characters have been written. If s2 is longer than n
   characters, NO terminating '\0' will be written to s1. If the arrays overlap,
   behaviour is undefined.
   Returns the value of s1.
*/
_PDCLIB_PUBLIC char * strncpy( char * _PDCLIB_restrict s1, const char * _PDCLIB_restrict s2, size_t n );

/* Concatenation functions */

/* Append the contents of the character array s2 (including terminating '\0') to
   the character array s1 (first character of s2 overwriting the '\0' of s1). If
   the arrays overlap, behaviour is undefined.
   Returns the value of s1.
*/
_PDCLIB_PUBLIC char * strcat( char * _PDCLIB_restrict s1, const char * _PDCLIB_restrict s2 );

/* Append a maximum of n characters from the character array s2 to the character
   array s1 (first character of s2 overwriting the '\0' of s1). A terminating
   '\0' is ALWAYS appended, even if the full n characters have already been
   written. If the arrays overlap, behaviour is undefined.
   Returns the value of s1.
*/
_PDCLIB_PUBLIC char * strncat( char * _PDCLIB_restrict s1, const char * _PDCLIB_restrict s2, size_t n );

/* Comparison functions */

/* Compare the first n characters of the memory areas pointed to by s1 and s2.
   Returns 0 if s1 == s2, a negative number if s1 < s2, and a positive number if
   s1 > s2.
*/
_PDCLIB_PUBLIC int memcmp( const void * s1, const void * s2, size_t n );

/* Compare the character arrays s1 and s2.
   Returns 0 if s1 == s2, a negative number if s1 < s2, and a positive number if
   s1 > s2.
*/
_PDCLIB_PUBLIC int strcmp( const char * s1, const char * s2 );

/* Compare the character arrays s1 and s2, interpreted as specified by the
   LC_COLLATE category of the current locale.
   Returns 0 if s1 == s2, a negative number if s1 < s2, and a positive number if
   s1 > s2.
   TODO: Currently a dummy wrapper for strcmp() as PDCLib does not yet support
   locales.
*/
_PDCLIB_PUBLIC int strcoll( const char * s1, const char * s2 );

/* Compare no more than the first n characters of the character arrays s1 and
   s2.
   Returns 0 if s1 == s2, a negative number if s1 < s2, and a positive number if
   s1 > s2.
*/
_PDCLIB_PUBLIC int strncmp( const char * s1, const char * s2, size_t n );

/* Transform the character array s2 as appropriate for the LC_COLLATE setting of
   the current locale. If length of resulting string is less than n, store it in
   the character array pointed to by s1. Return the length of the resulting
   string.
*/
_PDCLIB_PUBLIC size_t strxfrm( char * _PDCLIB_restrict s1, const char * _PDCLIB_restrict s2, size_t n );

/* Search functions */

/* Search the first n characters in the memory area pointed to by s for the
   character c (interpreted as unsigned char).
   Returns a pointer to the first instance found, or NULL.
*/
_PDCLIB_PUBLIC void * memchr( const void * s, int c, size_t n );

/* Search the character array s (including terminating '\0') for the character c
   (interpreted as char).
   Returns a pointer to the first instance found, or NULL.
*/
_PDCLIB_PUBLIC char * strchr( const char * s, int c );

/* Determine the length of the initial substring of character array s1 which
   consists only of characters not from the character array s2.
   Returns the length of that substring.
*/
_PDCLIB_PUBLIC size_t strcspn( const char * s1, const char * s2 );

/* Search the character array s1 for any character from the character array s2.
   Returns a pointer to the first occurrence, or NULL.
*/
_PDCLIB_PUBLIC char * strpbrk( const char * s1, const char * s2 );

/* Search the character array s (including terminating '\0') for the character c
   (interpreted as char).
   Returns a pointer to the last instance found, or NULL.
*/
_PDCLIB_PUBLIC char * strrchr( const char * s, int c );

/* Determine the length of the initial substring of character array s1 which
   consists only of characters from the character array s2.
   Returns the length of that substring.
*/
_PDCLIB_PUBLIC size_t strspn( const char * s1, const char * s2 );

/* Search the character array s1 for the substring in character array s2.
   Returns a pointer to that sbstring, or NULL. If s2 is of length zero,
   returns s1.
*/
_PDCLIB_PUBLIC char * strstr( const char * s1, const char * s2 );

/* In a series of subsequent calls, parse a C string into tokens.
   On the first call to strtok(), the first argument is a pointer to the to-be-
   parsed C string. On subsequent calls, the first argument is NULL unless you
   want to start parsing a new string. s2 holds an array of separator characters
   which can differ from call to call. Leading separators are skipped, the first
   trailing separator overwritten with '\0'.
   Returns a pointer to the next token.
   WARNING: This function uses static storage, and as such is not reentrant.
*/
_PDCLIB_PUBLIC char * strtok( char * _PDCLIB_restrict s1, const char * _PDCLIB_restrict s2 );

/* Miscellaneous functions */

/* Write the character c (interpreted as unsigned char) to the first n
   characters of the memory area pointed to by s.
   Returns s.
*/
_PDCLIB_PUBLIC void * memset( void * s, int c, size_t n );

/* Map an error number to a (locale-specific) error message string. Error
   numbers are typically errno values, but any number is mapped to a message.
   TODO: PDCLib does not yet support locales.
*/
_PDCLIB_PUBLIC char * strerror( int errnum );

/* Returns the length of the string s (excluding terminating '\0').
*/
_PDCLIB_PUBLIC size_t strlen( const char * s );

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

/* Copy a number of n characters from the memory area pointed to by s2 to the
   area pointed to by s1 of size s1max.
   Returns zero if successful, non-zero otherwise.
   The following conditions will be considered runtime constraint violations:
   - s1 or s2 being NULL.
   - s1max or n being > RSIZE_MAX.
   - n > s1max (not enough space in s1).
   - copying between overlapping objects.
   In case of a constraint violation, if s1 is not NULL and s1max <= RSIZE_MAX
   then the first s1max characters of s1 will be set to zero.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC errno_t memcpy_s( void * _PDCLIB_restrict s1, rsize_t s1max, const void * _PDCLIB_restrict s2, rsize_t n );

/* Copy a number of n characters from the memory area pointed to by s2 to the
   area pointed to by s1 of size s1max. The two areas may overlap.
   Returns zero if successful, non-zero otherwise.
   The following conditions will be considered runtime constraint violations:
   - s1 or s2 being NULL.
   - s1max or n being > RSIZE_MAX.
   - n > s1max (not enough space in s1).
   In case of a constraint violation, if s1 is not NULL and s1max <= RSIZE_MAX
   then the first s1max characters of s1 will be set to zero.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC errno_t memmove_s( void * _PDCLIB_restrict s1, rsize_t s1max, const void * _PDCLIB_restrict s2, rsize_t n );

/* Copy the character array s2 (including terminating '\0' byte) into the
   character array s1.
   Returns zero if successful, non-zero otherwise.
   The following conditions will be considered runtime constraint violations:
   - s1 or s2 being NULL.
   - s1max being zero or > RSIZE_MAX.
   - s1max not greater than strnlen_s( s2, s1max ) (not enough space in s1).
   - copying between overlapping objects.
   In case of a constraint violation, if s1 is not NULL and s1max <= RSIZE_MAX
   then s1[0] will be set to '\0'.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC errno_t strcpy_s( char * _PDCLIB_restrict s1, rsize_t s1max, const char * _PDCLIB_restrict s2 );

/* Copy a maximum of n characters from the character array s2 into the character
   array s1. If s2 is longer than n, s1[n] will be set to '\0'.
   Returns zero if successful, non-zero otherwise.

   ATTENTION ATTENTION ATTENTION

   This function differs in two fundamental ways from strncpy():
   - remaining space in s1 will NOT be zeroed. Their value is unspecified.
   - s1 WILL be zero-terminated even if there is not enough space to hold
     all n characters from s2.

   THANK YOU FOR YOUR ATTENTION.

   The following conditions will be considered runtime constraint violations:
   - s1 or s2 being NULL.
   - s1max or n being > RSIZE_MAX.
   - s1max being zero.
   - n >= s1max and s1max <= strnlen_s( s2, s1max ) (not enough space in s1).
   - copying between overlapping objects.
   In case of a constraint violation, if s1 is not NULL and s1max is greater
   zero and <= RSIZE_MAX, s1[0] will be set to '\0'.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC errno_t strncpy_s( char * _PDCLIB_restrict s1, rsize_t s1max, const char * _PDCLIB_restrict s2, rsize_t n );

/* Append the contents of the character array s2 (including terminating '\0') to
   the character array s1 (first character of s2 overwriting the '\0' of s1).
   Elements following the terminating null character (if any) take unspecified
   values.
   Returns zero if successful, non-zero otherwise.
   The following conditions will be considered runtime constraint violations:
   - s1 or s2 being NULL.
   - s1max being > RSIZE_MAX.
   - s1max being zero.
   - not enough space in s1 for both s1 and the characters copied from s2.
   - copying between overlapping objects.
   In case of a constraint violation, if s1 is not NULL and s1max is greater
   zero and <= RSIZE_MAX, s1[0] will be set to '\0'.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC errno_t strcat_s( char * _PDCLIB_restrict s1, rsize_t s1max, const char * _PDCLIB_restrict s2 );

/* Append a maximum of n characters from the character array s2 to the
   character array s1 (first character of s2 overwriting the '\0' of s1). A
   terminating '\0' is ALWAYS appended, even if the full n characters have
   already been written.
   Elements following the terminating null character (if any) take unspecified
   values.
   Returns zero if successful, non-zero otherwise.
   The following conditions will be considered runtime constraint violations:
   - s1 or s2 being NULL.
   - s1max or n being > RSIZE_MAX.
   - s1max being zero.
   - not enough space in s1 for both s1 and the characters copied from s2.
   - copying between overlapping objects.
   In case of a constraint violation, if s1 is not NULL and s1max is greater
   zero and <= RSIZE_MAX, s1[0] will be set to '\0'.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC errno_t strncat_s( char * _PDCLIB_restrict s1, rsize_t s1max, const char * _PDCLIB_restrict s2, rsize_t n );

/* In a series of subsequent calls, parse a C string into tokens.
   On the first call to strtok(), the first argument is a pointer to the to-be-
   parsed C string of size *s1max. On subsequent calls, the first argument is
   NULL unless you want to start parsing a new string. s2 holds an array of
   separator characters which can differ from call to call. Leading separators
   are skipped, the first trailing separator overwritten with '\0'.
   Returns a pointer to the next token.
   The following conditions will be considered runtime constraint violations:
   - s1max, s2, or ptr being NULL.
   - s1max or n being > RSIZE_MAX.
   - s1max being zero.
   - not enough space in s1 for both s1 and the characters copied from s2.
   - copying between overlapping objects.
   In case of a constraint violation, if s1 is not NULL and s1max is greater
   zero and <= RSIZE_MAX, s1[0] will be set to '\0'.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC char * strtok_s( char * _PDCLIB_restrict s1, rsize_t * _PDCLIB_restrict s1max, const char * _PDCLIB_restrict s2, char ** _PDCLIB_restrict ptr );

/* Write the character c (interpreted as unsigned char) to the first n
   characters of the memory area pointed to by s of size smax.
   Returns zero if successful, non-zero otherwise.
   The following conditions will be considered runtime constraint violations:
   - s being NULL.
   - smax or n being > RSIZE_MAX.
   - n being > smax.
   In case of a constraint violation, if s is not NULL and smax is <= RSIZE_MAX
   the value of c (interpreted as unsigned char) is written to the first smax
   characters of s.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC errno_t memset_s( void * s, rsize_t smax, int c, rsize_t n );

/* Map an error number to a (locale-specific) error message string. Error
   numbers are typically errno values, but any number is mapped to a message.
   TODO: PDCLib does not yet support locales.
   If the length of the mapped string is < maxsize, the string is copied to s.
   Otherwise, if maxsize is greater than zero, as much of the string as does
   fit is copied, and s[maxsize-1] set to '\0'. If maxsize is greater than 3,
   the partial string is made to end in "...".
   Returns zero if the string was copied successfully in full, non-zero
   otherwise.
   The following conditions will be considered runtime constraint violations:
   - s being NULL.
   - maxsize being zero or > RSIZE_MAX.
   In case of a constraint violation, s is not modified.
   The currently active constraint violation handler function will be called
   (see set_constraint_handler_s()).
*/
_PDCLIB_PUBLIC errno_t strerror_s( char * s, rsize_t maxsize, errno_t errnum );

/* Map an error number to a (locale-specific) error message string, the same
   way as strerror_s() would do. Error numbers are typically errno values,
   but any number is mapped to a message.
   TODO: PDCLib does not yet support locales.
   Returns the length of the mapped string.
*/
_PDCLIB_PUBLIC size_t strerrorlen_s( errno_t errnum );

/* Returns the length of the string s (excluding terminating '\0').
   If there is no null character in the first maxsize characters of s,
   rerturns maxsize. If s is NULL, returns zero.
   At most the first maxsize characters of s shall be accessed by the
   function.
*/
_PDCLIB_PUBLIC size_t strnlen_s( const char * s, size_t maxsize );

#endif

#ifdef __cplusplus
}
#endif

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_STRING_H
#include _PDCLIB_EXTEND_STRING_H
#endif

#endif
