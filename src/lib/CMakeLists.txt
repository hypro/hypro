add_subdirectory(datastructures)
add_subdirectory(numbers)
add_subdirectory(representations)

set(lib_hypro_sources
	${lib_hypro_number_sources}
	${lib_hypro_representation_sources}
	${lib_hypro_datastructure_sources}
)

if(${STATICLIB_SWITCH} STREQUAL "ON")
	set(STATICLIB "STATIC")
endif()

add_library(lib_${PROJECT_NAME} ${STATICLIB} ${lib_hypro_sources})

target_link_libraries(lib_${PROJECT_NAME} ${libraries})
