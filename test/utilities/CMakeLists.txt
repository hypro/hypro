if (${STATICLIB_SWITCH} STREQUAL "OFF")

    # reduce compiler optimization for tests
    set(utility_test_sources
            SerializationTest.cpp
            SequenceGenerationTest.cpp
            )

    SET_SOURCE_FILES_PROPERTIES(${utility_test_sources} PROPERTIES COMPILE_FLAGS -O0)

    ################################
    # Unit Tests
    ################################

    add_executable(runUtilityTests ${utility_test_sources})

    message(STATUS "GTEST INCLUDE DIR IN UTIL_TEST: ${GTEST_INCLUDE_DIR}")
    message(STATUS "GTEST LIBRARIES IN UTIL_TEST: ${GTEST_LIBRARIES}")

    add_dependencies(runUtilityTests hypro_resources)
    target_include_directories(runUtilityTests PRIVATE ${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test/include/
            ${cereal_INCLUDE_DIR})

    target_link_libraries(runUtilityTests PUBLIC
            ${GTEST_LIBRARIES}
            ${PROJECT_NAME}-shared
            cereal::cereal
            )

    cotire(runUtilityTests)

    add_test(NAME utility COMMAND runUtilityTests)

    if (DEVELOPER)
        set_property(TEST utility PROPERTY
                ENVIRONMENT LD_PRELOAD=${asanLocation}
                )
    endif ()

    add_dependencies(allTests runUtilityTests)
endif ()
