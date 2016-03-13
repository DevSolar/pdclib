#ifndef REGTEST
#include <threads.h>
#include <windows.h>

static volatile HANDLE onceHandle = NULL;

static void initOnceHandle( _PDCLIB_once_flag *flag )
{
    HANDLE tOnceHandle = CreateEvent(NULL, TRUE, TRUE, NULL);
    HANDLE oldVal 
        = InterlockedCompareExchangePointer(&flag->_Handle, tOnceHandle, NULL);
    if(oldVal != NULL)
        CloseHandle(tOnceHandle);
}

void _PDCLIB_call_once(_PDCLIB_once_flag *flag, void (*func)(void))
{
   if(!flag->_Handle) initOnceHandle(flag);

   long oldVal = InterlockedCompareExchange(&flag->_State, 1, -1);
   for(;;) {
        if(oldVal == 0) {
            // Initialized
            return;
        } else if(oldVal == -1) {
            // We are doing the initialization
            func();
            if(InterlockedDecrement(&flag->_State) == 0)
                CloseHandle(flag->_Handle);
            SetEvent(flag->_Handle);
            return;
        } else {
            // Somebody else is initializing - we are waiting
            long newOldVal = InterlockedCompareExchange(&flag->_State, oldVal, 
                                                        oldVal+1);
            if(newOldVal == oldVal) {
                // We incremented the "waiters" counter
                if(WaitForSingleObject(flag->_Handle, INFINITE) != WAIT_OBJECT_0)
                    abort();
                if(InterlockedDecrement(&flag->_State) == 0)
                    CloseHandle(flag->_Handle);
                return;
            } else {
                oldVal = newOldVal;
                continue;
            }
        }
    }
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
