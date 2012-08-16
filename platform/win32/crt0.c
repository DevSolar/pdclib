#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <wchar.h> // Watcom bug: winnt.h assumes string.h defines wchar_t
#include <windows.h>

static char ** argvToAnsi( wchar_t ** wargv, int argc )
{
    char ** argv = malloc( sizeof( *argv ) * argc );
    for ( int i = 0; i != argc; ++i ) {
        int sz = WideCharToMultiByte( CP_ACP, WC_COMPOSITECHECK | WC_SEPCHARS,
                                      wargv[i], -1, NULL, 0, NULL, NULL );
        if(!(argv[i] = malloc(sz))) {
            fputs("Error in C runtime initialization: "
                  "unable to allocate buffer for argument", stderr);
            abort();
        }

        int rv = WideCharToMultiByte( CP_ACP, WC_COMPOSITECHECK | WC_SEPCHARS,
                                      wargv[i], -1, argv[i], sz, NULL, NULL );

        if(rv != sz) {
            fputs("Error in C runtime initialization: "
                  "size mismatch during character set conversion", stderr);
        }
    }
    return argv;
}

static int        argc;
static wchar_t *  cl;
static wchar_t ** wargv;
static char    ** argv;

static void freeArgs( void )
{
    for(int i = 0; i != argc; i++) {
        free( argv[i] );
    }
    free( argv );
    LocalFree( wargv );
}

extern void (*_PDCLIB_sigfpe)( int );
extern void (*_PDCLIB_sigill)( int );
extern void (*_PDCLIB_sigsegv)( int );

static LPTOP_LEVEL_EXCEPTION_FILTER oldFilter;
static LONG CALLBACK sehExceptionFilter( EXCEPTION_POINTERS * exInfo )
{
    int sig;
    void (*handler)( int );

    switch( exInfo->ExceptionRecord->ExceptionCode ) {
        case EXCEPTION_ACCESS_VIOLATION:
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        case EXCEPTION_DATATYPE_MISALIGNMENT:
        case EXCEPTION_GUARD_PAGE:
        case EXCEPTION_IN_PAGE_ERROR:
        case EXCEPTION_STACK_OVERFLOW:
            sig = SIGSEGV;
            handler = _PDCLIB_sigsegv;
            break;

        case EXCEPTION_ILLEGAL_INSTRUCTION:
        case EXCEPTION_PRIV_INSTRUCTION:
            sig = SIGILL;
            handler = _PDCLIB_sigill;
            break;

        case EXCEPTION_INT_DIVIDE_BY_ZERO:
        case EXCEPTION_INT_OVERFLOW:
        case EXCEPTION_FLT_DENORMAL_OPERAND:
        case EXCEPTION_FLT_DIVIDE_BY_ZERO:
        case EXCEPTION_FLT_INEXACT_RESULT:
        case EXCEPTION_FLT_INVALID_OPERATION:
        case EXCEPTION_FLT_OVERFLOW:
        case EXCEPTION_FLT_STACK_CHECK:
        case EXCEPTION_FLT_UNDERFLOW:
            sig = SIGFPE;
            handler = _PDCLIB_sigfpe;
            break;

        default:
            return oldFilter ? oldFilter( exInfo ) : EXCEPTION_EXECUTE_HANDLER;
    }

    if(handler == SIG_DFL) {
        return EXCEPTION_EXECUTE_HANDLER;
    } else if(handler == SIG_IGN) {
        return EXCEPTION_CONTINUE_EXECUTION;
    } else {
        handler( sig );
        return EXCEPTION_CONTINUE_EXECUTION;
    }
}

extern int main( int argc, char ** argv, char ** envp );

void __cdecl mainCRTStartup( void ) 
{
    stdin->handle  = GetStdHandle(STD_INPUT_HANDLE);
    stdout->handle = GetStdHandle(STD_OUTPUT_HANDLE);
    stderr->handle = GetStdHandle(STD_ERROR_HANDLE);

    oldFilter = SetUnhandledExceptionFilter( sehExceptionFilter );

    cl    = GetCommandLineW();
    wargv = CommandLineToArgvW(cl, &argc);
    argv  = argvToAnsi(wargv, argc);
    atexit(freeArgs);

    int exitStatus = main(argc, argv, NULL);

    exit(exitStatus);
}