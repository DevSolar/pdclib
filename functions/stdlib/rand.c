// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

int rand( void ) { /* TODO */ };
void srand( unsigned int seed ) { /* TODO */ };

/* PDPC code - unreviewed
static unsigned long myseed = 1;

void srand(unsigned int seed)
{
    myseed = seed;
    return;
}

int rand(void)
{
    int ret;
    
    myseed = myseed * 1103515245UL + 12345;
    ret = (int)((myseed >> 16) & 0x8fff);
    return (ret);
}
*/
