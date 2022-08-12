# - Try to find soplex
# Once done this will define
#  soplex_FOUND - System has soplex
#  soplex_INCLUDE_DIRS - The soplex include directories
#  soplex_LIBRARIES - The libraries needed to use soplex
#  soplex_DEFINITIONS - Compiler switches required for using soplex

find_package(PkgConfig)
pkg_check_modules(PC_LIBsoplex QUIET soplex-pic)
set(soplex_DEFINITIONS ${PC_LIBsoplex_CFLAGS_OTHER})

find_path(soplex_INCLUDE_DIR soplex.h
          HINTS ${PC_LIBsoplex_INCLUDEDIR} ${PC_LIBsoplex_INCLUDE_DIRS}
          PATH_SUFFIXES soplex )

find_library(soplex_LIBRARY NAMES libsoplex-pic.a soplex-pic
             HINTS ${PC_LIBsoplex_LIBDIR} ${PC_LIBsoplex_LIBRARY_DIRS}
             PATHS /usr/local/lib )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set soplex_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(soplex  FOUND_VAR soplex_FOUND
                                  REQUIRED_VARS soplex_LIBRARY soplex_INCLUDE_DIR)

set(soplex_LIBRARIES ${soplex_LIBRARY} )
set(soplex_INCLUDE_DIRS ${soplex_INCLUDE_DIR} )


mark_as_advanced(soplex_INCLUDE_DIR soplex_LIBRARY )
