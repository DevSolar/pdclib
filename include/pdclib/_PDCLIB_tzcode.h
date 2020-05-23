/* TZ Code declarations and definitions <_PDCLIB_tzcode.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_TZCODE_H
#define _PDCLIB_TZCODE_H _PDCLIB_TZCODE_H

#include <stdbool.h>
#include <stdint.h>
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

struct _PDCLIB_timezone
{
    unsigned char ver;
    int_fast32_t leapcnt;
    int_fast32_t timecnt;
    int_fast32_t typecnt;
    int_fast32_t charcnt;

    int_fast32_t leapcap;
    int_fast32_t timecap;

    struct transition_t
    {
        time_t        time;
        unsigned char typeidx;
    } * transition;

    struct type_t
    {
        int_fast32_t utoff;
        bool         isdst;
        int          desigidx;
        bool         isstd;
        bool         isut;
    } * type;

    char * designations;

    struct leapsecond_t
    {
        time_t       occur;
        int_fast32_t corr;
    } * leapsecond;

    bool goback;
    bool goahead;

    /* The time type to use for early times or if no transitions.
       It is always zero for recent tzdb releases.
       If might be nonzero for data from tzdb 2018e or earlier.
    */
    unsigned char defaulttype;
};

void init_tzdata_type( struct type_t * type, int_fast32_t utoff, bool isdst, int desigidx );
void gmtload( void );
int tzload( char const * name, struct _PDCLIB_timezone * data, bool doextend );
bool tzparse( char const * name, struct _PDCLIB_timezone * data, bool lastditch );

#endif
