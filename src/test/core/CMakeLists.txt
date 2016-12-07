if(${STATICLIB_SWITCH} STREQUAL "OFF")
	include_directories(${GTEST_INCLUDE_DIR})

	################################
	# Unit Tests
	################################

	add_executable(runCoreTests
		EigenAdaptionsTest.cpp
		#ifdef LOGGING_HYPRO
		#LoggerTest.cpp
		#endif
		OptimizerTest.cpp
		ParserTest.cpp
		UtilityTest.cpp
	)

	add_dependencies(runCoreTests googletest)

	target_link_libraries(runCoreTests
							${PROJECT_NAME}
							${GTEST_LIBRARIES}
							)

	cotire(runCoreTests)

	add_test( NAME core COMMAND runCoreTests )
endif()
