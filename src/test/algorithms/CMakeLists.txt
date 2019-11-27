if(${STATICLIB_SWITCH} STREQUAL "OFF")

    # reduce compiler optimization for tests
    set(algorithm_test_sources
      ##BoxReachabilityTest.cpp
      ##FacetEnumerationTest.cpp
      ##ForwardReachabilityTest.cpp
			##HyReachTest.cpp
      ##MinkowskiSumTest.cpp
      ##SumPerformanceTest.cpp
      ## rahsTwoTankTest.cpp
      #FourierMotzkinQETest.cpp
      #VertexEnumerationTest.cpp
      #UtilityTest.cpp
      TemplatePolyhedronContextTest.cpp
    )

  SET_SOURCE_FILES_PROPERTIES(${algorithm_test_sources} PROPERTIES COMPILE_FLAGS -O0)

    ################################
    # Unit Tests
    ################################

    add_executable(runAlgorithmTests
    		${algorithm_test_sources}
    )

    add_dependencies(runAlgorithmTests resources)
    target_include_directories(runAlgorithmTests PRIVATE ${GTEST_INCLUDE_DIR})

    target_link_libraries(runAlgorithmTests LINK_PUBLIC
			${GTEST_LIBRARIES}
			${PROJECT_NAME}-shared
			)

    cotire(runAlgorithmTests)

    add_test( NAME algorithms COMMAND runAlgorithmTests )

endif()
