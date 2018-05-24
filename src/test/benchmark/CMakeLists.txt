if(${STATICLIB_SWITCH} STREQUAL "OFF")

	################################
	# Unit Tests
	################################

	add_executable(runBenchmark
		AllBenchmarkTest.cpp
	)

	add_dependencies(runBenchmark resources)
	target_include_directories(runBenchmark PRIVATE ${GTEST_INCLUDE_DIR})

	target_link_libraries(runBenchmark
							${PROJECT_NAME}
							${GTEST_LIBRARIES})

	cotire(runBenchmark)

	#add_test( NAME benchmark COMMAND runBenchmark )
endif()
