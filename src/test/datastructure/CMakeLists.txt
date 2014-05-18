if(${STATICLIB_SWITCH} STREQUAL "OFF")
    include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/lib ${include_dirs} )
    link_directories(${CMAKE_BINARY_DIR}/lib)

    ################################
    # Unit Tests
    ################################

    add_executable(runDatastructureTests
            PointTest.cpp
            VertexTest.cpp
            VertexContainerTest.cpp
            HybridAutomataTest.cpp
    )

    add_dependencies(runDatastructureTests googletest)

    target_link_libraries(runDatastructureTests
							${PROJECT_NAME}
                            ${libraries})
    add_test( NAME datastructures COMMAND runDatastructureTests )
endif()
