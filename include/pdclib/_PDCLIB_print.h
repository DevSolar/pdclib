/* PDCLib printf logic <_PDCLIB_print.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_PRINT_H
#define _PDCLIB_PRINT_H _PDCLIB_PRINT_H

#include "pdclib/_PDCLIB_internal.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* This macro delivers a given character to either a memory buffer or a stream,
   depending on the contents of 'status' (struct _PDCLIB_status_t).
   x - the character to be delivered
   i - pointer to number of characters already delivered in this call
   n - pointer to maximum number of characters to be delivered in this call
   s - the buffer into which the character shall be delivered
*/
#define PUT( x ) \
    do { \
        int character = x; \
        if ( status->i < status->n ) { \
            if ( status->stream != NULL ) \
                putc( character, status->stream ); \
            else \
                status->s[status->i] = character; \
        } \
        ++(status->i); \
    } while ( 0 )


/* Using an integer's bits as flags for both the conversion flags and length
   modifiers.
*/
#define E_minus    (INT32_C(1)<<0)
#define E_plus     (INT32_C(1)<<1)
#define E_alt      (INT32_C(1)<<2)
#define E_space    (INT32_C(1)<<3)
#define E_zero     (INT32_C(1)<<4)
#define E_done     (INT32_C(1)<<5)

#define E_char     (INT32_C(1)<<6)
#define E_short    (INT32_C(1)<<7)
#define E_long     (INT32_C(1)<<8)
#define E_llong    (INT32_C(1)<<9)
#define E_intmax   (INT32_C(1)<<10)
#define E_size     (INT32_C(1)<<11)
#define E_ptrdiff  (INT32_C(1)<<12)
#define E_pointer  (INT32_C(1)<<13)

#define E_double   (INT32_C(1)<<14)
#define E_ldouble  (INT32_C(1)<<15)

#define E_decimal  (INT32_C(1)<<18)
#define E_exponent (INT32_C(1)<<19)
#define E_generic  (INT32_C(1)<<20)
#define E_hexa     (INT32_C(1)<<21)

#define E_lower    (INT32_C(1)<<16)
#define E_unsigned (INT32_C(1)<<17)

void _PDCLIB_print_integer( struct _PDCLIB_imaxdiv_t div, struct _PDCLIB_status_t * status );
void _PDCLIB_print_string( const char * s, struct _PDCLIB_status_t * status );
void _PDCLIB_print_double( double value, struct _PDCLIB_status_t * status );
void _PDCLIB_print_ldouble( long double value, struct _PDCLIB_status_t * status );

#endif
