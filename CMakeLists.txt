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
project(hypro CXX)

set(PROJECT_FULLNAME "HyPro")
set(PROJECT_DESCRIPTION "A Toolbox for the Reachability Analysis of Hybrid Systems using Geometric Approximations")
set(hypro_MAJORVERSION 0)
set(hypro_MINORVERSION 1)
set(hypro_MAINTENANCEVERSION 0)
set(hypro_VERSION "${hypro_MAJORVERSION}.${hypro_MINORVERSION}.${hypro_MAINTENANCEVERSION}")
set(PROJECT_VERSION "${hypro_MAJORVERSION}.${hypro_MINORVERSION}.${hypro_MAINTENANCEVERSION}")
set(hypro_NAME "HyPro" )
set(hypro_DESCRIPTION ${PROJECT_DESCRIPTION} )

# # # # # # # # # # # # # # # # # # # # # #
# B. Options
# # # # # # # # # # # # # # # # # # # # # #

# options
option(STATICLIB_SWITCH "Compile a statically linked version of the library." OFF)

# general compiler and linker settings
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -std=c++0x -fPIC")
if(${STATICLIB_SWITCH} STREQUAL "ON")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.so")
endif()

# path to put in the executables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message(“OSX”)
endif()

# # # # # # # # # # # # # # # # # # # # # #
# C. Find system tools and libraries.
#
# 1. Required libraries for core.
# 2. Optional libraries for core.
# 3. Development and debug libraries.
# # # # # # # # # # # # # # # # # # # # # #

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# # # # # # # # # # # # # # # # # # # # # #
# C.1. Required libraries for core.
# # # # # # # # # # # # # # # # # # # # # #

find_package(MPFR REQUIRED)
include_directories(${MPFR_INCLUDE_DIRS})
set(libraries ${libraries} ${MPFR_LIBRARY})

find_package(GMP REQUIRED)
include_directories(${GMP_INCLUDE_DIRS})
set(libraries ${libraries} ${GMP_LIBRARY})

# # # # # # # # # # # # # # # # # # # # # #
# C.2. required libraries
# # # # # # # # # # # # # # # # # # # # # #

#gTest as external project
#find_package(GTest REQUIRED)
if(${STATICLIB_SWITCH} STREQUAL "OFF")
    file(WRITE gtest.patch "")
    include(ExternalProject)
    set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/ThirdParty)
    
    #download gTest
    ExternalProject_Add(
        googletest
        SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
        SVN_REVISION -r 660
        TIMEOUT 10
        PATCH_COMMAND svn patch ${CMAKE_SOURCE_DIR}/gtest.patch ${CMAKE_BINARY_DIR}/ThirdParty/src/googletest
        # Force separate output paths for debug and release builds to allow easy
        # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                   -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
                   -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
                   -Dgtest_force_shared_crt=ON
        # Disable install step
        INSTALL_COMMAND ""
        # Wrap download, configure and build steps in a script to log output
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
    )

    ExternalProject_Get_Property(googletest source_dir)
    include_directories(${source_dir}/include)

    ExternalProject_Get_Property(googletest binary_dir)
    if(MSVC)
      set(Suffix ".lib")
    else()
      set(Suffix ".a")
      set(Pthread "-pthread")
    endif()
endif()

# # # # # # # # # # # # # # # # # # # # # #
# C.3. Development and debug libraries.
# # # # # # # # # # # # # # # # # # # # # #

# # # # # # # # # # # # # # # # # # # # # #
# D. Invoke subdirectories.
# # # # # # # # # # # # # # # # # # # # # #

add_subdirectory(src)
add_subdirectory(examples)
