// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Date and time
// ----------------------------------------------------------------------------

#ifndef __TIME_H
#define __TIME_H __TIME_H

// ----------------------------------------------------------------------------
// MACROS

#define CLOCKS_PER_SEC // TODO
#define NULL           0

// ----------------------------------------------------------------------------
// TYPES

typedef clock_t;
typedef size_t;
typedef time_t;
struct tm;

// ----------------------------------------------------------------------------
// FUNCTIONS

char * asctime( const struct tm * tptr );
clock_t clock( void );
char * ctime( const time_t * tod );
double difftime( time_t t1, time_t t0 );
struct tm * gmtime( const time_t * tod );
struct tm * localtime( const time_t * tod );
time_t mktime( struct tm * tptr );
size_t strftime( char * restrict s, size_t n, const char * restrict format,
                 const struct tm * restrict tptr );
time_t time( time_t * tod );

#endif // __TIME_H
