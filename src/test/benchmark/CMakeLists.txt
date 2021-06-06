if(${STATICLIB_SWITCH} STREQUAL "OFF")

	################################
	# Unit Tests
	################################

	add_executable(runBenchmark
		AllBenchmarkTest.cpp
	)

	add_dependencies(runBenchmark hypro_resources)
	target_include_directories(runBenchmark PRIVATE ${GTEST_INCLUDE_DIR})

	target_link_libraries(runBenchmark
							${PROJECT_NAME}-shared
							${GTEST_LIBRARIES})

	cotire(runBenchmark)

	#add_test( NAME benchmark COMMAND runBenchmark )
endif()

file(GLOB_RECURSE BM_SOURCES ${CMAKE_CURRENT_LIST_DIR}/hyproBenchmark/*.cpp)

# general collection of benchmarks
add_executable(benchmark
	${BM_SOURCES}
)
target_link_libraries(benchmark PUBLIC
						${PROJECT_NAME}-shared
)
cotire(runBenchmark)
cotire(benchmark)
