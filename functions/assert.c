/* _PDCLIB_assert( char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#include <_PDCLIB_aux.h>

#if _PDCLIB_C_VERSION == 99
void _PDCLIB_assert( char const * const message1, char const * const function, char const * const message2 )
{
    fputs( message1, stderr );
    fputs( function, stderr );
    fputs( message2, stderr );
    abort();
}
#else
void _PDCLIB_assert( char const * const message )
{
    fputs( message, stderr );
    abort();
}
#endif


#ifdef TEST
int main()
{
    return 0;
}
#endif
