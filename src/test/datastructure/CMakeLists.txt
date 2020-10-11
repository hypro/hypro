if(${STATICLIB_SWITCH} STREQUAL "OFF")

	# reduce compiler optimization for tests
	set(datastructure_test_sources
		DAGTest.cpp
		DecompositionTest.cpp
		EventTimingProviderTest.cpp
		FlowpipeTest.cpp
		HalfspaceTest.cpp
		HIVTest.cpp
		PointTest.cpp
		VertexTest.cpp
		VertexContainerTest.cpp
		RangeTest.cpp
		StateTest.cpp
		StateVisitorTest.cpp
		TreeTest.cpp
		#StrategyTest.cpp
		HybridAutomataTest.cpp
		##HybridAutomataOutputTest.cpp
		WorkQueueTest.cpp
		##HybridAutomataParallelCompositionTest.cpp
	)

	SET_SOURCE_FILES_PROPERTIES(${datastructure_test_sources} PROPERTIES COMPILE_FLAGS -O0)

	################################
	# Unit Tests
	################################

	add_executable(runDatastructureTests
		${datastructure_test_sources}
	)

	add_dependencies(runDatastructureTests resources)
	target_include_directories(runDatastructureTests PRIVATE ${GTEST_INCLUDE_DIR})

	target_link_libraries(runDatastructureTests
							${PROJECT_NAME}-shared
							${GTEST_LIBRARIES}
							)

	cotire(runDatastructureTests)

	add_test( NAME datastructures COMMAND runDatastructureTests )

	if(DEVELOPER)
	set_property(TEST datastructures PROPERTY
		ENVIRONMENT LD_PRELOAD=${asanLocation}
	)
	endif()

	add_dependencies(allTests runDatastructureTests)
endif()
