add_subdirectory(datastructures)
add_subdirectory(representations)
add_subdirectory(parser)

# Create config.h by adding cmake defines dependend on option switches
configure_file( ${CMAKE_SOURCE_DIR}/src/lib/types.h.in ${CMAKE_SOURCE_DIR}/src/lib/types.h )

set(lib_hypro_headers
	config.h
    util/VariablePool.h
    util/eigenTypetraits.h
	util/types.h
	util/convexHull.h
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

file(GLOB_RECURSE headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE template_implementations RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.tpp)

set(headers ${headers} ${template_implementations})
#MESSAGE(STATUS "Globbed header files: ${headers}")

file(GLOB_RECURSE sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
#MESSAGE(STATUS "Globbed header sources: ${test_sources}")

if(${STATICLIB_SWITCH} STREQUAL "ON")
	set(STATICLIB "STATIC")
else()
	set(STATICLIB "SHARED")
endif()

add_library(${PROJECT_NAME} ${STATICLIB} 
	${sources}
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} ${libraries})

if(USE_COTIRE)
	cotire(${PROJECT_NAME})
endif()

install(FILES ${headers} DESTINATION include)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
