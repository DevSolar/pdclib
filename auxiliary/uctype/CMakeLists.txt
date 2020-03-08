cmake_minimum_required( VERSION 2.9 FATAL_ERROR )

project( get_uctypes LANGUAGES C )

set( CMAKE_C_STANDARD 11 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_EXTENSIONS OFF )

set( uctype_SOURCES
     derived_properties.c
     text_utilities.c
     uctype.c
     unicode_data.c
)

set( uctype_HEADERS
     derived_properties.h
     test.h
     text_utilities.h
     uctype.h
     unicode_data.h
)

add_library( uctype STATIC ${uctype_SOURCES} )
target_include_directories( uctype PRIVATE ${CMAKE_SOURCE_DIR} )

add_executable( get_uctypes main.c )
target_include_directories( get_uctypes PRIVATE ${CMAKE_SOURCE_DIR} )
target_link_libraries( get_uctypes uctype )

foreach( file ${uctype_SOURCES} )
    get_filename_component( basename ${file} NAME_WE )

    # Test driver.
    add_executable( ${basename}_t ${file} )
    set_property( TARGET ${basename}_t APPEND_STRING PROPERTY COMPILE_FLAGS "-DTEST" )

    if ( IGNORE_NO_TESTDRIVER )
        set_property( TARGET ${basename}_t APPEND_STRING PROPERTY COMPILE_FLAGS " -DNO_TESTDRIVER=1" )
    endif()

    target_include_directories( ${basename}_t PRIVATE ${CMAKE_SOURCE_DIR} )
    target_link_libraries( ${basename}_t uctype )
    add_test( ${basename}_t ${basename}_t )
endforeach()
