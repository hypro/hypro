if(${STATICLIB_SWITCH} STREQUAL "OFF")
	include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/lib ${include_dirs} )
	link_directories(${CMAKE_BINARY_DIR}/lib)

	################################
	# Unit Tests
	################################

	add_executable(runBenchmark
		AllBenchmarkTest.cpp
	)

	add_dependencies(runBenchmark googletest)

	target_link_libraries(runBenchmark
							${PROJECT_NAME}
							${libraries})
	add_test( NAME benchmark COMMAND runBenchmark )
endif()