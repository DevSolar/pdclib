/* Localization <locale.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_LOCALE_H
#define _PDCLIB_LOCALE_H _PDCLIB_LOCALE_H

#include "pdclib/_PDCLIB_int.h"

#ifndef _PDCLIB_NULL_DEFINED
#define _PDCLIB_NULL_DEFINED _PDCLIB_NULL_DEFINED
#define NULL _PDCLIB_NULL
#endif

/* The structure returned by localeconv().

   The values for *_sep_by_space:
   0 - no space
   1 - if symbol and sign are adjacent, a space seperates them from the value;
       otherwise a space seperates the symbol from the value
   2 - if symbol and sign are adjacent, a space seperates them; otherwise a
       space seperates the sign from the value

   The values for *_sign_posn:
   0 - Parentheses surround value and symbol
   1 - sign precedes value and symbol
   2 - sign succeeds value and symbol
   3 - sign immediately precedes symbol
   4 - sign immediately succeeds symbol
*/
struct lconv
{
    char * decimal_point;      /* decimal point character                     */ /* LC_NUMERIC */
    char * thousands_sep;      /* character for seperating groups of digits   */ /* LC_NUMERIC */
    char * grouping;           /* string indicating the size of digit groups  */ /* LC_NUMERIC */
    char * mon_decimal_point;  /* decimal point for monetary quantities       */ /* LC_MONETARY */
    char * mon_thousands_sep;  /* thousands_sep for monetary quantities       */ /* LC_MONETARY */
    char * mon_grouping;       /* grouping for monetary quantities            */ /* LC_MONETARY */
    char * positive_sign;      /* string indicating nonnegative mty. qty.     */ /* LC_MONETARY */
    char * negative_sign;      /* string indicating negative mty. qty.        */ /* LC_MONETARY */
    char * currency_symbol;    /* local currency symbol (e.g. '$')            */ /* LC_MONETARY */
    char * int_curr_symbol;    /* international currency symbol (e.g. "USD"   */ /* LC_MONETARY */
    char frac_digits;          /* fractional digits in local monetary qty.    */ /* LC_MONETARY */
    char p_cs_precedes;        /* if currency_symbol precedes positive qty.   */ /* LC_MONETARY */
    char n_cs_precedes;        /* if currency_symbol precedes negative qty.   */ /* LC_MONETARY */
    char p_sep_by_space;       /* if it is seperated by space from pos. qty.  */ /* LC_MONETARY */
    char n_sep_by_space;       /* if it is seperated by space from neg. qty.  */ /* LC_MONETARY */
    char p_sign_posn;          /* positioning of positive_sign for mon. qty.  */ /* LC_MONETARY */
    char n_sign_posn;          /* positioning of negative_sign for mon. qty.  */ /* LC_MONETARY */
    char int_frac_digits;      /* Same as above, for international format     */ /* LC_MONETARY */
    char int_p_cs_precedes;    /* Same as above, for international format     */ /* LC_MONETARY */
    char int_n_cs_precedes;    /* Same as above, for international format     */ /* LC_MONETARY */
    char int_p_sep_by_space;   /* Same as above, for international format     */ /* LC_MONETARY */
    char int_n_sep_by_space;   /* Same as above, for international format     */ /* LC_MONETARY */
    char int_p_sign_posn;      /* Same as above, for international format     */ /* LC_MONETARY */
    char int_n_sign_posn;      /* Same as above, for international format     */ /* LC_MONETARY */
};

/* First arguments to setlocale().
   TODO: Beware, values might change before v0.6 is released.
*/
/* Entire locale */
#define LC_ALL      0
/* Collation (strcoll(), strxfrm()) */
#define LC_COLLATE  1
/* Character types (<ctype.h>) */
#define LC_CTYPE    2
/* Monetary formatting (as returned by localeconv) */
#define LC_MONETARY 3
/* Decimal-point character (for printf() / scanf() functions), string
   conversions, nonmonetary formatting as returned by localeconv              */
#define LC_NUMERIC  4
/* Time formats (strftime(), wcsftime()) */
#define LC_TIME     5

/* The category parameter can be any of the LC_* macros to specify if the call
   to setlocale() shall affect the entire locale or only a portion thereof.
   The category locale specifies which locale should be switched to, with "C"
   being the minimal default locale, and "" being the locale-specific native
   environment. A NULL pointer makes setlocale() return the *current* setting.
   Otherwise, returns a pointer to a string associated with the specified
   category for the new locale.
*/
char * setlocale( int category, const char * locale );

/* Returns a struct lconv initialized to the values appropriate for the current
   locale setting.
*/
struct lconv * localeconv( void );

#endif
