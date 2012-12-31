#ifndef __PDCLIB_LOCALE_H
#define __PDCLIB_LOCALE_H __PDCLIB_LOCALE_H
#include <locale.h>

#define _PDCLIB_threadlocale() (uselocale(NULL))

struct _PDCLIB_locale {
    struct _PDCLIB_charcodec    *_Codec;
    struct lconv                 _Conv;
};

#endif
