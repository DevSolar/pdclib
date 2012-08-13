#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

extern int main( int argc, char ** argv, char ** envp );
_PDCLIB_noreturn void mainCRTStartup( void ) 
{
    stdin->handle  = GetStdHandle(STD_INPUT_HANDLE);
    stdout->handle = GetStdHandle(STD_OUTPUT_HANDLE);
    stderr->handle = GetStdHandle(STD_ERROR_HANDLE);

    cl    = GetCommandLineW();
    wargv = CommandLineToArgvW(cl, &argc);
    argv  = argvToAnsi(wargv, argc);
    atexit(freeArgs);

    int exitStatus = main(argc, argv, NULL);
    exit(exitStatus);
}
