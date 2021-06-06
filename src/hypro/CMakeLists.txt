
########################################################################################
# Create object library first
file(GLOB_RECURSE sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
# filter out matlab-bindings
list(FILTER sources EXCLUDE REGEX MHyPro.cpp|MReach.cpp|CompareMHyProAndCORA/example_box.cpp|CompareMHyProAndCORA/example_zonotope.cpp)

add_library(${PROJECT_NAME}-objects OBJECT ${sources})
add_dependencies(${PROJECT_NAME}-objects hypro_resources)
build_target_include_dirs_from(${PROJECT_NAME}-objects SYSTEM PUBLIC GLPK_STATIC ANTLR4_SHARED clp_STATIC coinUtils_STATIC z3_SHARED)
target_include_directories(${PROJECT_NAME}-objects
		PRIVATE ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}
		PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}/resources/include/antlr4-runtime>
		$<INSTALL_INTERFACE:include/${PROJECT_NAME}>
	)

########################################################################################
# Create static and shared libraries

add_library(${PROJECT_NAME}-static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}-objects>)
set_target_properties( ${PROJECT_NAME}-static PROPERTIES
	VERSION "${PROJECT_VERSION}"
	SOVERSION "${PROJECT_VERSION}"
	OUTPUT_NAME ${PROJECT_NAME}
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
	LINKER_LANGUAGE CXX
)

target_link_libraries(${PROJECT_NAME}-static PUBLIC ${${PROJECT_NAME}_LIBRARIES_STATIC})
target_link_libraries(${PROJECT_NAME}-static PUBLIC pthread)

target_include_directories(${PROJECT_NAME}-static
	PRIVATE ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
	$<INSTALL_INTERFACE:include/${PROJECT_NAME}>
	INTERFACE
	$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/resources/include/antlr4-runtime>
)

##### SHARED LIBRARY

add_library(${PROJECT_NAME}-shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}-objects>)
set_target_properties( ${PROJECT_NAME}-shared PROPERTIES
	VERSION "${PROJECT_VERSION}"
	SOVERSION "${PROJECT_VERSION}"
	OUTPUT_NAME ${PROJECT_NAME}
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
	LINKER_LANGUAGE CXX
)

target_link_libraries(${PROJECT_NAME}-shared PUBLIC ${${PROJECT_NAME}_LIBRARIES_DYNAMIC})
target_link_libraries(${PROJECT_NAME}-shared PUBLIC pthread)

target_include_directories(${PROJECT_NAME}-shared
	PRIVATE ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
	$<INSTALL_INTERFACE:include/${PROJECT_NAME}>
	INTERFACE
	$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/resources/include/antlr4-runtime>
)

# Meta-target which combines static and shared library
add_custom_target(${PROJECT_NAME} DEPENDS ${PROJECT_NAME}-shared ${PROJECT_NAME}-static)


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set_target_properties(${PROJECT_NAME}-shared PROPERTIES LINKER_LANGUAGE CXX INSTALL_RPATH "@loader_path/../lib")
	set_target_properties(${PROJECT_NAME}-static PROPERTIES LINKER_LANGUAGE CXX INSTALL_RPATH "@loader_path/../lib")
endif()
set(HYPRO_TARGETS "${PROJECT_NAME}-shared" "${PROJECT_NAME}-static" CACHE STRING INTERNAL FORCE)


# Options for static linking
if (APPLE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mmacosx-version-min=10.7")
else()
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

########################################################################################

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.tpp")

install(TARGETS ${PROJECT_NAME}-static
		EXPORT ${PROJECT_NAME}
		LIBRARY DESTINATION ${LIB_INSTALL_DIR}
		ARCHIVE DESTINATION ${LIB_INSTALL_DIR}/static)
install(TARGETS ${PROJECT_NAME}-shared
		EXPORT ${PROJECT_NAME}
		LIBRARY DESTINATION ${LIB_INSTALL_DIR}
		ARCHIVE DESTINATION ${LIB_INSTALL_DIR}/static)



########################################################################################

if(CLANG_TIDY)
	add_custom_target(tidy
		COMMAND clang-tidy -p ../../build/compile_commands.json ${CLANG_TIDY_CHECKS} -header-filter='.*' ${sources}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/hypro/
	)
endif()

########################################################################################
