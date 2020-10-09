/* Character handling <ctype.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_CTYPE_H
#define _PDCLIB_CTYPE_H _PDCLIB_CTYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_internal.h"

/* Character classification functions */

/* Note that there is a difference between "whitespace" (any printing, non-
   graph character, like horizontal and vertical tab), and "blank" (the literal
   ' ' space character).

   There will be masking macros for each of these later on, but right now I
   focus on the functions only.
*/

/* Returns isalpha( c ) || isdigit( c ) */
_PDCLIB_PUBLIC int isalnum( int c );

/* Returns isupper( c ) || islower( c ) in the "C" locale.
   In any other locale, also returns true for a locale-specific set of
   alphabetic characters which are neither control characters, digits,
   punctation, or whitespace.
*/
_PDCLIB_PUBLIC int isalpha( int c );

/* Returns true if the character isspace() and used for separating words within
   a line of text. In the "C" locale, only ' ' and '\t' are considered blanks.
*/
_PDCLIB_PUBLIC int isblank( int c );

/* Returns true if the character is a control character. */
_PDCLIB_PUBLIC int iscntrl( int c );

/* Returns true if the character is a decimal digit. Locale-independent. */
_PDCLIB_PUBLIC int isdigit( int c );

/* Returns true for every printing character except space (' ').
   NOTE: This definition differs from that of iswgraph() in <wctype.h>,
         which considers any iswspace() character, not only ' '.
*/
_PDCLIB_PUBLIC int isgraph( int c );

/* Returns true for lowercase letters in the "C" locale.
   In any other locale, also returns true for a locale-specific set of
   characters which are neither control characters, digits, punctation, or
   space (' '). In a locale other than the "C" locale, a character might test
   true for both islower() and isupper().
*/
_PDCLIB_PUBLIC int islower( int c );

/* Returns true for every printing character including space (' '). */
_PDCLIB_PUBLIC int isprint( int c );

/* Returns true for a locale-specific set of punctuation charcters; these
   may not be whitespace or alphanumeric. In the "C" locale, returns true
   for every printing character that is not whitespace or alphanumeric.
*/
_PDCLIB_PUBLIC int ispunct( int c );

/* Returns true for every standard whitespace character (' ', '\f', '\n', '\r',
   '\t', '\v') in the "C" locale. In any other locale, also returns true for a
   locale-specific set of characters for which isalnum() is false.
*/
_PDCLIB_PUBLIC int isspace( int c );

/* Returns true for uppercase letters in the "C" locale.
   In any other locale, also returns true for a locale-specific set of
   characters which are neither control characters, digits, punctation, or
   space (' '). In a locale other than the "C" locale, a character might test
   true for both islower() and isupper().
*/
_PDCLIB_PUBLIC int isupper( int c );

/* Returns true for any hexadecimal-digit character. Locale-independent. */
_PDCLIB_PUBLIC int isxdigit( int c );

/* Character case mapping functions */

/* Converts an uppercase letter to a corresponding lowercase letter. Input that
   is not an uppercase letter remains unchanged.
*/
_PDCLIB_PUBLIC int tolower( int c );

/* Converts a lowercase letter to a corresponding uppercase letter. Input that
   is not a lowercase letter remains unchanged.
*/
_PDCLIB_PUBLIC int toupper( int c );

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_CTYPE_H
#include _PDCLIB_EXTEND_CTYPE_H
#endif

#ifdef __cplusplus
}
#endif

#endif
