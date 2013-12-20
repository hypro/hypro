add_subdirectory(datastructures)
#add_subdirectory(numbers)
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
	#$<TARGET_OBJECTS:datastructures>
	#$<TARGET_OBJECTS:numbers>
	#$<TARGET_OBJECTS:representations>
)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} ${libraries})

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

install(FILES ${lib_hypro_number_headers} DESTINATION include)
