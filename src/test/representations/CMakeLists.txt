if(${STATICLIB_SWITCH} STREQUAL "OFF")

	# reduce compiler optimization for tests
	set(representation_test_sources 
		BoxTest.cpp
		CarlPolytopeTest.cpp
		ConverterTest.cpp
		DifferenceBoundsTest.cpp
		GridTest.cpp
		HPolytopeTest.cpp
		NeighborhoodContainerTest.cpp
		OrthogonalPolyhedronTest.cpp
		PolytopeSupportFunctionTest.cpp
		SupportFunctionTest.cpp
		#TaylorModelTest.cpp
		VPolytopeTest.cpp
		ZonotopeTest.cpp
		SupportFunctionNewTest.cpp)

	if(HYPRO_USE_PPL)
		set(representation_test_sources "${representation_test_sources} PolytopeTest.cpp PolytopeUtilTest.cpp")
	endif()

	SET_SOURCE_FILES_PROPERTIES(${representation_test_sources} PROPERTIES COMPILE_FLAGS -O0)

	################################
	# Unit Tests
	################################

	add_executable(runRepresentationTests ${representation_test_sources})

	add_dependencies(runRepresentationTests resources)
	target_include_directories(runRepresentationTests PRIVATE ${GTEST_INCLUDE_DIR})

	target_link_libraries(runRepresentationTests LINK_PUBLIC
		${GTEST_LIBRARIES}
		${PROJECT_NAME}-shared
	)

	cotire(runRepresentationTests)

	add_test( NAME representations COMMAND runRepresentationTests )
endif()
