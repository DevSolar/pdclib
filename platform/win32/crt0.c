#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <threads.h>
#include <wchar.h> // Watcom bug: winnt.h assumes string.h defines wchar_t
#include <windows.h>
#include "_PDCLIB_io.h"
#include "_PDCLIB_locale.h"
#include "_PDCLIB_clocale.h"

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
            abort();
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

void __cdecl mainCRTStartup( void );

void __cdecl mainCRTStartup( void ) 
{
    stdin->handle.pointer  = GetStdHandle(STD_INPUT_HANDLE);
    stdout->handle.pointer = GetStdHandle(STD_OUTPUT_HANDLE);
    stderr->handle.pointer = GetStdHandle(STD_ERROR_HANDLE);

    oldFilter = SetUnhandledExceptionFilter( sehExceptionFilter );

    cl    = GetCommandLineW();
    wargv = CommandLineToArgvW(cl, &argc);
    argv  = argvToAnsi(wargv, argc);

    _PDCLIB_initclocale( &_PDCLIB_global_locale );

    if(tss_create(&_PDCLIB_locale_tss, (tss_dtor_t) freelocale) 
            != thrd_success) {
        fputs( "Error during C runtime initialization: "
               "Unable to allocate locale TLS", stderr );
        exit( EXIT_FAILURE );
    }

    if(        mtx_init(&stdin->lock, mtx_recursive) != thrd_success 
            || mtx_init(&stdout->lock, mtx_recursive) != thrd_success
            || mtx_init(&stderr->lock, mtx_recursive) != thrd_success ) {
        fputs( "Error during C runtime initialization: "
            "Unable to allocate stdio mutex", stderr );
        exit( EXIT_FAILURE );
    }

    atexit(freeArgs);

    int exitStatus = main(argc, argv, NULL);

    exit(exitStatus);
}