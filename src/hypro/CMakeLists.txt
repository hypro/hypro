
# Create config.h by adding cmake defines dependend on option switches
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/flags.h.in ${CMAKE_CURRENT_SOURCE_DIR}/flags.h )

########################################################################################
# Create object library first
file(GLOB_RECURSE sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_library(${PROJECT_NAME}-objects OBJECT ${sources})
add_dependencies(${PROJECT_NAME}-objects resources)
target_include_dirs_from(${PROJECT_NAME}-objects SYSTEM PUBLIC EIGEN3 COCOA_SHARED Boost_SHARED Boost_program_options_SHARED carl-shared GMP_SHARED GMPXX_SHARED GLPK_STATIC ANTLR4_SHARED)
target_include_directories(${PROJECT_NAME}-objects
		PRIVATE ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}
		PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
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
	target_link_libraries(${PROJECT_NAME}-static PUBLIC carl-static)
	#target_link_libraries(${PROJECT_NAME}-static PUBLIC COCOA_STATIC)
	target_link_libraries(${PROJECT_NAME}-static PUBLIC EIGEN3)
	target_link_libraries(${PROJECT_NAME}-static PUBLIC Boost_STATIC)
	target_link_libraries(${PROJECT_NAME}-static PUBLIC Boost_program_options_STATIC)
	#target_link_libraries(${PROJECT_NAME}-static PUBLIC COCOA_STATIC)
	target_link_libraries(${PROJECT_NAME}-static PUBLIC GMP_STATIC)
	target_link_libraries(${PROJECT_NAME}-static PUBLIC GMPXX_STATIC)
	target_include_directories(${PROJECT_NAME}-static
		PRIVATE ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}
		PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<INSTALL_INTERFACE:include/${PROJECT_NAME}>
	)

	add_library(${PROJECT_NAME}-shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}-objects>)
	set_target_properties( ${PROJECT_NAME}-shared PROPERTIES
		VERSION "${PROJECT_VERSION}"
		SOVERSION "${PROJECT_VERSION}"
		OUTPUT_NAME ${PROJECT_NAME}
		LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
		ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
		LINKER_LANGUAGE CXX
	)
	target_link_libraries(${PROJECT_NAME}-shared EIGEN3)
	target_link_libraries(${PROJECT_NAME}-shared ${${PROJECT_NAME}_LIBRARIES_DYNAMIC})
	target_link_libraries(${PROJECT_NAME}-shared carl-shared)
	target_link_libraries(${PROJECT_NAME}-shared Boost_SHARED)
	#target_link_libraries(${PROJECT_NAME}-shared COCOA_SHARED)
	target_link_libraries(${PROJECT_NAME}-shared Boost_program_options_SHARED)
	target_link_libraries(${PROJECT_NAME}-shared GMP_SHARED)
	target_link_libraries(${PROJECT_NAME}-shared GMPXX_SHARED)
	target_link_libraries(${PROJECT_NAME}-shared GLPK_STATIC)
	target_link_libraries(${PROJECT_NAME}-shared ANTLR4_SHARED)
	target_link_libraries(${PROJECT_NAME}-shared pthread)
	if(HYPRO_USE_SMTRAT)
		target_link_libraries(${PROJECT_NAME}-shared PUBLIC smtrat-solver-shared smtrat-module-LRAModule-shared)
		target_link_libraries(${PROJECT_NAME}-static PUBLIC smtrat-solver-static smtrat-module-LRAModule-static)
	endif()

	target_include_directories(${PROJECT_NAME}-shared
		PRIVATE ${${PROJECT_NAME}_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}
		PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<INSTALL_INTERFACE:include/${PROJECT_NAME}>
		INTERFACE
		$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/resources/include/antlr4-runtime>
	)

	add_custom_target(${PROJECT_NAME} DEPENDS ${PROJECT_NAME}-shared ${PROJECT_NAME}-static)
	add_dependencies(${PROJECT_NAME} resources)



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

cotire(${PROJECT_NAME}-shared)
cotire(${PROJECT_NAME}-static)

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
