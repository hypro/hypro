add_subdirectory(datastructures)
add_subdirectory(numbers)
add_subdirectory(representations)

set(lib_hypro_sources
	
)

if(${STATICLIB_SWITCH} STREQUAL "ON")
	set(STATICLIB "STATIC")
else()
	set(STATICLIB "SHARED")
endif()

add_library(${PROJECT_NAME} ${STATICLIB} 
	${lib_hypro_sources}
	$<TARGET_OBJECTS:datastructures>
	$<TARGET_OBJECTS:numbers>
	$<TARGET_OBJECTS:representations>
)

target_link_libraries(${PROJECT_NAME} ${libraries})
