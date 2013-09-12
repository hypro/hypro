if(GTEST_FOUND)
	set(GTEST_LIBRARIES ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} PARENT_SCOPE)
	include_directories(${GTEST_INCLUDE_DIR})
else()
	# Add gtest (local build)
	message("-- Use shipped version of GTest")
	ExternalProject_Add(
		googletest
		#For downloads (may be useful later!)
		#SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
		#TIMEOUT 10
		DOWNLOAD_COMMAND ""
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/resources/gtest-1.6.0"
		# Force separate output paths for debug and release builds to allow easy
		# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
		CMAKE_ARGS -Dgtest_force_shared_crt=ON
		# Disable install step
		INSTALL_COMMAND ""
		# Wrap download, configure and build steps in a script to log output
		LOG_CONFIGURE ON
		LOG_BUILD ON)

	# Specify include dir
	ExternalProject_Get_Property(googletest source_dir)
	set(GTEST_INCLUDE_DIR ${source_dir}/include PARENT_SCOPE)
	
	# Specify MainTest's link libraries
	ExternalProject_Get_Property(googletest binary_dir)
	set(GTEST_LIBRARIES ${binary_dir}/libgtest.a ${binary_dir}/libgtest_main.a PARENT_SCOPE)

	add_dependencies(resources googletest)
endif()
