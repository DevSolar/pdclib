// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------

/* PDPC code - unreviewed
static void (*handlers[6])(int) = {
    __sigdfl,
    __sigdfl,
    __sigdfl,
    __sigdfl,
    __sigdfl,
    __sigdfl };

void __sigdfl(int sig)
{
    handlers[sig] = SIG_DFL;
    if (sig == SIGABRT)
    {
        exit(EXIT_FAILURE);
    }
    return;
}

void __sigerr(int sig)
{
    (void)sig;
    return;
}

void __sigign(int sig)
{
    (void)sig;
    return;
}

#define SIG_DFL __sigdfl
#define SIG_ERR __sigerr
#define SIG_IGN __sigign

#define SIGABRT 1
#define SIGFPE 2
#define SIGILL 3
#define SIGINT 4
#define SIGSEGV 5
#define SIGTERM 6
*/

int raise( int sig ) { /* TODO */ };

/* PDPC code - unreviewed
{
    (handlers[sig])(sig);
    return (0);
}
*/

void ( * signal( int sig, void ( *func )( int ) ) ) ( int ) { /* TODO */ };

/* PDPC code - unreviewed
{
    handlers[sig] = func;
    return (func);
}    
*/
