# CMake is a meta-buildsystem that allows you to *generate* the necessary
# files for your build system of choice (Makefile, rules.ninja, CodeBlocks
# project, MSVC solution, ...) from the configuration given below.
#
# Install CMake for your system (https://www.cmake.org), call
# cmake --help
# to get a list of buildfile generators available, then (from an empty dir)
# cmake [-G <generator>] path/to/pdclib_source
# to generate the desired build files. CMake will automatically track a
# dependency on this configuration file, and re-build the buildfiles if you
# make changes to it, so you need not re-run that generator step manually.
#
# Check
# ctest --help
# to find out about CMake's testing client.
#
# Check
# cpack --help
# to get a list of packaging options, and
# cpack -G <generator>
# to create a package of your compiled version of PDCLib.

cmake_minimum_required( VERSION 3.1.3 FATAL_ERROR )

project( pdclib )

option( IGNORE_NO_TESTDRIVER "Ignore NO_TESTDRIVER flags instead of reporting them as error. Default: OFF." OFF )
option( AS_CXX "Compile as C++. (For testing purposes.) Default: OFF." OFF )
option( AS_C11 "Compile as C11. (For testing purposes.) Default: OFF." OFF )
option( AS_C90 "Compile as C90. (For testing purposes.) Default: OFF." OFF )

# Setting compiler to standard, no extensions.
if ( AS_C11 )
    set( CMAKE_C_STANDARD 11 )
elseif( AS_C90 )
    set( CMAKE_C_STANDARD 90 )
else()
    set( CMAKE_C_STANDARD 99 )
endif()

set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_EXTENSIONS OFF )

# Debug is the default setting anyway, but better to make it explicit and
# give output about it.
if ( NOT CMAKE_BUILD_TYPE )
    message( "++ CMAKE_BUILD_TYPE not set. Defaulting to 'Debug'." )
    set( CMAKE_BUILD_TYPE Debug )
endif()

# Use the test support built-in to CMake. Use the "ctest" client to run
# tests of built binaries.
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
     functions/stdio/fopen_s.c
     functions/stdio/fprintf.c
     functions/stdio/fputc.c
     functions/stdio/fputs.c
     functions/stdio/fread.c
     functions/stdio/freopen.c
     functions/stdio/freopen_s.c
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
     functions/stdio/remove.c
     functions/stdio/rename.c
     functions/stdio/rewind.c
     functions/stdio/scanf.c
     functions/stdio/setbuf.c
     functions/stdio/setvbuf.c
     functions/stdio/snprintf.c
     functions/stdio/sprintf.c
     functions/stdio/sscanf.c
     functions/stdio/tmpfile_s.c
     functions/stdio/tmpnam.c
     functions/stdio/ungetc.c
     functions/stdio/vfprintf.c
     functions/stdio/vfscanf.c
     functions/stdio/vprintf.c
     functions/stdio/vscanf.c
     functions/stdio/vsnprintf.c
     functions/stdio/vsprintf.c
     functions/stdio/vsscanf.c
     platform/example/functions/stdio/tmpfile.c

     functions/stdlib/abort.c
     functions/stdlib/abort_handler_s.c
     functions/stdlib/abs.c
     functions/stdlib/at_quick_exit.c
     functions/stdlib/atexit.c
     functions/stdlib/atoi.c
     functions/stdlib/atol.c
     functions/stdlib/atoll.c
     functions/stdlib/bsearch.c
     functions/stdlib/bsearch_s.c
     functions/stdlib/div.c
     functions/stdlib/exit.c
     functions/stdlib/_Exit.c
     functions/stdlib/ignore_handler_s.c
     functions/stdlib/labs.c
     functions/stdlib/ldiv.c
     functions/stdlib/llabs.c
     functions/stdlib/lldiv.c
     functions/stdlib/qsort.c
     functions/stdlib/qsort_s.c
     functions/stdlib/quick_exit.c
     functions/stdlib/rand.c
     functions/stdlib/set_constraint_handler_s.c
     functions/stdlib/srand.c
     functions/stdlib/strtol.c
     functions/stdlib/strtoll.c
     functions/stdlib/strtoul.c
     functions/stdlib/strtoull.c
     platform/example/functions/stdlib/getenv.c
     platform/example/functions/stdlib/getenv_s.c
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
     functions/string/strtok_s.c
     functions/string/strxfrm.c
     functions/string/memcpy_s.c
     functions/string/memmove_s.c
     functions/string/memset_s.c
     functions/string/strcat_s.c
     functions/string/strcpy_s.c
     functions/string/strerror_s.c
     functions/string/strerrorlen_s.c
     functions/string/strncat_s.c
     functions/string/strncpy_s.c

     platform/example/functions/threads/call_once.c
     platform/example/functions/threads/cnd_broadcast.c
     platform/example/functions/threads/cnd_destroy.c
     platform/example/functions/threads/cnd_init.c
     platform/example/functions/threads/cnd_signal.c
     platform/example/functions/threads/cnd_timedwait.c
     platform/example/functions/threads/cnd_wait.c
     platform/example/functions/threads/mtx_destroy.c
     platform/example/functions/threads/mtx_init.c
     platform/example/functions/threads/mtx_lock.c
     platform/example/functions/threads/mtx_timedlock.c
     platform/example/functions/threads/mtx_trylock.c
     platform/example/functions/threads/mtx_unlock.c
     platform/example/functions/threads/thrd_create.c
     platform/example/functions/threads/thrd_current.c
     platform/example/functions/threads/thrd_detach.c
     platform/example/functions/threads/thrd_equal.c
     platform/example/functions/threads/thrd_exit.c
     platform/example/functions/threads/thrd_join.c
     platform/example/functions/threads/thrd_sleep.c
     platform/example/functions/threads/thrd_yield.c
     platform/example/functions/threads/tss_create.c
     platform/example/functions/threads/tss_delete.c
     platform/example/functions/threads/tss_get.c
     platform/example/functions/threads/tss_set.c

     functions/time/asctime.c
     functions/time/asctime_s.c
     functions/time/ctime.c
     functions/time/ctime_s.c
     functions/time/difftime.c
     functions/time/gmtime.c
     functions/time/gmtime_s.c
     functions/time/localtime.c
     functions/time/localtime_s.c
     functions/time/mktime.c
     functions/time/strftime.c
     platform/example/functions/time/clock.c
     platform/example/functions/time/time.c
     platform/example/functions/time/timespec_get.c

     functions/_tzcode/_PDCLIB_gmtcheck.c
     functions/_tzcode/_PDCLIB_gmtsub.c
     functions/_tzcode/_PDCLIB_increment_overflow.c
     functions/_tzcode/_PDCLIB_init_ttinfo.c
     functions/_tzcode/_PDCLIB_localsub.c
     functions/_tzcode/_PDCLIB_localtime_tzset.c
     functions/_tzcode/_PDCLIB_mktime_tzname.c
     functions/_tzcode/_PDCLIB_timesub.c
     functions/_tzcode/_PDCLIB_tzload.c
     functions/_tzcode/_PDCLIB_tzparse.c
     functions/_tzcode/_PDCLIB_tzset_unlocked.c
     functions/_tzcode/_PDCLIB_update_tzname_etc.c

     functions/_PDCLIB/assert.c
     functions/_PDCLIB/errno.c
     functions/_PDCLIB/_PDCLIB_atomax.c
     functions/_PDCLIB/_PDCLIB_bigint.c
     functions/_PDCLIB/_PDCLIB_bigint2.c
     functions/_PDCLIB/_PDCLIB_bigint10.c
     functions/_PDCLIB/_PDCLIB_bigint32.c
     functions/_PDCLIB/_PDCLIB_bigint64.c
     functions/_PDCLIB/_PDCLIB_bigint_add.c
     functions/_PDCLIB/_PDCLIB_bigint_sub.c
     functions/_PDCLIB/_PDCLIB_bigint_cmp.c
     functions/_PDCLIB/_PDCLIB_bigint_log2.c
     functions/_PDCLIB/_PDCLIB_bigint_mul.c
     functions/_PDCLIB/_PDCLIB_bigint_mul_dig.c
     functions/_PDCLIB/_PDCLIB_bigint_div.c
     functions/_PDCLIB/_PDCLIB_bigint_div_dig.c
     functions/_PDCLIB/_PDCLIB_bigint_shl.c
     functions/_PDCLIB/_PDCLIB_bigint_tostring.c
     functions/_PDCLIB/_PDCLIB_closeall.c
     functions/_PDCLIB/_PDCLIB_digits.c
     functions/_PDCLIB/_PDCLIB_filemode.c
     functions/_PDCLIB/_PDCLIB_getstream.c
     functions/_PDCLIB/_PDCLIB_init_file_t.c
     functions/_PDCLIB/_PDCLIB_is_leap.c
     functions/_PDCLIB/_PDCLIB_isstream.c
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
     functions/_PDCLIB/_PDCLIB_print_float.c
     functions/_PDCLIB/_PDCLIB_print_integer.c
     functions/_PDCLIB/_PDCLIB_print_string.c
     functions/_PDCLIB/_PDCLIB_scan.c
     functions/_PDCLIB/_PDCLIB_seed.c
     functions/_PDCLIB/_PDCLIB_strtok.c
     functions/_PDCLIB/_PDCLIB_strtox_main.c
     functions/_PDCLIB/_PDCLIB_strtox_prelim.c
     functions/_PDCLIB/stdarg.c

     platform/example/functions/_PDCLIB/_PDCLIB_changemode.c
     platform/example/functions/_PDCLIB/_PDCLIB_close.c
     platform/example/functions/_PDCLIB/_PDCLIB_Exit.c
     platform/example/functions/_PDCLIB/_PDCLIB_fillbuffer.c
     platform/example/functions/_PDCLIB/_PDCLIB_flushbuffer.c
     platform/example/functions/_PDCLIB/_PDCLIB_float_split.c
     platform/example/functions/_PDCLIB/_PDCLIB_double_split.c
     platform/example/functions/_PDCLIB/_PDCLIB_long_double_split.c
     platform/example/functions/_PDCLIB/_PDCLIB_open.c
     platform/example/functions/_PDCLIB/_PDCLIB_realpath.c
     platform/example/functions/_PDCLIB/_PDCLIB_rename.c
     platform/example/functions/_PDCLIB/_PDCLIB_remove.c
     platform/example/functions/_PDCLIB/_PDCLIB_seek.c
     platform/example/functions/_PDCLIB/_PDCLIB_stdinit.c
)

# List of header files. Not required for actually building, but if they
# are not listed (in add_library()), they do not show up in IDE project
# files (like MSVC solutions).
# These get installed to your system's default include directory.
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
     platform/example/include/threads.h
)

# These get installed in a "pdclib" subdirectory of your system's default
# "include" directory.
set( PDCLIB_PRIVATE_HEADERS
     include/pdclib/_PDCLIB_glue.h
     include/pdclib/_PDCLIB_internal.h
     include/pdclib/_PDCLIB_lib_ext1.h
     platform/example/include/pdclib/_PDCLIB_config.h
)

# These do not get installed on your system at all, they are for building
# PDCLib only, not for using it.
set( PDCLIB_NOINSTALL_HEADERS
     include/pdclib/_PDCLIB_glue.h
     include/pdclib/_PDCLIB_print.h
     #include/pdclib/_PDCLIB_tzcode.h
)

# dlmalloc, compiled separately as its inclusion of system headers conflicts
# with PDCLib headers (specifically, struct timespec).
add_library( _dlmalloc OBJECT functions/_dlmalloc/malloc.c )
add_library( _dlmallocs OBJECT functions/_dlmalloc/malloc.c )
target_include_directories( _dlmalloc  PRIVATE ${CMAKE_SOURCE_DIR}/platform/example/include/pdclib )
target_include_directories( _dlmallocs PRIVATE ${CMAKE_SOURCE_DIR}/platform/example/include/pdclib )

# Two libraries, one for dynamic linking, one for static linking.
add_library( pdclib  SHARED ${PDCLIB_SOURCES} $<TARGET_OBJECTS:_dlmalloc>  ${PDCLIB_HEADERS} ${PDCLIB_PRIVATE_HEADERS} ${PDCLIB_NOINSTALL_HEADERS} )
add_library( pdclibs STATIC ${PDCLIB_SOURCES} $<TARGET_OBJECTS:_dlmallocs> ${PDCLIB_HEADERS} ${PDCLIB_PRIVATE_HEADERS} ${PDCLIB_NOINSTALL_HEADERS} )

# The example implementation makes use of pthread. We use CMake facilities
# to locate the pthread library for linking.
set( CMAKE_THREAD_PREFER_PTHREAD 1 )
set( THREADS_PREFER_PTHREAD_FLAG 1 )
find_package( Threads )
if ( NOT CMAKE_USE_PTHREADS_INIT )
    message( FATAL_ERROR "Example platform requires pthread to be available." )
endif()

target_link_libraries( pdclib Threads::Threads )
target_link_libraries( pdclibs Threads::Threads )

# Compilation shall use PDCLib's over system include directories.
target_include_directories( pdclib  BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/platform/example/include )
target_include_directories( pdclibs BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/platform/example/include )

# The code for the DLL / shared object should be compiled with whatever
# options are appropriate for your compiler to generate relocatable code.
set_property( TARGET pdclib _dlmalloc PROPERTY POSITION_INDEPENDENT_CODE 1 )

# List of strict warnings; the compiler is your friend.
if ( CMAKE_COMPILER_IS_GNUCC )
    # The bit about -D_STDC_PREDEF_H is a heavy-handed way to interdict
    # GCC making statements about the standard library's capabilities,
    # specifically __STDC_NO_THREADS__ (by including stdc-predef.h). I
    # was unable to identify a more elegant way to achieve this.
    set( FLAGS "-Wall -Wextra -pedantic -Wno-unused-parameter -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Winline -Wno-long-long -Wuninitialized -fno-builtin -fvisibility=hidden -D_STDC_PREDEF_H -nostdlib" )

    if ( NOT AS_CXX )
        string( APPEND FLAGS " -Wmissing-prototypes -Wnested-externs -Wstrict-prototypes -Wdeclaration-after-statement" )
    endif()
elseif( MSVC )
    set( FLAGS "/W4 /D_CRT_SECURE_NO_WARNINGS /wd4996" )
endif()

# Optionally, use C++ compiler instead of C compiler.
if ( AS_CXX )
    set_source_files_properties( ${PDCLIB_SOURCES} PROPERTIES LANGUAGE CXX )
endif()

# Optionally, make TESTCASE( NO_TESTDRIVER ) succeed instead of fail.
if ( IGNORE_NO_TESTDRIVER )
    string( APPEND FLAGS " -DNO_TESTDRIVER=1" )
endif()

# Setting symbol visibility (_PDCLIB_LOCAL / _PDCLIB_PUBLIC configuration
# in _PDCLIB_config.h)
set_property( TARGET pdclib  APPEND_STRING PROPERTY COMPILE_FLAGS "-D_PDCLIB_BUILD ${FLAGS}" )
set_property( TARGET pdclibs APPEND_STRING PROPERTY COMPILE_FLAGS "-D_PDCLIB_STATIC_DEFINE ${FLAGS}" )

# On Windows, both a dynamic .dll and a static .a library require their own
# respective .lib file, which is why the static library has its distinctive
# name pdclibs.a (note the "s").
# On Unix-like OS' (and Cygwin), we can have both .so and .a with the same
# base name, so we do away with the "s" suffix.
if ( UNIX )
    set_target_properties( pdclibs PROPERTIES OUTPUT_NAME pdclib )
endif()

add_custom_target( testdrivers )
add_custom_target( regtestdrivers )

# Each source file can be compiled to
# 1) a test driver for the function it defines,
# 2) a regression test driver for the function as defined by the system's
#    C library.
foreach( file ${PDCLIB_SOURCES} )
    get_filename_component( basename ${file} NAME_WE )

    # Test driver, _t suffix, compiled with -DTEST against static lib.
    add_executable( ${basename}_t ${file} )
    set_property( TARGET ${basename}_t APPEND_STRING PROPERTY COMPILE_FLAGS "-DTEST -D_PDCLIB_BUILD ${FLAGS}" )
    set_property( TARGET ${basename}_t PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test_support/testdrivers )
    target_include_directories( ${basename}_t BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/platform/example/include ${CMAKE_SOURCE_DIR}/test_support )
    target_link_libraries( ${basename}_t pdclibs )
    add_test( ${basename}_t test_support/testdrivers/${basename}_t )
    add_dependencies( testdrivers ${basename}_t )

    # Regression test driver, _r suffix, compiled with -DTEST -DREGTEST
    # against system libc.
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

###########################################################################
# Executables meant for library maintainers, not for distribution         #
###########################################################################

# A helper executable to read, from the system library, this platform's
# errno numbers and perror() / strerror() texts, to faciliate adapting
# PDCLib to use the same numbers / texts on any given platform.
# (Platform maintainers are supposed to use the output to adapt their
# platform's platform/<xyz>/functions/_PDCLIB/_PDCLIB_stdinit.c and
# platform/<xyz>/include/pdclib/_PDCLIB_config.h.)
add_subdirectory( auxiliary/errno )

# A helper executable to parse up-to-date Unicode metadata from the
# Unicode database.
add_subdirectory( auxiliary/uctype )

# A helper executable to read, from the system <pthread.h>, some size
# parameters of pthread stuctures.
# (Platform maintainers are supposed to use the output to adapt their
# platform's platform/<xyz>/include/pdclib/_PDCLIB_config.h.)
add_subdirectory( auxiliary/pthread )

# A helper executable storing a given floating point number into the
# various FP data types of the platform (float, double, long double, ...)
# and displaying their encoding. Nothing more than a "I understood those
# encodings correctly" confidence check.
add_subdirectory( auxiliary/fpconvert )
