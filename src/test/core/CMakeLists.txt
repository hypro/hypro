if(${STATICLIB_SWITCH} STREQUAL "OFF")

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
	target_include_directories(runCoreTests PRIVATE ${GTEST_INCLUDE_DIR})

	target_link_libraries(runCoreTests
							${PROJECT_NAME}
							${GTEST_LIBRARIES}
							)

	cotire(runCoreTests)

	add_test( NAME core COMMAND runCoreTests )
endif()
