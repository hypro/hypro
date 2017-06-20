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
		#AntlrParserTest.cpp				#new for antlr
	)

	add_dependencies(runCoreTests googletest)
	target_include_directories(runCoreTests PRIVATE ${GTEST_INCLUDE_DIR})

	target_link_libraries(runCoreTests
							${PROJECT_NAME}
							${GTEST_LIBRARIES}
							)

	cotire(runCoreTests)

	add_test( NAME core COMMAND runCoreTests )

	#New for AnTLR
	message("I made it to AntlrTests")
	add_executable(runAntlrTests AntlrParserTest.cpp)
	message("Added executable")
	add_dependencies(runAntlrTests googletest antlr4cpp)
	message("Added dependencies")
	target_include_directories(runAntlrTests PRIVATE ${GTEST_INCLUDE_DIR} ${ANTLR4CPP_INCLUDE_DIRS})
	target_link_libraries(runAntlrTests ${PROJECT_NAME} ${GTEST_LIBRARIES} ${ANTLR4CPP_LIBS})
	message("Targeted link libraries: " ${PROJECT_NAME} ${GTEST_LIBRARIES} ${ANTLR4CPP_LIBS})
	add_test( NAME parser COMMAND runAntlrTests )
	message("Added a test named parser")
endif()
