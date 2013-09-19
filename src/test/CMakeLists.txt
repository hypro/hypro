if(${STATICLIB_SWITCH} STREQUAL "OFF")
	include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src )

	################################
	# Unit Tests
	################################
	add_executable(runNumberTests
		NumberTest.cpp
	)
	target_link_libraries(runNumberTests gtest gtest_main hypro ${libraries})
	add_test( NAME numbers COMMAND runNumberTests )
endif()

