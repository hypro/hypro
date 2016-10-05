message("-- Use shipped version of glpk")
set(glpk_version "4.60")
ExternalProject_Add(
	glpk
	URL ftp://ftp.gnu.org/gnu/glpk/glpk-${glpk_version}.tar.gz
	#SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/resources/glpk-${glpk_version}"
    CONFIGURE_COMMAND ./configure --prefix=${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/ --with-gmp
	PREFIX ${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/
            #BUILD_COMMAND make
            BUILD_IN_SOURCE 1
            INSTALL_DIR ${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/
            INSTALL_COMMAND make install
	)

ExternalProject_Get_Property(glpk source_dir)
ExternalProject_Get_Property(glpk binary_dir)

add_imported_library(GLPK SHARED "${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/lib/libglpk.so" "${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/include")

message("Set glpk include dir to ${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/include")

set( GLPK_INCLUDE_DIR "${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/include" PARENT_SCOPE )
set( GLPK_LIBRARIES "${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/lib/libglpk.so" PARENT_SCOPE )

add_dependencies(resources glpk)
