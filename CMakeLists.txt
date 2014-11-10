##############################################################################
# Project Settings and Properties
##############################################################################
cmake_minimum_required( VERSION 2.8 )

set( target ConsoleWriter )

set( CMAKE_CXX_FLAGS                "-Wall -std=c++11" )
set( CMAKE_CXX_FLAGS_DEBUG          "-g" )
set( CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG" )
set( CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG" )
set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g" )

##############################################################################
# Header Search Paths
##############################################################################
include_directories( "${PROJECT_SOURCE_DIR}/Internal" )
include_directories( "${PROJECT_SOURCE_DIR}/External" )

include_directories( "/opt/local/include" )
include_directories( "/usr/local/include" )
include_directories( "/usr/local/include/Eloquent" )
include_directories( "/usr/include" )

##############################################################################
# Library Search Paths
##############################################################################
link_directories( "/opt/local/lib" )
link_directories( "/usr/local/lib" )
link_directories( "/usr/lib" )


##############################################################################
# Build
##############################################################################
file( GLOB src "${PROJECT_SOURCE_DIR}/*.cpp" )

set( lib Eloquent )

add_library( ${target} SHARED ${src} )
target_link_libraries( ${target} ${lib} )

##############################################################################
# Install
##############################################################################
if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
	set_target_properties( ${target} PROPERTIES MACOSX_RPATH 1 )
endif()

install( TARGETS ${target} LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/eloquent/extensions" )
