#ifndef REGTEST
#include <threads.h>
#include <pthread.h>

void call_once(once_flag *flag, void (*func)(void))
{
    pthread_once(flag, func);
}
#endif

#ifdef TEST
#include "_PDCLIB_test.h"

#ifndef REGTEST
static int count = 0;
static once_flag once = ONCE_FLAG_INIT;

static void do_once(void)
{
    count++;
}
#endif

int main( void )
{
#ifndef REGTEST
    TESTCASE(count == 0);
    call_once(&once, do_once);
    TESTCASE(count == 1);
    call_once(&once, do_once);
    TESTCASE(count == 1);
    do_once();
    TESTCASE(count == 2);
#endif
    return TEST_RESULTS;
}

#endif
