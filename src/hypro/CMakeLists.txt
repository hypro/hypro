add_subdirectory(datastructures)
add_subdirectory(representations)
add_subdirectory(parser)

# Create config.h by adding cmake defines dependend on option switches
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/flags.h.in ${CMAKE_CURRENT_SOURCE_DIR}/flags.h )

########################################################################################

# Simplified access to *.h and *.cpp
foreach(name algorithms datastructures parser representations util)
	collect_files(hypro ${name})
endforeach()

##file(GLOB_RECURSE headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
##file(GLOB_RECURSE template_implementations RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.tpp)

set(headers
	${hypro_algorithms_headers}
	${hypro_datastructures_headers}
	${hypro_parser_headers}
	${hypro_representations_headers}
	${hypro_util_headers})


file(GLOB_RECURSE headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
#MESSAGE(STATUS "Globbed header sources: ${sources}")

if(STATICLIB_SWITCH)
	set(STATICLIB "STATIC")
else()
	set(STATICLIB "SHARED")
endif()

########################################################################################

if(STATICLIB_SWITCH)
	message("-- linking static")
	add_library(${PROJECT_NAME}_static STATIC ${sources})
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
	target_link_libraries(${PROJECT_NAME} PUBLIC ${hypro_LIBRARIES_STATIC})
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
	#message("hypro sources: " ${sources})
	#message("hypro headers: " ${headers})
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

set(HYPRO_TARGETS ${PROJECT_NAME} CACHE STRING INTERNAL FORCE)


########################################################################################

cotire(${PROJECT_NAME})

install(FILES ${headers} DESTINATION include)

########################################################################################

if (CLANG_TIDY)
	add_custom_target(tidy
		COMMAND clang-tidy -p ../../build/compile_commands.json ${CLANG_TIDY_CHECKS} -header-filter='.*' ${sources}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/hypro/
	)
endif()

########################################################################################

include(${CMAKE_MODULE_PATH}/coverage.cmake)
