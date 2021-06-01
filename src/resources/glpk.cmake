set(glpk_version "4.45")

# create build folder to be able to use it as an include folder
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/src/resources/glpk-${glpk_version}/build/include)

ExternalProject_Add(
	glpk
	SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/resources/glpk-${glpk_version}"
    CONFIGURE_COMMAND ./configure --prefix=${CMAKE_SOURCE_DIR}/src/resources/glpk-${glpk_version}/build --with-gmp --with-pic CPPFLAGS=-fPIC --disable-shared --disable-dl --enable-static
	PREFIX ${CMAKE_SOURCE_DIR}/src/resources/glpk-${glpk_version}/build
    BUILD_IN_SOURCE 1
    INSTALL_DIR ${CMAKE_SOURCE_DIR}/src/resources/glpk-${glpk_version}/build
    INSTALL_COMMAND make install
	)


set( GLPK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/resources/glpk-${glpk_version}/build/include" )
set( GLPK_LIBRARIES "${CMAKE_SOURCE_DIR}/src/resources/glpk-${glpk_version}/build/lib/${CMAKE_FIND_LIBRARY_PREFIXES}glpk${CMAKE_STATIC_LIBRARY_SUFFIX}" )

add_imported_library(GLPK STATIC "${GLPK_LIBRARIES}" "${GLPK_INCLUDE_DIR}")

add_dependencies(GLPK_STATIC glpk)
add_dependencies(hypro_resources GLPK_STATIC)

target_link_libraries(${PROJECT_NAME}-shared PUBLIC GLPK_STATIC)
target_link_libraries(${PROJECT_NAME}-static PUBLIC GLPK_STATIC)
