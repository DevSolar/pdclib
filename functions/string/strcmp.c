/* $Id$ */

/* Release $Name$ */

/* strcmp( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

int strcmp( const char * s1, const char * s2 )
{
    while ( ( *s1 ) && ( *s1 == *s2 ) )
    {
        ++s1;
        ++s2;
    }
    return ( *s1 - *s2 );
}

#warning Test driver missing.

#ifdef TEST
int main()
{
    return 0;
}
#endif
