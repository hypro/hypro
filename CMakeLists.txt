# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# File: CMakeLists.txt                                        #
#                                                             #
# Project name: HyPro                                         #
# Contact:                  #
#	   Stefan Schupp stefan.schupp@cs.rwth-aachen.de      #
#                                                             #
# Author: Stefan Schupp
# Credit: Sebastian Junges, Gereon Kremer
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

# # # # # # # # # # # # # # # # # # # # # #
# A. Project properties
# # # # # # # # # # # # # # # # # # # # # #
project(hypro CXX C)

set(PROJECT_FULLNAME "HyPro")
set(PROJECT_DESCRIPTION "A Toolbox for the Reachability Analysis of Hybrid Systems using Geometric Approximations")
string(TIMESTAMP hypro_MINORVERSION %m)
string(TIMESTAMP hypro_MAJORVERSION %y)
set(hypro_VERSION "${hypro_MAJORVERSION}.${hypro_MINORVERSION}")
set(PROJECT_VERSION "${hypro_VERSION}")
set(hypro_NAME "HyPro" )
set(hypro_DESCRIPTION ${PROJECT_DESCRIPTION})

# path to find own modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}/cmake/Modules/")
# Include own macros.
include( hypromacros )

# # # # # # # # # # # # # # # # # # # # # #
# B. Options
# # # # # # # # # # # # # # # # # # # # # #

# options
option(STATICLIB_SWITCH "Compile a statically linked version of the library." OFF)
option(HYPRO_USE_COTIRE "Use the COmpilation TIme REducer." OFF)
option(HYPRO_USE_OPENMP "Use OpenMp for parallelization in Eigen3." OFF)
option(HYPRO_USE_PPL "Use PPl polytope wrapper." OFF)
option(HYPRO_BUILD_OFFLINE "Do not attempt to update ressources (work offline)." OFF)
option(HYPRO_LOGGING "Allow logging." ON)
option(HYPRO_MATLAB_BINDINGS "Create Matlab bindings." OFF)
option(HYPRO_COVERAGE "Enable compiler flags for test coverage diagnostics." OFF)
option(HYPRO_STATISTICS "Create a statistic file." OFF)
option(CLANG_TIDY "Enable usage of clang-tidy" OFF )
option(CREATE_DOC "Allow creation of a doxygen documentation." OFF)
option(DOC_CREATE_PDF "Create pdf document for documentation." OFF)
option(DEVELOPER "Compile in developer mode, i.e. more warnings." OFF)
option(EXPORT_TO_CMAKE "Export the project to CMake for easy inclusion" ON)
option(RESET_REFINEMENT "Return to Level 0 after successful backtracking" ON)
mark_as_advanced(HYPRO_COVERAGE)
mark_as_advanced(HYPRO_BUILD_OFFLINE)
mark_as_advanced(HYPRO_STATISTICS)
mark_as_advanced(HYPRO_MATLAB_BINDINGS)
mark_as_advanced(CLANG_TIDY)
mark_as_advanced(DEVELOPER)
mark_as_advanced(RESET_REFINEMENT)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug Release" FORCE)
endif()
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")

# handling of optimization backends
include(optimization_backends)

if(HYPRO_BUILD_OFFLINE)
set_property(DIRECTORY ${hypro_SOURCE_DIR} PROPERTY EP_UPDATE_DISCONNECTED 1)
endif()

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/.travis/sonar-project.properties.in ${CMAKE_CURRENT_SOURCE_DIR}/.travis/sonar-project.properties )

###########################################################################################
#### EXPORT SETTINGS
# Offer the user the choice of overriding the installation directories

set(INCLUDE_INSTALL_DIR include/ CACHE PATH "Installation directory for header files" )
set(LIB_INSTALL_DIR lib/ CACHE PATH "Installation directory for libraries")
set(BIN_INSTALL_DIR lib/ CACHE PATH "Installation directory for executables")
# path to put in the executables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/${PROJECT_NAME})
endif()
set(CMAKE_INSTALL_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

foreach(p LIB BIN INCLUDE CMAKE)
  set(var ${p}_INSTALL_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

include(compiler-settings)

###########################################################################################

# # # # # # # # # # # # # # # # # # # # # #
# C. Find system tools and libraries.
#
# 1. Required libraries for core.
# 2. Optional libraries for core.
# 3. Development and debug libraries.
# # # # # # # # # # # # # # # # # # # # # #

load_library(${PROJECT_NAME} GTest 0)

#load_library(${PROJECT_NAME} carl 19.01)
load_library(${PROJECT_NAME} carl 0)
include(carlVersionMacros)

add_subdirectory(src/resources)

# # # # # # # # # # # # # # # # # # # # # #
# C.3. Development and debug libraries.
# # # # # # # # # # # # # # # # # # # # # #

if(CLANG_TIDY)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	set(CLANG_TIDY_CHECKS "google,modernize,performance,portability,readability")
	#set(CLANG_TIDY_CHECKS "*")
	#set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-llvm-header-guard")
	#set(CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS},-cppcoreguidelines")
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


enable_testing()

# # # # # # # # # # # # # # # # # # # # # #
# D. Invoke subdirectories.
# # # # # # # # # # # # # # # # # # # # # #

add_subdirectory(src)
add_subdirectory(src/test)
add_subdirectory(examples EXCLUDE_FROM_ALL)


##############################################################################
#### EXPORT SETTINGS

# # # # # # # # # # # # # # # # # # # # # #
# E. Export Compile Information.
# # # # # # # # # # # # # # # # # # # # # #

include(export)


if(CREATE_DOC)
	add_subdirectory(doc EXCLUDE_FROM_ALL)
endif()

# # # # # # # # # # # # # # # # # # # # # #
# F. Adding tool folder.
# # # # # # # # # # # # # # # # # # # # # #

add_subdirectory(src/tool)
