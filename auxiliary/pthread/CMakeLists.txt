cmake_minimum_required( VERSION 2.9 FATAL_ERROR )

project( pthread_readout LANGUAGES C )

set( CMAKE_C_STANDARD 11 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_EXTENSIONS OFF )

add_executable( pthread_readout pthread_readout.c )

# For this executable specifically, make the _PDCLIB_* headers available
# but *not* PDCLib's standard headers -- so we can check PDCLib config
# against the host system.
target_include_directories( pthread_readout BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/include/pdclib ${CMAKE_SOURCE_DIR}/platform/example/include/pdclib )

# PThread linkage.
set( CMAKE_THREAD_PREFER_PTHREAD 1 )
set( THREADS_PREFER_PTHREAD_FLAG 1 )
find_package( Threads )

if ( NOT CMAKE_USE_PTHREADS_INIT )
    message( FATAL_ERROR "Cannot find pthread." )
endif()

target_link_libraries( pthread_readout Threads::Threads )
