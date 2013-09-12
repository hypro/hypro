include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src ${include_dirs})

################################
# Unit Tests
################################
add_executable(runAllTests
	NumberTest.cpp
)
target_link_libraries(runAllTests gtest gtest_main)
add_test( runAllTests runAllTests )
