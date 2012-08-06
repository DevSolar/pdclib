#include <threads.h>

void _PDCLIB_call_once(_PDCLIB_once_flag *flag, void (*func)(void))
{
	if(*flag != _PDCLIB_ONCE_FLAG_DONE) {
		func();
		*flag = _PDCLIB_ONCE_FLAG_DONE;
	}
}

#ifdef TEST
#include <_PDCLIB_test.h>

static int count = 0;
once_flag once = ONCE_FLAG_INIT;

static void do_once(void)
{
    count++;
}

int main( void )
{
    TESTCASE(count == 0);
    call_once(&once, do_once);
    TESTCASE(count == 1);
    call_once(&once, do_once);
    TESTCASE(count == 1);
    do_once();
    TESTCASE(count == 2);
    return TEST_RESULTS;
}

#endif
