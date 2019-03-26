{
    char buffer[100];
    int i;
    unsigned int u;
    int * p;
    /* basic: reading of three-char string */
    SCANF_TEST( 1, "foo", "%3c", buffer );
    TESTCASE( memcmp( buffer, "foo", 3 ) == 0 );
#ifndef TEST_CONVERSION_ONLY
    /* %% for single % */
    SCANF_TEST( 1, "%x", "%%%c", buffer );
    TESTCASE( buffer[0] == 'x' );
    /* * to skip assignment */
    SCANF_TEST( 1, "3xfoo", "%*dx%3c", buffer );
    TESTCASE( memcmp( buffer, "foo", 3 ) == 0 );
#endif
    /* domain testing on 'int' type */
    SCANF_TEST( 1, "-" INT_MIN_DEZ_STR, "%d", &i );
    TESTCASE( i == INT_MIN );
    SCANF_TEST( 1, INT_MAX_DEZ_STR, "%d", &i );
    TESTCASE( i == INT_MAX );
    SCANF_TEST( 1, "-1", "%d", &i );
    TESTCASE( i == -1 );
    SCANF_TEST( 1, "0", "%d", &i );
    TESTCASE( i == 0 );
    SCANF_TEST( 1, "1", "%d", &i );
    TESTCASE( i == 1 );
    SCANF_TEST( 1, "-" INT_MIN_DEZ_STR, "%i", &i );
    TESTCASE( i == INT_MIN );
    SCANF_TEST( 1, INT_MAX_DEZ_STR, "%i", &i );
    TESTCASE( i == INT_MAX );
    SCANF_TEST( 1, "-1", "%i", &i );
    TESTCASE( i == -1 );
    SCANF_TEST( 1, "0", "%i", &i );
    TESTCASE( i == 0 );
    SCANF_TEST( 1, "1", "%i", &i );
    TESTCASE( i == 1 );
    SCANF_TEST( 1, "0x7" INT_HEXDIG, "%i", &i );
    TESTCASE( i == INT_MAX );
    SCANF_TEST( 1, "0x0", "%i", &i );
    TESTCASE( i == 0 );
#ifndef TEST_CONVERSION_ONLY
    SCANF_TEST( 1, "00", "%i%n", &i, &u );
    TESTCASE( i == 0 );
    TESTCASE( u == 2 );
#endif
    /* domain testing on 'unsigned int' type */
    SCANF_TEST( 1, UINT_MAX_DEZ_STR, "%u", &u );
    TESTCASE( u == UINT_MAX );
    SCANF_TEST( 1, "0", "%u", &u );
    TESTCASE( u == 0 );
    SCANF_TEST( 1, "f" INT_HEXDIG, "%x", &u );
    TESTCASE( u == UINT_MAX );
    SCANF_TEST( 1, "7" INT_HEXDIG, "%x", &u );
    TESTCASE( u == INT_MAX );
    SCANF_TEST( 1, "0", "%o", &u );
    TESTCASE( u == 0 );
    SCANF_TEST( 1, INT_OCTDIG, "%o", &u );
    TESTCASE( u == UINT_MAX );
    /* testing %c */
    memset( buffer, '\0', 100 );
    SCANF_TEST( 1, "x", "%c", buffer );
    TESTCASE( memcmp( buffer, "x\0", 2 ) == 0 );
    /* testing %s */
    memset( buffer, '\0', 100 );
    SCANF_TEST( 1, "foo bar", "%s", buffer );
    TESTCASE( memcmp( buffer, "foo\0", 4 ) == 0 );
#ifndef TEST_CONVERSION_ONLY
    SCANF_TEST( 2, "foo bar  baz", "%s %s %n", buffer, buffer + 4, &u );
    TESTCASE( u == 9 );
    TESTCASE( memcmp( buffer, "foo\0bar\0", 8 ) == 0 );
#endif
    /* testing %[ */
    SCANF_TEST( 1, "abcdefg", "%[cba]", buffer );
    TESTCASE( memcmp( buffer, "abc\0", 4 ) == 0 );
    /* testing %p */
    p = NULL;
    sprintf( buffer, "%p", p );
    p = &i;
    SCANF_TEST( 1, buffer, "%p", &p );
    TESTCASE( p == NULL );
    p = &i;
    sprintf( buffer, "%p", p );
    p = NULL;
    SCANF_TEST( 1, buffer, "%p", &p );
    TESTCASE( p == &i );
}
