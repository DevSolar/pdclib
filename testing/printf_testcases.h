    {
#if CHAR_MIN == -128
    assert(CHAR_MIN == -128);
    PRINTF_TEST( 4,   "-128", "%hhd", CHAR_MIN );
    assert(CHAR_MAX == 127);
    PRINTF_TEST( 3,    "127", "%hhd", CHAR_MAX );
#else
    assert(CHAR_MIN == 0);
    PRINTF_TEST( 1,   "0", "%hhd", CHAR_MIN );
    assert(CHAR_MAX == 255);
    PRINTF_TEST( 3,    "255", "%hhd", CHAR_MAX );
#endif
    PRINTF_TEST( 1,      "0", "%hhd", 0 );
    assert(SHRT_MIN == -32768);
    PRINTF_TEST( 6, "-32768",  "%hd", SHRT_MIN );
    assert(SHRT_MAX == 32767);
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
    PRINTF_TEST( INT_DIG + 1, "-" INT_MIN_DEZ_STR, "%3.6d", INT_MIN );
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
    /* PDCLIB-20: Verify "unusual" combinations of length and signedness */
    PRINTF_TEST( 1,  "1", "%tu", (ptrdiff_t)  1); // unsigned prtdiff_t
    PRINTF_TEST( 2, "-1", "%jd", (intmax_t)  -1); // intmax_t
    PRINTF_TEST( 1,  "1", "%ju", (uintmax_t)  1); // uintmax_t
    PRINTF_TEST( 1,  "1", "%zd", (size_t)     1); // signed size_t

/******************************************************************************
 * NOTE: The following test cases are imported from the Tyndur project. They  *
 *       are therefore under the license of said project, not CC0.            *
 *       As said code comprises test cases, it does not form part of the      *
 *       final compiled library, and has no bearing on its licensing.         *
 *                                                                            *
 *       See bug PDCLIB-6 for full details                                    *
 ******************************************************************************/
/*
 * Copyright (c) 2011 The tyndur Project. All rights reserved.
 *
 * This code is derived from software contributed to the tyndur Project
 * by Kevin Wolf.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
    {
#ifndef TEST_CONVERSION_ONLY
    /* Ein String ohne alles */
    PRINTF_TEST(12, "Hallo heimur", "Hallo heimur");
#endif
    /* Einfache Konvertierungen */
    PRINTF_TEST(12, "Hallo heimur", "%s", "Hallo heimur");
    PRINTF_TEST(4, "1024", "%d", 1024);
    PRINTF_TEST(5, "-1024", "%d", -1024);
    PRINTF_TEST(4, "1024", "%i", 1024);
    PRINTF_TEST(5, "-1024", "%i", -1024);
    PRINTF_TEST(4, "1024", "%u", 1024u);
    PRINTF_TEST(10, "4294966272", "%u", -1024u);
    PRINTF_TEST(3, "777", "%o", 0777u);
    PRINTF_TEST(11, "37777777001", "%o", -0777u);
    PRINTF_TEST(8, "1234abcd", "%x", 0x1234abcdu);
    PRINTF_TEST(8, "edcb5433", "%x", -0x1234abcdu);
    PRINTF_TEST(8, "1234ABCD", "%X", 0x1234abcdu);
    PRINTF_TEST(8, "EDCB5433", "%X", -0x1234abcdu);
    PRINTF_TEST(1, "x", "%c", 'x');
    PRINTF_TEST(1, "%", "%%");
    /* Mit %c kann man auch Nullbytes ausgeben */
    PRINTF_TEST(1, "\0", "%c", '\0');
    /* Vorzeichen erzwingen (Flag +) */
    PRINTF_TEST(12, "Hallo heimur", "%+s", "Hallo heimur");
    PRINTF_TEST(5, "+1024", "%+d", 1024);
    PRINTF_TEST(5, "-1024", "%+d", -1024);
    PRINTF_TEST(5, "+1024", "%+i", 1024);
    PRINTF_TEST(5, "-1024", "%+i", -1024);
    PRINTF_TEST(4, "1024", "%+u", 1024u);
    PRINTF_TEST(10, "4294966272", "%+u", -1024u);
    PRINTF_TEST(3, "777", "%+o", 0777u);
    PRINTF_TEST(11, "37777777001", "%+o", -0777u);
    PRINTF_TEST(8, "1234abcd", "%+x", 0x1234abcdu);
    PRINTF_TEST(8, "edcb5433", "%+x", -0x1234abcdu);
    PRINTF_TEST(8, "1234ABCD", "%+X", 0x1234abcdu);
    PRINTF_TEST(8, "EDCB5433", "%+X", -0x1234abcdu);
    PRINTF_TEST(1, "x", "%+c", 'x');
    /* Vorzeichenplatzhalter erzwingen (Flag <space>) */
    PRINTF_TEST(12, "Hallo heimur", "% s", "Hallo heimur");
    PRINTF_TEST(5, " 1024", "% d", 1024);
    PRINTF_TEST(5, "-1024", "% d", -1024);
    PRINTF_TEST(5, " 1024", "% i", 1024);
    PRINTF_TEST(5, "-1024", "% i", -1024);
    PRINTF_TEST(4, "1024", "% u", 1024u);
    PRINTF_TEST(10, "4294966272", "% u", -1024u);
    PRINTF_TEST(3, "777", "% o", 0777u);
    PRINTF_TEST(11, "37777777001", "% o", -0777u);
    PRINTF_TEST(8, "1234abcd", "% x", 0x1234abcdu);
    PRINTF_TEST(8, "edcb5433", "% x", -0x1234abcdu);
    PRINTF_TEST(8, "1234ABCD", "% X", 0x1234abcdu);
    PRINTF_TEST(8, "EDCB5433", "% X", -0x1234abcdu);
    PRINTF_TEST(1, "x", "% c", 'x');
    /* Flag + hat Vorrang über <space> */
    PRINTF_TEST(12, "Hallo heimur", "%+ s", "Hallo heimur");
    PRINTF_TEST(5, "+1024", "%+ d", 1024);
    PRINTF_TEST(5, "-1024", "%+ d", -1024);
    PRINTF_TEST(5, "+1024", "%+ i", 1024);
    PRINTF_TEST(5, "-1024", "%+ i", -1024);
    PRINTF_TEST(4, "1024", "%+ u", 1024u);
    PRINTF_TEST(10, "4294966272", "%+ u", -1024u);
    PRINTF_TEST(3, "777", "%+ o", 0777u);
    PRINTF_TEST(11, "37777777001", "%+ o", -0777u);
    PRINTF_TEST(8, "1234abcd", "%+ x", 0x1234abcdu);
    PRINTF_TEST(8, "edcb5433", "%+ x", -0x1234abcdu);
    PRINTF_TEST(8, "1234ABCD", "%+ X", 0x1234abcdu);
    PRINTF_TEST(8, "EDCB5433", "%+ X", -0x1234abcdu);
    PRINTF_TEST(1, "x", "%+ c", 'x');
    /* Alternative Form */
    PRINTF_TEST(4, "0777", "%#o", 0777u);
    PRINTF_TEST(12, "037777777001", "%#o", -0777u);
    PRINTF_TEST(10, "0x1234abcd", "%#x", 0x1234abcdu);
    PRINTF_TEST(10, "0xedcb5433", "%#x", -0x1234abcdu);
    PRINTF_TEST(10, "0X1234ABCD", "%#X", 0x1234abcdu);
    PRINTF_TEST(10, "0XEDCB5433", "%#X", -0x1234abcdu);
    PRINTF_TEST(1, "0", "%#o", 0u);
    PRINTF_TEST(1, "0", "%#x", 0u);
    PRINTF_TEST(1, "0", "%#X", 0u);
    /* Feldbreite: Kleiner als Ausgabe */
    PRINTF_TEST(12, "Hallo heimur", "%1s", "Hallo heimur");
    PRINTF_TEST(4, "1024", "%1d", 1024);
    PRINTF_TEST(5, "-1024", "%1d", -1024);
    PRINTF_TEST(4, "1024", "%1i", 1024);
    PRINTF_TEST(5, "-1024", "%1i", -1024);
    PRINTF_TEST(4, "1024", "%1u", 1024u);
    PRINTF_TEST(10, "4294966272", "%1u", -1024u);
    PRINTF_TEST(3, "777", "%1o", 0777u);
    PRINTF_TEST(11, "37777777001", "%1o", -0777u);
    PRINTF_TEST(8, "1234abcd", "%1x", 0x1234abcdu);
    PRINTF_TEST(8, "edcb5433", "%1x", -0x1234abcdu);
    PRINTF_TEST(8, "1234ABCD", "%1X", 0x1234abcdu);
    PRINTF_TEST(8, "EDCB5433", "%1X", -0x1234abcdu);
    PRINTF_TEST(1, "x", "%1c", 'x');
    /* Feldbreite: Größer als Ausgabe */
    PRINTF_TEST(20, "               Hallo", "%20s", "Hallo");
    PRINTF_TEST(20, "                1024", "%20d", 1024);
    PRINTF_TEST(20, "               -1024", "%20d", -1024);
    PRINTF_TEST(20, "                1024", "%20i", 1024);
    PRINTF_TEST(20, "               -1024", "%20i", -1024);
    PRINTF_TEST(20, "                1024", "%20u", 1024u);
    PRINTF_TEST(20, "          4294966272", "%20u", -1024u);
    PRINTF_TEST(20, "                 777", "%20o", 0777u);
    PRINTF_TEST(20, "         37777777001", "%20o", -0777u);
    PRINTF_TEST(20, "            1234abcd", "%20x", 0x1234abcdu);
    PRINTF_TEST(20, "            edcb5433", "%20x", -0x1234abcdu);
    PRINTF_TEST(20, "            1234ABCD", "%20X", 0x1234abcdu);
    PRINTF_TEST(20, "            EDCB5433", "%20X", -0x1234abcdu);
    PRINTF_TEST(20, "                   x", "%20c", 'x');
    /* Feldbreite: Linksbündig */
    PRINTF_TEST(20, "Hallo               ", "%-20s", "Hallo");
    PRINTF_TEST(20, "1024                ", "%-20d", 1024);
    PRINTF_TEST(20, "-1024               ", "%-20d", -1024);
    PRINTF_TEST(20, "1024                ", "%-20i", 1024);
    PRINTF_TEST(20, "-1024               ", "%-20i", -1024);
    PRINTF_TEST(20, "1024                ", "%-20u", 1024u);
    PRINTF_TEST(20, "4294966272          ", "%-20u", -1024u);
    PRINTF_TEST(20, "777                 ", "%-20o", 0777u);
    PRINTF_TEST(20, "37777777001         ", "%-20o", -0777u);
    PRINTF_TEST(20, "1234abcd            ", "%-20x", 0x1234abcdu);
    PRINTF_TEST(20, "edcb5433            ", "%-20x", -0x1234abcdu);
    PRINTF_TEST(20, "1234ABCD            ", "%-20X", 0x1234abcdu);
    PRINTF_TEST(20, "EDCB5433            ", "%-20X", -0x1234abcdu);
    PRINTF_TEST(20, "x                   ", "%-20c", 'x');
    /* Feldbreite: Padding mit 0 */
    PRINTF_TEST(20, "00000000000000001024", "%020d", 1024);
    PRINTF_TEST(20, "-0000000000000001024", "%020d", -1024);
    PRINTF_TEST(20, "00000000000000001024", "%020i", 1024);
    PRINTF_TEST(20, "-0000000000000001024", "%020i", -1024);
    PRINTF_TEST(20, "00000000000000001024", "%020u", 1024u);
    PRINTF_TEST(20, "00000000004294966272", "%020u", -1024u);
    PRINTF_TEST(20, "00000000000000000777", "%020o", 0777u);
    PRINTF_TEST(20, "00000000037777777001", "%020o", -0777u);
    PRINTF_TEST(20, "0000000000001234abcd", "%020x", 0x1234abcdu);
    PRINTF_TEST(20, "000000000000edcb5433", "%020x", -0x1234abcdu);
    PRINTF_TEST(20, "0000000000001234ABCD", "%020X", 0x1234abcdu);
    PRINTF_TEST(20, "000000000000EDCB5433", "%020X", -0x1234abcdu);
    /* Feldbreite: Padding und alternative Form */
    PRINTF_TEST(20, "                0777", "%#20o", 0777u);
    PRINTF_TEST(20, "        037777777001", "%#20o", -0777u);
    PRINTF_TEST(20, "          0x1234abcd", "%#20x", 0x1234abcdu);
    PRINTF_TEST(20, "          0xedcb5433", "%#20x", -0x1234abcdu);
    PRINTF_TEST(20, "          0X1234ABCD", "%#20X", 0x1234abcdu);
    PRINTF_TEST(20, "          0XEDCB5433", "%#20X", -0x1234abcdu);
    PRINTF_TEST(20, "00000000000000000777", "%#020o", 0777u);
    PRINTF_TEST(20, "00000000037777777001", "%#020o", -0777u);
    PRINTF_TEST(20, "0x00000000001234abcd", "%#020x", 0x1234abcdu);
    PRINTF_TEST(20, "0x0000000000edcb5433", "%#020x", -0x1234abcdu);
    PRINTF_TEST(20, "0X00000000001234ABCD", "%#020X", 0x1234abcdu);
    PRINTF_TEST(20, "0X0000000000EDCB5433", "%#020X", -0x1234abcdu);
    /* Feldbreite: - hat Vorrang vor 0 */
    PRINTF_TEST(20, "Hallo               ", "%0-20s", "Hallo");
    PRINTF_TEST(20, "1024                ", "%0-20d", 1024);
    PRINTF_TEST(20, "-1024               ", "%0-20d", -1024);
    PRINTF_TEST(20, "1024                ", "%0-20i", 1024);
    PRINTF_TEST(20, "-1024               ", "%0-20i", -1024);
    PRINTF_TEST(20, "1024                ", "%0-20u", 1024u);
    PRINTF_TEST(20, "4294966272          ", "%0-20u", -1024u);
    PRINTF_TEST(20, "777                 ", "%-020o", 0777u);
    PRINTF_TEST(20, "37777777001         ", "%-020o", -0777u);
    PRINTF_TEST(20, "1234abcd            ", "%-020x", 0x1234abcdu);
    PRINTF_TEST(20, "edcb5433            ", "%-020x", -0x1234abcdu);
    PRINTF_TEST(20, "1234ABCD            ", "%-020X", 0x1234abcdu);
    PRINTF_TEST(20, "EDCB5433            ", "%-020X", -0x1234abcdu);
    PRINTF_TEST(20, "x                   ", "%-020c", 'x');
    /* Feldbreite: Aus Parameter */
    PRINTF_TEST(20, "               Hallo", "%*s", 20, "Hallo");
    PRINTF_TEST(20, "                1024", "%*d", 20, 1024);
    PRINTF_TEST(20, "               -1024", "%*d", 20, -1024);
    PRINTF_TEST(20, "                1024", "%*i", 20, 1024);
    PRINTF_TEST(20, "               -1024", "%*i", 20, -1024);
    PRINTF_TEST(20, "                1024", "%*u", 20, 1024u);
    PRINTF_TEST(20, "          4294966272", "%*u", 20, -1024u);
    PRINTF_TEST(20, "                 777", "%*o", 20, 0777u);
    PRINTF_TEST(20, "         37777777001", "%*o", 20, -0777u);
    PRINTF_TEST(20, "            1234abcd", "%*x", 20, 0x1234abcdu);
    PRINTF_TEST(20, "            edcb5433", "%*x", 20, -0x1234abcdu);
    PRINTF_TEST(20, "            1234ABCD", "%*X", 20, 0x1234abcdu);
    PRINTF_TEST(20, "            EDCB5433", "%*X", 20, -0x1234abcdu);
    PRINTF_TEST(20, "                   x", "%*c", 20, 'x');
    /* Präzision / Mindestanzahl von Ziffern */
    PRINTF_TEST(12, "Hallo heimur", "%.20s", "Hallo heimur");
    PRINTF_TEST(20, "00000000000000001024", "%.20d", 1024);
    PRINTF_TEST(21, "-00000000000000001024", "%.20d", -1024);
    PRINTF_TEST(20, "00000000000000001024", "%.20i", 1024);
    PRINTF_TEST(21, "-00000000000000001024", "%.20i", -1024);
    PRINTF_TEST(20, "00000000000000001024", "%.20u", 1024u);
    PRINTF_TEST(20, "00000000004294966272", "%.20u", -1024u);
    PRINTF_TEST(20, "00000000000000000777", "%.20o", 0777u);
    PRINTF_TEST(20, "00000000037777777001", "%.20o", -0777u);
    PRINTF_TEST(20, "0000000000001234abcd", "%.20x", 0x1234abcdu);
    PRINTF_TEST(20, "000000000000edcb5433", "%.20x", -0x1234abcdu);
    PRINTF_TEST(20, "0000000000001234ABCD", "%.20X", 0x1234abcdu);
    PRINTF_TEST(20, "000000000000EDCB5433", "%.20X", -0x1234abcdu);
    /* Feldbreite und Präzision */
    PRINTF_TEST(20, "               Hallo", "%20.5s", "Hallo heimur");
    PRINTF_TEST(20, "               01024", "%20.5d", 1024);
    PRINTF_TEST(20, "              -01024", "%20.5d", -1024);
    PRINTF_TEST(20, "               01024", "%20.5i", 1024);
    PRINTF_TEST(20, "              -01024", "%20.5i", -1024);
    PRINTF_TEST(20, "               01024", "%20.5u", 1024u);
    PRINTF_TEST(20, "          4294966272", "%20.5u", -1024u);
    PRINTF_TEST(20, "               00777", "%20.5o", 0777u);
    PRINTF_TEST(20, "         37777777001", "%20.5o", -0777u);
    PRINTF_TEST(20, "            1234abcd", "%20.5x", 0x1234abcdu);
    PRINTF_TEST(20, "          00edcb5433", "%20.10x", -0x1234abcdu);
    PRINTF_TEST(20, "            1234ABCD", "%20.5X", 0x1234abcdu);
    PRINTF_TEST(20, "          00EDCB5433", "%20.10X", -0x1234abcdu);
    /* Präzision: 0 wird ignoriert */
    PRINTF_TEST(20, "               Hallo", "%020.5s", "Hallo heimur");
    PRINTF_TEST(20, "               01024", "%020.5d", 1024);
    PRINTF_TEST(20, "              -01024", "%020.5d", -1024);
    PRINTF_TEST(20, "               01024", "%020.5i", 1024);
    PRINTF_TEST(20, "              -01024", "%020.5i", -1024);
    PRINTF_TEST(20, "               01024", "%020.5u", 1024u);
    PRINTF_TEST(20, "          4294966272", "%020.5u", -1024u);
    PRINTF_TEST(20, "               00777", "%020.5o", 0777u);
    PRINTF_TEST(20, "         37777777001", "%020.5o", -0777u);
    PRINTF_TEST(20, "            1234abcd", "%020.5x", 0x1234abcdu);
    PRINTF_TEST(20, "          00edcb5433", "%020.10x", -0x1234abcdu);
    PRINTF_TEST(20, "            1234ABCD", "%020.5X", 0x1234abcdu);
    PRINTF_TEST(20, "          00EDCB5433", "%020.10X", -0x1234abcdu);
    /* Präzision 0 */
    PRINTF_TEST(0, "", "%.0s", "Hallo heimur");
    PRINTF_TEST(20, "                    ", "%20.0s", "Hallo heimur");
    PRINTF_TEST(0, "", "%.s", "Hallo heimur");
    PRINTF_TEST(20, "                    ", "%20.s", "Hallo heimur");
    PRINTF_TEST(20, "                1024", "%20.0d", 1024);
    PRINTF_TEST(20, "               -1024", "%20.d", -1024);
    PRINTF_TEST(20, "                    ", "%20.d", 0);
    PRINTF_TEST(20, "                1024", "%20.0i", 1024);
    PRINTF_TEST(20, "               -1024", "%20.i", -1024);
    PRINTF_TEST(20, "                    ", "%20.i", 0);
    PRINTF_TEST(20, "                1024", "%20.u", 1024u);
    PRINTF_TEST(20, "          4294966272", "%20.0u", -1024u);
    PRINTF_TEST(20, "                    ", "%20.u", 0u);
    PRINTF_TEST(20, "                 777", "%20.o", 0777u);
    PRINTF_TEST(20, "         37777777001", "%20.0o", -0777u);
    PRINTF_TEST(20, "                    ", "%20.o", 0u);
    PRINTF_TEST(20, "            1234abcd", "%20.x", 0x1234abcdu);
    PRINTF_TEST(20, "            edcb5433", "%20.0x", -0x1234abcdu);
    PRINTF_TEST(20, "                    ", "%20.x", 0u);
    PRINTF_TEST(20, "            1234ABCD", "%20.X", 0x1234abcdu);
    PRINTF_TEST(20, "            EDCB5433", "%20.0X", -0x1234abcdu);
    PRINTF_TEST(20, "                    ", "%20.X", 0u);
    /* Negative Präzision wird ignoriert */
    /* XXX glibc tut nicht, was ich erwartet habe, vorerst deaktiviert... */
    /*
     * Präzision und Feldbreite aus Parameter.
     * + hat Vorrang vor <space>, - hat Vorrang vor 0 (das eh ignoriert wird,
     * weil eine Präzision angegeben ist)
     */
    PRINTF_TEST(20, "Hallo               ", "% -0+*.*s", 20, 5, "Hallo heimur");
    PRINTF_TEST(20, "+01024              ", "% -0+*.*d", 20, 5, 1024);
    PRINTF_TEST(20, "-01024              ", "% -0+*.*d", 20, 5, -1024);
    PRINTF_TEST(20, "+01024              ", "% -0+*.*i", 20, 5, 1024);
    PRINTF_TEST(20, "-01024              ", "% 0-+*.*i", 20, 5, -1024);
    PRINTF_TEST(20, "01024               ", "% 0-+*.*u", 20, 5, 1024u);
    PRINTF_TEST(20, "4294966272          ", "% 0-+*.*u", 20, 5, -1024u);
    PRINTF_TEST(20, "00777               ", "%+ -0*.*o", 20, 5, 0777u);
    PRINTF_TEST(20, "37777777001         ", "%+ -0*.*o", 20, 5, -0777u);
    PRINTF_TEST(20, "1234abcd            ", "%+ -0*.*x", 20, 5, 0x1234abcdu);
    PRINTF_TEST(20, "00edcb5433          ", "%+ -0*.*x", 20, 10, -0x1234abcdu);
    PRINTF_TEST(20, "1234ABCD            ", "% -+0*.*X", 20, 5, 0x1234abcdu);
    PRINTF_TEST(20, "00EDCB5433          ", "% -+0*.*X", 20, 10, -0x1234abcdu);
    }
/******************************************************************************/
