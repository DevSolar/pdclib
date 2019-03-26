cmake_minimum_required( VERSION 2.9 FATAL_ERROR )

project( pdclib LANGUAGES C )

set( CMAKE_C_STANDARD 99 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_EXTENSIONS OFF )

if ( NOT CMAKE_BUILD_TYPE )
    message( "++ CMAKE_BUILD_TYPE not set. Defaulting to 'Debug'." )
    set( CMAKE_BUILD_TYPE Debug )
endif()

include( CTest )
mark_as_advanced( BUILD_TESTING )
file( MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test_support )

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

add_library( pdclib_obj_shared SHARED OBJECT ${PDCLIB_SOURCES} )
target_include_directories( pdclib_obj_shared BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/platform/example/include )
set_property( TARGET pdclib_obj_shared PROPERTY POSITION_INDEPENDENT_CODE 1 )

add_library( pdclib_obj_static STATIC OBJECT ${PDCLIB_SOURCES} )
target_include_directories( pdclib_obj_static BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/platform/example/include )

set( GCC_WARNINGS "-Wall -Wextra -pedantic -Wno-unused-parameter -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes -Wdeclaration-after-statement -fno-builtin" )
set( MSVC_WARNINGS "/W4 /D_CRT_SECURE_NO_WARNINGS /wd4996" )

if ( CMAKE_COMPILER_IS_GNUCC )
    set_property( TARGET pdclib_obj_shared APPEND_STRING PROPERTY COMPILE_FLAGS ${GCC_WARNINGS} )
    set_property( TARGET pdclib_obj_static APPEND_STRING PROPERTY COMPILE_FLAGS ${GCC_WARNINGS} )
elseif( MSVC )
    set_property( TARGET pdclib_obj_shared APPEND_STRING PROPERTY COMPILE_FLAGS ${MSVC_WARNINGS} )
    set_property( TARGET pdclib_obj_static APPEND_STRING PROPERTY COMPILE_FLAGS ${MSVC_WARNINGS} )
endif()

add_library( pdclib SHARED $<TARGET_OBJECTS:pdclib_obj_shared> ${PDCLIB_HEADERS} )
add_library( pdclibs STATIC $<TARGET_OBJECTS:pdclib_obj_static> ${PDCLIB_HEADERS} )

if ( UNIX )
    # On Unix-like OS, we can have pdclib.a and pdclib.so.
    # On Windows, either needs a .lib file, which would collide,
    # so on Windows the statically linked lib is pdclibs.a (note
    # the "s" in the library name).
    set_target_properties( pdclibs PROPERTIES OUTPUT_NAME pdclib )
endif()

foreach( file ${PDCLIB_SOURCES} )
    get_filename_component( stub ${file} NAME_WE )

    add_executable( ${stub}_t ${file} )
    set_property( TARGET ${stub}_t APPEND_STRING PROPERTY COMPILE_FLAGS "-DTEST" )
    target_include_directories( ${stub}_t BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/platform/example/include ${CMAKE_SOURCE_DIR}/test_support )
    target_link_libraries( ${stub}_t pdclib )
    add_test( ${stub}_t ./${stub}_t )

    add_executable( ${stub}_r ${file} )
    set_property( TARGET ${stub}_r APPEND_STRING PROPERTY COMPILE_FLAGS "-DTEST -DREGTEST" )
    target_include_directories( ${stub}_r BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/test_support )
    add_test( ${stub}_r ./${stub}_r )
endforeach()
