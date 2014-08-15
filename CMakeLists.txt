##############################################################################
# Project Settings and Properties
##############################################################################
cmake_minimum_required( VERSION 2.8 )

project( eloquentd )

ADD_DEFINITIONS( -std=c++11 )

set( target ConsoleWriter )

##############################################################################
# Header Search Paths
##############################################################################
set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME	 OFF)

find_package( Boost 1.55.0 COMPONENTS system filesystem thread regex program_options )

if(Boost_FOUND)
	include_directories( ${Boost_INCLUDE_DIRS} )
endif()

include_directories( "${PROJECT_SOURCE_DIR}/Internal" )
include_directories( "${PROJECT_SOURCE_DIR}/External" )

include_directories( "/usr/include" )
include_directories( "/usr/local/include" )
include_directories( "/opt/local/include" )
include_directories( "/usr/local/include/Eloquent" )

##############################################################################
# Library Search Paths
##############################################################################
link_directories( "/usr/lib" )
link_directories( "/usr/local/lib" )
link_directories( "/opt/local/lib" )

##############################################################################
# Build
##############################################################################
file( GLOB src
	"${PROJECT_SOURCE_DIR}/*.cpp"
)

set( lib
	${Boost_SYSTEM_LIBRARY}
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_REGEX_LIBRARY}
	streamlog
	Eloquent
)

add_library( ${target} SHARED ${src} )
target_link_libraries( ${target} ${lib} )

##############################################################################
# Install
##############################################################################
if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
	set_target_properties( ${target} PROPERTIES MACOSX_RPATH 1 )
endif()

install( TARGETS ${target} LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/eloquent/extensions" )