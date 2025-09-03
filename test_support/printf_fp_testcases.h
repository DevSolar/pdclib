    {
#if __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif
    /* Floating Point */
    /* Hex - Double */
    PRINTF_TEST( 6, "0x0p+0", "%a", 0.0 );
    PRINTF_TEST( 7, "+0x0p+0", "%+a", 0.0 );
    PRINTF_TEST( 7, " 0x0p+0", "% a", 0.0 );
    PRINTF_TEST( 6, "0x1p+2", "%a", 4.0 );
    PRINTF_TEST( 6, "0x1p-2", "%a", 0.25 );
    PRINTF_TEST( 7, "-0x1p+0", "%a", -1.0 );
    PRINTF_TEST( 23, "0x1.fffffffffffffp+1023", "%a", DBL_MAX );
    PRINTF_TEST( 9, "0x1p-1022", "%a", DBL_MIN );
#if defined( REGTEST ) && defined( __CYGWIN__ )
    /* Cygwin's BSD libc normalizes denormals. Other libc's do not. */
    PRINTF_TEST( 9, "0x1p-1074", "%a", 0x0.0000000000002p-1023 );
#else
    PRINTF_TEST( 23, "0x0.0000000000001p-1022", "%a", 0x0.0000000000002p-1023 );
#endif
    PRINTF_TEST( 20, "0x1.0000000000001p+0", "%a", 1.0 + DBL_EPSILON );
    PRINTF_TEST( 8, "  0x0p+0", "% 8a", 0.0 );
    PRINTF_TEST( 8, " 0x0p+0 ", "%- 8a", 0.0 );
    PRINTF_TEST( 8, "0x000p+0", "%08a", 0.0 );
    PRINTF_TEST( 11, "0x2.0000p+0", "%.4a", 1.999998 );
    PRINTF_TEST( 12, "0x1.ffffep+0", "%.5a", 1.999998 );
    PRINTF_TEST( 3, "inf", "%a", 1e500 );
    PRINTF_TEST( 4, "-inf", "%a", -1e500 );
    PRINTF_TEST( 3, "INF", "%A", 1e500 );
    PRINTF_TEST( 4, "-INF", "%A", -1e500 );
    /* Hex - Long Double */
    PRINTF_TEST( 6, "0x0p+0", "%La", 0.0L );
    PRINTF_TEST( 7, "+0x0p+0", "%+La", 0.0L );
    PRINTF_TEST( 7, " 0x0p+0", "% La", 0.0L );
    PRINTF_TEST( 8, "  0x0p+0", "% 8La", 0.0L );
    PRINTF_TEST( 8, " 0x0p+0 ", "%- 8La", 0.0L );
    PRINTF_TEST( 8, "0x000p+0", "%08La", 0.0L );
#if LDBL_MANT_DIG == 64
#if ! defined( REGTEST ) || ( defined( REGTEST ) && defined( __CYGWIN__ ) )
    /* As opposed to glibc, Cygwin's BSD libc does not make use of
       the (allowed) optimization to arrange the integral part of
       the significand in a way that aligns the remaining bits on
       four bit boundaries. Hence, output is normalized differently.
    */
    PRINTF_TEST( 6, "0x1p+2", "%La", 4.0L );
    PRINTF_TEST( 6, "0x1p-2", "%La", 0.25L );
    PRINTF_TEST( 7, "-0x1p+0", "%La", -1.0L );
    PRINTF_TEST( 11, "0x2.0000p+0", "%.4La", 1.999998L );
    PRINTF_TEST( 12, "0x1.ffffep+0", "%.5La", 1.999998L );
#else
    PRINTF_TEST( 6, "0x8p-1", "%La", 4.0L );
    PRINTF_TEST( 6, "0x8p-5", "%La", 0.25L );
    PRINTF_TEST( 7, "-0x8p-3", "%La", -1.0L );
    PRINTF_TEST( 11, "0xf.ffffp-3", "%.4La", 1.999998L );
    PRINTF_TEST( 12, "0xf.fffefp-3", "%.5La", 1.999998L );
#endif
#elif LDBL_MANT_DIG == 113
    PRINTF_TEST( 6, "0x1p+2", "%La", 4.0L );
    PRINTF_TEST( 6, "0x1p-2", "%La", 0.25L );
    PRINTF_TEST( 7, "-0x1p+0", "%La", -1.0L );
    PRINTF_TEST( 8, "0x1.8p+0", "%La", 1.5L );
    PRINTF_TEST( 11, "0x2.0000p+0", "%.4La", 1.999998L );
    PRINTF_TEST( 12, "0x1.ffffep+0", "%.5La", 1.999998L );
#endif
    /* Decimal -- Double */
    PRINTF_TEST( 20, "1230000000000.000000", "%f", 123e10 );
    PRINTF_TEST( 15, "12300000.000000", "%f", 12300000.0 );
    PRINTF_TEST( 11, "1230.000000", "%f", 1230.0 );
    PRINTF_TEST( 10, "123.000000", "%f", 123.0 );
    PRINTF_TEST(  9, "12.300000", "%f", 12.3 );
    PRINTF_TEST(  8, "1.230000", "%f", 1.23 );
    PRINTF_TEST(  8, "0.123000", "%f", 0.123 );
    PRINTF_TEST(  8, "0.012300", "%f", 0.0123 );
    PRINTF_TEST(  8, "0.001230", "%f", 0.00123 );
    PRINTF_TEST(  8, "0.000123", "%f", 0.000123 );
    PRINTF_TEST(  8, "0.000012", "%f", 0.0000123 );
    PRINTF_TEST(  8, "0.000001", "%f", 0.00000123 );
    PRINTF_TEST(  8, "0.000000", "%f", 123e-10 );

    PRINTF_TEST( 17, "1230000000000.000", "%.3f", 123e10 );
    PRINTF_TEST( 12, "12300000.000", "%.3f", 12300000.0 );
    PRINTF_TEST(  8, "1230.000", "%.3f", 1230.0 );
    PRINTF_TEST(  7, "123.000", "%.3f", 123.0 );
    PRINTF_TEST(  6, "12.300", "%.3f", 12.3 );
    PRINTF_TEST(  5, "1.230", "%.3f", 1.23 );
    PRINTF_TEST(  5, "0.123", "%.3f", 0.123 );
    PRINTF_TEST(  5, "0.012", "%.3f", 0.0123 );
    PRINTF_TEST(  5, "0.001", "%.3f", 0.00123 );
    PRINTF_TEST(  5, "0.000", "%.3f", 0.000123 );

    PRINTF_TEST( 13, "1230000000000", "%.0f", 123e10 );
    PRINTF_TEST(  8, "12300000", "%.0f", 12300000.0 );
    PRINTF_TEST(  4, "1230", "%.0f", 1230.0 );
    PRINTF_TEST(  3, "123", "%.0f", 123.0 );
    PRINTF_TEST(  2, "12", "%.0f", 12.3 );
    PRINTF_TEST(  1, "1", "%.0f", 1.23 );
    PRINTF_TEST(  1, "0", "%.0f", 0.123 );

    PRINTF_TEST( 12, "12300000.000", "%12.3f", 12300000.0 );
    PRINTF_TEST( 12, "    1230.000", "%12.3f", 1230.0 );
    PRINTF_TEST( 12, "     123.000", "%12.3f", 123.0 );
    PRINTF_TEST( 12, "      12.300", "%12.3f", 12.3 );
    PRINTF_TEST( 12, "       1.230", "%12.3f", 1.23 );
    PRINTF_TEST( 12, "       0.123", "%12.3f", 0.123 );
    PRINTF_TEST( 12, "       0.012", "%12.3f", 0.0123 );
    PRINTF_TEST( 12, "       0.001", "%12.3f", 0.00123 );
    PRINTF_TEST( 12, "       0.000", "%12.3f", 0.000123 );

    PRINTF_TEST( 12, "12300000.000", "%012.3f", 12300000.0 );
    PRINTF_TEST( 12, "00001230.000", "%012.3f", 1230.0 );
    PRINTF_TEST( 12, "00000123.000", "%012.3f", 123.0 );
    PRINTF_TEST( 12, "00000012.300", "%012.3f", 12.3 );
    PRINTF_TEST( 12, "00000001.230", "%012.3f", 1.23 );
    PRINTF_TEST( 12, "00000000.123", "%012.3f", 0.123 );
    PRINTF_TEST( 12, "00000000.012", "%012.3f", 0.0123 );
    PRINTF_TEST( 12, "00000000.001", "%012.3f", 0.00123 );
    PRINTF_TEST( 12, "00000000.000", "%012.3f", 0.000123 );

    PRINTF_TEST( 12, "12300000.000", "%-12.3f", 12300000.0 );
    PRINTF_TEST( 12, "1230.000    ", "%-12.3f", 1230.0 );
    PRINTF_TEST( 12, "123.000     ", "%-12.3f", 123.0 );
    PRINTF_TEST( 12, "12.300      ", "%-12.3f", 12.3 );
    PRINTF_TEST( 12, "1.230       ", "%-12.3f", 1.23 );
    PRINTF_TEST( 12, "0.123       ", "%-12.3f", 0.123 );
    PRINTF_TEST( 12, "0.012       ", "%-12.3f", 0.0123 );
    PRINTF_TEST( 12, "0.001       ", "%-12.3f", 0.00123 );
    PRINTF_TEST( 12, "0.000       ", "%-12.3f", 0.000123 );

    /* Exponent -- Double */
    PRINTF_TEST( 12, "1.230000e+12", "%e", 123e10 );
    PRINTF_TEST( 12, "1.230000e+07", "%e", 12300000.0 );
    PRINTF_TEST( 12, "1.230000e+03", "%e", 1230.0 );
    PRINTF_TEST( 12, "1.230000e+02", "%e", 123.0 );
    PRINTF_TEST( 12, "1.230000e+01", "%e", 12.3 );
    PRINTF_TEST( 12, "1.230000e+00", "%e", 1.23 );
    PRINTF_TEST( 12, "1.230000e-01", "%e", 0.123 );
    PRINTF_TEST( 12, "1.230000e-02", "%e", 0.0123 );
    PRINTF_TEST( 12, "1.230000e-03", "%e", 0.00123 );
    PRINTF_TEST( 12, "1.230000e-04", "%e", 0.000123 );
    PRINTF_TEST( 12, "1.230000e-05", "%e", 0.0000123 );
    PRINTF_TEST( 12, "1.230000e-06", "%e", 0.00000123 );
    PRINTF_TEST( 12, "1.230000e-08", "%e", 123e-10 );

    PRINTF_TEST(  9, "1.230e+12", "%.3e", 123e10 );
    PRINTF_TEST(  9, "1.230e+07", "%.3e", 12300000.0 );
    PRINTF_TEST(  9, "1.230e+03", "%.3e", 1230.0 );
    PRINTF_TEST(  9, "1.230e+02", "%.3e", 123.0 );
    PRINTF_TEST(  9, "1.230e+01", "%.3e", 12.3 );
    PRINTF_TEST(  9, "1.230e+00", "%.3e", 1.23 );
    PRINTF_TEST(  9, "1.230e-01", "%.3e", 0.123 );
    PRINTF_TEST(  9, "1.230e-02", "%.3e", 0.0123 );
    PRINTF_TEST(  9, "1.230e-03", "%.3e", 0.00123 );
    PRINTF_TEST(  9, "1.230e-04", "%.3e", 0.000123 );
    PRINTF_TEST(  9, "1.230e-05", "%.3e", 0.0000123 );
    PRINTF_TEST(  9, "1.230e-06", "%.3e", 0.00000123 );
    PRINTF_TEST(  9, "1.230e-08", "%.3e", 123e-10 );

    PRINTF_TEST(  5, "1e+12", "%.0e", 123e10 );
    PRINTF_TEST(  5, "1e+07", "%.0e", 12300000.0 );
    PRINTF_TEST(  5, "1e+03", "%.0e", 1230.0 );
    PRINTF_TEST(  5, "1e+02", "%.0e", 123.0 );
    PRINTF_TEST(  5, "1e+01", "%.0e", 12.3 );
    PRINTF_TEST(  5, "1e+00", "%.0e", 1.23 );
    PRINTF_TEST(  5, "1e-01", "%.0e", 0.123 );
    PRINTF_TEST(  5, "1e-02", "%.0e", 0.0123 );
    PRINTF_TEST(  5, "1e-03", "%.0e", 0.00123 );
    PRINTF_TEST(  5, "1e-04", "%.0e", 0.000123 );
    PRINTF_TEST(  5, "1e-05", "%.0e", 0.0000123 );
    PRINTF_TEST(  5, "1e-06", "%.0e", 0.00000123 );
    PRINTF_TEST(  5, "1e-08", "%.0e", 123e-10 );

    PRINTF_TEST( 12, "   1.230e+07", "%12.3e", 12300000.0 );
    PRINTF_TEST( 12, "   1.230e+03", "%12.3e", 1230.0 );
    PRINTF_TEST( 12, "   1.230e+02", "%12.3e", 123.0 );
    PRINTF_TEST( 12, "   1.230e+01", "%12.3e", 12.3 );
    PRINTF_TEST( 12, "   1.230e+00", "%12.3e", 1.23 );
    PRINTF_TEST( 12, "   1.230e-01", "%12.3e", 0.123 );
    PRINTF_TEST( 12, "   1.230e-02", "%12.3e", 0.0123 );
    PRINTF_TEST( 12, "   1.230e-03", "%12.3e", 0.00123 );
    PRINTF_TEST( 12, "   1.230e-04", "%12.3e", 0.000123 );
    PRINTF_TEST( 12, "   1.230e-05", "%12.3e", 0.0000123 );
    PRINTF_TEST( 12, "   1.230e-06", "%12.3e", 0.00000123 );
    PRINTF_TEST( 12, "   1.230e-08", "%12.3e", 123e-10 );

    PRINTF_TEST( 12, "0001.230e+07", "%012.3e", 12300000.0 );
    PRINTF_TEST( 12, "0001.230e+03", "%012.3e", 1230.0 );
    PRINTF_TEST( 12, "0001.230e+02", "%012.3e", 123.0 );
    PRINTF_TEST( 12, "0001.230e+01", "%012.3e", 12.3 );
    PRINTF_TEST( 12, "0001.230e+00", "%012.3e", 1.23 );
    PRINTF_TEST( 12, "0001.230e-01", "%012.3e", 0.123 );
    PRINTF_TEST( 12, "0001.230e-02", "%012.3e", 0.0123 );
    PRINTF_TEST( 12, "0001.230e-03", "%012.3e", 0.00123 );
    PRINTF_TEST( 12, "0001.230e-04", "%012.3e", 0.000123 );
    PRINTF_TEST( 12, "0001.230e-05", "%012.3e", 0.0000123 );
    PRINTF_TEST( 12, "0001.230e-06", "%012.3e", 0.00000123 );
    PRINTF_TEST( 12, "0001.230e-08", "%012.3e", 123e-10 );

    PRINTF_TEST( 12, "1.230e+07   ", "%-12.3e", 12300000.0 );
    PRINTF_TEST( 12, "1.230e+03   ", "%-12.3e", 1230.0 );
    PRINTF_TEST( 12, "1.230e+02   ", "%-12.3e", 123.0 );
    PRINTF_TEST( 12, "1.230e+01   ", "%-12.3e", 12.3 );
    PRINTF_TEST( 12, "1.230e+00   ", "%-12.3e", 1.23 );
    PRINTF_TEST( 12, "1.230e-01   ", "%-12.3e", 0.123 );
    PRINTF_TEST( 12, "1.230e-02   ", "%-12.3e", 0.0123 );
    PRINTF_TEST( 12, "1.230e-03   ", "%-12.3e", 0.00123 );
    PRINTF_TEST( 12, "1.230e-04   ", "%-12.3e", 0.000123 );
    PRINTF_TEST( 12, "1.230e-05   ", "%-12.3e", 0.0000123 );
    PRINTF_TEST( 12, "1.230e-06   ", "%-12.3e", 0.00000123 );
    PRINTF_TEST( 12, "1.230e-08   ", "%-12.3e", 123e-10 );

    /* Generic -- Double */
    /*
    PRINTF_TEST(  8, "1.23e+12", "%g", 123e10 );
    PRINTF_TEST(  8, "1.23e+07", "%g", 12300000.0 );
    PRINTF_TEST(  4, "1230", "%g", 1230.0 );
    PRINTF_TEST(  3, "123", "%g", 123.0 );
    PRINTF_TEST(  4, "12.3", "%g", 12.3 );
    PRINTF_TEST(  4, "1.23", "%g", 1.23 );
    PRINTF_TEST(  5, "0.123", "%g", 0.123 );
    PRINTF_TEST(  6, "0.0123", "%g", 0.0123 );
    PRINTF_TEST(  7, "0.00123", "%g", 0.00123 );
    PRINTF_TEST(  8, "0.000123", "%g", 0.000123 );
    PRINTF_TEST(  8, "1.23e-05", "%g", 0.0000123 );
    PRINTF_TEST(  8, "1.23e-06", "%g", 0.00000123 );
    PRINTF_TEST(  8, "1.23e-08", "%g", 123e-10 );

    PRINTF_TEST(  8, "1.23e+12", "%.3g", 123e10 );
    PRINTF_TEST(  8, "1.23e+07", "%.3g", 12300000.0 );
    PRINTF_TEST(  8, "1.23e+03", "%.3g", 1230.0 );
    PRINTF_TEST(  3, "123", "%.3g", 123.0 );
    PRINTF_TEST(  4, "12.3", "%.3g", 12.3 );
    PRINTF_TEST(  4, "1.23", "%.3g", 1.23 );
    PRINTF_TEST(  5, "0.123", "%.3g", 0.123 );
    PRINTF_TEST(  6, "0.0123", "%.3g", 0.0123 );
    PRINTF_TEST(  7, "0.00123", "%.3g", 0.00123 );
    PRINTF_TEST(  8, "0.000123", "%.3g", 0.000123 );
    PRINTF_TEST(  8, "1.23e-05", "%.3g", 0.0000123 );
    PRINTF_TEST(  8, "1.23e-06", "%.3g", 0.00000123 );
    PRINTF_TEST(  8, "1.23e-08", "%.3g", 123e-10 );

    PRINTF_TEST(  5, "1e+12", "%.0g", 123e10 );
    PRINTF_TEST(  5, "1e+07", "%.0g", 12300000.0 );
    PRINTF_TEST(  5, "1e+03", "%.0g", 1230.0 );
    PRINTF_TEST(  5, "1e+02", "%.0g", 123.0 );
    PRINTF_TEST(  5, "1e+01", "%.0g", 12.3 );
    PRINTF_TEST(  1, "1", "%.0g", 1.23 );
    PRINTF_TEST(  3, "0.1", "%.0g", 0.123 );
    PRINTF_TEST(  4, "0.01", "%.0g", 0.0123 );
    PRINTF_TEST(  5, "0.001", "%.0g", 0.00123 );
    PRINTF_TEST(  6, "0.0001", "%.0g", 0.000123 );
    PRINTF_TEST(  5, "1e-05", "%.0g", 0.0000123 );
    PRINTF_TEST(  5, "1e-06", "%.0g", 0.00000123 );
    PRINTF_TEST(  5, "1e-08", "%.0g", 123e-10 );

    PRINTF_TEST( 12, "    1.23e+07", "%12.3g", 12300000.0 );
    PRINTF_TEST( 12, "    1.23e+03", "%12.3g", 1230.0 );
    PRINTF_TEST( 12, "         123", "%12.3g", 123.0 );
    PRINTF_TEST( 12, "        12.3", "%12.3g", 12.3 );
    PRINTF_TEST( 12, "        1.23", "%12.3g", 1.23 );
    PRINTF_TEST( 12, "       0.123", "%12.3g", 0.123 );
    PRINTF_TEST( 12, "      0.0123", "%12.3g", 0.0123 );
    PRINTF_TEST( 12, "     0.00123", "%12.3g", 0.00123 );
    PRINTF_TEST( 12, "    0.000123", "%12.3g", 0.000123 );
    PRINTF_TEST( 12, "    1.23e-05", "%12.3g", 0.0000123 );
    PRINTF_TEST( 12, "    1.23e-06", "%12.3g", 0.00000123 );
    PRINTF_TEST( 12, "    1.23e-08", "%12.3g", 123e-10 );

    PRINTF_TEST( 12, "00001.23e+07", "%012.3g", 12300000.0 );
    PRINTF_TEST( 12, "00001.23e+03", "%012.3g", 1230.0 );
    PRINTF_TEST( 12, "000000000123", "%012.3g", 123.0 );
    PRINTF_TEST( 12, "0000000012.3", "%012.3g", 12.3 );
    PRINTF_TEST( 12, "000000001.23", "%012.3g", 1.23 );
    PRINTF_TEST( 12, "00000000.123", "%012.3g", 0.123 );
    PRINTF_TEST( 12, "0000000.0123", "%012.3g", 0.0123 );
    PRINTF_TEST( 12, "000000.00123", "%012.3g", 0.00123 );
    PRINTF_TEST( 12, "00000.000123", "%012.3g", 0.000123 );
    PRINTF_TEST( 12, "00001.23e-05", "%012.3g", 0.0000123 );
    PRINTF_TEST( 12, "00001.23e-06", "%012.3g", 0.00000123 );
    PRINTF_TEST( 12, "00001.23e-08", "%012.3g", 123e-10 );

    PRINTF_TEST( 12, "1.23e+07    ", "%-12.3g", 12300000.0 );
    PRINTF_TEST( 12, "1.23e+03    ", "%-12.3g", 1230.0 );
    PRINTF_TEST( 12, "123         ", "%-12.3g", 123.0 );
    PRINTF_TEST( 12, "12.3        ", "%-12.3g", 12.3 );
    PRINTF_TEST( 12, "1.23        ", "%-12.3g", 1.23 );
    PRINTF_TEST( 12, "0.123       ", "%-12.3g", 0.123 );
    PRINTF_TEST( 12, "0.0123      ", "%-12.3g", 0.0123 );
    PRINTF_TEST( 12, "0.00123     ", "%-12.3g", 0.00123 );
    PRINTF_TEST( 12, "0.000123    ", "%-12.3g", 0.000123 );
    PRINTF_TEST( 12, "1.23e-05    ", "%-12.3g", 0.0000123 );
    PRINTF_TEST( 12, "1.23e-06    ", "%-12.3g", 0.00000123 );
    PRINTF_TEST( 12, "1.23e-08    ", "%-12.3g", 123e-10 );
    */
    }
