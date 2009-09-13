/* $Id$ */

/* vsnprintf( char *, size_t, const char *, va_list ap )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int vsnprintf( char * s, size_t n, const char * format, _PDCLIB_va_list arg )
{
    /* TODO: This function should interpret format as multibyte characters.  */
    /* Members: base, flags, n, i, this, s, width, prec, stream, arg         */
    struct _PDCLIB_status_t status;
    status.base = 0;
    status.flags = 0;
    status.n = n;
    status.i = 0;
    status.this = 0;
    status.s = s;
    status.width = 0;
    status.prec = 0;
    status.stream = NULL;
    va_copy( status.arg, arg );
    // = { 0, 0, n, 0, 0, s, 0, 0, NULL };
    while ( *format != '\0' )
    {
        const char * rc;
        if ( ( *format != '%' ) || ( ( rc = _PDCLIB_print( format, &status ) ) == format ) )
        {
            /* No conversion specifier, print verbatim */
            s[ status.i++ ] = *(format++);
        }
        else
        {
            /* Continue parsing after conversion specifier */
            format = rc;
        }
    }
    s[ status.i ] = '\0';
    va_end( status.arg );
    return status.i;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#include <limits.h>
#include <stdint.h>
#include <string.h>


static int testprintf( char * s, size_t n, const char * format, ... )
{
    int i;
    va_list arg;
    va_start( arg, format );
    i = vsnprintf( s, n, format, arg );
    va_end( arg );
    return i;
}

int main( void )
{
    char buffer[100];
    TESTCASE( testprintf( buffer, 100, "%hhd", CHAR_MIN ) == 4 );
    TESTCASE( strcmp( buffer, "-128" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%hhd", CHAR_MAX ) == 3 );
    TESTCASE( strcmp( buffer, "127" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%hhd", 0 ) == 1 );
    TESTCASE( strcmp( buffer, "0" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%hd", SHRT_MIN ) == 6 );
    TESTCASE( strcmp( buffer, "-32768" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%hd", SHRT_MAX ) == 5 );
    TESTCASE( strcmp( buffer, "32767" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%hd", 0 ) == 1 );
    TESTCASE( strcmp( buffer, "0" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%d", 0 ) == 1 );
    TESTCASE( strcmp( buffer, "0" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%ld", LONG_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%ld", LONG_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%ld", 0l ) == 1 );
    TESTCASE( strcmp( buffer, "0" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%lld", LLONG_MIN ) == 20 );
    TESTCASE( strcmp( buffer, "-9223372036854775808" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%lld", LLONG_MAX ) == 19 );
    TESTCASE( strcmp( buffer, "9223372036854775807" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%lld", 0ll ) );
    TESTCASE( strcmp( buffer, "0" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%hhu", UCHAR_MAX ) == 3 );
    TESTCASE( strcmp( buffer, "255" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%hhu", (unsigned char)-1 ) == 3 );
    TESTCASE( strcmp( buffer, "255" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%hu", USHRT_MAX ) == 5 );
    TESTCASE( strcmp( buffer, "65535" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%hu", (unsigned short)-1 ) == 5 );
    TESTCASE( strcmp( buffer, "65535" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%u", UINT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "4294967295" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%u", -1u ) == 10 );
    TESTCASE( strcmp( buffer, "4294967295" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%lu", ULONG_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "4294967295" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%lu", -1ul ) == 10 );
    TESTCASE( strcmp( buffer, "4294967295" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%llu", ULLONG_MAX ) == 20 );
    TESTCASE( strcmp( buffer, "18446744073709551615" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%llu", -1ull ) == 20 );
    TESTCASE( strcmp( buffer, "18446744073709551615" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%X", UINT_MAX ) == 8 );
    TESTCASE( strcmp( buffer, "FFFFFFFF" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#X", -1u ) == 10 );
    TESTCASE( strcmp( buffer, "0XFFFFFFFF" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%x", UINT_MAX ) == 8 );
    TESTCASE( strcmp( buffer, "ffffffff" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#x", -1u ) == 10 );
    TESTCASE( strcmp( buffer, "0xffffffff" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%o", UINT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, "37777777777" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#o", -1u ) == 12 );
    TESTCASE( strcmp( buffer, "037777777777" ) == 0 );
    /* TODO: This test case is broken, doesn't test what it was intended to. */
    TESTCASE( testprintf( buffer, 100, "%.0#o", 0 ) == 5 );
    TESTCASE( strcmp( buffer, "%.0#o" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%+d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%+d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, "+2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%+d", 0 ) == 2 );
    TESTCASE( strcmp( buffer, "+0" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%+u", UINT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "4294967295" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%+u", -1u ) == 10 );
    TESTCASE( strcmp( buffer, "4294967295" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "% d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "% d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, " 2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "% d", 0 ) == 2 );
    TESTCASE( strcmp( buffer, " 0" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "% u", UINT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "4294967295" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "% u", -1u ) == 10 );
    TESTCASE( strcmp( buffer, "4294967295" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%9d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%9d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%10d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%10d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%11d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%11d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, " 2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%12d", INT_MIN ) == 12 );
    TESTCASE( strcmp( buffer, " -2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%12d", INT_MAX ) == 12 );
    TESTCASE( strcmp( buffer, "  2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-9d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-9d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-10d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-10d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-11d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-11d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, "2147483647 " ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-12d", INT_MIN ) == 12 );
    TESTCASE( strcmp( buffer, "-2147483648 " ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-12d", INT_MAX ) == 12 );
    TESTCASE( strcmp( buffer, "2147483647  " ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%09d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%09d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%010d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%010d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%011d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%011d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, "02147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%012d", INT_MIN ) == 12 );
    TESTCASE( strcmp( buffer, "-02147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%012d", INT_MAX ) == 12 );
    TESTCASE( strcmp( buffer, "002147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-09d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-09d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-010d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-010d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-011d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-011d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, "2147483647 " ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-012d", INT_MIN ) == 12 );
    TESTCASE( strcmp( buffer, "-2147483648 " ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%-012d", INT_MAX ) == 12 );
    TESTCASE( strcmp( buffer, "2147483647  " ) == 0 );
    TESTCASE( testprintf( buffer, 8, "%9d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483" ) == 0 );
    TESTCASE( testprintf( buffer, 8, "%9d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-214748" ) == 0 );
    TESTCASE( testprintf( buffer, 9, "%9d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "21474836" ) == 0 );
    TESTCASE( testprintf( buffer, 9, "%9d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483" ) == 0 );
    TESTCASE( testprintf( buffer, 10, "%9d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "214748364" ) == 0 );
    TESTCASE( testprintf( buffer, 10, "%9d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-21474836" ) == 0 );
    TESTCASE( testprintf( buffer, 9, "%10d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "21474836" ) == 0 );
    TESTCASE( testprintf( buffer, 9, "%10d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483" ) == 0 );
    TESTCASE( testprintf( buffer, 10, "%10d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "214748364" ) == 0 );
    TESTCASE( testprintf( buffer, 10, "%10d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-21474836" ) == 0 );
    TESTCASE( testprintf( buffer, 11, "%10d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 11, "%10d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-214748364" ) == 0 );
    TESTCASE( testprintf( buffer, 10, "%11d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, " 21474836" ) == 0 );
    TESTCASE( testprintf( buffer, 10, "%11d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-21474836" ) == 0 );
    TESTCASE( testprintf( buffer, 11, "%11d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, " 214748364" ) == 0 );
    TESTCASE( testprintf( buffer, 11, "%11d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-214748364" ) == 0 );
    TESTCASE( testprintf( buffer, 12, "%11d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, " 2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 12, "%11d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 11, "%12d", INT_MAX ) == 12 );
    TESTCASE( strcmp( buffer, "  21474836" ) == 0 );
    TESTCASE( testprintf( buffer, 11, "%12d", INT_MIN ) == 12 );
    TESTCASE( strcmp( buffer, " -21474836" ) == 0 );
    TESTCASE( testprintf( buffer, 12, "%12d", INT_MAX ) == 12 );
    TESTCASE( strcmp( buffer, "  214748364" ) == 0 );
    TESTCASE( testprintf( buffer, 12, "%12d", INT_MIN ) == 12 );
    TESTCASE( strcmp( buffer, " -214748364" ) == 0 );
    TESTCASE( testprintf( buffer, 13, "%12d", INT_MAX ) == 12 );
    TESTCASE( strcmp( buffer, "  2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 13, "%12d", INT_MIN ) == 12 );
    TESTCASE( strcmp( buffer, " -2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%030.20d", INT_MAX ) == 30 );
    TESTCASE( strcmp( buffer, "          00000000002147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%.6x", UINT_MAX ) == 8 );
    TESTCASE( strcmp( buffer, "ffffffff" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#6.3x", UINT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "0xffffffff" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#3.6x", UINT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "0xffffffff" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%.6d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%6.3d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%3.6d", INT_MIN ) == 11 );
    TESTCASE( strcmp( buffer, "-2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#0.6x", UINT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "0xffffffff" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#06.3x", UINT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "0xffffffff" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#03.6x", UINT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "0xffffffff" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#0.6d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#06.3d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#03.6d", INT_MAX ) == 10 );
    TESTCASE( strcmp( buffer, "2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#+.6d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, "+2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#+6.3d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, "+2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%#+3.6d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, "+2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%+0.6d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, "+2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%+06.3d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, "+2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%+03.6d", INT_MAX ) == 11 );
    TESTCASE( strcmp( buffer, "+2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "- %d", INT_MAX ) == 12 );
    TESTCASE( strcmp( buffer, "- 2147483647" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "- %d %% %d", INT_MAX, INT_MIN ) == 26 );
    TESTCASE( strcmp( buffer, "- 2147483647 % -2147483648" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%c", 'x' ) == 1 );
    TESTCASE( strcmp( buffer, "x" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%s", "abcdef" ) == 6 );
    TESTCASE( strcmp( buffer, "abcdef" ) == 0 );
    TESTCASE( testprintf( buffer, 100, "%p", (void *)0xdeadbeef ) == 10 );
    TESTCASE( strcmp( buffer, "0xdeadbeef" ) == 0 );
    {
        int val1, val2;
        TESTCASE( testprintf( buffer, 100, "123456%n789%n", &val1, &val2 ) == 9 );
        TESTCASE( strcmp( buffer, "123456789" ) == 0 );
        TESTCASE( val1 == 6 );
        TESTCASE( val2 == 9 );
    }
    return TEST_RESULTS;
}

#endif

