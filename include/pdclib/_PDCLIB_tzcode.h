/* TZ Code declarations and definitions <_PDCLIB_tzcode.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_TZCODE_H
#define _PDCLIB_TZCODE_H _PDCLIB_TZCODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <pdclib/_PDCLIB_config.h>

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

/* Handy macros that are independent of tzfile implementation. */
#define YEARSPERREPEAT  400 /* years before a Gregorian repeat */

#define SECSPERMIN      60
#define MINSPERHOUR     60
#define HOURSPERDAY     24
#define DAYSPERWEEK     7
#define DAYSPERNYEAR    365
#define DAYSPERLYEAR    366
#define SECSPERHOUR     (SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY      ((int_fast32_t) SECSPERHOUR * HOURSPERDAY)
#define MONSPERYEAR     12

#define AVGSECSPERYEAR 31556952L
#define SECSPERREPEAT ((int_fast64_t) YEARSPERREPEAT * (int_fast64_t) AVGSECSPERYEAR)
#define SECSPERREPEAT_BITS 34 /* ceil(log2(SECSPERREPEAT)) */

#define TM_SUNDAY    0
#define TM_MONDAY    1
#define TM_TUESDAY   2
#define TM_WEDNESDAY 3
#define TM_THURSDAY  4
#define TM_FRIDAY    5
#define TM_SATURDAY  6

#define TM_YEAR_BASE 1900

#define EPOCH_YEAR 1970
#define EPOCH_WDAY TM_THURSDAY

extern struct tm _PDCLIB_tm;
extern int lcl_is_set;

static const char gmt[] = "GMT";

static const int mon_lengths[ 2 ][ MONSPERYEAR ] =
{
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

static const int year_lengths[2] =
{
    DAYSPERNYEAR, DAYSPERLYEAR
};

/* time type information */
struct ttinfo
{
    int_fast32_t utoff;    /* UT offset in seconds    */
    bool         isdst;    /* used to set tm_isdst    */
    int          desigidx; /* abbreviation list index */
    bool         ttisstd;  /* transition is std time  */
    bool         ttisut;   /* transition is UT        */
};

/* leap second information */
struct lsinfo
{
    time_t       trans;    /* transition time         */
    int_fast64_t corr;     /* correction to apply     */
};

#define BIGGEST( a, b )  (((a) > (b)) ? (a) : (b))

#ifndef TZ_MAX_TIMES
#define TZ_MAX_TIMES 2000
#endif

#ifndef TZ_MAX_TYPES
/* This must be at least 17 for Europe/Vilnius. */
/* Limited by what (unsigned char)s can hold    */
#define TZ_MAX_TYPES 256
#endif

#ifndef TZ_MAX_CHARS
/* Maximum number of abbreviation characters    */
/* Limited by what (unsigned char)s can hold    */
#define TZ_MAX_CHARS 50
#endif

#ifndef TZ_MAX_LEAPS
/* Maximum number of leap second corrections    */
#define TZ_MAX_LEAPS 50
#endif

#ifdef TZNAME_MAX
#define MY_TZNAME_MAX TZNAME_MAX
#else
#define MY_TZNAME_MAX 255
#endif

struct state
{
    int            leapcnt;
    int            timecnt;
    int            typecnt;
    int            charcnt;
    bool           goback;
    bool           goahead;
    time_t         ats[ TZ_MAX_TIMES ];
    unsigned char  types[ TZ_MAX_TIMES ];
    struct ttinfo  ttis[ TZ_MAX_TYPES ];
    char           chars[ BIGGEST( BIGGEST( TZ_MAX_CHARS + 1, sizeof gmt ), ( 2 * ( MY_TZNAME_MAX + 1 ) ) ) ];
    struct lsinfo  lsis[ TZ_MAX_LEAPS ];

    /* The time type to use for early times or if no transitions.
       It is always zero for recent tzdb releases.
       It might be nonzero for data from tzdb 2018e or earlier.
    */
    int            defaulttype;
};

extern struct state _PDCLIB_lclmem;
extern struct state _PDCLIB_gmtmem;

void        _PDCLIB_gmtcheck(void);
struct tm * _PDCLIB_gmtsub( struct state const * sp, time_t const * timep, int_fast32_t offset, struct tm * tmp );
bool        _PDCLIB_increment_overflow( int * ip, int j );
void        _PDCLIB_init_ttinfo( struct ttinfo * s, int_fast32_t utoff, bool isdst, int desigidx );
struct tm * _PDCLIB_localsub( struct state const * sp, time_t const * timep, int_fast32_t setname, struct tm * const tmp );
struct tm * _PDCLIB_localtime_tzset( time_t const * timep, struct tm * tmp, bool setname );
time_t      _PDCLIB_mktime_tzname( struct state * sp, struct tm * tmp, bool setname );
struct tm * _PDCLIB_timesub( const time_t * timep, int_fast32_t offset, const struct state * sp, struct tm * tmp );
int         _PDCLIB_tzload( char const * name, struct state * sp, bool doextend );
bool        _PDCLIB_tzparse(char const *, struct state *, bool);
void        _PDCLIB_tzset_unlocked( void );
void        _PDCLIB_update_tzname_etc( struct state const * sp, struct ttinfo const * ttisp );

#ifdef __cplusplus
}
#endif

#endif
