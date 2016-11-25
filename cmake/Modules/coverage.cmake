
add_library(${PROJECT_NAME}_coverage SHARED EXCLUDE_FROM_ALL ${sources})
set_target_properties( ${PROJECT_NAME}_coverage PROPERTIES
	# create *nix style library versions + symbolic links
	VERSION "${PROJECT_VERSION}"
	SOVERSION "${PROJECT_VERSION}"
	# allow creating static and shared libs without conflicts
	CLEAN_DIRECT_OUTPUT 1
	# avoid conflicts between library and binary target names
	OUTPUT_NAME hypro
	COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage"
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
target_link_libraries(${PROJECT_NAME}_coverage PUBLIC ${hypro_LIBRARIES_DYNAMIC} pthread)
target_include_directories(${PROJECT_NAME}_coverage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${hypro_INCLUDE_DIRS})
