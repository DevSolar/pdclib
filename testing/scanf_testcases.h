{
    char buffer[100];
#ifndef TEST_CONVERSION_ONLY
    SCANF_TEST( 0, "foo", "foo", NULL );
#endif
    SCANF_TEST( 1, "foo", "%3c", buffer );
    TESTCASE( memcmp( buffer, "foo", 3 ) == 0 );
}
