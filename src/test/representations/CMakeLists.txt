if(${STATICLIB_SWITCH} STREQUAL "OFF")

	################################
	# Unit Tests
	################################

	if(HYPRO_USE_PPL)
		add_executable(runRepresentationTests
			#BoxTest.cpp
			#CarlPolytopeTest.cpp
			#ConverterTest.cpp
			#DifferenceBoundsTest.cpp
			#GridTest.cpp
			#HPolytopeTest.cpp
			#NeighborhoodContainerTest.cpp
			#OrthogonalPolyhedronTest.cpp
			#PolytopeTest.cpp
			#PolytopeUtilTest.cpp
			#PolytopeSupportFunctionTest.cpp
			#SupportFunctionTest.cpp
			##TaylorModelTest.cpp
			#VPolytopeTest.cpp
			#ZonotopeTest.cpp
			SupportFunctionNewTest.cpp
		)
	else()
		add_executable(runRepresentationTests
			#BoxTest.cpp
			#CarlPolytopeTest.cpp
			#ConverterTest.cpp
			#DifferenceBoundsTest.cpp
			#GridTest.cpp
			#HPolytopeTest.cpp
			#NeighborhoodContainerTest.cpp
			#OrthogonalPolyhedronTest.cpp
			#PolytopeSupportFunctionTest.cpp
			#SupportFunctionTest.cpp
			##TaylorModelTest.cpp
			#VPolytopeTest.cpp
			#ZonotopeTest.cpp
			SupportFunctionNewTest.cpp
		)
	endif()


	add_dependencies(runRepresentationTests resources)
	target_include_directories(runRepresentationTests PRIVATE ${GTEST_INCLUDE_DIR})

	target_link_libraries(runRepresentationTests LINK_PUBLIC
		${GTEST_LIBRARIES}
		${PROJECT_NAME}
	)

	cotire(runRepresentationTests)

	add_test( NAME representations COMMAND runRepresentationTests )
endif()
