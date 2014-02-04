add_custom_target(resources)
add_custom_target(install-resources)

# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/src/resources)

# Adding log4cplus.
if(LOG4CPLUS_FOUND)
	set(LOG4CPLUS_LIBRARY ${LOG4CPLUS_LIBRARY} PARENT_SCOPE)
	message("-- Use system version of Log4CPlus")	
else()
# Add log4cplus (local build)
	message("-- Use shipped version of Log4CPlus")
	ExternalProject_Add(
		log4cplus
		DOWNLOAD_COMMAND ""
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/resources/log4cplus-1.1.1"
		# Force separate output paths for debug and release builds to allow easy
		# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
		# CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
		#           -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}/src/resources/log4cplus-1.1.1/build
				   -DBUILD_SHARED_LIBS:BOOL=0
		INSTALL_DIR ${CMAKE_SOURCE_DIR}/src/resources/log4cplus-1.1.1/build
		# Wrap download, configure and build steps in a script to log output
		LOG_CONFIGURE ON
		LOG_BUILD ON)

	set( LOG4CPLUS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/resources/log4cplus-1.1.1/build/include" PARENT_SCOPE )
	set( LOG4CPLUS_LIBRARY "${CMAKE_SOURCE_DIR}/src/resources/log4cplus-1.1.1/build/lib/liblog4cplusS.a" PARENT_SCOPE )
	add_dependencies(resources log4cplus)
endif()


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
		DOWNLOAD_COMMAND ""
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/resources/gtest-1.6.0"
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

if(EIGEN3_FOUND)
	message("-- Use system version of Eigen3")
else()
	message("-- Use shipped version of Eigen3")
	ExternalProject_Add(
		eigen
		DOWNLOAD_COMMAND ""
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/resources/eigen-3.2.0"
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}/src/resources/eigen-3.2.0/build
		#		   -DBUILD_SHARED_LIBS:BOOL=0
		INSTALL_DIR ${CMAKE_SOURCE_DIR}/resources/eigen-3.2.0/build
		# Wrap download, configure and build steps in a script to log output
		LOG_CONFIGURE ON
		LOG_BUILD ON)


	set( EIGEN3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/resources/eigen-3.2.0/build/include" PARENT_SCOPE )
	#set( EIGEN3_LIBRARY "${CMAKE_SOURCE_DIR}/src/resources/eigen-3.2.0/build/lib/" PARENT_SCOPE )
	add_dependencies(resources eigen)
endif()