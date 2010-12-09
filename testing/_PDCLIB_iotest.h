/* $Id$ */

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
    #define RESULT_MISMATCH( act, exp ) \
        rewind( act ), \
        result_buffer[ fread( result_buffer, 1, strlen( exp ) + 1, act ) ] = '\0', \
        rewind( act ), \
        memcmp( result_buffer, exp, strlen( exp ) )
   #define RESULT_STRING( tgt ) result_buffer
#elif defined( _PDCLIB_STRINGIO )
   #define RESULT_MISMATCH( act, exp ) strcmp( act, exp ) != 0
   #define RESULT_STRING( tgt ) tgt
#endif

#ifdef _PDCLIB_FILEIO
#define PREP_RESULT_BUFFER char result_buffer[100];
#else
#define PREP_RESULT_BUFFER
#endif

#define PRINTF_TEST( expected_rc, expected_string, format, ... ) do { \
        PREP_RESULT_BUFFER \
        int actual_rc = testprintf( target, format, __VA_ARGS__ ); \
        if ( ( actual_rc != expected_rc ) || \
             ( RESULT_MISMATCH( target, expected_string ) ) ) \
        { \
            ++TEST_RESULTS; \
            fprintf( stderr, "FAILED: " __FILE__ " (" _PDCLIB_FILEID "), line %d\n        expected %2d, \"%s\"\n        actual   %2d, \"%s\"\n", __LINE__, expected_rc, expected_string, actual_rc, RESULT_STRING( target ) ); \
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

#define SCANF_TEST( expected_rc, input_string, format, ... ) do { \
        int actual_rc; \
        PREPARE_SOURCE( input_string ); \
        actual_rc = testscanf( source, format, __VA_ARGS__ ); \
        if ( actual_rc != expected_rc ) \
        { \
            ++TEST_RESULTS; \
            fprintf( stderr, "FAILED: " __FILE__ " (" _PDCLIB_FILEID "), line %d\n        expected %2d,        actual   %2d\n", __LINE__, expected_rc, actual_rc ); \
        } \
    } while ( 0 )

