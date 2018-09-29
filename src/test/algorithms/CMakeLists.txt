if(${STATICLIB_SWITCH} STREQUAL "OFF")

    ################################
    # Unit Tests
    ################################

    add_executable(runAlgorithmTests
    		#BoxReachabilityTest.cpp
    		FacetEnumerationTest.cpp
    		#ForwardReachabilityTest.cpp
			#HyReachTest.cpp
            #MinkowskiSumTest.cpp
            #SumPerformanceTest.cpp
              # rahsTwoTankTest.cpp
            VertexEnumerationTest.cpp
            UtilityTest.cpp
    )

    add_dependencies(runAlgorithmTests resources)
    target_include_directories(runAlgorithmTests PRIVATE ${GTEST_INCLUDE_DIR})

    target_link_libraries(runAlgorithmTests
			${PROJECT_NAME}
			${GTEST_LIBRARIES}
			)

    cotire(runAlgorithmTests)

    add_test( NAME algorithms COMMAND runAlgorithmTests )

endif()
