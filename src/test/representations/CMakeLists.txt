if(${STATICLIB_SWITCH} STREQUAL "OFF")
	include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/lib ${include_dirs} )
	link_directories(${CMAKE_BINARY_DIR}/lib)

	################################
	# Unit Tests
	################################

	add_executable(runRepresentationTests
		BoxTest.cpp
		#ConverterTest.cpp
		GridTest.cpp
		HPolytopeTest.cpp
		NeighborhoodContainerTest.cpp
		OrthogonalPolyhedronTest.cpp
		PolytopeTest.cpp
		PolytopeSupportFunctionTest.cpp
		PolytopeUtilTest.cpp
		SupportFunctionTest.cpp
		TaylorModelTest.cpp
		VPolytopeTest.cpp
		ZonotopeTest.cpp
	)

	################################
	# Tests for the practical term
	################################

	add_executable(runPTermTests
		PTermBoxTest.cpp
		PTermPolytopeTest.cpp
	)

	add_dependencies(runRepresentationTests googletest)
	add_dependencies(runPTermTests googletest)

	target_link_libraries(runRepresentationTests LINK_PUBLIC
		${libraries}
		${PROJECT_NAME}
	)

	target_link_libraries(runPTermTests
		${libraries}
		${PROJECT_NAME}
	)

	if(USE_COTIRE)
		cotire(runRepresentationTests)
		cotire(runPTermTests)
	endif()

	add_test( NAME representations COMMAND runRepresentationTests )
	add_test( NAME practicalTerm COMMAND runPTermTests )
endif()
