# -*- mode:cmake -*-
#
# This Cmake file is for those using a superbuild Cmake Pattern, it
# will download the tools and build locally
#
# use 2the antlr4cpp_process_grammar to support multiple grammars in the
# same project
#
# - Getting quicky started with Antlr4cpp
#
# Here is how you can use this external project to create the antlr4cpp
# demo to start your project off.
#
# create your project source folder somewhere. e.g. ~/srcfolder/
# + make a subfolder cmake
# + Copy this file to srcfolder/cmake
# + cut below and use it to create srcfolder/CMakeLists.txt,
# + from https://github.com/DanMcLaughlin/antlr4/tree/master/runtime/Cpp/demo Copy main.cpp, TLexer.g4 and TParser.g4 to ./srcfolder/
#
# next make a build folder e.g. ~/buildfolder/
# from the buildfolder, run cmake ~/srcfolder; make
#
###############################################################
# # minimum required CMAKE version
# CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12.2 FATAL_ERROR)
#
# LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )
#
# # compiler must be 11 or 14
# SET (CMAKE_CXX_STANDARD 11)
#
# # set variable pointing to the antlr tool that supports C++
# set(ANTLR4CPP_JAR_LOCATION /home/user/antlr4-4.5.4-SNAPSHOT.jar)
# # add external build for antlrcpp
# include( ExternalAntlr4Cpp )
# # add antrl4cpp artifacts to project environment
# include_directories( ${ANTLR4CPP_INCLUDE_DIRS} )
# link_directories( ${ANTLR4CPP_LIBS} )
# message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4CPP_INCLUDE_DIRS} ")
#
# # Call macro to add lexer and grammar to your build dependencies.
# antlr4cpp_process_grammar(demo antlrcpptest
#   ${CMAKE_CURRENT_SOURCE_DIR}/TLexer.g4
#   ${CMAKE_CURRENT_SOURCE_DIR}/TParser.g4)
# # include generated files in project environment
# include_directories(${antlr4cpp_include_dirs_antlrcpptest})
#
# # add generated grammar to demo binary target
# add_executable(demo main.cpp ${antlr4cpp_src_files_antlrcpptest})
# add_dependencies(demo antlr4cpp antlr4cpp_generation_antlrcpptest)
# target_link_libraries(demo antlr4-runtime)
#
###############################################################

# only JRE required
#FIND_PACKAGE(Java COMPONENTS Runtime REQUIRED)

set(ANTLR4CPP_LOCAL_REPO ${PROJECT_SOURCE_DIR}/src/resources/antlr4-cpp-runtime-4.7.1-source)

#if(NOT EXISTS "${ANTLR4CPP_JAR_LOCATION}")
#  message(FATAL_ERROR "Unable to find antlr tool. ANTLR4CPP_JAR_LOCATION:${ANTLR4CPP_JAR_LOCATION}")
#endif()

# default path for source files
if (NOT ANTLR4CPP_GENERATED_SRC_DIR)
  set(ANTLR4CPP_GENERATED_SRC_DIR ${CMAKE_BINARY_DIR}/antlr4cpp_generated_src)
endif()


# download runtime environment
ExternalProject_ADD(
  antlr4cpp
  #--Depend-on-antrl-tool-----------
  # DEPENDS antlrtool
  #--Core-directories-----------
  #PREFIX             ${ANTLR4CPP_EXTERNAL_ROOT}
  #PREFIX             ${ANTLR4CPP_BUILD_INCLUDE_DIR}		#Added for local copy
  #--Download step--------------
  # GIT_REPOSITORY    ${ANTLR4CPP_EXTERNAL_REPO}
  # GIT_TAG           ${ANTLR4CPP_EXTERNAL_TAG}
  URL  		      	  ${ANTLR4CPP_LOCAL_REPO}		#Added for local copy
  CONFIGURE_COMMAND  ${CMAKE_COMMAND} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=${RESSOURCES_FLAGS} -DBUILD_SHARED_LIBS=ON -DBUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DCMAKE_SOURCE_DIR:PATH=<SOURCE_DIR> -DWITH_DEMO=False -DWITH_LIBCXX=False <SOURCE_DIR>
  LOG_CONFIGURE ON
  # BUILD_COMMAND ${CMAKE_MAKE_PROGRAM}
  LOG_BUILD ON
  # INSTALL_COMMAND    ""
)

ExternalProject_Get_Property(antlr4cpp INSTALL_DIR)

file(MAKE_DIRECTORY ${INSTALL_DIR}/include/antlr4-runtime)

list(APPEND ANTLR4CPP_INCLUDE_DIRS ${INSTALL_DIR}/include/antlr4-runtime)
foreach(src_path misc atn dfa tree support)
  list(APPEND ANTLR4CPP_INCLUDE_DIRS ${INSTALL_DIR}/include/antlr4-runtime/${src_path})
endforeach(src_path)

set(ANTLR4CPP_STATIC_LIBS "${INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}antlr4-runtime${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(ANTLR4CPP_SHARED_LIBS "${INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}antlr4-runtime${CMAKE_SHARED_LIBRARY_SUFFIX}")
set(ANTLR4CPP_INCLUDE_DIRS ${ANTLR4CPP_INCLUDE_DIRS})

add_imported_library(ANTLR4 STATIC ${ANTLR4CPP_STATIC_LIBS} ${ANTLR4CPP_INCLUDE_DIRS})
add_imported_library(ANTLR4 SHARED ${ANTLR4CPP_SHARED_LIBS} ${ANTLR4CPP_INCLUDE_DIRS})

add_dependencies(ANTLR4_STATIC antlr4cpp)
add_dependencies(ANTLR4_SHARED antlr4cpp)
add_dependencies(hypro_resources ANTLR4_STATIC ANTLR4_SHARED)
