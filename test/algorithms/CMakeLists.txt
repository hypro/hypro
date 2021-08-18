if (${STATICLIB_SWITCH} STREQUAL "OFF")

    # reduce compiler optimization for tests
    set(algorithm_test_sources
            #FacetEnumerationTest.cpp
            #ForwardReachabilityTest.cpp
            #MinkowskiSumTest.cpp
            #SumPerformanceTest.cpp
            # rahsTwoTankTest.cpp
            ReachabilityAnalysisTest.cpp
            FourierMotzkinQETest.cpp
            #VertexEnumerationTest.cpp
            UtilityTest.cpp
            QuickhullTest.cpp
            QuickIntersectionTest.cpp
            RectangularReachabilityTest.cpp
            SingularReachabilityTest.cpp
            TimeEvolutionTest.cpp
            #TemplatePolyhedronContextTest.cpp #BROKEN since LTIContext broken
            #FirstSegmentHandlersTest.cpp #BROKEN
            )

    SET_SOURCE_FILES_PROPERTIES(${algorithm_test_sources} PROPERTIES COMPILE_FLAGS -O0)

    ################################
    # Unit Tests
    ################################

    add_executable(runAlgorithmTests
            ${algorithm_test_sources}
            )

    add_dependencies(runAlgorithmTests hypro_resources)
    target_include_directories(runAlgorithmTests PRIVATE ${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test/include/)

    target_link_libraries(runAlgorithmTests PUBLIC
            ${PROJECT_NAME}-shared
            ${GTEST_LIBRARIES}
            )

    #cotire(runAlgorithmTests)

    add_test(NAME algorithms COMMAND runAlgorithmTests)

    add_dependencies(allTests runAlgorithmTests)

endif ()
