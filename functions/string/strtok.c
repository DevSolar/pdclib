// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

char * strtok( char * restrict src, const char * restrict seperators )
{
    static char * store = NULL;
    size_t token_length;

    if ( src != NULL )
    {
        // new string
        store = src;
    }
    if ( store == NULL )
    {
        // no old string, no new string, nothing to do
        return NULL;
    }
    src += strspn( src, seperators ); // skipping leading seperators
    if ( strlen( src ) == 0 )
    {
        // no more to parse
        return ( store = NULL );
    }
    token_length = strcspn( src, seperators );
    if ( src[ token_length ] == '\0' )
    {
        // parsed to end of string
        store = NULL;
        return src;
    }
    src[ token_length ] = '\0';
    store = src + token_length + 1;
    return src;
}
