# reduce compiler optimization for tests
set(datastructure_test_sources
        DAGTest.cpp
        DecompositionTest.cpp
        #EventTimingProviderTest.cpp
        FlowpipeTest.cpp
        HalfspaceTest.cpp
        HIVTest.cpp
        HyperoctreeTest.cpp
        PointTest.cpp
        VertexTest.cpp
        VertexContainerTest.cpp
        RangeTest.cpp
        ReachabilitySettingsTest.cpp
        ReachTreeTest.cpp
        StateTest.cpp
        StateVisitorTest.cpp
        TreeTest.cpp
        #StrategyTest.cpp
        HybridAutomataTest.cpp
        HybridAutomataOutputTest.cpp
        WorkQueueTest.cpp
        HybridAutomataParallelCompositionTest.cpp
        )

SET_SOURCE_FILES_PROPERTIES(${datastructure_test_sources} PROPERTIES COMPILE_FLAGS -O0)

################################
# Unit Tests
################################

add_executable(runDatastructureTests
        ${datastructure_test_sources}
        )

add_dependencies(runDatastructureTests ${PROJECT_NAME}-resources ${PROJECT_NAME}-parser)
target_include_directories(runDatastructureTests PRIVATE ${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test/include/)

if (HYPRO_USE_SERIALIZATION)
    target_link_libraries(runDatastructureTests PUBLIC
            ${PROJECT_NAME}-shared
            ${PROJECT_NAME}-parser
            ${GTEST_LIBRARIES}
            cereal::cereal
            )
else ()
    target_link_libraries(runDatastructureTests PUBLIC
            ${PROJECT_NAME}-shared
            ${PROJECT_NAME}-parser
            ${GTEST_LIBRARIES}
            )
endif ()

add_test(NAME datastructures COMMAND runDatastructureTests --gtest_catch_exceptions=0)

if (DEVELOPER)
    set_property(TEST datastructures PROPERTY
            ENVIRONMENT LD_PRELOAD=${asanLocation}
            )
endif ()

add_dependencies(allTests runDatastructureTests)
