// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

__assert( char const * const expression, char const * const file,
          char const * const function, int const line )
{
    fprintf(stderr, "Assertion failed: %s, function %s, file %s, line %d.\n",
                    expression, function, file, line );
    abort();
}
