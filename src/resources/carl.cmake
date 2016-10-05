ExternalProject_Add(
	carl
	GIT_REPOSITORY http://github.com/smtrat/carl.git
	INSTALL_COMMAND "")

find_package(carl QUIET)
list(APPEND hypro_LIBRARIES_DYNAMIC ${carl_LIBRARIES})
list(APPEND hypro_LIBRARIES_STATIC ${carl_LIBRARIES})
list(APPEND hypro_INCLUDE_DIRS ${carl_INCLUDE_DIR})

message("Current libraries (dynamic): ${hypro_LIBRARIES_DYNAMIC}")
message("Current include directories: ${hypro_INCLUDE_DIRS}")

message("Carl libraries (dynamic): ${carl_LIBRARIES}")
message("Carl include directories: ${carl_INCLUDE_DIR}")

add_imported_library(carl SHARED "${carl_LIBRARIES}" "${carl_INCLUDE_DIR}")
#add_imported_library(carl STATIC "${carl_LIBRARIES}" "${carl_INCLUDE_DIR}")

add_dependencies(resources carl)
