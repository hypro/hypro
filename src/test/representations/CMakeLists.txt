if(${STATICLIB_SWITCH} STREQUAL "OFF")
	include_directories(${GTEST_INCLUDE_DIR})

	################################
	# Unit Tests
	################################

	if(USE_PPL)
		add_executable(runRepresentationTests
			#BoxTest.cpp
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

	################################
	# Tests for the practical term
	################################

	#add_executable(runPTermTests
	#	PTermBoxTest.cpp
	#	PTermPolytopeTest.cpp
	#)

	add_dependencies(runRepresentationTests googletest)
	#add_dependencies(runPTermTests googletest)

	target_link_libraries(runRepresentationTests LINK_PUBLIC
		${GTEST_LIBRARIES}
		${PROJECT_NAME}
	)

	#target_link_libraries(runPTermTests
	#	${libraries}
	#	${PROJECT_NAME}
	#)

	cotire(runRepresentationTests)
	#	cotire(runPTermTests)

	add_test( NAME representations COMMAND runRepresentationTests )
	#add_test( NAME practicalTerm COMMAND runPTermTests )
endif()
