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

// ----------------------------------------------------------------------------
// MACROS

#include "__NULL.h"

// ----------------------------------------------------------------------------
// TYPEDEFS

#include "__size_t.h"

// ----------------------------------------------------------------------------
// FUNCTIONS

/** MEMory search for CHaRacter. Searches a memory area for a character.
 *  @param src The memory area.
 *  @param c The character to look for.
 *  @param n Number of characters to search.
 *  @return A pointer to the first occurrence of c in src, or NULL if no match
 *          found.
 *  @see strchr()
 */
void * memchr( const void * s, int c, size_t n );

/** MEMory CoMPare. Compares two memory areas until a difference is found.
 *  This implementation actually returns the difference of the first differing
 *  byte.
 *  This behaviour is implementation-defined and should not be relied upon to
 *  keep your code portable across implementations.
 *  @param src_1 The first memory area.
 *  @param src_2 The second memory area.
 *  @param n Number of bytes to compare.
 *  @return 0, if both areas are identical. If a difference is found, returns a
 *          value < 0 if the byte from memory area src_1 is smaller than that
 *          from src_2, or > 0 if otherwise.
 *  @see strncmp()
 */
int memcmp( const void * s1, const void * s2, size_t n );

/** MEMory CoPY. Copies a source memory area of size n into a destination
 *  memory area.
 *  Should the memory areas pointed to by dest and src overlap, behaviour is
 *  undefined.
 *  @param dest The destination memory area.
 *  @param src The source memory area.
 *  @param n The size of the source memory area.
 *  @return A pointer to the destination memory area.
 *  @see strncpy()
 */
void * memcpy( void * restrict s1, const void * restrict s2, size_t n );

/** MEMory CoPY. Moves a source memory area of size n into a destination
 *  memory area. The memory areas may overlap.
 *  @param dest The destination memory area.
 *  @param src The source memory area.
 *  @param n The size of the source memory area.
 *  @return A pointer to the destination memory area.
 *  @see strncpy()
 */
void * memmove( void * s1, const void * s2, size_t n );

/** MEMory SET. Fills a memory area with a given character.
 *  @param dest The destination memory area.
 *  @param c The character to be written to dest.
 *  @param n The number of characters to be written to dest.
 *  @return A pointer to the destination memory area.
 */
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

/** STRing N CoMPare. Compares two C strings until two differing characters are
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

/** STRing X FRoM. This function transforms a C string into another using a
 *  transformation rule depending on the current locale.
 *  @param dest The destination, where the transformed string should be written
 *         to.
 *  @param src The source string to be transformed.
 *  @param n The maximum number of characters to be written to dest. If this
 *         parameter is zero, 'dest' can be a NULL pointer (to determine the
 *         required space before doing the actual transformation).
 *  @return The length of the string after transformation. If return value > n,
 *          the transformed string has not been written, and the contents of
 *          'dest' are undefined.
 *  @see locale.h
 *  @see strcoll()
 */
size_t strxfrm( char * restrict s1, const char * restrict s2, size_t n );

/** STRing search, return Pointer to BReaK. Searches a C string (including
 *  terminating \0) for any character contained in a second string. If the
 *  first string is not properly terminated, behaviour is undefined.
 *  @param src_1 The string to be seached.
 *  @param src_2 The string containing the characters to be searched.
 *  @return A pointer into src_1 pointing to the first occurrence of any
 *          character from src_2, or NULL if no match found.
 */
char * strpbrk( const char * src_1, const char * src_2 );

/** STRing Reverse search for CHaRacter. Searches a C string (including
 *  terminating \0) for a character. If the string is not properly terminated,
 *  behaviour is undefined.
 *  @param src The source string.
 *  @param c The character to look for.
 *  @return A pointer to the last occurrence of c in src, or NULL if no match
 *          found.
 */
char * strrchr( const char * s, int c );

/** STRing search for STRing. Searches a C string for a substring.
 *  @param src_1 The string to be searched in.
 *  @param src_2 The substring to be searched for.
 *  @return A pointer to the first occurrence of src_2 in src_1, or NULL if no
 *          match found.
 */
char * strstr( const char * src_1, const char * src_2 );

#endif // __STRING_H
