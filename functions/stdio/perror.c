// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

void perror( const char * s ) { /* TODO */ };

/* PDPC code - unreviewed
{
    if ((s != NULL) && (*s != '\0'))
    {
        printf("%s: ");
    }
    if (errno == 0)
    {
        printf("No error has occurred\n");
    }
    else
    {
        printf("An error has occurred\n");
    }
    return;
}
*/
