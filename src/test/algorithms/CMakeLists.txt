if(${STATICLIB_SWITCH} STREQUAL "OFF")
    include_directories(${GTEST_INCLUDE_DIR})

    ################################
    # Unit Tests
    ################################

    add_executable(runAlgorithmTests
    		#BoxReachabilityTest.cpp
    		#FacetEnumerationTest.cpp
    		#ForwardReachabilityTest.cpp
			#HyReachTest.cpp
            #MinkowskiSumTest.cpp
            #SumPerformanceTest.cpp
              # rahsTwoTankTest.cpp
            VertexEnumerationTest.cpp
    )

    add_dependencies(runAlgorithmTests googletest)

    target_link_libraries(runAlgorithmTests
			${PROJECT_NAME}
			${GTEST_LIBRARIES}
			)

    cotire(runAlgorithmTests)

    add_test( NAME algorithms COMMAND runAlgorithmTests )

endif()
