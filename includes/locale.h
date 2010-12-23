/* $Id$ */

/* 7.11 Localization <locale.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_LOCALE_H
#define _PDCLIB_LOCALE_H _PDCLIB_LOCALE_H

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
    char * decimal_point;      /* decimal point character                     */
    char * thousands_sep;      /* character for seperating groups of digits   */
    char * grouping;           /* string indicating the size of digit groups  */
    char * mon_decimal_point;  /* decimal point for monetary quantities       */
    char * mon_thousands_sep;  /* thousands_sep for monetary quantities       */
    char * mon_grouping;       /* grouping for monetary quantities            */
    char * positive_sign;      /* string indicating nonnegative mty. qty.     */
    char * negative_sign;      /* string indicating negative mty. qty.        */
    char * currency_symbol;    /* local currency symbol (e.g. '$')            */
    char * int_curr_symbol;    /* international currency symbol (e.g. "USD"   */
    char frac_digits;          /* fractional digits in local monetary qty.    */
    char p_cs_precedes;        /* if currency_symbol precedes positive qty.   */
    char n_cs_precedes;        /* if currency_symbol precedes negative qty.   */
    char p_sep_by_space;       /* if it is seperated by space from pos. qty.  */
    char n_sep_by_space;       /* if it is seperated by space from neg. qty.  */
    char p_sign_posn;          /* positioning of positive_sign for mon. qty.  */
    char n_sign_posn;          /* positioning of negative_sign for mon. qty.  */
    char int_frac_digits;      /* Same as above, for international format     */
    char int_p_cs_precedes;    /* Same as above, for international format     */
    char int_n_cs_precedes;    /* Same as above, for international format     */
    char int_p_sep_by_space;   /* Same as above, for international format     */
    char int_n_sep_by_space;   /* Same as above, for international format     */
    char int_p_sign_posn;      /* Same as above, for international format     */
    char int_n_sign_posn;      /* Same as above, for international format     */
}

#ifndef _PDCLIB_NULL_DEFINED
#define _PDCLIB_NULL_DEFINED _PDCLIB_NULL_DEFINED
#define NULL _PDCLIB_NULL
#endif

/* LC_ALL
   - entire locale
   LC_COLLATE
   - strcoll(), strxfrm()
   LC_CTYPE
   - <ctype.h>
   LC_MONETARY
   - monetary formatting as returned by localeconv
   LC_NUMERIC
   - decimal-point character for printf() / scanf() functions, string
     conversions, and nonmonetary formattign as returned by localeconv
   LC_TIME
   - strftime(), wcsftime()

   First arguments to setlocale().
*/

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

