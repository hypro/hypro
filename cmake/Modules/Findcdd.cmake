#
#
#
#
#
#

# find paths
find_package(PkgConfig)
pkg_check_modules(PC_LIBCDD QUIET libcdd)

# find_path searches header PATHS
find_path(LIBCDD_INCLUDE_DIR NAMES cdd_f.h  cdd.h  cddmp_f.h  cddmp.h  cddtypes_f.h  cddtypes.h
	HINTS ${PC_LIBCDD_INCLUDEDIR} ${PC_LIBCDD_INCLUDE_DIRS})

# find_library searches for library files
find_library(LIBCDD_LIBRARY NAMES cdd libcdd cddgmp libcddgmp 
	HINTS ${PC_LIBCDD_LIBDIR} ${PC_LIBCDD_LIBRARY_DIRS})

set(LIBCDD_LIBRARIES ${LIBCDD_LIBRARY})
set(LIBCDD_INCLUDE_DIRS ${LIBCDD_INCLUDE_DIR})

# sets the found option and creates error messages
find_package_handle_standard_args(libcdd  DEFAULT_MSG
                                  LIBCDD_LIBRARY LIBCDD_INCLUDE_DIR)