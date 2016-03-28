/* strftime( char * restrict, size_t, const char * restrict, const struct tm * restrict )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>

#ifndef REGTEST

size_t strftime( char * _PDCLIB_restrict s, size_t maxsize, const char * _PDCLIB_restrict format, const struct tm * _PDCLIB_restrict timeptr )
{
    /*
    If the total number of resulting characters including the terminating null character is not
    more than maxsize, the strftime function returns the number of characters placed
    into the array pointed to by s not including the terminating null character.
    (i.e., < maxsize)
    */
    size_t rc = 0;

    while ( rc < maxsize )
    {
        if ( *format != '%' )
        {
            if ( ( *s++ = *format++ ) == '\0' )
            {
                return rc;
            }
            else
            {
                ++rc;
            }
        }
        else
        {
            char flag = 0;
            switch ( *++format )
            {
                case 'E':
                case 'O':
                    flag = *format++;
                    break;
                default:
                    /* EMPTY */
                    break;
            }
            switch( *format++ )
            {
                case 'a':
                    /* tm_wday abbreviated */
                    break;
                case 'A':
                    /* tm_wday full */
                    break;
                case 'b':
                case 'h':
                    /* tm_mon abbreviated */
                    break;
                case 'B':
                    /* tm_mon full */
                    break;
                case 'c':
                    /* locale's date / time representation, %a %b %e %T %Y for C locale */
                    /* 'E' for locale's alternative representation */
                    break;
                case 'C':
                    /* tm_year divided by 100, truncated to decimal (00-99) */
                    /* 'E' for base year (period) in locale's alternative representation */
                    break;
                case 'd':
                    /* tm_mday as decimal (01-31) */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 'D':
                    /* %m/%d/%y */
                    break;
                case 'e':
                    /* tm_mday as decimal ( 1-31) */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 'F':
                    /* %Y-%m-%d */
                    break;
                case 'g':
                    /* last 2 digits of the week-based year as decimal (00-99) */
                    break;
                case 'G':
                    /* week-based year as decimal (e.g. 1997) */
                    break;
                case 'H':
                    /* tm_hour as 24h decimal (00-23) */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 'I':
                    /* tm_hour as 12h decimal (01-12) */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 'j':
                    /* tm_yday as decimal (001-366) */
                    break;
                case 'm':
                    /* tm_mon as decimal (01-12) */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 'M':
                    /* tm_min as decimal (00-59) */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 'n':
                    /* newline */
                    break;
                case 'p':
                    /* tm_hour locale's AM/PM designations */
                    break;
                case 'r':
                    /* tm_hour / tm_min / tm_sec as locale's 12-hour clock time, %I:%M:%S %p for C locale */
                    break;
                case 'R':
                    /* %H:%M */
                    break;
                case 'S':
                    /* tm_sec as decimal (00-60) */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 't':
                    /* tabulator */
                    break;
                case 'T':
                    /* %H:%M:%S */
                    break;
                case 'u':
                    /* tm_wday as decimal (1-7) with Monday == 1 */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 'U':
                    /* week number of the year (first Sunday as the first day of week 1) as decimal (00-53) */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 'V':
                    /* week number as decimal (01-53) */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 'w':
                    /* tm_wday as decimal number (0-6) with Sunday == 0 */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 'W':
                    /* week number of the year (first Monday as the first day of week 1) as decimal (00-53) */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 'x':
                    /* locale's date representation, %m/%d/%y for C locale */
                    /* 'E' for locale's alternative representation */
                    break;
                case 'X':
                    /* locale's time representation, %T for C locale */
                    /* 'E' for locale's alternative representation */
                    break;
                case 'y':
                    /* last 2 digits of tm_year as decimal (00-99) */
                    /* 'E' for offset from %EC (year only) in locale's alternative representation */
                    /* 'O' for locale's alternative numeric symbols */
                    break;
                case 'Y':
                    /* tm_year as decimal (e.g. 1997) */
                    /* 'E' for locale's alternative representation */
                    break;
                case 'z':
                    /* tm_isdst / UTC offset in ISO8601 format (e.g. -0430 meaning 4 hours 30 minutes behind Greenwich), or no characters */
                    break;
                case 'Z':
                    /* tm_isdst / locale's time zone name or abbreviation, or no characters */
                    break;
                case '%':
                    /* '%' character */
                    break;
            }
        }
    }

    return 0;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
