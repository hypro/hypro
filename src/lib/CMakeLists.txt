add_subdirectory(datastructures)
add_subdirectory(representations)
add_subdirectory(parser)

# Create config.h by adding cmake defines dependend on option switches
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/flags.h.in ${CMAKE_CURRENT_SOURCE_DIR}/flags.h )

set(lib_hypro_headers
	config.h
	util/Optimizer.h
    util/VariablePool.h
    util/adaptions_eigen/adaptions_eigen.h
    util/adaptions_eigen/adaptions_eigen_double.h
	util/types.h
	util/convexHull.h
	util/smtrat/SimplexSolver.h
	util/smtrat/convenience.h
	${lib_hypro_datastructure_headers}
	${lib_hypro_representation_headers}
    ${lib_hypro_parser_headers}
    ${lib_hypro_algorithm_headers}
)

set(lib_hypro_sources
	${lib_hypro_datastructure_sources}
	${lib_hypro_representation_sources}
    ${lib_hypro_parser_sources}
)

########################################################################################
##### EXPORT SETTINGS

#add_library(lib_hypro SHARED ${lib_hypro_sources})

#set_target_properties( ${PROJECT_NAME} PROPERTIES
#	create *nix style library versions + symbolic links
#	VERSION "${PROJECT_VERSION}"
#	SOVERSION "${PROJECT_VERSION}"
#	# allow creating static and shared libs without conflicts
#	CLEAN_DIRECT_OUTPUT 1
#	# avoid conflicts between library and binary target names
#	OUTPUT_NAME hypro
#	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
#	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
	# we currently do not use public header option, as it doesnt support multi-directory headers
#)

#target_link_libraries( lib_hypro ${hypro_LIBRARIES_DYNAMIC} )

########################################################################################

# Simplified access to *.h and *.cpp
foreach(name algorithms datastructures parser representations util)
	collect_files(hypro ${name})
endforeach()

##file(GLOB_RECURSE headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
##file(GLOB_RECURSE template_implementations RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.tpp)

##set(headers ${headers} ${template_implementations})
set(headers
	${hypro_algorithms_headers}
	${hypro_datastructures_headers}
	${hypro_parser_headers}
	${hypro_representations_headers}
	${hypro_util_headers})

##file(GLOB_RECURSE sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
#MESSAGE(STATUS "Globbed header sources: ${test_sources}")

set(sources
	${hypro_algorithms_sources}
	${hypro_datastructures_sources}
	${hypro_parser_sources}
	${hypro_representations_sources}
	${hypro_util_sources})

if(STATICLIB_SWITCH)
	set(STATICLIB "STATIC")
else()
	set(STATICLIB "SHARED")
endif()

########################################################################################
#### EXPORT SETTINGS

if(STATICLIB_SWITCH)
	message("-- linking static")
	add_library(lib_hypro_static STATIC ${sources})
	set_target_properties( lib_hypro_static PROPERTIES
		# create *nix style library versions + symbolic links
		VERSION "${PROJECT_VERSION}"
		SOVERSION "${PROJECT_VERSION}"
		# allow creating static and shared libs without conflicts
		CLEAN_DIRECT_OUTPUT 1
		# avoid conflicts between library and binary target names
		OUTPUT_NAME hypro
		LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
		ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
		# we currently do not use public header option, as it doesnt support multi-directory headers
	)
	target_link_libraries(${PROJECT_NAME} PUBLIC ${libraries} ${hypro_LIBRARIES_STATIC})
	target_include_directories(lib_hypro_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${hypro_INCLUDE_DIRS})
else()
	message("-- linking dynamic")
	add_library(${PROJECT_NAME} SHARED ${sources})
	set_target_properties( ${PROJECT_NAME} PROPERTIES
		# create *nix style library versions + symbolic links
		VERSION "${PROJECT_VERSION}"
		SOVERSION "${PROJECT_VERSION}"
		# allow creating static and shared libs without conflicts
		CLEAN_DIRECT_OUTPUT 1
		# avoid conflicts between library and binary target names
		OUTPUT_NAME hypro
		LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
		ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
	)
	#message("hypro libraries dynamic: " ${hypro_LIBRARIES_DYNAMIC})
	#message("hypro include dirs: " ${hypro_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${hypro_LIBRARIES_DYNAMIC} pthread)
	target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${hypro_INCLUDE_DIRS})
endif()

if(STATICLIB_SWITCH)
	set_target_properties(${PROJECT_NAME}_static PROPERTIES LINKER_LANGUAGE CXX)
else()
	if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX INSTALL_RPATH "@loader_path/../lib")
	else()
		set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
	endif()
endif()

# Options for static linking
if (APPLE)
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mmacosx-version-min=10.7")
else()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

#target_link_libraries( lib_hypro_static ${hypro_LIBRARIES_STATIC} )
#set(HYPRO_TARGETS lib_hypro lib_hypro_static CACHE STRING INTERNAL FORCE)
#else()
set(HYPRO_TARGETS ${PROJECT_NAME} CACHE STRING INTERNAL FORCE)
#endif()

########################################################################################

cotire(${PROJECT_NAME})

install(FILES config.h flags.h typedefs.h DESTINATION include/hypro/lib/)
##install(FILES ${headers} DESTINATION include)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

########################################################################################
##### EXPORT SETTINGS

# Install destination and permissions for the library
# # # # # # # # # # # # # # # # # # # # # # # # # # #

#install( TARGETS ${HYPRO_TARGETS}
#	EXPORT hyproTargets
#	LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
#    ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
#    COMPONENT shlib
#	PERMISSIONS
#		OWNER_READ OWNER_WRITE OWNER_EXECUTE
#		GROUP_READ GROUP_EXECUTE
#		WORLD_READ WORLD_EXECUTE
#)
### "${PROJECT_BINARY_DIR}" THE FOLLOWING CMD IS FROM CARL... HERE WE DO HAVE A PROBLEM, BUT I DUNNO WHAT IT IS

########################################################################################

if (CLANG_TIDY)
	add_custom_target(tidy
		COMMAND clang-tidy -p ../../build/compile_commands.json ${CLANG_TIDY_CHECKS} -header-filter='.*' ${sources}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/lib/
	)
endif()
