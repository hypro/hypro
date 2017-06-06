

ExternalProject_Add(
	carl
	GIT_REPOSITORY http://github.com/smtrat/carl.git
	BUILD_COMMAND make lib_carl
	INSTALL_COMMAND "")

ExternalProject_Add_Step(carl ReloadCMake
	COMMAND cmake ../..
	COMMENT "Re-run CMake."
	DEPENDEES build
	)

#ExternalProject_Get_Property(carl source_dir)
#ExternalProject_Get_Property(carl binary_dir)

#set( carl_INCLUDE_DIR "${EP_PREFIX_DIR}/src/carl/src" PARENT_SCOPE )
#set( carl_LIBRARIES "${EP_PREFIX_DIR}/src/carl-build/libcarl${CMAKE_SHARED_LIBRARY_SUFFIX}" PARENT_SCOPE )

#add_library(carl_SHARED SHARED IMPORTED)
#set_target_properties(carl_SHARED PROPERTIES IMPORTED_LOCATION "${carl_LIBRARIES}")
#set_target_properties(carl_SHARED PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${carl_INCLUDE_DIR}")
#set(hypro_LIBRARIES_DYNAMIC ${hypro_LIBRARIES_DYNAMIC} ${carl_LIBRARIES} )

#find_package(carl QUIET)
#list(APPEND hypro_LIBRARIES_DYNAMIC ${EP_PREFIX_DIR}/src/carl-build/libcarl${CMAKE_SHARED_LIBRARY_PREFIX})
#list(APPEND hypro_LIBRARIES_STATIC ${EP_PREFIX_DIR}/src/carl-build/libcarl${CMAKE_STATIC_LIBRARY_PREFIX})
#list(APPEND hypro_INCLUDE_DIRS ${EP_PREFIX_DIR}/src/carl/src )

#message("Current libraries (dynamic): ${hypro_LIBRARIES_DYNAMIC}")
#message("Current include directories: ${hypro_INCLUDE_DIRS}")

#message("Attempted carl dir: ${EP_PREFIX_DIR}/src/carl/src")

add_dependencies(resources carl)

#add_imported_library(carl SHARED "${EP_PREFIX_DIR}/src/carl-build/libcarl${CMAKE_SHARED_LIBRARY_SUFFIX}" "${EP_PREFIX_DIR}/src/carl/src")
#add_imported_library(carl_static STATIC "${EP_PREFIX_DIR}/src/carl-build/libcarl${CMAKE_STATIC_LIBRARY_SUFFIX}" "${EP_PREFIX_DIR}/src/carl/src")

