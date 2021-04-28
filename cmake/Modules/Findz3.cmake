# - Try to find z3
# Once done this will define
#  z3_FOUND - System has z3
#  z3_INCLUDE_DIRS - The z3 include directories
#  z3_LIBRARIES - The libraries needed to use z3
#  z3_DEFINITIONS - Compiler switches required for using z3

find_package(PkgConfig)
pkg_check_modules(PC_LIBz3 QUIET libz3)
set(z3_DEFINITIONS ${PC_LIBz3_CFLAGS_OTHER})

find_path(z3_INCLUDE_DIR z3++.h
          HINTS ${PC_LIBz3_INCLUDEDIR} ${PC_LIBz3_INCLUDE_DIRS}
          PATH_SUFFIXES z3 )

find_library(z3_LIBRARY NAMES z3 z3
             HINTS ${PC_LIBz3_LIBDIR} ${PC_LIBz3_LIBRARY_DIRS} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set z3_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(z3  FOUND_VAR z3_FOUND
                                  REQUIRED_VARS z3_LIBRARY z3_INCLUDE_DIR)

set(z3_LIBRARIES ${z3_LIBRARY} )
set(z3_INCLUDE_DIRS ${z3_INCLUDE_DIR} )

mark_as_advanced(z3_INCLUDE_DIR z3_LIBRARY )
