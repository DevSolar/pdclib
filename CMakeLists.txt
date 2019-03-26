cmake_minimum_required( VERSION 2.9 FATAL_ERROR )

project( pdclib LANGUAGES C )

# Setting compiler to C99 standard at minimum, no extensions.
set( CMAKE_C_STANDARD 99 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_EXTENSIONS OFF )

# Debug is the default setting anyway, but better to make it explicit
# and give output about it.
if ( NOT CMAKE_BUILD_TYPE )
    message( "++ CMAKE_BUILD_TYPE not set. Defaulting to 'Debug'." )
    set( CMAKE_BUILD_TYPE Debug )
endif()

# Test drivers write files to test_support/..., but this directory
# only exists in the source dir, so we create it in the build dir.
file( MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test_support )
include( CTest )
mark_as_advanced( BUILD_TESTING )

# List of source files.
set( PDCLIB_SOURCES
     functions/ctype/isalnum.c
     functions/ctype/isalpha.c
     functions/ctype/isblank.c
     functions/ctype/iscntrl.c
     functions/ctype/isdigit.c
     functions/ctype/isgraph.c
     functions/ctype/islower.c
     functions/ctype/isprint.c
     functions/ctype/ispunct.c
     functions/ctype/isspace.c
     functions/ctype/isupper.c
     functions/ctype/isxdigit.c
     functions/ctype/tolower.c
     functions/ctype/toupper.c

     functions/inttypes/imaxabs.c
     functions/inttypes/imaxdiv.c
     functions/inttypes/strtoimax.c
     functions/inttypes/strtoumax.c

     functions/locale/localeconv.c
     functions/locale/setlocale.c

     functions/_PDCLIB/assert.c
     functions/_PDCLIB/errno.c
     functions/_PDCLIB/_PDCLIB_atomax.c
     functions/_PDCLIB/_PDCLIB_closeall.c
     functions/_PDCLIB/_PDCLIB_digits.c
     functions/_PDCLIB/_PDCLIB_filemode.c
     functions/_PDCLIB/_PDCLIB_is_leap.c
     functions/_PDCLIB/_PDCLIB_load_lc_collate.c
     functions/_PDCLIB/_PDCLIB_load_lc_ctype.c
     functions/_PDCLIB/_PDCLIB_load_lc_messages.c
     functions/_PDCLIB/_PDCLIB_load_lc_monetary.c
     functions/_PDCLIB/_PDCLIB_load_lc_numeric.c
     functions/_PDCLIB/_PDCLIB_load_lc_time.c
     functions/_PDCLIB/_PDCLIB_load_lines.c
     functions/_PDCLIB/_PDCLIB_prepread.c
     functions/_PDCLIB/_PDCLIB_prepwrite.c
     functions/_PDCLIB/_PDCLIB_print.c
     functions/_PDCLIB/_PDCLIB_scan.c
     functions/_PDCLIB/_PDCLIB_seed.c
     functions/_PDCLIB/_PDCLIB_strtox_main.c
     functions/_PDCLIB/_PDCLIB_strtox_prelim.c
     functions/_PDCLIB/stdarg.c

     platform/example/functions/_PDCLIB/_PDCLIB_allocpages.c
     platform/example/functions/_PDCLIB/_PDCLIB_close.c
     platform/example/functions/_PDCLIB/_PDCLIB_Exit.c
     platform/example/functions/_PDCLIB/_PDCLIB_fillbuffer.c
     platform/example/functions/_PDCLIB/_PDCLIB_flushbuffer.c
     platform/example/functions/_PDCLIB/_PDCLIB_open.c
     platform/example/functions/_PDCLIB/_PDCLIB_rename.c
     platform/example/functions/_PDCLIB/_PDCLIB_seek.c
     platform/example/functions/_PDCLIB/_PDCLIB_stdinit.c

     platform/example/functions/signal/raise.c
     platform/example/functions/signal/signal.c

     functions/stdio/clearerr.c
     functions/stdio/fclose.c
     functions/stdio/feof.c
     functions/stdio/ferror.c
     functions/stdio/fflush.c
     functions/stdio/fgetc.c
     functions/stdio/fgetpos.c
     functions/stdio/fgets.c
     functions/stdio/fopen.c
     functions/stdio/fprintf.c
     functions/stdio/fputc.c
     functions/stdio/fputs.c
     functions/stdio/fread.c
     functions/stdio/freopen.c
     functions/stdio/fscanf.c
     functions/stdio/fseek.c
     functions/stdio/fsetpos.c
     functions/stdio/ftell.c
     functions/stdio/fwrite.c
     functions/stdio/getc.c
     functions/stdio/getchar.c
     functions/stdio/perror.c
     functions/stdio/printf.c
     functions/stdio/putc.c
     functions/stdio/putchar.c
     functions/stdio/puts.c
     functions/stdio/rename.c
     functions/stdio/rewind.c
     functions/stdio/scanf.c
     functions/stdio/setbuf.c
     functions/stdio/setvbuf.c
     functions/stdio/snprintf.c
     functions/stdio/sprintf.c
     functions/stdio/sscanf.c
     functions/stdio/tmpnam.c
     functions/stdio/ungetc.c
     functions/stdio/vfprintf.c
     functions/stdio/vfscanf.c
     functions/stdio/vprintf.c
     functions/stdio/vscanf.c
     functions/stdio/vsnprintf.c
     functions/stdio/vsprintf.c
     functions/stdio/vsscanf.c

     platform/example/functions/stdio/remove.c
     platform/example/functions/stdio/tmpfile.c

     functions/stdlib/abort.c
     functions/stdlib/abs.c
     functions/stdlib/atexit.c
     functions/stdlib/atoi.c
     functions/stdlib/atol.c
     functions/stdlib/atoll.c
     functions/stdlib/bsearch.c
     functions/stdlib/calloc.c
     functions/stdlib/div.c
     functions/stdlib/exit.c
     functions/stdlib/_Exit.c
     functions/stdlib/free.c
     functions/stdlib/labs.c
     functions/stdlib/ldiv.c
     functions/stdlib/llabs.c
     functions/stdlib/lldiv.c
     functions/stdlib/malloc.c
     functions/stdlib/qsort.c
     functions/stdlib/rand.c
     functions/stdlib/realloc.c
     functions/stdlib/srand.c
     functions/stdlib/strtol.c
     functions/stdlib/strtoll.c
     functions/stdlib/strtoul.c
     functions/stdlib/strtoull.c

     platform/example/functions/stdlib/getenv.c
     platform/example/functions/stdlib/system.c

     functions/string/memchr.c
     functions/string/memcmp.c
     functions/string/memcpy.c
     functions/string/memmove.c
     functions/string/memset.c
     functions/string/strcat.c
     functions/string/strchr.c
     functions/string/strcmp.c
     functions/string/strcoll.c
     functions/string/strcpy.c
     functions/string/strcspn.c
     functions/string/strerror.c
     functions/string/strlen.c
     functions/string/strncat.c
     functions/string/strncmp.c
     functions/string/strncpy.c
     functions/string/strpbrk.c
     functions/string/strrchr.c
     functions/string/strspn.c
     functions/string/strstr.c
     functions/string/strtok.c
     functions/string/strxfrm.c

     functions/time/asctime.c
     functions/time/ctime.c
     functions/time/difftime.c
     functions/time/gmtime.c
     functions/time/localtime.c
     functions/time/mktime.c
     functions/time/strftime.c

     platform/example/functions/time/clock.c
     platform/example/functions/time/time.c
     platform/example/functions/time/timespec_get.c
)

# List of header files. Not required for actually building, but if
# they are not listed in add_library(), they do not show up in IDE
# project files.
set( PDCLIB_HEADERS
     include/assert.h
     include/ctype.h
     include/errno.h
     include/inttypes.h
     include/iso646.h
     include/limits.h
     include/locale.h
     include/stdalign.h
     include/stdarg.h
     include/stdbool.h
     include/stddef.h
     include/stdint.h
     include/stdio.h
     include/stdlib.h
     include/stdnoreturn.h
     include/string.h
     include/time.h
     include/wctype.h
     include/pdclib/_PDCLIB_aux.h
     include/pdclib/_PDCLIB_glue.h
     include/pdclib/_PDCLIB_int.h
     platform/example/include/float.h
     platform/example/include/signal.h
     platform/example/include/pdclib/_PDCLIB_config.h
)

# Two libraries, one for dynamic linking, one for static linking.
add_library( pdclib  SHARED ${PDCLIB_SOURCES} ${PDCLIB_HEADERS} )
add_library( pdclibs STATIC ${PDCLIB_SOURCES} ${PDCLIB_HEADERS} )

# Compilation shall use PDCLib's over system include directories.
target_include_directories( pdclib  BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/platform/example/include )
target_include_directories( pdclibs BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/platform/example/include )

# The code for pdclib_obj_shared should be compiled with whatever
# options the compiler used requires to generate relocatable code.
set_property( TARGET pdclib PROPERTY POSITION_INDEPENDENT_CODE 1 )

# List of strict warnings; the compiler is your friend.
if ( CMAKE_COMPILER_IS_GNUCC )
    set( WARNINGS "-Wall -Wextra -pedantic -Wno-unused-parameter -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes -Wdeclaration-after-statement -fno-builtin" )
    set_property( TARGET pdclib  APPEND_STRING PROPERTY COMPILE_FLAGS ${WARNINGS} )
    set_property( TARGET pdclibs APPEND_STRING PROPERTY COMPILE_FLAGS ${WARNINGS} )
elseif( MSVC )
    set( WARNINGS "/W4 /D_CRT_SECURE_NO_WARNINGS /wd4996" )
    set_property( TARGET pdclib  APPEND_STRING PROPERTY COMPILE_FLAGS ${WARNINGS} )
    set_property( TARGET pdclibs APPEND_STRING PROPERTY COMPILE_FLAGS ${WARNINGS} )
endif()

# On Windows, both a dynamic .dll and a static .a library require
# their own respective .lib file, which is why the static library
# has its distinctive name pdclibs.a (note the "s").
# On Unix-like OS', we can have both .so and .a with the same base
# name, so we do away with the "s".
if ( UNIX )
    set_target_properties( pdclibs PROPERTIES OUTPUT_NAME pdclib )
endif()

# Each source file can be compiled to 1) a test driver for the
# function it defines, and 2) a regression test driver for the
# function as defined by the system's C library.
foreach( file ${PDCLIB_SOURCES} )
    get_filename_component( basename ${file} NAME_WE )
    # Test driver.
    add_executable( ${basename}_t ${file} )
    set_property( TARGET ${basename}_t APPEND_STRING PROPERTY COMPILE_FLAGS "-DTEST" )
    target_include_directories( ${basename}_t BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/platform/example/include ${CMAKE_SOURCE_DIR}/test_support )
    target_link_libraries( ${basename}_t pdclib )
    add_test( ${basename}_t ./${basename}_t )

    # Regression test driver.
    add_executable( ${basename}_r ${file} )
    set_property( TARGET ${basename}_r APPEND_STRING PROPERTY COMPILE_FLAGS "-DTEST -DREGTEST" )
    target_include_directories( ${basename}_r BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/test_support )
    add_test( ${basename}_r ./${basename}_r )
endforeach()
