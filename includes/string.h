// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// String handling
// ----------------------------------------------------------------------------

#ifndef __STRING_H
#define __STRING_H __STRING_H

// TODO: Documentation

// ----------------------------------------------------------------------------
// MACROS

#include "__NULL.h"

// ----------------------------------------------------------------------------
// TYPEDEFS

#include "__size_t.h"

// ----------------------------------------------------------------------------
// FUNCTIONS

int memcmp( const void * s1, const void * s2, size_t n );
void * memcpy( void * restrict s1, const void * restrict s2, size_t n );
void * memmove( void * s1, const void * s2, size_t n );
void * memset( void * s, int c, size_t n );

/** STRing conCATenation. Appends a C string to another. If the memory area
 *  pointed to by 'dest' is not large enough to hold both 'dest' and 'src',
 *  behaviour is undefined.
 *  @param dest The destination string.
 *  @param src The source string.
 *  @return A pointer to the destination string.
 *  @see strncat()
 */
char * strcat( char * restrict dest, const char * restrict src );

/** STRing search for CHaRacter. Searches a C string (including terminating \0)
 *  for a character. If the string is not properly terminated, behaviour is
 *  undefined.
 *  @param src The source string.
 *  @param c The character to look for.
 *  @return A pointer to the first occurrence of c in src, or NULL if no match
 *          found.
 */
char * strchr( const char * src, int c );

/** STRing CoMPare. Compares two C strings until two differing characters are
 *  found, or both strings end. If the input strings are not correctly
 *  teminated with \0, behaviour is undefined.
 *  This implementation actually returns the difference of the two characters.
 *  This behaviour is implementation-defined and should not be relied upon to
 *  keep your code portable across implementations.
 *  @param src_1 The first string to be compared.
 *  @param src_2 The second string to be compared.
 *  @return 0, if both strings are identical. If two differing characters are
 *          found, returns a value < 0 if the character from src_1 is smaller
 *          than that from src_2, or > 0 if otherwise.
 *  @see strncmp()
 */
int strcmp( const char * src_1, const char * src_2 );

/** STRing COLLate. Compares two C strings until two differing characters are
 *  found, honoring the current locale.
 *  This implementation actually returns the difference of the two characters.
 *  This behaviour is implementation-defined and should not be relied upon to
 *  keep your code portable across implementations.
 *  @param src_1 The first string to be compared.
 *  @param src_2 The second string to be compared.
 *  @return 0, if both strings are identical. If two differing characters are
 *          found, returns a value < 0 if the character from src_1 is smaller
 *          than that from src_2, or > 0 if otherwise.
 *  @see locale.h
 */
int strcoll( const char * src_1, const char * src_2 );

/** STRing CoPY. Copies a source string (including terminating \0) into a
 *  destination string. If the memory area pointed to by dest is not large
 *  enough to hold src, behaviour is undefined. Should the memory areas pointed
 *  to by dest and src overlap, behavious is undefined.
 *  @param dest The destination string.
 *  @param src The source string.
 *  @return A pointer to the destination string.
 *  @see strncpy()
 */
char * strcpy( char * restrict dest, const char * restrict src );

/** STRing Character SPaN. Compares two C strings, determining the length of
 *  the substring not containing any character from the second string.
 *  @param src_1 The string to be searched.
 *  @param src_2 The string containing the characters to be searched for.
 *  @return The length of the src_1 substring not containing any character
 *          from src_2.
 */
size_t strcspn( const char * src_1, const char * src_2 );

/** STRing ERROR. Returns the error message corresponding to an error code.
 *  @param errorcode The error code.
 *  @return The plaintext error message corresponding to the error code.
 *  @see errno.h
 *  @see fenv.h
 */
char * strerror( int errorcode );

/** STRing LENgth. Returns the number of characters in a C string, not counting
 *  the terminating \0.
 *  @param src The source string.
 *  @return The number of characters in the string, not counting the
 *          terminating \0.
 */
size_t strlen( const char * src );

/** STRing N conCATenate. Appends a C string to another, setting a limit on the
 *  number of characters copied.
 *  @param dest The destination string.
 *  @param src The source string.
 *  @param n The maximum number of characters to be copied.
 *  @return A pointer to the destination string.
 *  @see strcat()
 */
char * strncat( char * restrict dest, const char * restrict src, size_t n );

/** STRing CoMPare. Compares two C strings until two differing characters are
 *  found, both strings end, or a maximum number of characters has been
 *  compared.
 *  This implementation actually returns the difference of the two characters.
 *  This behaviour is implementation-defined and should not be relied upon to
 *  keep your code portable across implementations.
 *  @param src_1 The first string to be compared.
 *  @param src_2 The second string to be compared.
 *  @param n The maximum number of characters to be compared.
 *  @return 0, if both strings are identical. If two differing characters are
 *          found, returns a value < 0 if the character from src_1 is smaller
 *          than that from src_2, or > 0 if otherwise.
 *  @see strcmp()
 */
int strncmp( const char * src_1, const char * src_2, size_t n );

/** STRing CoPY. Copies a source string (including terminating \0) into a
 *  destination string, setting a limit on the number of characters copied.
 *  Should the memory areas pointed to by dest and src overlap, behaviour is
 *  undefined.
 *  @param dest The destination string.
 *  @param src The source string.
 *  @param n The maximum number of characters to be copied.
 *  @return A pointer to the destination string.
 *  @see strcpy()
 */
char * strncpy( char * restrict s1, const char * restrict s2, size_t n );

/** STRing SPaN. Compares two C strings, determining the length of the
 *  substring where both strings are equal.
 *  @param src_1 The first string to be compared.
 *  @param src_2 The second string to be compared.
 *  @return The length of the identical substring.
 */
size_t strspn( const char * s1, const char * s2 );

/** STRing TOKenizer. This (complex and not thread-safe) function allows, by
 *  subsequent calls, to parse a string for tokens. The first parameter to the
 *  function is the C string to be parsed, the second parameter a C string
 *  containing a collection of seperating characters. On first call to the
 *  function, strtok() skips leading seperators, sets the first seperator after
 *  the token to \0, and returns a pointer to the token. Subsequent calls to
 *  strtok() with NULL as the first parameter return pointers to subsequent
 *  tokens, or NULL when all tokens have been parsed.
 *  Beware, this function is not thread-safe.
 *  @param src The string to be parsed (on first call), or NULL (to parse
 *         subsequent tokens).
 *  @param seperators The string containing the seperator(s).
 *  @return The next token parsed, or NULL if parse completed.
 */
char * strtok( char * restrict src, const char * restrict seperators );

size_t strxfrm( char * restrict s1, const char * restrict s2, size_t n );

void * memchr( const void * s, int c, size_t n );
char * strpbrk( const char *s1, const char * s2 );
char * strrchr( const char * s, int c );
char * strstr( const char * s1, const char * s2 );

#endif // __STRING_H
