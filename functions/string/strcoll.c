// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

// TODO: Dummy function, does not support locales.

int strcmp( const char * src_1, const char * src_2 );

int strcoll( const char * src_1, const char * src_2 )
{
    return strcmp( src_1, src_2 );
}
