/* strftime( char * restrict, size_t, const char * restrict, const struct tm * restrict )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#ifndef REGTEST

/* TODO: Alternative representations / numerals not supported. */

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
                            strcpy( s, day );
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
                            strcpy( s, day );
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
                            strcpy( s, month );
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
                            strcpy( s, month );
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
                        size_t count = strftime( s, maxsize - rc, _PDCLIB_lconv.date_time_format, timeptr );
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
                            div_t period = div( ( timeptr->tm_year / 100 ), 10 );
                            *s++ = '0' + period.quot;
                            *s++ = '0' + period.rem;
                            rc += 2;
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
                            *s++ = '0' + day.quot;
                            *s++ = '0' + day.rem;
                            rc += 2;
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
                        size_t count = strftime( s, maxsize - rc, "%m/%d/%y", timeptr );
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
                            *s++ = ( day.quot > 0 ) ? '0' + day.quot : ' ';
                            *s++ = '0' + day.rem;
                            rc += 2;
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
                        size_t count = strftime( s, maxsize - rc, "%Y-%m-%d", timeptr );
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
                            *s++ = '0' + hour.quot;
                            *s++ = '0' + hour.rem;
                            rc += 2;
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
                            *s++ = '0' + hour.quot;
                            *s++ = '0' + hour.rem;
                            rc += 2;
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
                            *s++ = '0' + yday.quot;
                            *s++ = '0' + yday.rem / 10;
                            *s++ = '0' + yday.rem % 10;
                            rc += 3;
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
                            *s++ = '0' + mon.quot;
                            *s++ = '0' + mon.rem;
                            rc += 2;
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
                            div_t min = div( timeptr->tm_min + 1, 10 );
                            *s++ = '0' + min.quot;
                            *s++ = '0' + min.rem;
                            rc += 2;
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
                        *s++ = '\n';
                        ++rc;
                        break;
                    }
                case 'p':
                    {
                        /* tm_hour locale's AM/PM designations */
                        const char * designation = _PDCLIB_lconv.am_pm[ timeptr->tm_hour > 11 ];
                        size_t len = strlen( designation );
                        if ( rc < ( maxsize - len ) )
                        {
                            strcpy( s, designation );
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
                        size_t count = strftime( s, maxsize - rc, _PDCLIB_lconv.time_format_12h, timeptr );
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
                        size_t count = strftime( s, maxsize - rc, "%H:%M", timeptr );
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
                            div_t sec = div( timeptr->tm_sec + 1, 10 );
                            *s++ = '0' + sec.quot;
                            *s++ = '0' + sec.rem;
                            rc += 2;
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
                        *s++ = '\t';
                        ++rc;
                        break;
                    }
                case 'T':
                    {
                        /* %H:%M:%S */
                        size_t count = strftime( s, maxsize - rc, "%H:%M:%S", timeptr );
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
                        *s++ = ( timeptr->tm_wday == 0 ) ? '7' : '0' + timeptr->tm_wday;
                        ++rc;
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
                        *s++ = '0' + timeptr->tm_wday;
                        ++rc;
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
                        size_t count = strftime( s, maxsize - rc, _PDCLIB_lconv.date_format, timeptr );
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
                        size_t count = strftime( s, maxsize - rc, _PDCLIB_lconv.time_format, timeptr );
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
                            *s++ = '0' + year.quot;
                            *s++ = '0' + year.rem;
                            rc += 2;
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
                            int year = timeptr->tm_year;

                            for ( int i = 3; i >= 0; --i )
                            {
                                div_t digit = div( year, 10 );
                                s[i] = '0' + digit.rem;
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
                        *s++ = '%';
                        ++rc;
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
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
