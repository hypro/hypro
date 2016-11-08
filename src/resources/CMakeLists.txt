add_custom_target(resources ALL)

# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/resources)

if(carl_FOUND)
	message("-- Use system version of CArL")
else()
	message("-- Download version of CArL")
	include(carl.cmake)
endif()

if(GTEST_FOUND)
	#set(GTEST_LIBRARIES ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} PARENT_SCOPE)
	message("-- Use system version of GTest")
else()
	message("-- Download version of GTest")
	include(gtest.cmake)
endif()

if(GLPK_FOUND)
	message("-- Use system version of glpk")
else()
	message("-- Download version of glpk")
	include(glpk.cmake)
endif()

if(HYPRO_LOGGING)
	if(LOG4CPLUS_FOUND)
		message("-- Use system version of log4cplus")
	else()
		message("-- Download version of log4cplus")
		include(log4cplus.cmake)

		#set(LOG4CPLUS_INCLUDE_DIRS "${source_dir}/include" PARENT_SCOPE)
		#set(LOG4CPLUS_LIBRARIES "${binary_dir}" PARENT_SCOPE)
		set(LOG4CPLUS_FOUND "TRUE" PARENT_SCOPE)
	endif()
endif()
