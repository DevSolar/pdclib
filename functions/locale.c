// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

/* PDPC code - unreviewed
static struct lconv thislocale = {
    ".",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX,
    CHAR_MAX
};
*/

char * setlocale( int categories, const char * locale_name ) { /* TODO */ };

/* PDPC code - unreviewed
{
    (void)category;
    if (locale == NULL)
    {
        return ("C");
    }
    else if ((strcmp(locale, "C") == 0)
             || (strcmp(locale, "") == 0))
    {
        return ("C");
    }
    else
    {
        return (NULL);
    }
}
*/

struct lconv * localeconv( void ) { /* TODO */ };

/* PDPC code - unreviewed
{
    return (&thislocale);
}
*/
