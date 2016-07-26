# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# File: CMakeLists.txt                                        #
#                                                             #
# Project name: HyPro                                         #
# Contact:                  #
#	   Stefan Schupp stefan.schupp@cs.rwth-aachen.de      #
#                                                             #
# Author: Sebastian Junges, Stefan Schupp                     #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #


# # # # # # # # # # # # # # # # # # # # # #
# A. Project properties.
# B. Options.
# C. Find system tools and libraries.
# D. Invoke subdirectories.
# E. Export Compile Information.
# # # # # # # # # # # # # # # # # # # # # #

cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

# # # # # # # # # # # # # # # # # # # # # #
# A. Project properties
# # # # # # # # # # # # # # # # # # # # # #
project(hypro CXX C)

set(PROJECT_FULLNAME "HyPro")
set(PROJECT_DESCRIPTION "A Toolbox for the Reachability Analysis of Hybrid Systems using Geometric Approximations")
set(hypro_MAJORVERSION 0)
set(hypro_MINORVERSION 1)
set(hypro_MAINTENANCEVERSION 0)
set(hypro_VERSION "${hypro_MAJORVERSION}.${hypro_MINORVERSION}.${hypro_MAINTENANCEVERSION}")
set(PROJECT_VERSION "${hypro_VERSION}")
set(hypro_NAME "HyPro" )
set(hypro_DESCRIPTION ${PROJECT_DESCRIPTION} )

# path to find own modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# # # # # # # # # # # # # # # # # # # # # #
# B. Options
# # # # # # # # # # # # # # # # # # # # # #

# options
option(STATICLIB_SWITCH "Compile a statically linked version of the library." OFF)
option(FORCE_SHIPPED_RESOURCES "Make explicit use of the shipped resources." OFF)
option(USE_PPL "Use PPl polytope wrapper." OFF)
option(USE_COTIRE "Use the COmpilation TIme REducer." OFF)
option(USE_SMTRAT "Use SMT-RAT for linear solving." ON)
option(USE_Z3 "Use Z3 for linear solving." OFF)
option(CLANG_TIDY "Enable usage of clang-tidy" OFF )
option(LOGGING_HYPRO "Allow log4cplus logging." OFF)

# Include own macros.
include( hypromacros )

###########################################################################################
#### EXPORT SETTINGS
# Offer the user the choice of overriding the installation directories

set(INCLUDE_INSTALL_DIR include/ CACHE PATH "Installation directory for header files" )
set(LIB_INSTALL_DIR lib/ CACHE PATH "Installation directory for libraries")
set(BIN_INSTALL_DIR lib/ CACHE PATH "Installation directory for executables")

###########################################################################################

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	if (APPLE)
		message("-- Using clang on apple")
		set(CMAKE_MACOSX_RPATH 1)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
	else()
		message("-- Using clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
	set(CMAKE_CXX_RELEASE_FLAGS "${CMAKE_CXX_RELEASE_FLAGS} -O3")
	set(CMAKE_CXX_DEBUG_FLAGS "${CMAKE_CXX_DEBUG_FLAGS} -g -O0")
	set(USE_CLANG PARENT SCOPE)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	message("-- Using g++")
	#if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
#		message(FATAL_ERROR " g++ version must be at least 4.9!")
	#endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	set(CMAKE_CXX_RELEASE_FLAGS "${CMAKE_CXX_RELEASE_FLAGS} -O3")
	set(CMAKE_CXX_DEBUG_FLAGS "${CMAKE_CXX_DEBUG_FLAGS} -g -O1")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=auto")
	endif()
else()
	message("-- Possibly unsupported compiler")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# general compiler and linker settings
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo
MinSizeRel." FORCE)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11 -fPIC -DBOOST_SPIRIT_USE_PHOENIX_V3=1")
if(${STATICLIB_SWITCH} STREQUAL "ON")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.so")
endif()

# path to put in the executables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_USE_OWN_TR1_TUPLE=1")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	if(${STATICLIB_SWITCH} STREQUAL "OFF")
		set(CMAKE_MACOSX_RPATH 1)
	endif()
endif()

if(USE_COTIRE)
	# We use cotire, simply include it
	message(STATUS "using cotire")
	include(cotire)
else()
	# We do not use cotire, create dummy function.
	message(STATUS "not using cotire")
	function(cotire)
	endfunction(cotire)
endif()

# # # # # # # # # # # # # # # # # # # # # #
# C. Find system tools and libraries.
#
# 1. Required libraries for core.
# 2. Optional libraries for core.
# 3. Development and debug libraries.
# # # # # # # # # # # # # # # # # # # # # #

# # # # # # # # # # # # # # # # # # # # # #
# C.1. Required libraries for core.
# # # # # # # # # # # # # # # # # # # # # #
find_package(Boost REQUIRED)
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON) 
set(Boost_USE_STATIC_RUNTIME    OFF) 
find_package(Boost 1.55.0 COMPONENTS program_options) 
if(Boost_FOUND)   
	include_directories(${Boost_INCLUDE_DIRS})   
	set(libraries ${libraries} ${Boost_LIBRARIES})
endif()
find_package(carl REQUIRED)
include_directories(${carl_INCLUDE_DIR})
set(libraries ${libraries} ${carl_LIBRARIES})
set(INCLUDES ${INCLUDES} ${carl_INCLUDE_DIR})
if(carl_FOUND)
    MESSAGE(STATUS "Found carl: ${carl_LIBRARIES}")
else()
    MESSAGE(FATAL_ERROR "Could not find carl")
endif()

if(USE_PPL)
	find_package(PPL REQUIRED)
	include_directories(${PPL_INCLUDES})
	set(libraries ${libraries} ${PPL_LIBRARIES})
endif()

if(USE_SMTRAT)
find_package(smtrat REQUIRED)
if(smtrat_FOUND)
    MESSAGE(STATUS "Found smtrat: ${smtrat_LIBRARIES}")
endif()
include_directories(${smtrat_INCLUDE_DIR})
set(libraries ${libraries} ${smtrat_LIBRARIES})
set(INCLUDES ${INCLUDES} ${smtrat_INCLUDE_DIR})
endif()

if(USE_Z3)
	find_package(z3 REQUIRED)
	include_directories(${z3_INCLUDE_DIRS})
		MESSAGE(${z3_LIBRARY})
	set(libraries ${libraries} ${z3_LIBRARY})
endif()

#find_package(Eigen3 REQUIRED)
#include_directories(${EIGEN3_INCLUDE_DIR})
#set(INCLUDES ${INCLUDES} ${EIGEN3_INCLUDE_DIR})
#set(libraries ${libraries} ${EIGEN3_LIBRARY})

if(NOT FORCE_SHIPPED_RESOURCES)
find_package(GTest)
find_package(GLPK)
endif()

add_subdirectory(src/resources EXCLUDE_FROM_ALL)

include_directories( ${GLPK_INCLUDE_DIR} )
set(libraries ${libraries} ${GLPK_LIBRARIES} pthread)

if(LOGGING_HYPRO)
	include_directories( ${LOG4CPLUS_INCLUDE_DIRS} )
	set(libraries ${libraries} ${LOG4CPLUS_LIBRARIES} )
endif()

if(CLANG_TIDY)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	set(CLANG_TIDY_CHECKS "*")
	set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-llvm-header-guard")
	#set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-google-readability-namespace-comments,-llvm-namespace-comment")
	#set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-google-readability-braces-around-statements,-readability-braces-around-statements")
	#set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-readability-else-after-return")
	#set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-google-readability-todo")
	#set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-google-runtime-int")
	#set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-misc-macro-parentheses")
	#set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-clang-analyzer-alpha.core.CastToStruct")
	set(CLANG_TIDY_CHECKS "-checks='${CLANG_TIDY_CHECKS}'")
	message(STATUS "Enabled checks for clang-tidy: ${CLANG_TIDY_CHECKS}")
endif()

include_directories( src/lib )
add_subdirectory(src)

enable_testing()
add_subdirectory(src/test)

# # # # # # # # # # # # # # # # # # # # # #
# C.2. required libraries
# # # # # # # # # # # # # # # # # # # # # #

# # # # # # # # # # # # # # # # # # # # # #
# C.3. Development and debug libraries.
# # # # # # # # # # # # # # # # # # # # # #

add_subdirectory(doc EXCLUDE_FROM_ALL)

# # # # # # # # # # # # # # # # # # # # # #
# D. Invoke subdirectories.
# # # # # # # # # # # # # # # # # # # # # #

add_subdirectory(examples EXCLUDE_FROM_ALL)

##############################################################################
#### EXPORT SETTINGS

# # # # # # # # # # # # # # # # # # # # # #
# E. Export Compile Information.
# # # # # # # # # # # # # # # # # # # # # #

# Add all targets to the build-tree export set
export(TARGETS ${HYPRO_TARGETS} FILE "${PROJECT_BINARY_DIR}/hyproTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE ${PROJECT_NAME})

include(CMakePackageConfigHelpers)
# Create the hyproConfig.cmake and hyproConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src") # TODO looks not correct, this would be hypro_INCLUDE_DIR
set(CONF_INCLUDES ${INCLUDES})
set(CONF_LINKER_LIBS ${libraries})
#message(STATUS ${libraries})
configure_package_config_file(cmake/Modules/hyproConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/hyproConfig.cmake
							  INSTALL_DESTINATION ${PROJECT_BINARY_DIR}
							  PATH_VARS PROJECT_BINARY_DIR #SYSCONFIG_INSTALL_DIR
							 )

# ... for the install tree
set(CONF_INCLUDE_DIRS "\${hypro_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_package_config_file(cmake/Modules/hyproConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/hyproConfig.cmake
							  INSTALL_DESTINATION ${PROJECT_BINARY_DIR}
							  PATH_VARS PROJECT_BINARY_DIR #SYSCONFIG_INSTALL_DIR
			 )
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/hyproConfigVersion.cmake
								 VERSION 0.1.0
								 COMPATIBILITY SameMajorVersion )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/hyproConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/hyproConfigVersion.cmake
		DESTINATION ${PROJECT_BINARY_DIR} )

# Install the export set for use with the install-tree
#install(EXPORT ${HYPRO_TARGETS} DESTINATION ${PROJECT_BINARY_DIR}) # COMPONENT dev)
