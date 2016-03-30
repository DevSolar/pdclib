/* strftime( char * restrict, size_t, const char * restrict, const struct tm * restrict )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#ifndef REGTEST

/* TODO: Alternative representations / numerals not supported. Multibyte support missing. */

/* This implementation's code is highly repetitive, but I did not really
   care for putting it into a number of macros / helper functions.
*/

size_t strftime( char * _PDCLIB_restrict s, size_t maxsize, const char * _PDCLIB_restrict format, const struct tm * _PDCLIB_restrict timeptr )
{
    size_t rc = 0;

    while ( rc < maxsize )
    {
        if ( *format != '%' )
        {
            if ( ( s[rc] = *format++ ) == '\0' )
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
            /* char flag = 0; */
            switch ( *++format )
            {
                case 'E':
                case 'O':
                    /* flag = *format++; */
                    break;
                default:
                    /* EMPTY */
                    break;
            }
            switch( *format++ )
            {
                case 'a':
                    {
                        /* tm_wday abbreviated */
                        const char * day = _PDCLIB_lconv.day_name_abbr[ timeptr->tm_wday ];
                        size_t len = strlen( day );
                        if ( rc < ( maxsize - len ) )
                        {
                            strcpy( s + rc, day );
                            rc += len;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'A':
                    {
                        /* tm_wday full */
                        const char * day = _PDCLIB_lconv.day_name_full[ timeptr->tm_wday ];
                        size_t len = strlen( day );
                        if ( rc < ( maxsize - len ) )
                        {
                            strcpy( s + rc, day );
                            rc += len;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'b':
                case 'h':
                    {
                        /* tm_mon abbreviated */
                        const char * month = _PDCLIB_lconv.month_name_abbr[ timeptr->tm_mon ];
                        size_t len = strlen( month );
                        if ( rc < ( maxsize - len ) )
                        {
                            strcpy( s + rc, month );
                            rc += len;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'B':
                    {
                        /* tm_mon full */
                        const char * month = _PDCLIB_lconv.month_name_full[ timeptr->tm_mon ];
                        size_t len = strlen( month );
                        if ( rc < ( maxsize - len ) )
                        {
                            strcpy( s + rc, month );
                            rc += len;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'c':
                    {
                        /* locale's date / time representation, %a %b %e %T %Y for C locale */
                        /* 'E' for locale's alternative representation */
                        size_t count = strftime( s + rc, maxsize - rc, _PDCLIB_lconv.date_time_format, timeptr );
                        if ( count == 0 )
                        {
                            return 0;
                        }
                        else
                        {
                            rc += count;
                        }
                        break;
                    }
                case 'C':
                    {
                        /* tm_year divided by 100, truncated to decimal (00-99) */
                        /* 'E' for base year (period) in locale's alternative representation */
                        if ( rc < ( maxsize - 2 ) )
                        {
                            div_t period = div( ( ( timeptr->tm_year + 1900 ) / 100 ), 10 );
                            s[rc++] = '0' + period.quot;
                            s[rc++] = '0' + period.rem;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'd':
                    {
                        /* tm_mday as decimal (01-31) */
                        /* 'O' for locale's alternative numeric symbols */
                        if ( rc < ( maxsize - 2 ) )
                        {
                            div_t day = div( timeptr->tm_mday, 10 );
                            s[rc++] = '0' + day.quot;
                            s[rc++] = '0' + day.rem;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'D':
                    {
                        /* %m/%d/%y */
                        size_t count = strftime( s + rc, maxsize - rc, "%m/%d/%y", timeptr );
                        if ( count == 0 )
                        {
                            return 0;
                        }
                        else
                        {
                            rc += count;
                        }
                        break;
                    }
                case 'e':
                    {
                        /* tm_mday as decimal ( 1-31) */
                        /* 'O' for locale's alternative numeric symbols */
                        if ( rc < ( maxsize - 2 ) )
                        {
                            div_t day = div( timeptr->tm_mday, 10 );
                            s[rc++] = ( day.quot > 0 ) ? '0' + day.quot : ' ';
                            s[rc++] = '0' + day.rem;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'F':
                    {
                        /* %Y-%m-%d */
                        size_t count = strftime( s + rc, maxsize - rc, "%Y-%m-%d", timeptr );
                        if ( count == 0 )
                        {
                            return 0;
                        }
                        else
                        {
                            rc += count;
                        }
                        break;
                    }
                case 'g':
                    {
                        /* last 2 digits of the week-based year as decimal (00-99) */
                        /* TODO: 'g' */
                        break;
                    }
                case 'G':
                    {
                        /* week-based year as decimal (e.g. 1997) */
                        /* TODO: 'G' */
                        break;
                    }
                case 'H':
                    {
                        /* tm_hour as 24h decimal (00-23) */
                        /* 'O' for locale's alternative numeric symbols */
                        if ( rc < ( maxsize - 2 ) )
                        {
                            div_t hour = div( timeptr->tm_hour, 10 );
                            s[rc++] = '0' + hour.quot;
                            s[rc++] = '0' + hour.rem;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'I':
                    {
                        /* tm_hour as 12h decimal (01-12) */
                        /* 'O' for locale's alternative numeric symbols */
                        if ( rc < ( maxsize - 2 ) )
                        {
                            div_t hour = div( ( timeptr->tm_hour + 1 ) % 12, 10 );
                            s[rc++] = '0' + hour.quot;
                            s[rc++] = '0' + hour.rem;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'j':
                    {
                        /* tm_yday as decimal (001-366) */
                        if ( rc < ( maxsize - 3 ) )
                        {
                            div_t yday = div( timeptr->tm_yday, 100 );
                            s[rc++] = '0' + yday.quot;
                            s[rc++] = '0' + yday.rem / 10;
                            s[rc++] = '0' + yday.rem % 10;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'm':
                    {
                        /* tm_mon as decimal (01-12) */
                        /* 'O' for locale's alternative numeric symbols */
                        if ( rc < ( maxsize - 2 ) )
                        {
                            div_t mon = div( timeptr->tm_mon + 1, 10 );
                            s[rc++] = '0' + mon.quot;
                            s[rc++] = '0' + mon.rem;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'M':
                    {
                        /* tm_min as decimal (00-59) */
                        /* 'O' for locale's alternative numeric symbols */
                        if ( rc < ( maxsize - 2 ) )
                        {
                            div_t min = div( timeptr->tm_min, 10 );
                            s[rc++] = '0' + min.quot;
                            s[rc++] = '0' + min.rem;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'n':
                    {
                        /* newline */
                        s[rc++] = '\n';
                        break;
                    }
                case 'p':
                    {
                        /* tm_hour locale's AM/PM designations */
                        const char * designation = _PDCLIB_lconv.am_pm[ timeptr->tm_hour > 11 ];
                        size_t len = strlen( designation );
                        if ( rc < ( maxsize - len ) )
                        {
                            strcpy( s + rc, designation );
                            rc += len;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'r':
                    {
                        /* tm_hour / tm_min / tm_sec as locale's 12-hour clock time, %I:%M:%S %p for C locale */
                        size_t count = strftime( s + rc, maxsize - rc, _PDCLIB_lconv.time_format_12h, timeptr );
                        if ( count == 0 )
                        {
                            return 0;
                        }
                        else
                        {
                            rc += count;
                        }
                        break;
                    }
                case 'R':
                    {
                        /* %H:%M */
                        size_t count = strftime( s + rc, maxsize - rc, "%H:%M", timeptr );
                        if ( count == 0 )
                        {
                            return 0;
                        }
                        else
                        {
                            rc += count;
                        }
                        break;
                    }
                case 'S':
                    {
                        /* tm_sec as decimal (00-60) */
                        /* 'O' for locale's alternative numeric symbols */
                        if ( rc < ( maxsize - 2 ) )
                        {
                            div_t sec = div( timeptr->tm_sec, 10 );
                            s[rc++] = '0' + sec.quot;
                            s[rc++] = '0' + sec.rem;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 't':
                    {
                        /* tabulator */
                        s[rc++] = '\t';
                        break;
                    }
                case 'T':
                    {
                        /* %H:%M:%S */
                        size_t count = strftime( s + rc, maxsize - rc, "%H:%M:%S", timeptr );
                        if ( count == 0 )
                        {
                            return 0;
                        }
                        else
                        {
                            rc += count;
                        }
                        break;
                    }
                case 'u':
                    {
                        /* tm_wday as decimal (1-7) with Monday == 1 */
                        /* 'O' for locale's alternative numeric symbols */
                        s[rc++] = ( timeptr->tm_wday == 0 ) ? '7' : '0' + timeptr->tm_wday;
                        break;
                    }
                case 'U':
                    {
                        /* week number of the year (first Sunday as the first day of week 1) as decimal (00-53) */
                        /* 'O' for locale's alternative numeric symbols */
                        /* TODO: 'U' */
                        break;
                    }
                case 'V':
                    {
                        /* week number as decimal (01-53) */
                        /* 'O' for locale's alternative numeric symbols */
                        /* TODO: 'V' */
                        break;
                    }
                case 'w':
                    {
                        /* tm_wday as decimal number (0-6) with Sunday == 0 */
                        /* 'O' for locale's alternative numeric symbols */
                        s[rc++] = '0' + timeptr->tm_wday;
                        break;
                    }
                case 'W':
                    {
                        /* week number of the year (first Monday as the first day of week 1) as decimal (00-53) */
                        /* 'O' for locale's alternative numeric symbols */
                        /* TODO: 'W' */
                        break;
                    }
                case 'x':
                    {
                        /* locale's date representation, %m/%d/%y for C locale */
                        /* 'E' for locale's alternative representation */
                        size_t count = strftime( s + rc, maxsize - rc, _PDCLIB_lconv.date_format, timeptr );
                        if ( count == 0 )
                        {
                            return 0;
                        }
                        else
                        {
                            rc += count;
                        }
                        break;
                    }
                case 'X':
                    {
                        /* locale's time representation, %T for C locale */
                        /* 'E' for locale's alternative representation */
                        size_t count = strftime( s + rc, maxsize - rc, _PDCLIB_lconv.time_format, timeptr );
                        if ( count == 0 )
                        {
                            return 0;
                        }
                        else
                        {
                            rc += count;
                        }
                        break;
                    }
                case 'y':
                    {
                        /* last 2 digits of tm_year as decimal (00-99) */
                        /* 'E' for offset from %EC (year only) in locale's alternative representation */
                        /* 'O' for locale's alternative numeric symbols */
                        if ( rc < ( maxsize - 2 ) )
                        {
                            div_t year = div( ( timeptr->tm_year % 100 ), 10 );
                            s[rc++] = '0' + year.quot;
                            s[rc++] = '0' + year.rem;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'Y':
                    {
                        /* tm_year as decimal (e.g. 1997) */
                        /* 'E' for locale's alternative representation */
                        if ( rc < ( maxsize - 4 ) )
                        {
                            int year = timeptr->tm_year + 1900;

                            for ( int i = 3; i >= 0; --i )
                            {
                                div_t digit = div( year, 10 );
                                s[ rc + i ] = '0' + digit.rem;
                                year = digit.quot;
                            }

                            rc += 4;
                        }
                        else
                        {
                            return 0;
                        }
                        break;
                    }
                case 'z':
                    {
                        /* tm_isdst / UTC offset in ISO8601 format (e.g. -0430 meaning 4 hours 30 minutes behind Greenwich), or no characters */
                        /* TODO: 'z' */
                        break;
                    }
                case 'Z':
                    {
                        /* tm_isdst / locale's time zone name or abbreviation, or no characters */
                        /* TODO: 'Z' */
                        break;
                    }
                case '%':
                    {
                        /* '%' character */
                        s[rc++] = '%';
                        break;
                    }
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
#ifndef REGTEST
    /* Replace with a call to mktime() once that is implemented. */
    struct tm timeptr = { 59, 30, 12, 1, 9, 72, 0, 274, -1 };
    char buffer[100];
    TESTCASE( strftime( buffer, 100, "%a ", &timeptr ) == 4 );
    TESTCASE( strcmp( buffer, "Sun " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%A ", &timeptr ) == 7 );
    TESTCASE( strcmp( buffer, "Sunday " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%b ", &timeptr ) == 4 );
    TESTCASE( strcmp( buffer, "Oct " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%h ", &timeptr ) == 4 );
    TESTCASE( strcmp( buffer, "Oct " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%B ", &timeptr ) == 8 );
    TESTCASE( strcmp( buffer, "October " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%c ", &timeptr ) == 25 );
    TESTCASE( strcmp( buffer, "Sun Oct  1 12:30:59 1972 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%C ", &timeptr ) == 3 );
    TESTCASE( strcmp( buffer, "19 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%d ", &timeptr ) == 3 );
    TESTCASE( strcmp( buffer, "01 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%D ", &timeptr ) == 9 );
    TESTCASE( strcmp( buffer, "10/01/72 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%e ", &timeptr ) == 3 );
    TESTCASE( strcmp( buffer, " 1 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%F ", &timeptr ) == 11 );
    TESTCASE( strcmp( buffer, "1972-10-01 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%H ", &timeptr ) == 3 );
    TESTCASE( strcmp( buffer, "12 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%I ", &timeptr ) == 3 );
    TESTCASE( strcmp( buffer, "01 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%j ", &timeptr ) == 4 );
    TESTCASE( strcmp( buffer, "274 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%m ", &timeptr ) == 3 );
    TESTCASE( strcmp( buffer, "10 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%M ", &timeptr ) == 3 );
    TESTCASE( strcmp( buffer, "30 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%p ", &timeptr ) == 3 );
    TESTCASE( strcmp( buffer, "PM " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%r ", &timeptr ) == 12 );
    TESTCASE( strcmp( buffer, "01:30:59 PM " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%R ", &timeptr ) == 6 );
    TESTCASE( strcmp( buffer, "12:30 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%S ", &timeptr ) == 3 );
    TESTCASE( strcmp( buffer, "59 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%T ", &timeptr ) == 9 );
    TESTCASE( strcmp( buffer, "12:30:59 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%u ", &timeptr ) == 2 );
    TESTCASE( strcmp( buffer, "7 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%w ", &timeptr ) == 2 );
    TESTCASE( strcmp( buffer, "0 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%x ", &timeptr ) == 9 );
    TESTCASE( strcmp( buffer, "10/01/72 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%X ", &timeptr ) == 9 );
    TESTCASE( strcmp( buffer, "12:30:59 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%y ", &timeptr ) == 3 );
    TESTCASE( strcmp( buffer, "72 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%Y ", &timeptr ) == 5 );
    TESTCASE( strcmp( buffer, "1972 " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%% ", &timeptr ) == 2 );
    TESTCASE( strcmp( buffer, "% " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%n ", &timeptr ) == 2 );
    TESTCASE( strcmp( buffer, "\n " ) == 0 );
    TESTCASE( strftime( buffer, 100, "%t ", &timeptr ) == 2 );
    TESTCASE( strcmp( buffer, "\t " ) == 0 );
#endif
    return TEST_RESULTS;
}

#endif
