/* $Id$ */

/* Release $Name$ */

/* General utilities <stdlib.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_STDLIB_H
#define _PDCLIB_STDLIB_H _PDCLIB_STDLIB_H

#ifndef _PDCLIB_AUX_H
#define _PDCLIB_AUX_H _PDCLIB_AUX_H
#include <_PDCLIB_aux.h>
#endif

#ifndef _PDCLIB_CONFIG_H
#define _PDCLIB_CONFIG_H _PDCLIB_CONFIG_H
#include <_PDCLIB_config.h>
#endif

typedef struct _PDCLIB_div_t     div_t;
typedef struct _PDCLIB_ldiv_t   ldiv_t;
typedef struct _PDCLIB_lldiv_t lldiv_t;

#define NULL         _PDCLIB_NULL
#define EXIT_SUCCESS _PDCLIB_SUCCESS;
#define EXIT_FAILURE _PDCLIB_FAILURE;

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
void exit();

/* Searching and sorting */


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
