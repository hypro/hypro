#
#
#
#
#
#

# find paths
find_package(PkgConfig)
pkg_check_modules(PC_LIBPOLYMAKE QUIET libpolymake)

# find_path searches header PATHS
find_path(LIBPOLYMAKE_INCLUDE_DIR NAMES Main.h
	HINTS ${PC_LIBPOLYMAKE_INCLUDEDIR} ${PC_LIBPOLYMAKE_INCLUDE_DIRS}
	PATH_SUFFIXES polymake)

# find_library searches for library files
find_library(LIBPOLYMAKE_LIBRARY NAMES polymake libpolymake
	HINTS ${PC_LIBPOLYMAKE_LIBDIR} ${PC_LIBPOLYMAKE_LIBRARY_DIRS})

set(LIBPOLYMAKE_LIBRARIES ${LIBPOLYMAKE_LIBRARY})
set(LIBPOLYMAKE_INCLUDE_DIRS ${LIBPOLYMAKE_INCLUDE_DIR})

# sets the found option and creates error messages
find_package_handle_standard_args(libcdd  DEFAULT_MSG
                                  LIBPOLYMAKE_LIBRARY LIBPOLYMAKE_INCLUDE_DIR)

if(POLYMAKE_FOUND)
   if(NOT POLYMAKE_FIND_QUIETLY)
      MESSAGE(STATUS "Found Polymake: ${POLYMAKE_LIBRARY}")
   endif()
elseif(POLYMAKE_FOUND)
   if(POLYMAKE_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find Polymake")
   endif()
endif()