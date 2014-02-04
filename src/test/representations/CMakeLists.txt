if(${STATICLIB_SWITCH} STREQUAL "OFF")
    include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/lib ${include_dirs} )
    link_directories(${CMAKE_BINARY_DIR}/build/lib)

    ################################
    # Unit Tests
    ################################

    add_executable(runRepresentationTests
					BoxTest.cpp
    )

    add_dependencies(runRepresentationTests googletest)

get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

    target_link_libraries(runRepresentationTests
							${PROJECT_NAME}
                            ${libraries})
    add_test( NAME representations COMMAND runRepresentationTests )
endif()
