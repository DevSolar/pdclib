/* $Id$ */

/* Release $Name$ */

/* multiinclude

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */

/* This is a dummy file that tests the standard headers for idempotency (i.e.,
   checks that nothing bad happens if you include them more than once).
*/

#include <complex.h>
#include <ctype.h>
#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <inttypes.h>
#include <iso646.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <time.h>
/*#include <wchar.h>*/ /* glibc <wchar.h> relies on <stdio.h> being glibc, too. */
#include <wctype.h>

#include <complex.h>
#include <ctype.h>
#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <inttypes.h>
#include <iso646.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <time.h>
/*#include <wchar.h>*/ /* glibc <wchar.h> relies on <stdio.h> being glibc, too. */
#include <wctype.h>

#ifdef TEST

int main()
{
    return 0;
}

#endif
