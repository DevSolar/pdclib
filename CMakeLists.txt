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

     platform/example/include/float.h
     platform/example/include/signal.h
)

set( PDCLIB_PRIVATE_HEADERS
     include/pdclib/_PDCLIB_aux.h
     include/pdclib/_PDCLIB_glue.h
     include/pdclib/_PDCLIB_int.h
     platform/example/include/pdclib/_PDCLIB_config.h
)

# Two libraries, one for dynamic linking, one for static linking.
add_library( pdclib  SHARED ${PDCLIB_SOURCES} ${PDCLIB_HEADERS} ${PDCLIB_PRIVATE_HEADERS} )
add_library( pdclibs STATIC ${PDCLIB_SOURCES} ${PDCLIB_HEADERS} ${PDCLIB_PRIVATE_HEADERS} )

# Compilation shall use PDCLib's over system include directories.
target_include_directories( pdclib  BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/platform/example/include )
target_include_directories( pdclibs BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/platform/example/include )

# The code for pdclib_obj_shared should be compiled with whatever
# options the compiler used requires to generate relocatable code.
set_property( TARGET pdclib PROPERTY POSITION_INDEPENDENT_CODE 1 )

# List of strict warnings; the compiler is your friend.
if ( CMAKE_COMPILER_IS_GNUCC )
    set( FLAGS "-Wall -Wextra -pedantic -Wno-unused-parameter -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wstrict-prototypes -Wdeclaration-after-statement -fno-builtin -fvisibility=hidden" )
    set_property( TARGET pdclib  APPEND_STRING PROPERTY COMPILE_FLAGS ${FLAGS} )
    set_property( TARGET pdclibs APPEND_STRING PROPERTY COMPILE_FLAGS ${FLAGS} )
elseif( MSVC )
    set( FLAGS "/W4 /D_CRT_SECURE_NO_WARNINGS /wd4996" )
    set_property( TARGET pdclib  APPEND_STRING PROPERTY COMPILE_FLAGS ${FLAGS} )
    set_property( TARGET pdclibs APPEND_STRING PROPERTY COMPILE_FLAGS ${FLAGS} )
endif()

# On Windows, both a dynamic .dll and a static .a library require
# their own respective .lib file, which is why the static library
# has its distinctive name pdclibs.a (note the "s").
# On Unix-like OS', we can have both .so and .a with the same base
# name, so we do away with the "s".
if ( UNIX )
    set_target_properties( pdclibs PROPERTIES OUTPUT_NAME pdclib )
endif()

add_custom_target( testdrivers )
add_custom_target( regtestdrivers )

# Each source file can be compiled to 1) a test driver for the
# function it defines, and 2) a regression test driver for the
# function as defined by the system's C library.
foreach( file ${PDCLIB_SOURCES} )
    get_filename_component( basename ${file} NAME_WE )
    # Test driver.
    add_executable( ${basename}_t ${file} )
    set_property( TARGET ${basename}_t APPEND_STRING PROPERTY COMPILE_FLAGS "-DTEST ${FLAGS}" )
    set_property( TARGET ${basename}_t PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test_support/testdrivers )
    target_include_directories( ${basename}_t BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/platform/example/include ${CMAKE_SOURCE_DIR}/test_support )
    target_link_libraries( ${basename}_t pdclibs )
    add_test( ${basename}_t test_support/testdrivers/${basename}_t )
    add_dependencies( testdrivers ${basename}_t )

    # Regression test driver.
    add_executable( ${basename}_r ${file} )
    set_property( TARGET ${basename}_r APPEND_STRING PROPERTY COMPILE_FLAGS "-DTEST -DREGTEST ${FLAGS}" )
    set_property( TARGET ${basename}_r PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test_support/regtestdrivers )
    target_include_directories( ${basename}_r BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/test_support )
    add_test( ${basename}_r test_support/regtestdrivers/${basename}_r )
    add_dependencies( regtestdrivers ${basename}_r )
endforeach()

# Installation files

if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    install( TARGETS pdclib pdclibs DESTINATION lib64 )
else()
    install( TARGETS pdclib pdclibs DESTINATION lib )
endif()

install( FILES ${PDCLIB_HEADERS} DESTINATION include )
install( FILES ${PDCLIB_PRIVATE_HEADERS} DESTINATION include/pdclib )

# CPack config

set( CPACK_PACKAGE_VERSION_MAJOR "0" )
set( CPACK_PACKAGE_VERSION_MINOR "6" )
set( CPACK_PACKAGE_VERSION_PATCH "0" )
set( CPACK_PACKAGE_CONTACT "Martin Baute <solar@rootdirectory.de>" )
set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "PDCLib -- Public Domain C Library" )
set( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING.CC0" )
set( CPACK_PACKAGE_VENDOR "Martin Baute -- http://pdclib.rootdirectory.de" )
set( CPACK_PACKAGE_NAME "pdclib" )
if ( WIN32 )
    set( CPACK_GENERATOR "ZIP" )
    set( CPACK_SOURCE_GENERATOR "ZIP" )
else()
    set( CPACK_GENERATOR "TGZ" )
    set( CPACK_SOURCE_GENERATOR "TGZ" )
endif()
include( CPack )

# errno_readout
# -------------
# A helper executable to read, from the system library, this platform's
# errno numbers and perror() / strerror() texts, to faciliate adapting
# PDCLib to use the same numbers / texts on any given platform.
# (Platform maintainers are supposed to use the output to adapt their
# platform's platform/<xyz>/functions/_PDCLIB/_PDCLIB_stdinit.c and
# platform/<xyz>/include/pdclib/_PDCLIB_config.h.)
add_executable( errno_readout
                auxiliary/errno/errno_readout.c )

# get_uctypes
# -----------
# A helper executable to parse up-to-date Unicode metadata from the
# Unicode database.
set( uctype_SOURCES
     auxiliary/uctype/derived_properties.c
     auxiliary/uctype/text_utilities.c
     auxiliary/uctype/uctype.c
     auxiliary/uctype/unicode_data.c
)

set( uctype_HEADERS
     auxiliary/uctype/derived_properties.h
     auxiliary/uctype/test.h
     auxiliary/uctype/text_utilities.h
     auxiliary/uctype/uctype.h
     auxiliary/uctype/unicode_data.h
)

add_library( uctype STATIC ${uctype_SOURCES} )
set_property( TARGET uctype APPEND_STRING PROPERTY COMPILE_FLAGS ${FLAGS} )
target_include_directories( uctype PRIVATE ${CMAKE_SOURCE_DIR}/auxiliary/uctype )

add_executable( get_uctypes auxiliary/uctype/main.c )
set_property( TARGET get_uctypes APPEND_STRING PROPERTY COMPILE_FLAGS ${FLAGS} )
target_include_directories( get_uctypes PRIVATE ${CMAKE_SOURCE_DIR}/auxiliary/uctype )
target_link_libraries( get_uctypes uctype )

foreach( file ${uctype_SOURCES} )
    get_filename_component( basename ${file} NAME_WE )

    # Test driver.
    add_executable( ${basename}_t ${file} )
    set_property( TARGET ${basename}_t APPEND_STRING PROPERTY COMPILE_FLAGS "-DTEST ${FLAGS}" )
    set_property( TARGET ${basename}_t PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test_support/uctype )
    target_include_directories( ${basename}_t PRIVATE ${CMAKE_SOURCE_DIR}/auxiliary/uctype )
    target_link_libraries( ${basename}_t uctype )
    add_test( ${basename}_t test_support/uctype/${basename}_t )
    add_dependencies( testdrivers ${basename}_t )
endforeach()
