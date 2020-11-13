cmake_minimum_required( VERSION 2.9 FATAL_ERROR )

project( fpconvert LANGUAGES C )

include( CheckIncludeFile )

set( CMAKE_REQUIRED_QUIET ON )
CHECK_INCLUDE_FILE( quadmath.h QUADMATH )

add_executable( fpconvert fpconvert.c )

if ( QUADMATH )
    target_link_libraries( fpconvert quadmath )
endif()
