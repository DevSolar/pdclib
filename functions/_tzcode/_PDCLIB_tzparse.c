/* _PDCLIB_tzparse( char const *, struct _PDCLIB_timezone *, bool )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_config.h"
#include "pdclib/_PDCLIB_tzcode.h"

#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SECSPERMIN    60
#define MINSPERHOUR   60
#define HOURSPERDAY   24
#define DAYSPERWEEK    7
#define SECSPERHOUR  (SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY   ((int_fast32_t)SECSPERHOUR * HOURSPERDAY)
#define MONSPERYEAR   12
#define DAYSPERNYEAR 365
#define DAYSPERLYEAR 366

#define isleap(y) (((y) % 4) == 0 && (((y) % 100) != 0 || ((y) % 400) == 0))

/* Name of the time zone data file with the default definitions */
#define TZDEFRULES "posixrules"
#define TZDEFRULESTRING ",M3.2.0,M11.1.0"

#define EPOCH_YEAR 1970
#define YEARSPERREPEAT 400

/* Number of entries added to transitions each time space runs out.
   (Minimum value is 2.)
*/
#define _PDCLIB_EXPAND_BY 2

static const int mon_lengths[2][MONSPERYEAR] =
{
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

static int const year_lengths[ 2 ] = { DAYSPERNYEAR, DAYSPERLYEAR };

enum r_type
{
    INVALID,
    JULIAN_DAY,           /* Jn = Julian day */
    DAY_OF_YEAR,          /* n = day of year */
    MONTH_NTH_DAY_OF_WEEK /* Mm.n.d = month, week, day of week */
};

struct rule
{
    enum r_type  type;  /* type of rule */
    int_fast32_t day;   /* day number of rule */
    int_fast32_t week;  /* week number of rule */
    int_fast32_t month; /* month number of rule */
    int_fast32_t time;  /* transition time of rule */
};

/* Given the address of a string, extract a number within the given min..max
   range.
   Return the extracted number and advance the string to the first character
   after the number. Return INT_FAST32_MIN if there is no address, no string
   at that address, no number, or the number is out of range -- in this case
   the position of the string will be indeterminate.
*/
static int_fast32_t getnum( char const ** str, int min, int max )
{
    char c;
    int num = 0;

    if ( str == NULL || *str == NULL || ! isdigit( (unsigned char)(c = **str) ) )
    {
        return INT_FAST32_MIN;
    }

    do
    {
        num = num * 10 + ( c - '0' );

        if ( num > max )
        {
            return INT_FAST32_MIN;
        }

        c = *(++(*str));
    } while ( isdigit( c ) );

    if ( num < min )
    {
        return INT_FAST32_MIN;
    }

    return num;
}

/* Given the address of a string, extract a time offset in [+-]HH[:MM[:SS]]
   notation.
   Return the extracted offset in seconds and advance the string to the first
   character after the number. Return INT_FAST32_MIN if there is no address,
   no string at that address, or no number -- in this case the position of the
   string will be indeterminate.
*/
static int_fast32_t getoffset( char const ** str )
{
    int_fast32_t seconds = 0;
    int_fast32_t num;
    bool neg = false;

    if ( str == NULL || *str == NULL )
    {
        return INT_FAST32_MIN;
    }

    if ( **str == '-' )
    {
        neg = true;
        ++*str;
    }
    else if ( **str == '+' )
    {
        ++*str;
    }

    if ( ( num = getnum( str, 0, HOURSPERDAY * DAYSPERWEEK - 1 ) ) == INT_FAST32_MIN )
    {
        return INT_FAST32_MIN;
    }

    seconds = num * SECSPERHOUR;

    if ( **str == ':' )
    {
        ++*str;

        if ( ( num = getnum( str, 0, MINSPERHOUR - 1 ) ) == INT_FAST32_MIN )
        {
            return INT_FAST32_MIN;
        }

        seconds += num * SECSPERMIN;

        if ( **str == ':' )
        {
            ++*str;

            if ( ( num = getnum( str, 0, SECSPERMIN ) ) == INT_FAST32_MIN )
            {
                return INT_FAST32_MIN;
            }

            seconds += num;
        }
    }

    if ( neg )
    {
        seconds = -seconds;
    }

    return seconds;
}

/* Given the address of a string, extract a timezone rule in the format
   [JM]nnn[/time].
   Return the extracted rule and advance the string to the first character
   after the number. Return a rule with rule.type == INVALID if there is no
   address, no string at that address, or a malformed timezone rule -- in
   this case the position of the string will be indeterminate.
*/
static struct rule getrule( char const ** str )
{
    /* Default initialization */
    struct rule rule = { INVALID, 0, 0, 0, 2 * SECSPERHOUR };

    if ( **str == 'J' )
    {
        /* Julian day */
        ++*str;

        if ( ( rule.day = getnum( str, 1, DAYSPERNYEAR ) ) == INT_FAST32_MIN )
        {
            return rule;
        }

        rule.type = JULIAN_DAY;
    }
    else if ( **str == 'M' )
    {
        /* Month.week.day */
        ++*str;

        if ( ( rule.month = getnum( str, 1, MONSPERYEAR ) ) == INT_FAST32_MIN )
        {
            return rule;
        }

        if ( *(*str++) != '.' )
        {
            return rule;
        }

        if ( ( rule.week = getnum( str, 1, 5 ) ) == INT_FAST32_MIN )
        {
            return rule;
        }

        if ( *(*str++) != '.' )
        {
            return rule;
        }

        if ( ( rule.day = getnum( str, 0, DAYSPERWEEK - 1 ) ) == INT_FAST32_MIN )
        {
            return rule;
        }

        rule.type = MONTH_NTH_DAY_OF_WEEK;
    }
    else if ( isdigit( **str ) )
    {
        /* Day of year */
        if ( ( rule.day = getnum( str, 0, DAYSPERLYEAR - 1 ) ) == INT_FAST32_MIN )
        {
            return rule;
        }

        rule.type = DAY_OF_YEAR;
    }
    else
    {
        /* Invalid format */
        return rule;
    }

    if ( **str == '/' )
    {
        /* Time specified */
        ++str;
        rule.time = getoffset( str );
    }

    return rule;
}

/* Given the address of a string, scan until a character that is not valid
   in a time zone abbreviation is found, and advance the string to that
   character.
*/
static void skipzname( char const ** str )
{
    char c;

    while ( ( c = **str ) != '\0' &&
            ! isdigit( (unsigned char)c ) &&
            c != ',' &&
            c != '-' &&
            c != '+' )
    {
        ++(*str);
    }
}

/* Given the address of a string, scan until the given delimiter is found,
   and advance the string to that character.
   Return true if the delimiter was found, false otherwise.
*/
static bool skipuntil( char const ** str, int delim )
{
    int c;

    while ( ( c = **str ) != '\0' &&
            c != delim )
    {
        ++(*str);
    }

    return c == delim;
}

/* Given a year, a rule, and the offset from UT at the time that rule takes
   effect, calculate the year-relative time that rule takes effect.
*/
static int_fast32_t transtime( int year, struct rule const * rule, int_fast32_t offset )
{
    int_fast32_t value = 0;
    bool leapyear = isleap( year );

    switch ( rule->type )
    {
        case JULIAN_DAY:
            /* Jn - Julian day. 1 == January 1, 60 == March 1 even in leap
               years. It is impossible to explicitly refer to the occasional
               February 29. So on leap years, we need to add another day's
               worth of seconds for any day from March 1 onwards.
            */
            value = ( rule->day - 1 ) * SECSPERDAY;

            if ( leapyear && rule->day >= 60 )
            {
                value += SECSPERDAY;
            }

            break;

        case DAY_OF_YEAR:
            /* n - day of year.
               Just add SECSPERDAY times the day number to the time of
               January 1, midnight, to get the day.
            */
            value = rule->day * SECSPERDAY;
            break;

        case MONTH_NTH_DAY_OF_WEEK:
        {
            int i, d, m, dow;
            div_t yy;

            /* Mm.n.d -- nth "dth day" of month m.
               Use Zeller's Congruence to get day-of-week of first day of
               month.
            */
            yy = div( ( rule->month <= 2 ) ? ( year - 1 ) : year, 100 );
            m = ( rule->month + 9 ) % 12 + 1;
            dow = ( ( 26 * m - 2 ) / 10 +
                    1 + yy.rem + yy.rem / 4 + yy.quot / 4 - 2 * yy.quot ) % 7;

            if ( dow < 0 )
            {
                dow += DAYSPERWEEK;
            }

            /* "dow" is the day-of-week of the first day of the month. Get
               the day-of-month (zero-origin) of the first "dow" day of the
               month.
            */
            d = rule->day - dow;

            if ( d < 0 )
            {
                d += DAYSPERWEEK;
            }

            for ( i = 1; i < rule->week; ++i )
            {
                if ( d + DAYSPERWEEK >= mon_lengths[ leapyear ][ rule->month - 1 ] )
                {
                    break;
                }

                d += DAYSPERWEEK;
            }

            /* "d" is the day-of-month (zero-origin) of the day we want. */
            value = d * SECSPERDAY;

            for ( i = 0; i < rule->month - 1; ++i )
            {
                value += mon_lengths[ leapyear ][ i ] * SECSPERDAY;
            }

            break;
        }
        case INVALID:
            assert( false );
            break;
    }

    /* "value" is the year-relative time of 00:00:00 UT on the day in
       question. To get the year-relative time of the specified local
       time on that day, add the transition time and the current offset
       from UT.
    */
    return value + rule->time + offset;
}

/* Initialize a given tzdata.type. */
static void init_tzdata_type( struct _PDCLIB_type_t * type, int_fast32_t utoff, bool isdst, int desigidx )
{
    type->utoff    = utoff;
    type->isdst    = isdst;
    type->desigidx = desigidx;
    type->isstd    = false;
    type->isut     = false;
}

/* Add given value to given time_t. Return true if the addition would
   overflow, false if addition is successful.
*/
static bool increment_overflow_time( time_t * t, int_fast32_t j )
{
    if ( ( j < 0 ) ? _PDCLIB_TIME_MIN - j <= *t : *t <= _PDCLIB_TIME_MAX - j )
    {
        return true;
    }

    *t += j;
    return false;
}

/* Given a POSIX section 8-style TZ string, fill in the rule tables of the
   given data structure as appropriate.
*/
bool _PDCLIB_tzparse( char const * name, struct _PDCLIB_timezone * data, bool lastditch )
{
    char const * stdname;
    char const * dstname;
    size_t       stdlen;
    size_t       dstlen;
    size_t       charcnt;
    int_fast32_t stdoffset;
    int_fast32_t dstoffset;
    char *       cp;
    bool         load_ok;

    stdname = name;

    if ( lastditch )
    {
        stdlen = sizeof( _PDCLIB_gmt ) - 1;
        name += stdlen;
        stdoffset = 0;
    }
    else
    {
        if ( *name == '<' )
        {
            /* <+01>, <-05> etc. */
            ++name;
            stdname = name;

            if ( ! skipuntil( &name, '>' ) )
            {
                return false;
            }

            stdlen = name - stdname;
            ++name;
        }
        else
        {
            /* GMT, MET etc. */
            skipzname( &name );
            stdlen = name - stdname;
        }

        if ( ! stdlen )
        {
            return false;
        }

        /* -9, 3:30 etc. */
        if ( ( stdoffset = getoffset( &name ) ) == INT_FAST32_MIN )
        {
            return false;
        }
    }

    charcnt = stdlen + 1;

    /* FIXME: dynamic */
    if ( sizeof( data->charcnt ) < charcnt )
    {
        return false;
    }

    /* Loading default rules */
    load_ok = _PDCLIB_tzload( TZDEFRULES, data, false ) == 0;

    if ( ! load_ok )
    {
        data->leapcnt = 0; /* so, we are off a little */
    }

    if ( *name != '\0' )
    {
        if ( *name == '<' )
        {
            dstname = ++name;

            if ( ! skipuntil( &name, '>' ) )
            {
                return false;
            }

            dstlen = name - dstname;
            ++name;
        }
        else
        {
            dstname = name;
            skipzname( &name );
            dstlen = name - dstname; /* length of DST abbr. */
        }

        if ( ! dstlen )
        {
            return false;
        }

        charcnt += dstlen + 1;

        if ( sizeof( data->charcnt ) < charcnt )
        {
            return false;
        }

        if ( *name != '\0' && *name != ',' && *name != ';' )
        {
            if ( ( dstoffset = getoffset( &name ) ) == INT_FAST32_MIN )
            {
                return false;
            }
        }
        else
        {
            dstoffset = stdoffset - SECSPERHOUR;
        }

        if ( *name == '\0' && ! load_ok )
        {
            name = TZDEFRULESTRING;
        }

        if ( *name == ',' || *name == ';' )
        {
            struct rule start;
            struct rule end;
            int year;
            int yearlim;
            int timecnt;
            time_t janfirst;
            int_fast32_t janoffset = 0;
            int yearbeg;

            ++name;

            start = getrule( &name );

            if ( start.type == INVALID )
            {
                return false;
            }

            if ( *name++ != ',' )
            {
                return false;
            }

            end = getrule( &name );

            if ( end.type == INVALID )
            {
                return false;
            }

            if ( *name != '\0' )
            {
                return false;
            }

            data->typecnt = 2; /* standard time and DST */

            /* Two transitions per year, from EPOCH_YEAR forward */
            init_tzdata_type( &data->type[0], -stdoffset, false, 0 );
            init_tzdata_type( &data->type[1], -dstoffset, true, stdlen + 1 );
            data->defaulttype = 0;
            timecnt = 0;
            janfirst = 0;
            yearbeg = EPOCH_YEAR;

            do
            {
                int_fast32_t yearsecs = year_lengths[ isleap( yearbeg - 1 ) ] * SECSPERDAY;
                --yearbeg;

                if ( increment_overflow_time( &janfirst, -yearsecs ) )
                {
                    janoffset = -yearsecs;
                    break;
                }
            } while ( EPOCH_YEAR - YEARSPERREPEAT / 2 < yearbeg );

            yearlim = yearbeg + YEARSPERREPEAT + 1;

            for ( year = yearbeg; year < yearlim; ++year )
            {
                int_fast32_t starttime = transtime( year, &start, stdoffset );
                int_fast32_t endtime = transtime( year, &end, dstoffset );
                int_fast32_t yearsecs = ( year_lengths[ isleap( year ) ] * SECSPERDAY );
                bool reversed = endtime < starttime;

                if ( reversed )
                {
                    int_fast32_t swap = starttime;
                    starttime = endtime;
                    endtime = swap;
                }

                if ( reversed || ( starttime < endtime && ( endtime - starttime < ( yearsecs + ( stdoffset - dstoffset ) ) ) ) )
                {
                    if ( ( data->timecap - data->timecnt ) < 2 )
                    {
                        /* Not enough storage; expand */
                        void * new = realloc( data->transition, data->timecap + _PDCLIB_EXPAND_BY );

                        if ( new == NULL )
                        {
                            break;
                        }

                        data->transition = (struct _PDCLIB_transition_t *)new;
                        data->timecap += _PDCLIB_EXPAND_BY;
                    }

                    data->transition[ timecnt ].time = janfirst;

                    if ( ! increment_overflow_time( &data->transition[ timecnt ].time, janoffset + starttime ) )
                    {
                        data->transition[ timecnt++ ].typeidx = ! reversed;
                    }

                    data->transition[ timecnt ].time = janfirst;

                    if ( ! increment_overflow_time( &data->transition[ timecnt ].time, janoffset + endtime ) )
                    {
                        data->transition[ timecnt++ ].typeidx = reversed;
                        yearlim = year + YEARSPERREPEAT + 1;
                    }
                }

                if ( increment_overflow_time( &janfirst, janoffset + yearsecs ) )
                {
                    break;
                }

                janoffset = 0;
            }

            data->timecnt = timecnt;

            if ( ! timecnt )
            {
                data->type[ 0 ] = data->type[ 1 ];
                data->typecnt = 1; /* Perpetual DST */
            }
            else if ( YEARSPERREPEAT < year - yearbeg )
            {
                data->goback = data->goahead = true;
            }
        }
        else
        {
            int_fast32_t theirstdoffset = 0;
            int_fast32_t theirdstoffset = 0;
            int_fast32_t theiroffset;
            bool isdst = false;
            int i;
            int j;

            if ( *name != '\0' )
            {
                return false;
            }

            /* Initial values of theirstdoffset and theirdstoffset */
            for ( i = 0; i < data->timecnt; ++i )
            {
                j = data->transition[ i ].typeidx;

                if ( ! data->type[ j ].isdst )
                {
                    theirstdoffset = data->type[j].utoff;
                    break;
                }
            }

            for ( i = 0; i < data->timecnt; ++i )
            {
                j = data->transition[ i ].typeidx;

                if ( data->type[ j ].isdst )
                {
                    theirdstoffset = data->type[ j ].utoff;
                    break;
                }
            }

            /* Initially we assume to be in standard time */
            theiroffset = theirstdoffset;

            /* Now juggle transition times and types tracking offsets */
            for ( i = 0; i < data->timecnt; ++i )
            {
                j = data->transition[ i ].typeidx;
                data->transition[ i ].typeidx = data->type[ j ].isdst;

                if ( data->type[ j ].isut )
                {
                    /* TODO -- Empty? */
                    /* No adjustment to transition time */
                }
                else
                {
                    /* If daylight saving time is in effect, and the
                       transition time was not specified as standard time,
                       add the daylight saving time offset to the transition
                       time; otherwise, add the standard time offset to the
                       transition time.
                    */
                    /* Transitions from DST to DDST will effectively
                       disappear since POSIX provides for only one DST offset.
                    */
                    if ( isdst && ! data->type[ j ].isstd )
                    {
                        data->transition[ i ].time += dstoffset - theirdstoffset;
                    }
                    else
                    {
                        data->transition[ i ].time += stdoffset - theirstdoffset;
                    }
                }

                theiroffset = -data->type[ j ].utoff;

                if ( data->type[ j ].isdst )
                {
                    theirdstoffset = theiroffset;
                }
                else
                {
                    theirstdoffset = theiroffset;
                }
            }

            /* Finally, fill in type */
            init_tzdata_type( &data->type[ 0 ], -stdoffset, false, 0 );
            init_tzdata_type( &data->type[ 1 ], -dstoffset, true, stdlen + 1 );
            data->typecnt = 2;
            data->defaulttype = 0;
        }
    }
    else
    {
        dstlen = 0;
        data->typecnt = 1; /* only standard time */
        data->timecnt = 0;
        init_tzdata_type( &data->type[ 0 ], -stdoffset, false, 0 );
        data->defaulttype = 0;
    }

    data->charcnt = charcnt;
    cp = data->designations;
    memcpy( cp, stdname, stdlen );
    cp += stdlen;
    *cp++ = '\0';

    if ( dstlen != 0 )
    {
        memcpy( cp, dstname, dstlen );
        *(cp + dstlen ) = '\0';
    }

    return true;
}

#endif

#ifdef TEST

#include <inttypes.h>

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    char test[100] = "123_";
    char const * str;
    struct rule rule = { JULIAN_DAY, 0, 0, 0, 0 };

    /* getnum */
    str = test;
    TESTCASE( getnum( &str, 0, 123 ) == 123 );
    TESTCASE( str == test + 3 );
    str = test;
    TESTCASE( getnum( &str, 0, 122 ) == INT_FAST32_MIN );
    str = test;
    TESTCASE( getnum( &str, 123, 200 ) == 123 );
    TESTCASE( str == test + 3 );
    str = test;
    TESTCASE( getnum( &str, 124, 200 ) == INT_FAST32_MIN );

    /* getoffset */
    strcpy( test, "00:00:60" );
    str = test;
    TESTCASE( getoffset( &str ) == 60 );
    TESTCASE( str == ( test + 8 ) );
    strcpy( test, "00:01:01" );
    str = test;
    TESTCASE( getoffset( &str ) == 61 );
    TESTCASE( str == ( test + 8 ) );
    strcpy( test, "01:01:01" );
    str = test;
    TESTCASE( getoffset( &str ) == 3661 );
    TESTCASE( str == ( test + 8 ) );
    strcpy( test, "-00:00:01" );
    str = test;
    TESTCASE( getoffset( &str ) == -1 );
    TESTCASE( str == ( test + 9 ) );
    strcpy( test, "-00:01:01" );
    str = test;
    TESTCASE( getoffset( &str ) == -61 );
    TESTCASE( str == ( test + 9 ) );
    strcpy( test, "-01:01:01" );
    str = test;
    TESTCASE( getoffset( &str ) == -3661 );
    TESTCASE( str == ( test + 9 ) );
    strcpy( test, "00:00:61" );
    str = test;
    TESTCASE( getoffset( &str ) == INT_FAST32_MIN );
    strcpy( test, "00:59:01" );
    str = test;
    TESTCASE( getoffset( &str ) == 3541 );
    TESTCASE( str == ( test + 8 ) );
    strcpy( test, "00:60:01" );
    str = test;
    TESTCASE( getoffset( &str ) == INT_FAST32_MIN );
    strcpy( test, "167:00:00" );
    str = test;
    TESTCASE( getoffset( &str ) == 601200 );
    TESTCASE( str == ( test + 9 ) );
    strcpy( test, "168:00:00" );
    str = test;
    TESTCASE( getoffset( &str ) == INT_FAST32_MIN );

    /* skipzname */
    strcpy( test, "MET1MEST,MET" );
    str = test;
    skipzname( &str );
    TESTCASE( str == test + 3 );
    ++str;
    skipzname( &str );
    TESTCASE( str == test + 8 );
    ++str;
    skipzname( &str );
    TESTCASE( str == test + 12 );

    /* transtime */
    /* February 28 -- same for non-leap and leap year */
    rule.day = 59;
    TESTCASE( transtime( 2019, &rule, 0 ) == 5011200 );
    TESTCASE( transtime( 2020, &rule, 0 ) == 5011200 );
    /* March 1 -- leap year adds two day's worth in seconds */
    rule.day = 60;
    TESTCASE( transtime( 2019, &rule, 0 ) == 5097600 );
    TESTCASE( transtime( 2020, &rule, 0 ) == 5184000 );
    /* March 2 */
    rule.day = 61;
    TESTCASE( transtime( 2019, &rule, 0 ) == 5184000 );
    TESTCASE( transtime( 2020, &rule, 0 ) == 5270400 );
    /* Mm.n.d */
    /* Only a couple of random samples */
    rule.type = MONTH_NTH_DAY_OF_WEEK;
    rule.month = 3; rule.week = 3; rule.day = 3;
    TESTCASE( transtime( 2019, &rule, 0 ) == 6739200 );
    TESTCASE( transtime( 2020, &rule, 0 ) == 6652800 );
    rule.month = 9; rule.week = 2; rule.day = 4;
    TESTCASE( transtime( 2019, &rule, 0 ) == 21945600 );
    TESTCASE( transtime( 2020, &rule, 0 ) == 21859200 );
    rule.month = 1; rule.week = 1; rule.day = 0;
    TESTCASE( transtime( 2019, &rule, 0 ) == 432000 );
    TESTCASE( transtime( 2020, &rule, 0 ) == 345600 );
    rule.month = 12; rule.week = 5; rule.day = 7;
    TESTCASE( transtime( 2019, &rule, 0 ) == 31276800 );
    TESTCASE( transtime( 2020, &rule, 0 ) == 31190400 );
#endif

    return TEST_RESULTS;
}

#endif
