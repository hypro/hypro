# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# File: CMakeLists.txt                                        #
#                                                             #
# Project name: HyPro                                         #
# Contact:                  #
#	   Stefan Schupp stefan.schupp@cs.rwth-aachen.de      #
#                                                             #
# Author: Stefan Schupp
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# # # # # # # # # # # # # # # # # # # # # #
# A. Project properties
# # # # # # # # # # # # # # # # # # # # # #
project(hypro CXX C)

set(PROJECT_FULLNAME "HyPro")
set(PROJECT_DESCRIPTION "A Toolbox for the Reachability Analysis of Hybrid Systems using Geometric Approximations")
set(hypro_VERSION "2.0.4")
set(PROJECT_VERSION "${hypro_VERSION}")
set(hypro_NAME "HyPro")
set(hypro_DESCRIPTION ${PROJECT_DESCRIPTION})

# path to find own modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}/cmake/Modules/")
# Include own macros.
include(hypromacros)

# # # # # # # # # # # # # # # # # # # # # #
# B. Options
# # # # # # # # # # # # # # # # # # # # # #

# options
option(STATICLIB_SWITCH "Compile a statically linked version of the library." OFF)
option(HYPRO_USE_COTIRE "Use the COmpilation TIme REducer." OFF)
option(HYPRO_USE_OPENMP "Use OpenMp for parallelization in Eigen3." OFF)
option(HYPRO_USE_MIMALLOC "replace standard malloc/realloc/free with mimalloc" OFF)
option(HYPRO_USE_PPL "Use PPl polytope wrapper." OFF)
option(HYPRO_USE_SERIALIZATION "Enable support for cereal for object serialization" ON)
option(HYPRO_ENABLE_SPACEEX_OUTPUT "Allow to output hybrid automata to SpaceEx format" OFF)
option(HYPRO_GSL_INTEGRATION "Link to gsl and provide numerical integration methods" OFF)
option(HYPRO_BUILD_OFFLINE "Do not attempt to update ressources (work offline)." OFF)
option(HYPRO_LOGGING "Allow logging." OFF)
option(HYPRO_MATLAB_BINDINGS "Create Matlab bindings." OFF)
option(HYPRO_COVERAGE "Enable compiler flags for test coverage diagnostics." OFF)
option(HYPRO_BENCHMARK "Enable usage of the google-benchmark library and the targets in test/case_studies." OFF)
option(HYPRO_STATISTICS "Create a statistic file." OFF)
option(CLANG_TIDY "Enable usage of clang-tidy" OFF)
option(CREATE_DOC "Allow creation of a doxygen documentation." OFF)
option(DOC_CREATE_PDF "Create pdf document for documentation." OFF)
option(DEVELOPER "Compile in developer mode, i.e. more warnings." OFF)
option(EXPORT_TO_CMAKE "Export the project to CMake for easy inclusion" ON)
option(RESET_REFINEMENT "Return to Level 0 after successful backtracking" ON)
option(QUICKHULL_USE_LOW_DIMENSIONAL_IMPROVEMENT "Use cheap method for computing normal vectors in 2 and 3 dimensions" ON)
mark_as_advanced(HYPRO_COVERAGE)
mark_as_advanced(HYPRO_BENCHMARK)
mark_as_advanced(HYPRO_BUILD_OFFLINE)
mark_as_advanced(HYPRO_STATISTICS)
mark_as_advanced(HYPRO_MATLAB_BINDINGS)
mark_as_advanced(CLANG_TIDY)
mark_as_advanced(DEVELOPER)
mark_as_advanced(RESET_REFINEMENT)
mark_as_advanced(EXPORT_TO_CMAKE)

include(printCustomOptions)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug Release" FORCE)
endif ()
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")

# policies
cmake_policy(VERSION 3.15) # sets all policies to NEW that are available in cmake 3.15

# handling of optimization backends
include(optimization_backends)

if (HYPRO_BUILD_OFFLINE)
    set_property(DIRECTORY ${hypro_SOURCE_DIR} PROPERTY EP_UPDATE_DISCONNECTED 1)
endif ()

file(RELATIVE_PATH relBinaryDir ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/.travis/sonar-project.properties.in ${CMAKE_CURRENT_SOURCE_DIR}/.travis/sonar-project.properties)

###########################################################################################
#### EXPORT SETTINGS
# Offer the user the choice of overriding the installation directories

set(INCLUDE_INSTALL_DIR include/ CACHE PATH "Installation directory for header files")
set(LIB_INSTALL_DIR lib/ CACHE PATH "Installation directory for libraries")
set(BIN_INSTALL_DIR lib/ CACHE PATH "Installation directory for executables")
# path to put in the executables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (WIN32 AND NOT CYGWIN)
    set(DEF_INSTALL_CMAKE_DIR CMake)
else ()
    set(DEF_INSTALL_CMAKE_DIR lib/cmake/${PROJECT_NAME})
endif ()
set(CMAKE_INSTALL_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

foreach (p LIB BIN INCLUDE CMAKE)
    set(var ${p}_INSTALL_DIR)
    if (NOT IS_ABSOLUTE "${${var}}")
        set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
    endif ()
endforeach ()

include(compiler-settings)

###########################################################################################

# # # # # # # # # # # # # # # # # # # # # #
# C. Find system tools and libraries.
#
# 1. Required libraries for core.
# 2. Optional libraries for core.
# 3. Development and debug libraries.
# # # # # # # # # # # # # # # # # # # # # #

# # # # # # # # # # # # # # # # # # # # # #
# C.3. Development and debug libraries.
# # # # # # # # # # # # # # # # # # # # # #

if (CLANG_TIDY)
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
endif ()

# # # # # # # # # # # # # # # # # # # # # #
# D. Invoke subdirectories.
# # # # # # # # # # # # # # # # # # # # # #

add_subdirectory(src)

add_library(${PROJECT_NAME}-objects OBJECT ${${PROJECT_NAME}_sources})
add_dependencies(${PROJECT_NAME}-objects hypro_resources)
build_target_include_dirs_from(${PROJECT_NAME}-objects SYSTEM PUBLIC GLPK_STATIC ANTLR4_SHARED clp_STATIC coinUtils_STATIC z3_SHARED)
target_include_directories(${PROJECT_NAME}-objects
        PRIVATE ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        )

########################################################################################
# Create static and shared libraries

add_library(${PROJECT_NAME}-static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}-objects>)
set_target_properties(${PROJECT_NAME}-static PROPERTIES
        VERSION "${PROJECT_VERSION}"
        SOVERSION "${PROJECT_VERSION}"
        OUTPUT_NAME ${PROJECT_NAME}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        LINKER_LANGUAGE CXX
        )

#target_link_libraries(${PROJECT_NAME}-static PUBLIC ${${PROJECT_NAME}_LIBRARIES_STATIC})
target_link_libraries(${PROJECT_NAME}-static PUBLIC pthread)

target_include_directories(${PROJECT_NAME}-static
        PRIVATE ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

##### SHARED LIBRARY

add_library(${PROJECT_NAME}-shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}-objects>)
set_target_properties(${PROJECT_NAME}-shared PROPERTIES
        VERSION "${PROJECT_VERSION}"
        SOVERSION "${PROJECT_VERSION}"
        OUTPUT_NAME ${PROJECT_NAME}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        LINKER_LANGUAGE CXX
        )

#target_link_libraries(${PROJECT_NAME}-shared PUBLIC ${${PROJECT_NAME}_LIBRARIES_DYNAMIC})
target_link_libraries(${PROJECT_NAME}-shared PUBLIC pthread)

target_include_directories(${PROJECT_NAME}-shared
        PRIVATE ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

target_compile_features(${PROJECT_NAME}-objects PUBLIC cxx_std_17)
target_compile_features(${PROJECT_NAME}-static PUBLIC cxx_std_17)
target_compile_features(${PROJECT_NAME}-shared PUBLIC cxx_std_17)

target_compile_options(${PROJECT_NAME}-objects PUBLIC -fPIC)
target_compile_options(${PROJECT_NAME}-static PUBLIC -fPIC)
target_compile_options(${PROJECT_NAME}-shared PUBLIC -fPIC)
target_compile_options(${PROJECT_NAME}-objects PRIVATE -Wall -Wextra -Wno-attributes -pedantic -ftemplate-backtrace-limit=0 -funroll-loops)
target_compile_options(${PROJECT_NAME}-static PRIVATE -Wall -Wextra -Wno-attributes -pedantic -ftemplate-backtrace-limit=0 -funroll-loops)
target_compile_options(${PROJECT_NAME}-shared PRIVATE -Wall -Wextra -Wno-attributes -pedantic -ftemplate-backtrace-limit=0 -funroll-loops)
if (${DEVELOPER})
    target_compile_options(${PROJECT_NAME}-objects PRIVATE -Wswitch -Wno-deprecated-declarations -Wempty-body -Wconversion -Wreturn-type -Wparentheses -Wno-format -Wuninitialized -Wunreachable-code -Wunused-function -Wunused-value -Wunused-variable -fsanitize=address -fstack-protector-strong -g)
    target_compile_options(${PROJECT_NAME}-static PRIVATE -Wswitch -Wno-deprecated-declarations -Wempty-body -Wconversion -Wreturn-type -Wparentheses -Wno-format -Wuninitialized -Wunreachable-code -Wunused-function -Wunused-value -Wunused-variable -fsanitize=address -fstack-protector-strong -g)
    target_compile_options(${PROJECT_NAME}-shared PRIVATE -Wswitch -Wno-deprecated-declarations -Wempty-body -Wconversion -Wreturn-type -Wparentheses -Wno-format -Wuninitialized -Wunreachable-code -Wunused-function -Wunused-value -Wunused-variable -fsanitize=address -fstack-protector-strong -g)
endif ()
#target_link_options(${PROJECT_NAME}-objects PUBLIC LINKER:-no-as-needed)
#target_link_options(${PROJECT_NAME}-static PUBLIC LINKER:-no-as-needed)
#target_link_options(${PROJECT_NAME}-shared PUBLIC LINKER:-no-as-needed)

# Meta-target which combines static and shared library
add_custom_target(${PROJECT_NAME} DEPENDS ${PROJECT_NAME}-shared ${PROJECT_NAME}-static)


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set_target_properties(${PROJECT_NAME}-shared PROPERTIES LINKER_LANGUAGE CXX INSTALL_RPATH "@loader_path/../lib")
    set_target_properties(${PROJECT_NAME}-static PROPERTIES LINKER_LANGUAGE CXX INSTALL_RPATH "@loader_path/../lib")
endif ()
set(HYPRO_TARGETS "${PROJECT_NAME}-shared" "${PROJECT_NAME}-static" CACHE STRING INTERNAL FORCE)


# Options for static linking
if (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mmacosx-version-min=10.7")
endif ()

########################################################################################

include(GNUInstallDirs)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.tpp")

install(TARGETS ${PROJECT_NAME}-static
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}/static)
install(TARGETS ${PROJECT_NAME}-shared
        EXPORT ${PROJECT_NAME}_Targets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        EXPORT ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT ${PROJECT_NAME}_Runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT ${PROJECT_NAME}_Runtime
        NAMELINK_COMPONENT ${PROJECT_NAME}_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT ${PROJECT_NAME}_Development
        )


add_subdirectory(resources)
# Create config.h by adding cmake defines dependent on option switches
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/hypro/flags.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/hypro/flags.h @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/hypro/paths.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/hypro/paths.h
        @ONLY)

enable_testing()
add_subdirectory(test)
add_subdirectory(examples EXCLUDE_FROM_ALL)

##############################################################################
#### EXPORT SETTINGS

# # # # # # # # # # # # # # # # # # # # # #
# E. Export Compile Information.
# # # # # # # # # # # # # # # # # # # # # #
include(export)


if (CREATE_DOC)
    add_subdirectory(doc EXCLUDE_FROM_ALL)
endif ()

# # # # # # # # # # # # # # # # # # # # # #
# F. Adding tool folder.
# # # # # # # # # # # # # # # # # # # # # #

add_subdirectory(src/tool)
