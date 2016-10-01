add_custom_target(resources)

# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/resources)

if(GTEST_FOUND)
	#set(GTEST_LIBRARIES ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} PARENT_SCOPE)
	message("-- Use system version of GTest")
else()
	# Create configure command dependend on compiler
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
			set(cmake_command -Dgtest_force_shared_crt=ON -DCXX=/usr/bin/clang++ -DCMAKE_CXX_FLAGS=-stdlib=libc++ -DCMAKE_CXX_FLAGS=-std=c++11 -DCMAKE_CXX_FLAGS=-DGTEST_USE_OWN_TR1_TUPLE=1 )
	else()
			set(cmake_command -Dgtest_force_shared_crt=ON)
	endif()
	# Add gtest (local build)
	message("-- Use shipped version of GTest")
	ExternalProject_Add(
		googletest
		GIT_REPOSITORY http://github.com/google/googletest.git
		# Force separate output paths for debug and release builds to allow easy
		# identification of correct lib in subsequent TARGET_LINK_LIBRARIES
		#CMAKE_ARGS ${cmake_command}
		GIT_TAG "release-1.7.0"
		INSTALL_COMMAND "")

	# Specify include dir
	ExternalProject_Get_Property(googletest source_dir)
	ExternalProject_Get_Property(googletest binary_dir)

	add_imported_library(HYPRO_GTESTCORE STATIC "${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a" "${source_dir}/include")
	add_imported_library(HYPRO_GTESTMAIN STATIC "${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a" "${source_dir}/include")

	# required for testing.
	set( GTEST_INCLUDE_DIR "${source_dir}/include" PARENT_SCOPE)
	set( GTEST_LIBRARIES "${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a" "${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a" pthread dl PARENT_SCOPE)

	add_dependencies(resources googletest)
endif()

if(GLPK_FOUND)
	message("-- Use system version of glpk")
else()
	message("-- Use shipped version of glpk")
	set(glpk_version "4.60")
	ExternalProject_Add(
		glpk
		URL ftp://ftp.gnu.org/gnu/glpk/glpk-${glpk_version}.tar.gz
        CONFIGURE_COMMAND ./configure --prefix=${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/ --with-gmp
		PREFIX ${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/
                BUILD_IN_SOURCE 1
                INSTALL_DIR ${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/
                INSTALL_COMMAND make install
		)

	ExternalProject_Get_Property(googletest source_dir)
	ExternalProject_Get_Property(googletest binary_dir)

	message("GLPK include dir set to ${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/include")

	add_imported_library(GLPK SHARED "${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/lib/libglpk.so" "${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/include")

	set( GLPK_INCLUDE_DIR "${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/include" PARENT_SCOPE )
	set( GLPK_LIBRARIES "${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/lib/libglpk.so" PARENT_SCOPE )

	add_dependencies(resources glpk)
endif()

if(LOGGING_HYPRO)
	if(LOG4CPLUS_FOUND)
		message("-- Use system version of log4cplus")
	else()
		message("-- Download version of log4cplus")
		ExternalProject_Add(log4cplus
				GIT_REPOSITORY https://github.com/log4cplus/log4cplus.git
				INSTALL_COMMAND ""
				)

		add_dependencies(resources log4cplus)

		ExternalProject_Get_Property(log4cplus source_dir)
		ExternalProject_Get_Property(log4cplus binary_dir)

		message("source_dir: ${source_dir}")
		message("binary_dir: ${binary_dir}")
		message("shared library suffix: ${CMAKE_SHARED_LIBRARY_SUFFIX}")

		add_imported_library(log4cplus SHARED "${binary_dir}/src/${CMAKE_FIND_LIBRARY_PREFIXES}log4cplus${CMAKE_SHARED_LIBRARY_SUFFIX}" "${binary_dir}/include")

		set(LOG4CPLUS_INCLUDE_DIRS "${binary_dir}/include" PARENT_SCOPE)
		set(LOG4CPLUS_LIBRARIES "${binary_dir}/src" PARENT_SCOPE)
		set(LOG4CPLUS_FOUND "TRUE" PARENT_SCOPE)
	endif()
endif()
