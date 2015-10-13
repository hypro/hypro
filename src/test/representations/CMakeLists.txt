if(${STATICLIB_SWITCH} STREQUAL "OFF")
	include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/lib ${include_dirs} )
	link_directories(${CMAKE_BINARY_DIR}/lib)

	################################
	# Unit Tests
	################################

	add_executable(runRepresentationTests
	BoxTest.cpp
	ConverterTest.cpp
	GridTest.cpp
	HPolytopeTest.cpp
	NeighborhoodContainerTest.cpp
	OrthogonalPolyhedronTest.cpp
	PolytopeTest.cpp
	PolytopeSupportFunctionTest.cpp
	PolytopeUtilTest.cpp
	SupportFunctionTest.cpp
	#TaylorModelTest.cpp
	VPolytopeTest.cpp
	ZonotopeTest.cpp
	)

	add_dependencies(runRepresentationTests googletest)

	target_link_libraries(runRepresentationTests
		${libraries}
		${PROJECT_NAME}
	)
	cotire(runRepresentationTests)
	add_test( NAME representations COMMAND runRepresentationTests )
endif()
