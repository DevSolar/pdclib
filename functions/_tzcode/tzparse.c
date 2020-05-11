/* tzparse( char const *, struct state *, bool )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include "_PDCLIB_tzcode.h"

#include <ctype.h>

#define isleap(y) (((y) % 4) == 0 && (((y) % 100) != 0 || ((y) % 400) == 0))

#define SECSPERMIN    60
#define MINSPERHOUR   60
#define HOURSPERDAY   24
#define DAYSPERWEEK    7
#define SECSPERHOUR  (SECSPERMIN * MINSPERHOUR)
#define MONSPERYEAR   12
#define DAYSPERNYEAR 365
#define DAYSPERLYEAR 366

enum r_type
{
    INVALID,
    JULIAN_DAY,            /* Jn = Julian day */
    DAY_OF_YEAR,           /* n = day of year */
    MONTH_WEEK_DAY_OF_WEEK /* Mm.n.d = month, week, day of week */
};

struct rule
{
    enum r_type  type; /* type of rule */
    int_fast32_t day;  /* day number of rule */
    int_fast32_t week; /* week number of rule */
    int_fast32_t mon;  /* month number of rule */
    int_fast32_t time; /* transition time of rule */
};

/* Given the address of a string, extract a number within the given min..max
   range.
   Return the extracted number and advance the string to the first character
   after the number. Return INT_FAST32_MIN if there is no address, no string
   at that address, no number, or the number is out of range -- in this case
   the position of the string will be indeterminate.
*/
static int getnum( char ** str, int min, int max )
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
static int_fast32_t getoffset( char ** str )
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
static struct rule getrule( char ** str )
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

        if ( ( rule.mon = getnum( str, 1, MONSPERYEAR ) ) == INT_FAST32_MIN )
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

        rule.type = MONTH_WEEK_DAY_OF_WEEK;
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

/* Given a POSIX section 8-style TZ string, fill in the rule tables as
   appropriate.
*/
bool tzparse( char * name, struct tzdata_t * data, bool lastditch )
{
    return false;
}

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    char test[100] = "123_";
    char * str;

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
    TESTCASE( str = test + 8 );
    strcpy( test, "00:01:01" );
    str = test;
    TESTCASE( getoffset( &str ) == 61 );
    TESTCASE( str = test + 8 );
    strcpy( test, "01:01:01" );
    str = test;
    TESTCASE( getoffset( &str ) == 3661 );
    TESTCASE( str = test + 8 );
    strcpy( test, "-00:00:01" );
    str = test;
    TESTCASE( getoffset( &str ) == -1 );
    TESTCASE( str = test + 8 );
    strcpy( test, "-00:01:01" );
    str = test;
    TESTCASE( getoffset( &str ) == -61 );
    TESTCASE( str = test + 8 );
    strcpy( test, "-01:01:01" );
    str = test;
    TESTCASE( getoffset( &str ) == -3661 );
    TESTCASE( str = test + 8 );
    strcpy( test, "00:00:61" );
    str = test;
    TESTCASE( getoffset( &str ) == INT_FAST32_MIN );
    strcpy( test, "00:59:01" );
    str = test;
    TESTCASE( getoffset( &str ) == 3541 );
    TESTCASE( str = test + 8 );
    strcpy( test, "00:60:01" );
    str = test;
    TESTCASE( getoffset( &str ) == INT_FAST32_MIN );
    strcpy( test, "167:00:00" );
    str = test;
    TESTCASE( getoffset( &str ) == 601200 );
    TESTCASE( str = test + 8 );
    strcpy( test, "168:00:00" );
    str = test;
    TESTCASE( getoffset( &str ) == INT_FAST32_MIN );

    return TEST_RESULTS;
}

#endif
