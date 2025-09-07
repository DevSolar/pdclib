/* _PDCLIB_print_fp_deci( _PDCLIB_fp_t *, struct _PDCLIB_status_t *, char )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

#include <float.h>

static int prep( _PDCLIB_bigint_t * mantissa, int exponent )
{
    /* log10(2) to 128bit precision */
    const long double log_10_2 = 0.30102999566398119521373889472449302l;

    /* Get an approximation of the base 10 exponent we are looking at
       and make it fall one short in most cases as correction is easier
       that way.
    */
    double guess = (double)( _PDCLIB_bigint_log2( mantissa ) + exponent ) * log_10_2 - 0.69;
    int exp10 = ( (int)guess < guess ) ? (int)guess + 1 : (int)guess;

    return exp10;
}

int _PDCLIB_print_fp_deci( _PDCLIB_fp_t * fp,
                            struct _PDCLIB_status_t * status,
                            char * buffer )
{
    char * current = buffer;
    _PDCLIB_bigint_t divisor;
    _PDCLIB_bigint_digit_t msd;
    int digit;
    int cutoff;

    /* No decimal point in the mantissa, so we adjust the exponent. */
    int exponent = fp->exponent - fp->scale;

    int exp10 = prep( &fp->mantissa, exponent );

    if ( ( status->flags & E_decimal ) && ( status->prec >= 0 ) && ( exp10 <= -status->prec ) )
    {
        exp10 = -status->prec + 1;
    }

    /* Set up the fraction. */
    if ( exponent > 0 )
    {
        _PDCLIB_bigint_shl( &fp->mantissa, exponent );
        _PDCLIB_bigint_from_digit( &divisor, 1 );
    }
    else
    {
        _PDCLIB_bigint_from_pow2( &divisor, -exponent );
    }

    /* Using the approx. exp10, scale the fraction close to where
       we could start dividing.
     */
    if ( exp10 > 0 )
    {
        _PDCLIB_bigint_mul_pow10( &divisor, exp10 );
    }
    else if ( exp10 < 0 )
    {
        _PDCLIB_bigint_mul_pow10( &fp->mantissa, -exp10 );
    }

    /* Now we know if our approximation was good or needs correction.
       This is why we substracted as much as we could in prep(), as
       correctiong for one short is the cheaper operation.
    */
    if ( _PDCLIB_bigint_cmp( &fp->mantissa, &divisor ) >= 0 )
    {
        ++exp10;
    }
    else
    {
        _PDCLIB_bigint_mul10( &fp->mantissa );
    }

    /* We make sure the fraction is scaled properly.
       The previous operations already ensured that
       the mantissa is no more than divisor * 10.
       Now we make sure that the divisor has enough
       bits in the most significant digit to give a
       proper result, and that both mantissa and the
       divisor are scaled to the same bigint length.
    */
    msd = divisor.data[ divisor.size - 1 ];

    if ( ( msd < 8 ) || ( msd > ( _PDCLIB_BIGINT_DIGIT_MAX / 10 ) ) )
    {
        int shift = ( ( _PDCLIB_BIGINT_DIGIT_BITS * 2 - 5 ) - _PDCLIB_bigint_digit_log2( msd ) ) % 32;
        _PDCLIB_bigint_shl( &fp->mantissa, shift );
        _PDCLIB_bigint_shl( &divisor, shift );
    }

    /* Main loop - divide, generate digits, multiply with 10, repeat */
    switch ( status->flags & ( E_decimal | E_exponent | E_generic ) )
    {
        case E_decimal:
            cutoff = -status->prec;
            break;
        case E_exponent:
        case E_generic:
            cutoff = exp10 - status->prec - 1;
            break;
    }

    for (;;)
    {
        digit = _PDCLIB_bigint_div( &fp->mantissa, &divisor );
        --exp10;

        if ( fp->mantissa.size == 0 || exp10 == cutoff )
        {
            break;
        }

        *current++ = _PDCLIB_digits[ digit ];
        _PDCLIB_bigint_mul10( &fp->mantissa );
    }

    /* rounding */
    {
        int roundup = 0;

        switch ( FLT_ROUNDS )
        {
            case 3: /*FE_DOWNWARD*/
                roundup = ( fp->sign == '-' );
                break;
            case 2: /*FE_UPWARD*/
                roundup = ( fp->sign != '-' );
                break;
            case 0: /*FE_TOWARDZERO*/
                roundup = 0;
                break;
            default:
            case 1: /*FE_TONEAREST*/
            {
                int compare;
                _PDCLIB_bigint_shl( &fp->mantissa, 1 );
                compare = _PDCLIB_bigint_cmp( &fp->mantissa, &divisor );
                if ( ( compare > 0 ) /* Over 0.5 */
                     || ( ( compare == 0 ) && ( digit & 1 ) ) ) /* Break tie to even */
                {
                    roundup = 1;
                }
            }

            if ( roundup )
            {
                if ( digit < 9 )
                {
                    *current++ = _PDCLIB_digits[ ++digit ];
                }
                else
                {
                    for (;;)
                    {
                        ++exp10;

                        if ( current == buffer )
                        {
                            *current++ = _PDCLIB_digits[1];
                            ++exp10;
                            break;
                        }

                        if ( *--current != _PDCLIB_digits[9] )
                        {
                            ++*current++;
                            break;
                        }
                    }
                }
            }
            else
            {
                *current++ = _PDCLIB_digits[ digit ];
            }
        }

        while ( *(current - 1) == '0' )
        {
            --current;
            ++exp10;
        }
    }

    *current = '\0';
    return exp10;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( int argc, char * argv[] )
{
    /* Tested by _PDCLIB_print testdriver */
    return TEST_RESULTS;
}

#endif
