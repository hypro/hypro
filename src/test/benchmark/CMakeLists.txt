if(${STATICLIB_SWITCH} STREQUAL "OFF")
	include_directories(${GTEST_INCLUDE_DIR})

	################################
	# Unit Tests
	################################

	add_executable(runBenchmark
		AllBenchmarkTest.cpp
	)

	add_dependencies(runBenchmark googletest)

	target_link_libraries(runBenchmark
							${PROJECT_NAME}
							${GTEST_LIBRARIES})

	cotire(runBenchmark)

	#add_test( NAME benchmark COMMAND runBenchmark )
endif()
