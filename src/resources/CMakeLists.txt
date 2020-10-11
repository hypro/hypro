
# initialize lists for include directories and library files
set(${PROJECT_NAME}_INCLUDE_DIRS "" CACHE STRING "Include directories var")

add_custom_target(resources)

# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET(EP_PREFIX_DIR ${CMAKE_BINARY_DIR}/resources )
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${EP_PREFIX_DIR} )

if(carl_FOUND)
	message(STATUS "Use system version of CArL")
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
	message(STATUS "Use system version of GTest")
else()
	message(STATUS "Download version of GTest")
	include(gtest.cmake)
endif()

include(glpk.cmake)

if(HYPRO_USE_CLP)
	message(STATUS "Use clp")
	include(clp.cmake)
endif()

find_package(UUID QUIET)
if(NOT UUID_FOUND)
	message(SEND_ERROR "Package uuid-dev required to build antlr.")
endif()

if(HYPRO_MATLAB_BINDINGS)
	include(matlab.cmake)
endif()

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

if(HYPRO_GSL_INTEGRATION)
	load_library(${PROJECT_NAME} GSL 0)
    #find_package(GSL)
    #if(GSL_FOUND)
    #    if(STATICLIB_SWITCH)
	#		add_library(GSL_STATIC STATIC} IMPORTED GLOBAL)
	#		set_target_properties(GSL_STATIC PROPERTIES IMPORTED_LOCATION "${GSL_LIBRARIES}")
	#		set_target_properties(GSL_STATIC PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${GSL_INCLUDE_DIR}")
    #    else()
	#		add_library(GSL_SHARED SHARED IMPORTED GLOBAL)
	#		set_target_properties(GSL_SHARED PROPERTIES IMPORTED_LOCATION "${GSL_LIBRARIES}")
	#		set_target_properties(GSL_SHARED PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${GSL_INCLUDE_DIR}")
	#	endif()
#
    #    list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${GSL_INCLUDE_DIR})
    #else()
    #    message(STATUS "Library ${name} was not found.")
    #endif()
endif()
