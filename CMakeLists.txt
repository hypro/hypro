# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                             #
# File: CMakeLists.txt                                        #
#                                                             #
# Project name: HyPro                                         #
# Contact: Xin Chen chen@cs.rwth-aachen.de                    #
#	   Stefan Schupp stefan.schupp@cs.rwth-aachen.de      #
#                                                             #
# Author: Sebastian Junges, Stefan Schupp                     #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #


# # # # # # # # # # # # # # # # # # # # # #
# A. Project properties.
# B. Options.
# C. Find system tools and libraries.
# D. Invoke subdirectories.
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
option(COMPARE_CDD "Validate and test against Komei Fukudas cddlib." OFF)
option(COMPARE_POLYMAKE "Validate and test against polymake." OFF)
option(USE_COTIRE "Use the COmpilation TIme REducer." ON)
option(USE_OPENGL_PLOTTING "Use OpenGL plotting." OFF)
option(USE_SMTRAT "Use SMT-RAT for linear solving." OFF)
option(EXTERNALIZE_CLASSES "Use EXTERNALIZE_CLASSES." OFF)
option(EXTERNALIZE_CLASSES_ONLY_TO_TEST "An EXTERNALIZE_CLASSES for test purposes." OFF)

# Include own macros.
include( hypromacros )

if (CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 4.9 OR CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=auto")
endif()

# general compiler and linker settings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -fPIC")
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
	#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--with-gcc-toolchain")
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

find_package(carl REQUIRED)
include_directories(${carl_INCLUDE_DIR})
set(libraries ${libraries} ${carl_LIBRARIES})
if(carl_FOUND)
    MESSAGE(STATUS "Found carl: ${carl_INCLUDE_DIR}")
else()
    MESSAGE(FATAL_ERROR "Could not find carl")
endif()

#find_package(CLN REQUIRED)
#include_directories(${CLN_INCLUDE_DIRS})
#set(libraries ${libraries} ${CLN_LIBRARY})

#if(SUPPORT_MPFR)
#	find_package(MPFR REQUIRED)
#	include_directories(${MPFR_INCLUDE_DIRS})
#	set(libraries ${libraries} ${MPFR_LIBRARY})
#endif()

if(COMPARE_CDD)
	find_package(cdd REQUIRED)
endif()

if(COMPARE_POLYMAKE)
	find_package(Polymake REQUIRED)
endif()

if(USE_OPENGL_PLOTTING)
	find_package(Glut REQUIRED)
  include_directories(${Glut_INCLUDE_DIR})
  set(libraries ${libraries} ${Glut_LIBRARY})
endif()

#find_package(GMP REQUIRED)
#include_directories(${GMP_INCLUDE_DIRS} ${LIBCDD_INCLUDE_DIRS})
#set(libraries ${libraries} ${GMP_LIBRARY} ${LIBCDD_LIBRARIES})

find_package(PPL REQUIRED)
include_directories(${PPL_INCLUDES})
set(libraries ${libraries} ${PPL_LIBRARIES})

if(USE_SMTRAT)
find_package(smtrat REQUIRED)
if(smtrat_FOUND)
    MESSAGE(STATUS "Found smtrat: ${smtrat_INCLUDE_DIR}")
endif()
include_directories(${smtrat_INCLUDE_DIR})
set(libraries ${libraries} ${smtrat_LIBRARIES})
endif()

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
set(libraries ${libraries} ${EIGEN3_LIBRARY})

if(NOT FORCE_SHIPPED_RESOURCES)
find_package(GTest)
find_package(GLPK)
endif()

add_subdirectory(src)

enable_testing()

set(libraries ${libraries} ${GTEST_LIBRARIES} ${GLPK_LIBRARIES} pthread)
include_directories( ${include_directories} ${GLPK_INCLUDE_DIR} )

get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

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
