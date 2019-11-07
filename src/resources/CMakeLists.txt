
# initialize lists for include directories and library files
set(${PROJECT_NAME}_INCLUDE_DIRS "" CACHE STRING "Include directories var")

load_library(${PROJECT_NAME} GTest 0)

load_library(${PROJECT_NAME} carl 0)

add_custom_target(resources)

# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET(EP_PREFIX_DIR ${CMAKE_BINARY_DIR}/resources )
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${EP_PREFIX_DIR} )

if(carl_FOUND)
	message("-- Use system version of CArL")
else()
	message( FATAL_ERROR "Please install a version of CArL." )
	#message("-- Download version of CArL")
	#include(carl.cmake)
	## try again loading carl.
	#load_library(${PROJECT_NAME} carl 0)
	#if(carl_FOUND)
#		message("Found carl.")
	#	include(${CMAKE_BINARY_DIR}/resources/src/CArL-EP-build/carlConfig.cmake)
	#endif()
endif()

if(GTEST_FOUND)
	set(GTEST_LIBRARIES ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} PARENT_SCOPE)
	message("-- Use system version of GTest")
else()
	message("-- Download version of GTest")
	include(gtest.cmake)
endif()

include(glpk.cmake)

find_package(UUID QUIET)
if(NOT UUID_FOUND)
	message(SEND_ERROR "Package uuid-dev required to build antlr.")
endif()

#set variable pointing to antlr tool
#set(ANTLR4CPP_JAR_LOCATION ${PROJECT_SOURCE_DIR}/src/resources/antlr-4.7-complete.jar)
#include external cmake file
include(ExternalAntlr4Cpp.cmake)

# # # # # # # # # # # # # # # # # # # # # #
# C.2. Optional libraries
# # # # # # # # # # # # # # # # # # # # # #

if(HYPRO_USE_COTIRE)
	# We use cotire, simply include it
	message(STATUS "using cotire")
	include(cotire)
else()
	# We do not use cotire, create dummy function.
	message(STATUS "not using cotire")
	function(cotire)
	endfunction(cotire)
endif()

if(HYPRO_USE_PPL)
	load_library(${PROJECT_NAME} PPL 0)
endif()

if(HYPRO_USE_SMTRAT)
	find_package(smtrat)
endif()

if(HYPRO_USE_Z3)
	load_library(${PROJECT_NAME} z3 0)
endif()

if(HYPRO_USE_SOPLEX)
	load_library(${PROJECT_NAME} soplex 0)
endif()

if(HYPRO_USE_OPENMP)
	load_library(${PROJECT_NAME} OpenMP 0)
	if(OPENMP_FOUND)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
	endif()
endif()
