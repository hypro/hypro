if(${STATICLIB_SWITCH} STREQUAL "OFF")

	################################
	# Unit Tests
	################################

	add_executable(runDatastructureTests
		HalfspaceTest.cpp
		PointTest.cpp
		VertexTest.cpp
		VertexContainerTest.cpp
		HybridAutomataTest.cpp
	)

	add_dependencies(runDatastructureTests googletest)
	target_include_directories(runDatastructureTests PRIVATE ${GTEST_INCLUDE_DIR})

	target_link_libraries(runDatastructureTests
							${PROJECT_NAME}
							${GTEST_LIBRARIES}
							)

	cotire(runDatastructureTests)

	add_test( NAME datastructures COMMAND runDatastructureTests )
endif()
