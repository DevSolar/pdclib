    {
    PRINTF_TEST( 4,   "-128", "%hhd", CHAR_MIN );
    PRINTF_TEST( 3,    "127", "%hhd", CHAR_MAX );
    PRINTF_TEST( 1,      "0", "%hhd", 0 );
    PRINTF_TEST( 6, "-32768",  "%hd", SHRT_MIN );
    PRINTF_TEST( 5,  "32767",  "%hd", SHRT_MAX );
    PRINTF_TEST( 1,      "0",  "%hd", 0 );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%d", INT_MIN );
    PRINTF_TEST( INT_DIG, INT_MAX_DEZ_STR, "%d", INT_MAX );
    PRINTF_TEST( 1, "0", "%d", 0 );
    PRINTF_TEST( LONG_DIG + 1, "-" LONG_MIN_DEZ_STR, "%ld", LONG_MIN );
    PRINTF_TEST( LONG_DIG, LONG_MAX_DEZ_STR, "%ld", LONG_MAX );
    PRINTF_TEST( 1, "0", "%ld", 0l );
    PRINTF_TEST( LLONG_DIG + 1, "-" LLONG_MIN_DEZ_STR, "%lld", LLONG_MIN );
    PRINTF_TEST( LLONG_DIG, LLONG_MAX_DEZ_STR, "%lld", LLONG_MAX );
    PRINTF_TEST( 1, "0", "%lld", 0ll );
    PRINTF_TEST( 3, "255", "%hhu", UCHAR_MAX );
    PRINTF_TEST( 3, "255", "%hhu", (unsigned char)-1 );
    PRINTF_TEST( 5, "65535", "%hu", USHRT_MAX );
    PRINTF_TEST( 5, "65535", "%hu", (unsigned short)-1 );
    PRINTF_TEST( UINT_DIG, UINT_MAX_DEZ_STR, "%u", UINT_MAX );
    PRINTF_TEST( UINT_DIG, UINT_MAX_DEZ_STR, "%u", -1u );
    PRINTF_TEST( ULONG_DIG, ULONG_MAX_DEZ_STR, "%lu", ULONG_MAX );
    PRINTF_TEST( ULONG_DIG, ULONG_MAX_DEZ_STR, "%lu", -1ul );
    PRINTF_TEST( ULLONG_DIG, ULLONG_MAX_DEZ_STR, "%llu", ULLONG_MAX );
    PRINTF_TEST( ULLONG_DIG, ULLONG_MAX_DEZ_STR, "%llu", -1ull );
    PRINTF_TEST( (int)strlen( INT_HEXDIG ) + 1, "F" INT_HEXDIG, "%X", UINT_MAX );
    PRINTF_TEST( (int)strlen( INT_HEXDIG ) + 3, "0XF" INT_HEXDIG, "%#X", -1u );
    PRINTF_TEST( (int)strlen( INT_HEXDIG ) + 1, "f" INT_hexdig, "%x", UINT_MAX );
    PRINTF_TEST( (int)strlen( INT_HEXDIG ) + 3, "0xf" INT_hexdig, "%#x", -1u );
    PRINTF_TEST( (int)strlen( INT_OCTDIG ), INT_OCTDIG, "%o", UINT_MAX );
    PRINTF_TEST( (int)strlen( INT_OCTDIG ) + 1, "0" INT_OCTDIG, "%#o", -1u );
#if 0
    /* TODO: This test case is broken, doesn't test what it was intended to. */
    PRINTF_TEST( 5, "%.0#o", "%.0#o", 0 );
#endif
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%+d", INT_MIN );
    PRINTF_TEST( INT_DIG + 1, "+" INT_MAX_DEZ_STR, "%+d", INT_MAX );
    PRINTF_TEST( 2, "+0", "%+d", 0 );
    PRINTF_TEST( UINT_DIG, UINT_MAX_DEZ_STR, "%+u", UINT_MAX );
    PRINTF_TEST( UINT_DIG, UINT_MAX_DEZ_STR, "%+u", -1u );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "% d", INT_MIN );
    PRINTF_TEST( INT_DIG + 1, " " INT_MAX_DEZ_STR, "% d", INT_MAX );
    PRINTF_TEST( 2, " 0", "% d", 0 );
    PRINTF_TEST( UINT_DIG, UINT_MAX_DEZ_STR, "% u", UINT_MAX );
    PRINTF_TEST( UINT_DIG, UINT_MAX_DEZ_STR, "% u", -1u );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%" INT_DIG_LESS1 "d", INT_MIN );
    PRINTF_TEST( INT_DIG, INT_MAX_DEZ_STR, "%" INT_DIG_LESS1 "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%" sym2s(INT_DIG) "d", INT_MIN );
    PRINTF_TEST( INT_DIG, INT_MAX_DEZ_STR, "%" sym2s(INT_DIG) "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%" INT_DIG_PLUS1 "d", INT_MIN );
    PRINTF_TEST( INT_DIG + 1, " " INT_MAX_DEZ_STR, "%" INT_DIG_PLUS1 "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 2, " -" INT_MIN_DEZ_STR, "%" INT_DIG_PLUS2 "d", INT_MIN );
    PRINTF_TEST( INT_DIG + 2, "  " INT_MAX_DEZ_STR, "%" INT_DIG_PLUS2 "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%-" INT_DIG_LESS1 "d", INT_MIN );
    PRINTF_TEST( INT_DIG, INT_MAX_DEZ_STR, "%-" INT_DIG_LESS1 "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%-" sym2s(INT_DIG) "d", INT_MIN );
    PRINTF_TEST( INT_DIG, INT_MAX_DEZ_STR, "%-" sym2s(INT_DIG) "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%-" INT_DIG_PLUS1 "d", INT_MIN );
    PRINTF_TEST( INT_DIG + 1, INT_MAX_DEZ_STR " ", "%-" INT_DIG_PLUS1 "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 2, "-" INT_MIN_DEZ_STR " ", "%-" INT_DIG_PLUS2 "d", INT_MIN );
    PRINTF_TEST( INT_DIG + 2, INT_MAX_DEZ_STR "  ", "%-" INT_DIG_PLUS2 "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%0" INT_DIG_LESS1 "d", INT_MIN );
    PRINTF_TEST( INT_DIG, INT_MAX_DEZ_STR, "%0" INT_DIG_LESS1 "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%0" sym2s(INT_DIG) "d", INT_MIN );
    PRINTF_TEST( INT_DIG, INT_MAX_DEZ_STR, "%0" sym2s(INT_DIG) "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%0" INT_DIG_PLUS1 "d", INT_MIN );
    PRINTF_TEST( INT_DIG + 1, "0" INT_MAX_DEZ_STR, "%0" INT_DIG_PLUS1 "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 2, "-0" INT_MIN_DEZ_STR, "%0" INT_DIG_PLUS2 "d", INT_MIN );
    PRINTF_TEST( INT_DIG + 2, "00" INT_MAX_DEZ_STR, "%0" INT_DIG_PLUS2 "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%-0" INT_DIG_LESS1 "d", INT_MIN );
    PRINTF_TEST( INT_DIG, INT_MAX_DEZ_STR, "%-0" INT_DIG_LESS1 "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%-0" sym2s(INT_DIG) "d", INT_MIN );
    PRINTF_TEST( INT_DIG, INT_MAX_DEZ_STR, "%-0" sym2s(INT_DIG) "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%-0" INT_DIG_PLUS1 "d", INT_MIN );
    PRINTF_TEST( INT_DIG + 1, INT_MAX_DEZ_STR " ", "%-0" INT_DIG_PLUS1 "d", INT_MAX );
    PRINTF_TEST( INT_DIG + 2, "-" INT_MIN_DEZ_STR " ", "%-0" INT_DIG_PLUS2 "d", INT_MIN );
    PRINTF_TEST( INT_DIG + 2, INT_MAX_DEZ_STR "  ", "%-0" INT_DIG_PLUS2 "d", INT_MAX );
    /* FIXME: This test not yet 32/64 bit agnostic */
    PRINTF_TEST( 30, "          00000000002147483647", "%030.20d", INT_MAX );
    PRINTF_TEST( (int)strlen( INT_HEXDIG ) + 1, "f" INT_hexdig, "%.6x", UINT_MAX );
    PRINTF_TEST( (int)strlen( INT_HEXDIG ) + 3, "0xf" INT_hexdig, "%#6.3x", UINT_MAX );
    PRINTF_TEST( (int)strlen( INT_HEXDIG ) + 3, "0xf" INT_hexdig, "%#3.6x", UINT_MAX );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%.6d", INT_MIN );
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%6.3d", INT_MIN );
    PRINTF_TEST( INT_DIG + 1., "-" INT_MIN_DEZ_STR, "%3.6d", INT_MIN );
    PRINTF_TEST( UINT_DIG, "0xf" INT_hexdig, "%#0.6x", UINT_MAX );
    PRINTF_TEST( UINT_DIG, "0xf" INT_hexdig, "%#06.3x", UINT_MAX );
    PRINTF_TEST( UINT_DIG, "0xf" INT_hexdig, "%#03.6x", UINT_MAX );
    PRINTF_TEST( INT_DIG, INT_MAX_DEZ_STR, "%#0.6d", INT_MAX );
    PRINTF_TEST( INT_DIG, INT_MAX_DEZ_STR, "%#06.3d", INT_MAX );
    PRINTF_TEST( INT_DIG, INT_MAX_DEZ_STR, "%#03.6d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "+" INT_MAX_DEZ_STR, "%#+.6d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "+" INT_MAX_DEZ_STR, "%#+6.3d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "+" INT_MAX_DEZ_STR, "%#+3.6d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "+" INT_MAX_DEZ_STR, "%+0.6d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "+" INT_MAX_DEZ_STR, "%+06.3d", INT_MAX );
    PRINTF_TEST( INT_DIG + 1, "+" INT_MAX_DEZ_STR, "%+03.6d", INT_MAX );
#ifndef TEST_CONVERSION_ONLY
    PRINTF_TEST( INT_DIG + 2, "- " INT_MAX_DEZ_STR, "- %d", INT_MAX );
    PRINTF_TEST( INT_DIG * 2 + 6, "- " INT_MAX_DEZ_STR " % -" INT_MIN_DEZ_STR, "- %d %% %d", INT_MAX, INT_MIN );
#endif
    PRINTF_TEST( 1, "x", "%c", 'x' );
    PRINTF_TEST( 6, "abcdef", "%s", "abcdef" );
    /* FIXME: This test not yet 32/64 bit agnostic */
    PRINTF_TEST( 10, "0xdeadbeef", "%p", (void *)0xdeadbeef );
    PRINTF_TEST( 6, "   0x1", "%#6x", 1 );
#ifndef TEST_CONVERSION_ONLY
    {
        int val1, val2;
        PRINTF_TEST( 9, "123456789", "123456%n789%n", &val1, &val2 );
        TESTCASE( val1 == 6 );
        TESTCASE( val2 == 9 );
    }
#endif
    }
