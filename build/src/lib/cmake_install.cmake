# Install script for directory: /Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/config.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/util/VariablePool.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/util/eigenTypetraits.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/Facet.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/Point.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/Vertex.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/VertexContainer.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/HybridAutomaton.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/Location.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/Transition.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/util.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/GeometricObject.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/Box.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/Polytope.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/VariablePool.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/util.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/Zonotope.h"
    "/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/lib/Hyperplane.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/src/lib/datastructures/cmake_install.cmake")
  include("/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/src/lib/representations/cmake_install.cmake")
  include("/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/src/lib/parser/cmake_install.cmake")

endif()

