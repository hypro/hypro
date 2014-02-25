add_subdirectory(datastructures)
add_subdirectory(representations)

#set(GTEST_LIBRARIES ${GTEST_LIBRARIES} PARENT_SCOPE)
#set(EIGEN3_INCLUDE_DIR ${EIGEN3_INCLUDE_DIR} PARENT_SCOPE)
#set(LOG4CPLUS_LIBRARY ${LOG4CPLUS_LIBRARY} PARENT_SCOPE)

set(lib_hypro_headers
	config.h
	#${lib_hypro_number_headers}
	${lib_hypro_datastructure_headers}
	${lib_hypro_representation_headers}
)

set(lib_hypro_sources
	${lib_hypro_datastructure_sources}
	representations/${lib_hypro_representation_sources}
)

if(${STATICLIB_SWITCH} STREQUAL "ON")
	set(STATICLIB "STATIC")
else()
	set(STATICLIB "SHARED")
endif()

add_library(${PROJECT_NAME} ${STATICLIB} 
	${lib_hypro_sources}
	#$<TARGET_OBJECTS:datastructures>
	$<TARGET_OBJECTS:representations>
)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} ${libraries})

install(FILES ${lib_hypro_headers} DESTINATION include)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
