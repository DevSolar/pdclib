// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Provides functions for determining the locale-dependent type of a character,
// plus locale-aware uppercase / lowercase conversions. (See also locale.h.)
// ----------------------------------------------------------------------------

#ifndef __CTYPE_H
#define __CTYPE_H __CTYPE_H

// ----------------------------------------------------------------------------
// FUNCTIONS

// returns nonzero if c is alphanumeric in the locale.
int isalnum( int c );

// returns nonzero if c is alphabetic character in the locale.
int isalpha( int c );

// returns nonzero if c is a horizontal blank in the locale.
int isblank( int c );

// returns nonzero if c is a control character in the locale.
int iscntrl( int c );

// returns nonzero if c is a digit in the locale.
int isdigit( int c );

// returns nonzero if c is alphanumeric or a punctuation in the locale.
int isgraph( int c );

// returns nonzero if c is a lowercase alphabetic character in the locale.
int islower( int c );

// returns nonzero if c is a printable character ( isgraph(  ) or isblank(  ) ) in
// the locale.
int isprint( int c );

// returns nonzero if c is a punctuation in the locale.
int ispunct( int c );

// returns nonzero if c is a whitespace in the locale.
int isspace( int c );

// returns nonzero if c is an uppercase alphabetical character in the locale.
int isupper( int c );

// returns nonzero if c is a hexedecimal digit in the locale.
int isxdigit( int c );

// returns lowercase equivalent for c in locale.
int tolower( int c );

// returns uppercase equivalent for c in locale.
int toupper( int c );

#endif // __CTYPE_H
