# this files defines
#  - GLPK_INCLUDE_DIR
#  - GLPK_LIBRARIES
#  - GLPK_FOUND

INCLUDE(CheckIncludeFileCXX)
CHECK_INCLUDE_FILE_CXX(glpk.h FEELPP_HAS_GLPK_H)

#message(STATUS "Cmake find library suffixes: ${CMAKE_FIND_LIBRARY_SUFFIXES}")

FIND_LIBRARY( GLPK_LIBRARIES glpk PATHS /usr/local/lib /usr/lib $ENV{GLPK_DIR}/lib)

FIND_PATH(GLPK_INCLUDE_DIR
  glpk.h
  PATHS /usr/local/include /usr/include/ /usr/include/glpk $ENV{GLPK_DIR}/include
  DOC "Directory where GLPK header files are stored" )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLPK "Could not find GLPK " GLPK_INCLUDE_DIR GLPK_LIBRARIES)
MARK_AS_ADVANCED(GLPK_INCLUDE_DIR GLPK_LIBRARIES )
