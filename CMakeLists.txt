<<<<<<< .mine
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
option(FORCE_SHIPPED_RESOURCES "Make explicit use of the shipped resources." OFF)

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
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_USE_OWN_TR1_TUPLE=1")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	message(OSX)
	#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--with-gcc-toolchain") 
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

find_package(carl REQUIRED)
include_directories(${carl_INCLUDE_DIR})
set(libraries ${libraries} ${carl_LIBRARIES})
if(carl_FOUND)
    MESSAGE(STATUS "Found carl: ${carl_INCLUDE_DIR}")
else()
    MESSAGE(FATAL_ERROR "Could not find carl")
endif()

find_package(CLN REQUIRED)
include_directories(${CLN_INCLUDE_DIRS})
set(libraries ${libraries} ${CLN_LIBRARY})

find_package(MPFR REQUIRED)
include_directories(${MPFR_INCLUDE_DIRS})
set(libraries ${libraries} ${MPFR_LIBRARY})

find_package(GMP REQUIRED)
include_directories(${GMP_INCLUDE_DIRS})
set(libraries ${libraries} ${GMP_LIBRARY})

find_package(PPL REQUIRED)
include_directories(${PPL_INCLUDES})
set(libraries ${libraries} ${PPL_LIBRARIES})

find_package(GLPK REQUIRED)
include_directories(${GLPK_INCLUDES})
set(libraries ${libraries} ${GLPK_LIBRARIES})

find_package(NLOPT REQUIRED)
include_directories(${NLOPT_INCLUDES})
set(libraries ${libraries} ${NLOPT_LIBRARIES})

if(NOT FORCE_SHIPPED_RESOURCES)
find_package(Log4cplus)
find_package(Eigen3)
find_package(GTest)
endif()

add_subdirectory(src)

enable_testing()

set(libraries ${libraries} ${EIGEN3_LIBRARY} ${GTEST_LIBRARIES} ${LOG4CPLUS_LIBRARY} pthread)
include_directories( ${include_directories} ${EIGEN3_INCLUDE_DIR} ${LOG4CPLUS_INCLUDE_DIR} )

add_subdirectory(src/test)

# # # # # # # # # # # # # # # # # # # # # #
# C.2. required libraries
# # # # # # # # # # # # # # # # # # # # # #

# # # # # # # # # # # # # # # # # # # # # #
# C.3. Development and debug libraries.
# # # # # # # # # # # # # # # # # # # # # #

# # # # # # # # # # # # # # # # # # # # # #
# D. Invoke subdirectories.
# # # # # # # # # # # # # # # # # # # # # #

=======
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
option(FORCE_SHIPPED_RESOURCES "Make explicit use of the shipped resources." OFF)

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
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_USE_OWN_TR1_TUPLE=1")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	message(-- using clang++)
	#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--with-gcc-toolchain") 
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

find_package(carl REQUIRED)
include_directories(${carl_INCLUDE_DIR})
set(libraries ${libraries} ${carl_LIBRARIES})
if(carl_FOUND)
    MESSAGE(STATUS "Found carl: ${carl_INCLUDE_DIR}")
else()
    MESSAGE(FATAL_ERROR "Could not find carl")
endif()

find_package(CLN REQUIRED)
include_directories(${CLN_INCLUDE_DIRS})
set(libraries ${libraries} ${CLN_LIBRARY})

find_package(MPFR REQUIRED)
include_directories(${MPFR_INCLUDE_DIRS})
set(libraries ${libraries} ${MPFR_LIBRARY})

find_package(GMP REQUIRED)
include_directories(${GMP_INCLUDE_DIRS})
set(libraries ${libraries} ${GMP_LIBRARY})

find_package(PPL REQUIRED)
include_directories(${PPL_INCLUDES})
set(libraries ${libraries} ${PPL_LIBRARIES})

if(NOT FORCE_SHIPPED_RESOURCES)
find_package(Log4cplus)
find_package(Eigen3)
find_package(GTest)
endif()

add_subdirectory(src)

enable_testing()

set(libraries ${libraries} ${EIGEN3_LIBRARY} ${GTEST_LIBRARIES} ${LOG4CPLUS_LIBRARY} pthread)
include_directories( ${include_directories} ${EIGEN3_INCLUDE_DIR} ${LOG4CPLUS_INCLUDE_DIR} )

add_subdirectory(src/test)

# # # # # # # # # # # # # # # # # # # # # #
# C.2. required libraries
# # # # # # # # # # # # # # # # # # # # # #

# # # # # # # # # # # # # # # # # # # # # #
# C.3. Development and debug libraries.
# # # # # # # # # # # # # # # # # # # # # #

# # # # # # # # # # # # # # # # # # # # # #
# D. Invoke subdirectories.
# # # # # # # # # # # # # # # # # # # # # #

>>>>>>> .r282
add_subdirectory(examples EXCLUDE_FROM_ALL)