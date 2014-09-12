if(${STATICLIB_SWITCH} STREQUAL "OFF")
    include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/lib ${include_dirs} )
    link_directories(${CMAKE_BINARY_DIR}/lib)

    ################################
    # Unit Tests
    ################################

    add_executable(runAlgorithmTests
            ForwardReachabilityTest.cpp
	    #HyReachTest.cpp
            MinkowskiSumTest.cpp
    )

    add_dependencies(runAlgorithmTests googletest)

    target_link_libraries(runAlgorithmTests
			${PROJECT_NAME}
                        ${libraries})
    add_test( NAME algorithms COMMAND runAlgorithmTests )

endif()
