/* PDCLib testing suite <_PDCLIB_test.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* Helper macros for printf() / scanf() tests                                 */
/* -------------------------------------------------------------------------- */
/* Tucked away in a seperate header because these are ugly, complex, and not  */
/* needed in 95% of all test cases.                                           */
/* -------------------------------------------------------------------------- */

/* ...printf() tests */
#if defined( _PDCLIB_FILEIO )
   #define GET_RESULT \
      rewind( target ); \
      if ( (int)fread( result_buffer, 1, actual_rc, target ) != actual_rc ) \
      { \
          fprintf( stderr, "GET_RESULT failed." ); \
      }
   #define RESULT_MISMATCH( act, exp ) strcmp( result_buffer, exp ) != 0
   #define RESULT_STRING( tgt ) result_buffer
#elif defined( _PDCLIB_STRINGIO )
   #define RESULT_MISMATCH( act, exp ) strcmp( act, exp ) != 0
   #define GET_RESULT
   #define RESULT_STRING( tgt ) tgt
#endif

#ifdef _PDCLIB_FILEIO
#define PREP_RESULT_BUFFER char result_buffer[100] = { 0 }; rewind( target );
#else
#define PREP_RESULT_BUFFER
#endif

#define GETFMT( fmt, ... ) (fmt)
#define PRINTF_TEST( expected_rc, expected_string, ... ) do { \
        PREP_RESULT_BUFFER \
        int actual_rc = testprintf( target, __VA_ARGS__ ); \
        GET_RESULT \
        if ( ( actual_rc != expected_rc ) || \
             ( RESULT_MISMATCH( target, expected_string ) ) ) \
        { \
            ++TEST_RESULTS; \
            fprintf( stderr, \
                "FAILED: " __FILE__ " (" _PDCLIB_FILEID "), line %d\n" \
                "        format string \"%s\"\n" \
                "        expected %2d, \"%s\"\n" \
                "        actual   %2d, \"%s\"\n", \
                 __LINE__, GETFMT(__VA_ARGS__, 0), expected_rc, \
                 expected_string, actual_rc, RESULT_STRING( target ) ); \
        } \
    } while ( 0 )

/* ...scanf() tests */
#if defined( _PDCLIB_FILEIO )
    #define PREPARE_SOURCE( input_string ) \
        rewind( source ); \
        fwrite( input_string, 1, sizeof( input_string ), source ); \
        rewind( source );
#elif defined( _PDCLIB_STRINGIO )
    #define PREPARE_SOURCE( input_string ) \
        memcpy( source, input_string, sizeof( input_string ) );
#endif

#define SCANF_TEST( expected_rc, input_string, ... ) do { \
        int actual_rc; \
        PREPARE_SOURCE( input_string ); \
        actual_rc = testscanf( source, __VA_ARGS__ ); \
        if ( actual_rc != expected_rc ) \
        { \
            ++TEST_RESULTS; \
            fprintf( stderr, "FAILED: " __FILE__ " (" _PDCLIB_FILEID "), line %d\n        expected %2d,        actual   %2d\n", __LINE__, expected_rc, actual_rc ); \
        } \
    } while ( 0 )

/* Virtually everything in the printf() / scanf() test drivers is heavily
   depending on the platform, i.e. the width of the integer values. To do
   proper domain tests, we need the limits of the integers (largest and
   smallest value), which we can get from <limits.h>. But we also need the
   string representations of these numbers, to the various bases, which of
   course vary depending on how the platform defines 'int' and 'long'.
*/

#define sym2v( x ) #x
#define sym2s( x ) sym2v( x )

#if INT_MAX >> 15 == 1

#define UINT_DIG 5
#define INT_DIG  5
#define INT_DIG_LESS1 "4"
#define INT_DIG_PLUS1 "6"
#define INT_DIG_PLUS2 "7"
#define INT_HEXDIG "FFF"
#define INT_hexdig "fff"
#define INT_OCTDIG "177777"
#define INT_MAX_DEZ_STR  "32767"
#define INT_MIN_DEZ_STR  "32768"
#define UINT_MAX_DEZ_STR "65535"
#define INT_MAX_OCT_STR
#define INT_MIN_OCT_STR
#define UINT_MAX_OCT_STR
#define INT_MAX_HEX_STR
#define INT_MIN_HEX_STR
#define UINT_MAX_HEX_STR

#elif UINT_MAX >> 31 == 1

#define UINT_DIG 10
#define INT_DIG  10
#define INT_DIG_LESS1 "9"
#define INT_DIG_PLUS1 "11"
#define INT_DIG_PLUS2 "12"
#define INT_HEXDIG "FFFFFFF"
#define INT_hexdig "fffffff"
#define INT_OCTDIG "37777777777"
#define INT_MAX_DEZ_STR  "2147483647"
#define INT_MIN_DEZ_STR  "2147483648"
#define UINT_MAX_DEZ_STR "4294967295"
#define INT_MAX_OCT_STR
#define INT_MIN_OCT_STR
#define UINT_MAX_OCT_STR
#define INT_MAX_HEX_STR
#define INT_MIN_HEX_STR
#define UINT_MAX_HEX_STR

#elif UINT_MAX >> 63 == 1

#define UINT_DIG 20
#define INT_DIG  19
#define INT_DIG_LESS1 "18"
#define INT_DIG_PLUS1 "20"
#define INT_DIG_PLUS2 "21"
#define INT_HEXDIG "FFFFFFFFFFFFFFF"
#define INT_hexdig "fffffffffffffff"
#define INT_OCTDIG "1777777777777777777777"
#define INT_MAX_DEZ_STR   "9223372036854775807"
#define INT_MIN_DEZ_STR   "9223372036854775808"
#define UINT_MAX_DEZ_STR "18446744073709551615"
#define INT_MAX_OCT_STR
#define INT_MIN_OCT_STR
#define UINT_MAX_OCT_STR
#define INT_MAX_HEX_STR
#define INT_MIN_HEX_STR
#define UINT_MAX_HEX_STR

#else

#error Unsupported width of 'int' (neither 16, 32, nor 64 bit).

#endif


#if ULONG_MAX >> 31 == 1

#define ULONG_DIG 10
#define LONG_DIG  10
#define LONG_MAX_DEZ_STR  "2147483647"
#define LONG_MIN_DEZ_STR  "2147483648"
#define ULONG_MAX_DEZ_STR "4294967295"
#define LONG_MAX_OCT_STR
#define LONG_MIN_OCT_STR
#define ULONG_MAX_OCT_STR
#define LONG_MAX_HEX_STR
#define LONG_MIN_HEX_STR
#define ULONG_MAX_HEX_STR

#elif ULONG_MAX >> 63 == 1

#define ULONG_DIG 20
#define LONG_DIG  19
#define LONG_MAX_DEZ_STR   "9223372036854775807"
#define LONG_MIN_DEZ_STR   "9223372036854775808"
#define ULONG_MAX_DEZ_STR "18446744073709551615"
#define LONG_MAX_OCT_STR
#define LONG_MIN_OCT_STR
#define ULONG_MAX_OCT_STR
#define LONG_MAX_HEX_STR
#define LONG_MIN_HEX_STR
#define ULONG_MAX_HEX_STR

#else

#error Unsupported width of 'long' (neither 32 nor 64 bit).

#endif


#if ULLONG_MAX >> 63 == 1

#define ULLONG_DIG 20
#define LLONG_DIG  19
#define LLONG_MAX_DEZ_STR   "9223372036854775807"
#define LLONG_MIN_DEZ_STR   "9223372036854775808"
#define ULLONG_MAX_DEZ_STR "18446744073709551615"
#define LLONG_MAX_OCT_STR
#define LLONG_MIN_OCT_STR
#define ULLONG_MAX_OCT_STR
#define LLONG_MAX_HEX_STR
#define LLONG_MIN_HEX_STR
#define ULLONG_MAX_HEX_STR

#elif ULLONG_MAX >> 127 == 1

#define ULLONG_DIG 38
#define LLONG_DIG  38
#define LLONG_MAX_DEZ_STR  "170141183460469231731687303715884105727"
#define LLONG_MIN_DEZ_STR  "170141183460469231731687303715884105728"
#define ULLONG_MAX_DEZ_STR "340282366920938463463374607431768211455"
#define LLONG_MAX_OCT_STR
#define LLONG_MIN_OCT_STR
#define ULLONG_MAX_OCT_STR
#define LLONG_MAX_HEX_STR
#define LLONG_MIN_HEX_STR
#define ULLONG_MAX_HEX_STR

#else

#error Unsupported width of 'long long' (neither 64 nor 128 bit).

#endif
