if (${STATICLIB_SWITCH} STREQUAL "OFF")

    # reduce compiler optimization for tests
    set(core_test_sources
            EigenAdaptionsTest.cpp
            #ifdef LOGGING_HYPRO
            #LoggerTest.cpp
            #endif
            OptimizerTest.cpp
            PlotterTest.cpp
            ReachTreePlotterTest.cpp
            UtilityTest.cpp
            TypeTraitsTest.cpp
            )

    SET_SOURCE_FILES_PROPERTIES(${core_test_sources} PROPERTIES COMPILE_FLAGS -O0)

    ################################
    # Core Unit Tests
    ################################

    add_executable(runCoreTests
            ${core_test_sources}
            )

    add_dependencies(runCoreTests ${PROJECT_NAME}-resources ${PROJECT_NAME}-parser)
    target_include_directories(runCoreTests PRIVATE ${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test/include/)

    target_link_libraries(runCoreTests PUBLIC
            ${PROJECT_NAME}-shared
            ${PROJECT_NAME}-parser
            ${GTEST_LIBRARIES}
            )
    cotire(runCoreTests)

    add_test(NAME core COMMAND runCoreTests)

    add_dependencies(allTests runCoreTests)

    ################################
    # Parser Unit Tests
    ################################

    add_executable(runParserTests
            AntlrParserTest.cpp
            #AntlrParserCIFTest.cpp
            )
    add_dependencies(runParserTests ${PROJECT_NAME}-resources antlr4cpp ${PROJECT_NAME}-parser)
    target_include_directories(runParserTests PRIVATE ${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test/include/)
    target_link_libraries(runParserTests ${PROJECT_NAME}-shared ${PROJECT_NAME}-parser ${GTEST_LIBRARIES})
    #message("Targeted link libraries: " ${PROJECT_NAME} ${GTEST_LIBRARIES} ${ANTLR4CPP_LIBS})
    add_test(NAME parser COMMAND runParserTests WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test/core)

    add_dependencies(allTests runParserTests)

endif ()
