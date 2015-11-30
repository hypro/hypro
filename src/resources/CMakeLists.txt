add_custom_target(resources)
add_custom_target(install-resources)

# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/src/resources)

if(GTEST_FOUND)
	set(GTEST_LIBRARIES ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} PARENT_SCOPE)
	#set(GTEST_INCLUDE_DIR ${GTEST_INCLUDE_DIR} PARENT_SCOPE)
	message("-- Use system version of GTest")
else()
	# Create configure command dependend on compiler
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
			set (cmake_command -Dgtest_force_shared_crt=ON -DCXX=/usr/bin/clang++ -DCMAKE_CXX_FLAGS=-stdlib=libc++ -DCMAKE_CXX_FLAGS=-std=c++11 -DCMAKE_CXX_FLAGS=-DGTEST_USE_OWN_TR1_TUPLE=1 )
	else()
			set(cmake_command -Dgtest_force_shared_crt=ON)
	endif()
	# Add gtest (local build)
	message("-- Use shipped version of GTest")
	ExternalProject_Add(
		googletest
		#For downloads (may be useful later!)
		#SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
		#TIMEOUT 10
		SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.6.0"
		# Force separate output paths for debug and release builds to allow easy
		# identification of correct lib in subsequent TARGET_LINK_LIBRARIES
		CMAKE_ARGS ${cmake_command}
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

if(GLPK_FOUND)
	message("-- Use system version of GLPK")
else()
	message("-- Use shipped version of GLPK")
	ExternalProject_Add(
		glpk
		DOWNLOAD_COMMAND ""
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/resources/glpk-4.54"
                CONFIGURE_COMMAND ${CMAKE_SOURCE_DIR}/src/resources/glpk-4.54/configure --prefix=${CMAKE_BINARY_DIR}/resources/glpk-4.54/ --with-gmp
		PREFIX ${CMAKE_BINARY_DIR}/resources/glpk-4.54/
                #BUILD_COMMAND make
                BUILD_IN_SOURCE 1
                INSTALL_DIR ${CMAKE_BINARY_DIR}/resources/glpk-4.54/
                INSTALL_COMMAND make install
		LOG_CONFIGURE ON
		LOG_BUILD ON)

	set( GLPK_INCLUDE_DIR "${CMAKE_BINARY_DIR}/resources/glpk-4.54/include/" PARENT_SCOPE )
	set( GLPK_LIBRARIES "${CMAKE_BINARY_DIR}/resources/glpk-4.54/lib/libglpk.a" PARENT_SCOPE )
	set( GLPK_FOUND 1 PARENT_SCOPE)
	add_dependencies(resources glpk)
endif()