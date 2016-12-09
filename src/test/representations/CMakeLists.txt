if(${STATICLIB_SWITCH} STREQUAL "OFF")
	include_directories(${GTEST_INCLUDE_DIR})

	################################
	# Unit Tests
	################################

	if(HYPRO_USE_PPL)
		add_executable(runRepresentationTests
			BoxTest.cpp
			ConverterTest.cpp
			GridTest.cpp
			HPolytopeTest.cpp
			NeighborhoodContainerTest.cpp
			OrthogonalPolyhedronTest.cpp
			PolytopeTest.cpp
			PolytopeUtilTest.cpp
			PolytopeSupportFunctionTest.cpp
			SupportFunctionTest.cpp
			#TaylorModelTest.cpp
			VPolytopeTest.cpp
			ZonotopeTest.cpp
		)
	else()
		add_executable(runRepresentationTests
			BoxTest.cpp
			ConverterTest.cpp
			GridTest.cpp
			HPolytopeTest.cpp
			NeighborhoodContainerTest.cpp
			OrthogonalPolyhedronTest.cpp
			PolytopeSupportFunctionTest.cpp
			SupportFunctionTest.cpp
			#TaylorModelTest.cpp
			VPolytopeTest.cpp
			ZonotopeTest.cpp
		)
	endif()


	add_dependencies(runRepresentationTests googletest)

	target_link_libraries(runRepresentationTests LINK_PUBLIC
		${GTEST_LIBRARIES}
		${PROJECT_NAME}
	)

	cotire(runRepresentationTests)

	add_test( NAME representations COMMAND runRepresentationTests )
endif()
