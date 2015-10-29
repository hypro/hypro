add_subdirectory(datastructures)
add_subdirectory(representations)
add_subdirectory(parser)

# Create config.h by adding cmake defines dependend on option switches
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/flags.h.in ${CMAKE_CURRENT_SOURCE_DIR}/flags.h )

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
#MESSAGE(STATUS "Globbed header files: ${headers}")

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

add_library(${PROJECT_NAME} ${STATICLIB}
	${sources}
)

if(STATICLIB_SWITCH)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
else()
	if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX INSTALL_RPATH "@loader_path/../lib")
	else()
		set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
	endif()
endif()


target_link_libraries(${PROJECT_NAME} ${libraries})

cotire(${PROJECT_NAME})

##install(FILES ${headers} DESTINATION include)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
