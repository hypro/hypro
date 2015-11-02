if(${STATICLIB_SWITCH} STREQUAL "OFF")
    include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/lib ${include_dirs} )
    link_directories(${CMAKE_BINARY_DIR}/lib)

    ################################
    # Unit Tests
    ################################

    add_executable(runAlgorithmTests
    		#BoxReachabilityTest.cpp
    		ForwardReachabilityTest.cpp
			#HyReachTest.cpp
            #MinkowskiSumTest.cpp
            #SumPerformanceTest.cpp
              # rahsTwoTankTest.cpp
    )

    add_dependencies(runAlgorithmTests googletest)

    target_link_libraries(runAlgorithmTests
			${PROJECT_NAME}
                        ${libraries})

    cotire(runAlgorithmTests)

    add_test( NAME algorithms COMMAND runAlgorithmTests )

endif()
