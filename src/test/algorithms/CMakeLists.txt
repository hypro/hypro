if(${STATICLIB_SWITCH} STREQUAL "OFF")
    #include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/lib ${include_dirs} )
    include_directories(${GTEST_INCLUDE_DIR})
    #link_directories(${CMAKE_BINARY_DIR}/lib)

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

    #add_dependencies(runAlgorithmTests googletest)

    message("${GTEST_INCLUDE_DIR} VS: ${source_dir}/include")
	message("${GTEST_LIBRARIES}")

    message("Linkt to project: ${PROJECT_NAME}")
    target_link_libraries(runAlgorithmTests
			${PROJECT_NAME}
			${GTEST_LIBRARIES}
			)

    cotire(runAlgorithmTests)

    add_test( NAME algorithms COMMAND runAlgorithmTests )

endif()
