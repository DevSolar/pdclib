{
    char buffer[100];
    SCANF_TEST( 1, "foo", "%3c", buffer );
    TESTCASE( memcmp( buffer, "foo", 3 ) == 0 );
}
