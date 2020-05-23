/* TZ Code declarations and definitions <_PDCLIB_tzcode.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_TZCODE_H
#define _PDCLIB_TZCODE_H _PDCLIB_TZCODE_H

#include <pdclib/_PDCLIB_config.h>

#include <stdbool.h>

/* Fallback / default timezone */
static char const _PDCLIB_gmt[] = "GMT";

struct _PDCLIB_timezone
{
    unsigned char ver;
    _PDCLIB_int_fast32_t leapcnt;
    _PDCLIB_int_fast32_t timecnt;
    _PDCLIB_int_fast32_t typecnt;
    _PDCLIB_int_fast32_t charcnt;

    _PDCLIB_int_fast32_t leapcap;
    _PDCLIB_int_fast32_t timecap;

    struct _PDCLIB_transition_t
    {
        _PDCLIB_time_t time;
        unsigned char  typeidx;
    } * transition;

    struct _PDCLIB_type_t
    {
        _PDCLIB_int_fast32_t utoff;
        bool                 isdst;
        int                  desigidx;
        bool                 isstd;
        bool                 isut;
    } * type;

    char * designations;

    struct _PDCLIB_leapsecond_t
    {
        _PDCLIB_time_t       occur;
        _PDCLIB_int_fast32_t corr;
    } * leapsecond;

    bool goback;
    bool goahead;

    /* The time type to use for early times or if no transitions.
       It is always zero for recent tzdb releases.
       If might be nonzero for data from tzdb 2018e or earlier.
    */
    unsigned char defaulttype;
};

void _PDCLIB_gmtload( void );
int _PDCLIB_tzload( char const * name, struct _PDCLIB_timezone * data, bool doextend );
bool _PDCLIB_tzparse( char const * name, struct _PDCLIB_timezone * data, bool lastditch );

#endif
