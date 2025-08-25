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

/* -------------------------------------------------------------------------- */
/* _PDCLIB_bigint_t support (required for floating point conversions)         */
/* -------------------------------------------------------------------------- */

/* Must be divisible by 32.                                                   */
/* 1120 is enough for 64bit floats. A 128 float takes 16544 bits.             */
#define _PDCLIB_BIGINT_BITS 1120

#if _PDCLIB_BIGINT_DIGIT_BITS == 32
#define _PDCLIB_BIGINT_DIGIT_MAX _PDCLIB_UINT_LEAST32_C( 0xFFFFFFFF )
typedef _PDCLIB_uint_least32_t _PDCLIB_bigint_digit_t;
typedef _PDCLIB_int_least32_t _PDCLIB_bigint_sdigit_t;
typedef _PDCLIB_uint_least64_t _PDCLIB_bigint_arith_t;
#elif _PDCLIB_BIGINT_DIGIT_BITS == 16
#define _PDCLIB_BIGINT_DIGIT_MAX _PDCLIB_UINT_LEAST16_C( 0xFFFF )
typedef _PDCLIB_uint_least16_t _PDCLIB_bigint_digit_t;
typedef _PDCLIB_int_least16_t _PDCLIB_bigint_sdigit_t;
typedef _PDCLIB_uint_least32_t _PDCLIB_bigint_arith_t;
#else
#error _PDCLIB_BIGINT_DIGIT_BITS.needs to be 16 or 32.
#endif

/* How many "digits" a _PDCLIB_bigint_t holds.                                */
#define _PDCLIB_BIGINT_DIGITS _PDCLIB_BIGINT_BITS / _PDCLIB_BIGINT_DIGIT_BITS

/* Maximum number of characters needed for _PDCLIB_bigint_tostring()          */
#define _PDCLIB_BIGINT_CHARS ( _PDCLIB_BIGINT_BITS / 4 + _PDCLIB_BIGINT_DIGITS + 2 )

/* Type */
/* ---- */

typedef struct
{
    /* Number of digits used; zero value == zero size */
    _PDCLIB_size_t size;
    /* Least significant digit first */
    _PDCLIB_bigint_digit_t data[ _PDCLIB_BIGINT_DIGITS ];
} _PDCLIB_bigint_t;

typedef struct
{
    _PDCLIB_bigint_t mantissa;
    _PDCLIB_int_least16_t exponent;
    _PDCLIB_int_least16_t scale;
    enum
    {
        _PDCLIB_FP_NORMAL,
        _PDCLIB_FP_SUBNORMAL,
        _PDCLIB_FP_INF,
        _PDCLIB_FP_NAN
    } state;
    char sign;
} _PDCLIB_fp_t;

void _PDCLIB_fp_from_dbl( _PDCLIB_fp_t * fp, double value );
void _PDCLIB_fp_from_ldbl( _PDCLIB_fp_t * fp, long double value );

void _PDCLIB_bigint_from_digit( _PDCLIB_bigint_t * bigint, _PDCLIB_bigint_digit_t digit );
void _PDCLIB_bigint_from_pow2( _PDCLIB_bigint_t * bigint, unsigned pow );
void _PDCLIB_bigint_from_pow10( _PDCLIB_bigint_t * bigint, unsigned pow );
void _PDCLIB_bigint_from_bigint( _PDCLIB_bigint_t * bigint, _PDCLIB_bigint_t const * other );
void _PDCLIB_bigint_add( _PDCLIB_bigint_t * bigint, _PDCLIB_bigint_t const * other );
void _PDCLIB_bigint_mul( _PDCLIB_bigint_t * bigint, _PDCLIB_bigint_t const * other );
void _PDCLIB_bigint_mul_pow10( _PDCLIB_bigint_t * bigint, int pow10 );
int _PDCLIB_bigint_cmp( _PDCLIB_bigint_t const * lhs, _PDCLIB_bigint_t const * rhs );
void _PDCLIB_bigint_shl( _PDCLIB_bigint_t * bigint, _PDCLIB_size_t bits );
void _PDCLIB_bigint_mul10( _PDCLIB_bigint_t * bigint );
int _PDCLIB_bigint_digit_log2( _PDCLIB_bigint_digit_t digit );
int _PDCLIB_bigint_log2( _PDCLIB_bigint_t const * bigint );
unsigned _PDCLIB_bigint_div( _PDCLIB_bigint_t * dividend, _PDCLIB_bigint_t const * divisor );

void _PDCLIB_print_integer( struct _PDCLIB_imaxdiv_t div, struct _PDCLIB_status_t * status );
void _PDCLIB_print_string( const char * s, struct _PDCLIB_status_t * status );
void _PDCLIB_print_fp( _PDCLIB_fp_t * fp, struct _PDCLIB_status_t * status );
void _PDCLIB_print_fp_deci( _PDCLIB_fp_t * fp, struct _PDCLIB_status_t * status, char * buffer );
void _PDCLIB_print_fp_hexa( _PDCLIB_fp_t * fp, struct _PDCLIB_status_t * status, char * buffer );
void _PDCLIB_print_fp_dragon4( _PDCLIB_bigint_t * fp, struct _PDCLIB_status_t * status );

#endif
