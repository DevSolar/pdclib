#include <threads.h>

void _PDCLIB_call_once(_PDCLIB_once_flag *flag, void (*func)(void))
{
	if(*flag != _PDCLIB_ONCE_FLAG_DONE) {
		func();
		*flag = _PDCLIB_ONCE_FLAG_DONE;
	}
}