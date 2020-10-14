/* Wide character classification and mapping utilities <wctype.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_WCTYPE_H
#define _PDCLIB_WCTYPE_H _PDCLIB_WCTYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_internal.h"

typedef _PDCLIB_wint_t wint_t;
typedef int wctrans_t;
typedef int wctype_t;

#ifndef _PDCLIB_WEOF_DEFINED
#define _PDCLIB_WEOF_DEFINED _PDCLIB_WEOF_DEFINED
#define WEOF (wint_t)-1
#endif

/* Wide character classification functions */

/* Returns iswalpha( wc ) || iswdigit( wc ) */
_PDCLIB_PUBLIC int iswalnum( wint_t wc );

/* Returns true for wide characters for which either isupper( wc ) or
   islower( wc ) is true, as well as a set of locale-specific wide
   characters which are neither control characters, digits, punctuation,
   or whitespace.
*/
_PDCLIB_PUBLIC int iswalpha( wint_t wc );

/* Returns true if the character iswspace() and used for separating words
   within a line of text. In the "C" locale, only L' ' and L'\t' are
   considered blanks.
*/
_PDCLIB_PUBLIC int iswblank( wint_t wc );

/* Returns true if the wide character is a control character. */
_PDCLIB_PUBLIC int iswcntrl( wint_t wc );

/* Returns true if the wide character is a decimal digit. Locale-
   independent. */
_PDCLIB_PUBLIC int iswdigit( wint_t wc );

/* Returns iswprint( wc ) && ! iswspace( wc ).
   NOTE: This definition differs from that of isgraph() in <ctype.h>,
         which considers only ' ', not all isspace() characters.
*/
_PDCLIB_PUBLIC int iswgraph( wint_t wc );

/* Returns true for lowerspace wide characters, as well as a set of
   locale-specific wide characters which are neither control charcters,
   digits, punctuation, or whitespace.
*/
_PDCLIB_PUBLIC int iswlower( wint_t wc );

/* Returns true for every printing wide character. */
_PDCLIB_PUBLIC int iswprint( wint_t wc );

/* Returns true for a locale-specific set of punctuation characters that
   are neither whitespace nor alphanumeric.
*/
_PDCLIB_PUBLIC int iswpunct( wint_t wc );

/* Returns true for a locale-specific set of whitespace characters that
   are neither alphanumeric, graphic, or punctuation.
*/
_PDCLIB_PUBLIC int iswspace( wint_t wc );

/* Returns true for upperspace wide characters, as well as a set of
   locale-specific wide characters which are neither control charcters,
   digits, punctuation, or whitespace.
*/
_PDCLIB_PUBLIC int iswupper( wint_t wc );

/* Returns true if the wide character is a hexadecimal digit. Locale-
   independent. */
_PDCLIB_PUBLIC int iswxdigit( wint_t wc );

/* Extensible wide character classification functions */

/* Returns true if the wide character wc has the property described by
   desc (which was retrieved by a previous call to wctype() without
   changing the LC_CTYPE locale setting between the two calls).
*/
_PDCLIB_PUBLIC int iswctype( wint_t wc, wctype_t desc );

/* Returns a description object for a named character property, to be
   used as parameter to the iswctype() function. Supported property
   names are:
   "alnum" -- alphanumeric, as per iswalnum()
   "alpha" -- alphabetic, as per iswalpha()
   "blank" -- blank, as per iswblank()
   "cntrl" -- control, as per iswcntrl()
   "digit" -- decimal digit, as per iswdigit()
   "graph" -- graphic, as per iswgraph()
   "lower" -- lowercase, as per iswlower()
   "print" -- printing, as per iswprint()
   "punct" -- punctuation, as per iswprint()
   "space" -- whitespace, as per iswspace()
   "upper" -- uppercase, as per iswupper()
   "xdigit" -- hexadecimal digit, as per iswxdigit()
   For unsupported properties, the function returns zero.
*/
_PDCLIB_PUBLIC wctype_t wctype( const char * property );

/* Wide character case mapping utilities */

/* Converts an uppercase letter to a corresponding lowercase letter. Input for
   which no corresponding lowercase letter exists remains unchanged.
*/
_PDCLIB_PUBLIC wint_t towlower( wint_t wc );

/* Converts a lowercase letter to a corresponding uppercase letter. Input for
   which no corresponding uppercase letter exists remains unchanged.
*/
_PDCLIB_PUBLIC wint_t towupper( wint_t wc );

/* Extensible wide character case mapping utilities */

/* Converts the wide character wc according to the transition described
   by desc (which was retrieved by a previous call to wctrans() without
   changing the LC_CTYPE locale setting between the two calls).
*/
_PDCLIB_PUBLIC wint_t towctrans( wint_t wc, wctrans_t desc );

/* Returns a description object for a named character transformation, to
   be used as parameter to the towctrans() function. Supported transformation
   properties are:
   "tolower" -- lowercase mapping, as per towlower()
   "toupper" -- uppercase mapping, as per towupper()
   For unsupported properties, the function returns zero.
*/
_PDCLIB_PUBLIC wctrans_t wctrans( const char * property );

/* Extension hook for downstream projects that want to have non-standard
   extensions to standard headers.
*/
#ifdef _PDCLIB_EXTEND_WCTYPE_H
#include _PDCLIB_EXTEND_WCTYPE_H
#endif

#ifdef __cplusplus
}
#endif

#endif
