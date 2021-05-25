if(${STATICLIB_SWITCH} STREQUAL "OFF")

	# reduce compiler optimization for tests
	set(core_test_sources
		EigenAdaptionsTest.cpp
		#ifdef LOGGING_HYPRO
		#LoggerTest.cpp
		#endif
		OptimizerTest.cpp
		PlotterTest.cpp
		UtilityTest.cpp
	)

	SET_SOURCE_FILES_PROPERTIES(${core_test_sources} PROPERTIES COMPILE_FLAGS -O0)

	################################
	# Core Unit Tests
	################################

	add_executable(runCoreTests
		${core_test_sources}
	)

	add_dependencies(runCoreTests resources)
	target_include_directories(runCoreTests PRIVATE ${GTEST_INCLUDE_DIR})

	target_link_libraries(runCoreTests PUBLIC
							${PROJECT_NAME}-shared
							${GTEST_LIBRARIES}
							)
	cotire(runCoreTests)

	add_test( NAME core COMMAND runCoreTests )

	add_dependencies(allTests runCoreTests)

	################################
	# Parser Unit Tests
	################################

	add_executable(runParserTests
		AntlrParserTest.cpp
		ParserTest.cpp
		#AntlrParserCIFTest.cpp
	)
	add_dependencies(runParserTests resources antlr4cpp)
	target_include_directories(runParserTests PRIVATE ${GTEST_INCLUDE_DIR})
	target_link_libraries(runParserTests ${PROJECT_NAME}-shared ${GTEST_LIBRARIES})
	#message("Targeted link libraries: " ${PROJECT_NAME} ${GTEST_LIBRARIES} ${ANTLR4CPP_LIBS})
	add_test( NAME parser COMMAND runParserTests )

	add_dependencies(allTests runParserTests)

endif()
