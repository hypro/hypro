if(${STATICLIB_SWITCH} STREQUAL "OFF")
    include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/lib ${include_dirs} )
    link_directories(${CMAKE_BINARY_DIR}/lib)

    ################################
    # Unit Tests
    ################################

    add_executable(runRepresentationTests
        BoxTest.cpp
        VPolytopeTest.cpp
        #OrthogonalPolyhedronTest.cpp
        NeighbourhoodContainerTest.cpp
    )

    add_dependencies(runRepresentationTests googletest)

    target_link_libraries(runRepresentationTests
        ${libraries}
        ${PROJECT_NAME}
    )
    add_test( NAME representations COMMAND runRepresentationTests )
endif()
