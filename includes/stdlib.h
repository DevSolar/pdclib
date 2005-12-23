/* $Id$ */

/* Release $Name$ */

/* General utilities <stdlib.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_STDLIB_H
#define _PDCLIB_STDLIB_H _PDCLIB_STDLIB_H

#ifndef _PDCLIB_INT_H
#define _PDCLIB_INT_H _PDCLIB_INT_H
#include <_PDCLIB_int.h>
#endif

typedef struct _PDCLIB_div_t     div_t;
typedef struct _PDCLIB_ldiv_t   ldiv_t;
typedef struct _PDCLIB_lldiv_t lldiv_t;

#ifndef _PDCLIB_SIZE_T_DEFINED
#define _PDCLIB_SIZE_T_DEFINED _PDCLIB_SIZE_T_DEFINED
typedef _PDCLIB_size_t size_t;
#endif

#define NULL         _PDCLIB_NULL
#define EXIT_SUCCESS _PDCLIB_SUCCESS
#define EXIT_FAILURE _PDCLIB_FAILURE

/* Numeric conversion functions */

int atoi( const char * nptr );
long int atol( const char * nptr );
long long int atoll( const char * nptr );

long int strtol( const char * _PDCLIB_restrict nptr, char * * _PDCLIB_restrict endptr, int base );
long long int strtoll( const char * _PDCLIB_restrict nptr, char * * _PDCLIB_restrict endptr, int base );
unsigned long int strtoul( const char * _PDCLIB_restrict nptr, char * * _PDCLIB_restrict endptr, int base );
unsigned long long int strtoull( const char * _PDCLIB_restrict nptr, char * * _PDCLIB_restrict endptr, int base );

/* Pseudo-random sequence generation functions */

extern unsigned long int _PDCLIB_seed;

#define RAND_MAX 32767

int rand();
void srand( unsigned int seed );

/* Memory management functions */


/* Communication with the environment */

void abort();
void exit( int status );

/* Searching and sorting */

void * bsearch( const void * key, const void * base, size_t nmemb, size_t size, int (*compar)( const void *, const void * ) );
void qsort( void * base, size_t nmemb, size_t size, int (*compar)( const void *, const void * ) );

/* Integer arithmetic functions */

int abs( int j );
long int labs( long int j );
long long int llabs( long long int j );

div_t div( int numer, int denom );
ldiv_t ldiv( long int numer, long int denom );
lldiv_t lldiv( long long int numer, long long int denom );

/* Multibyte / wide character conversion functions */

/* TODO: Macro MB_CUR_MAX */

/* Multibyte / wide string conversion functions */


#endif
