set(hypro_VERSION 17.09)

get_filename_component(hypro_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)


if(NOT TARGET lib_carl)
  add_library(lib_carl SHARED IMPORTED)
  set_target_properties(lib_carl PROPERTIES IMPORTED_LOCATION "/home/justin/Documents/Masterarbeit/repo/carl/build/libcarl.so.17.08")
  set_target_properties(lib_carl PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "/home/justin/Documents/Masterarbeit/repo/carl/src")
endif()

if(NOT TARGET GLPK_STATIC)
  add_library(GLPK_STATIC STATIC IMPORTED)
  set_target_properties(GLPK_STATIC PROPERTIES IMPORTED_LOCATION "/home/justin/Documents/Masterarbeit/repo/hypro/src/resources/glpk-4.45/build/lib/libglpk.a")
  set_target_properties(GLPK_STATIC PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "/home/justin/Documents/Masterarbeit/repo/hypro/src/resources/glpk-4.45/build/include")
endif()

if(NOT TARGET Boost_SHARED)
  add_library(Boost_SHARED SHARED IMPORTED)
  set_target_properties(Boost_SHARED PROPERTIES IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libboost_system.so")
  set_target_properties(Boost_SHARED PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "/usr/include")
endif()

if(NOT TARGET EIGEN3)
  add_library(EIGEN3 INTERFACE IMPORTED)
  set_target_properties(EIGEN3 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "/home/justin/Documents/Masterarbeit/repo/carl/build/resources/include")
endif()

if(NOT TARGET GMP_SHARED)
  add_library(GMP_SHARED SHARED IMPORTED)
  set_target_properties(GMP_SHARED PROPERTIES IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libgmp.so")
  set_target_properties(GMP_SHARED PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "/usr/include/x86_64-linux-gnu")
endif()

if(NOT TARGET GMP_STATIC)
  add_library(GMP_STATIC STATIC IMPORTED)
  set_target_properties(GMP_STATIC PROPERTIES IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libgmp.a")
  set_target_properties(GMP_STATIC PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "/usr/include/x86_64-linux-gnu")
endif()

if(NOT TARGET GMPXX_SHARED)
  add_library(GMPXX_SHARED SHARED IMPORTED)
  set_target_properties(GMPXX_SHARED PROPERTIES IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libgmpxx.so")
  set_target_properties(GMPXX_SHARED PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "/usr/include")
endif()

if(NOT TARGET GMPXX_STATIC)
  add_library(GMPXX_STATIC STATIC IMPORTED)
  set_target_properties(GMPXX_STATIC PROPERTIES IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libgmpxx.a")
  set_target_properties(GMPXX_STATIC PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "/usr/include")
endif()
set_target_properties(GMPXX_STATIC PROPERTIES IMPORTED_LINK_INTERFACE_LIBRARIES "GMP_STATIC")

if(NOT TARGET ANTLR4_STATIC)
  add_library(ANTLR4_STATIC STATIC IMPORTED)
  set_target_properties(ANTLR4_STATIC PROPERTIES IMPORTED_LOCATION "/home/justin/Documents/Masterarbeit/repo/hypro/src/resources/antlr_build/lib/libantlr4-runtime.a")
  set_target_properties(ANTLR4_STATIC PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "/home/justin/Documents/Masterarbeit/repo/hypro/src/resources/antlr_build/include/antlr4-runtime")
endif()


# Our library dependencies (contains definitions for IMPORTED targets)
if(NOT TARGET hypro AND NOT hypro_BINARY_DIR)
  include("${hypro_CMAKE_DIR}/hyproTargets.cmake")
endif()


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was hyproConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(hypro_INCLUDE_DIR "${hypro_CMAKE_DIR}/../../../include")
set(hypro_INCLUDE_DIRS "")
set(hypro_INCLUDES "")
set(hypro_LINKER_LIBS "")
set(hypro_LIBRARIES hypro)
check_required_components(hypro)
