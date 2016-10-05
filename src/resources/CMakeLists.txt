add_custom_target(resources)

# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/resources)

if(GTEST_FOUND)
	#set(GTEST_LIBRARIES ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} PARENT_SCOPE)
	message("-- Use system version of GTest")
else()
	message("-- Download version of GTest")
	include(gtest.cmake)
	# required for testing.
	#set( GTEST_INCLUDE_DIR ${GTEST_INCLUDE_DIR} PARENT_SCOPE)
	#set( GTEST_LIBRARIES ${GTEST_LIBRARIES} PARENT_SCOPE)
endif()

if(GLPK_FOUND)
	message("-- Use system version of glpk")
else()
	message("-- Download version of glpk")
	include(glpk.cmake)

	message("GLPK_INCLUDE_DIR: ${GLPK_INCLUDE_DIR}")

	set( GLPK_INCLUDE_DIR ${GLPK_INCLUDE_DIR} PARENT_SCOPE )
	set( GLPK_LIBRARIES ${GLPK_LIBRARIES} PARENT_SCOPE )
endif()

if(LOGGING_HYPRO)
	if(LOG4CPLUS_FOUND)
		message("-- Use system version of log4cplus")
	else()
		message("-- Download version of log4cplus")
		include(log4cplus.cmake)

		set(LOG4CPLUS_INCLUDE_DIRS "${binary_dir}/include" PARENT_SCOPE)
		set(LOG4CPLUS_LIBRARIES "${binary_dir}/src" PARENT_SCOPE)
		set(LOG4CPLUS_FOUND "TRUE" PARENT_SCOPE)
	endif()
endif()
