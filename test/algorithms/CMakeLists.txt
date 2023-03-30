if (${STATICLIB_SWITCH} STREQUAL "OFF")

    # reduce compiler optimization for tests
    set(algorithm_test_sources
            DecompositionalReachabilityTest.cpp
            #FacetEnumerationTest.cpp
            #FirstSegmentHandlersTest.cpp #BROKEN
            #ForwardReachabilityTest.cpp
            FourierMotzkinQETest.cpp
            #MinkowskiSumTest.cpp
            #MultithreadedReachabilityAnalysisTest.cpp
            ParallelCompositionReachabilityAnalysisTest.cpp
            QuickhullTest.cpp
            QuickIntersectionTest.cpp
            # rahsTwoTankTest.cpp
            ReachabilityAnalysisTest.cpp
            RectangularReachabilityTest.cpp
            SetMinusReachabilityAnalysisTest.cpp
            SingularReachabilityTest.cpp
            #SumPerformanceTest.cpp
            #TemplatePolyhedronContextTest.cpp #BROKEN since LTIContext broken
            TimeEvolutionTest.cpp
            UrgencyReachabilityTest.cpp
            UtilityTest.cpp
            #VertexEnumerationTest.cpp
            ZenoDetectionTest.cpp
            )

    SET_SOURCE_FILES_PROPERTIES(${algorithm_test_sources} PROPERTIES COMPILE_FLAGS -O0)

    ################################
    # Unit Tests
    ################################

    add_executable(runAlgorithmTests
            ${algorithm_test_sources}
            )

    add_dependencies(runAlgorithmTests hypro_resources hypro-parser)
    target_include_directories(runAlgorithmTests PRIVATE ${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test/include/)

    target_link_libraries(runAlgorithmTests PUBLIC
            ${PROJECT_NAME}-shared
            ${PROJECT_NAME}-parser
            ${GTEST_LIBRARIES}
            )

    #cotire(runAlgorithmTests)

    add_test(NAME algorithms COMMAND runAlgorithmTests)

    add_dependencies(allTests runAlgorithmTests)

endif ()
