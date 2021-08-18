set(glpk_version "4.65")

# create include output folder
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/resources/src/glpk_download/include")

ExternalProject_Add(
    glpk_download
    LOG_DOWNLOAD true
    LOG_CONFIGURE true
    LOG_BUILD true
    TIMEOUT 10
	URL https://ftp.gnu.org/gnu/glpk/glpk-${glpk_version}.tar.gz
	#SOURCE_DIR "${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}"
    CONFIGURE_COMMAND ./configure --prefix=${CMAKE_BINARY_DIR}/resources/src/glpk_download --with-gmp --with-pic CPPFLAGS=-fPIC --disable-shared --disable-dl --enable-static
    #CONFIGURE_COMMAND ./configure --with-gmp --with-pic CPPFLAGS=-fPIC --disable-shared --disable-dl --enable-static
    BUILD_COMMAND make
    BUILD_IN_SOURCE 1
    #PREFIX glpk-${glpk_version}
    INSTALL_COMMAND make install
    #INSTALL_DIR ${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}
	)

set( GLPK_INCLUDE_DIR "${CMAKE_BINARY_DIR}/resources/src/glpk_download/include" )
set( GLPK_LIBRARIES "${CMAKE_BINARY_DIR}/resources/src/glpk_download/lib/${CMAKE_FIND_LIBRARY_PREFIXES}glpk${CMAKE_STATIC_LIBRARY_SUFFIX}" )

add_imported_library(GLPK STATIC "${GLPK_LIBRARIES}" "${GLPK_INCLUDE_DIR}")
list(APPEND ${PROJECT_NAME}_LIBRARIES_STATIC ${GLPK_LIBRARIES})
list(APPEND ${PROJECT_NAME}_LIBRARIES_DYNAMIC ${GLPK_LIBRARIES})
list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${GLPK_INCLUDE_DIR})
set(${PROJECT_NAME}_LIBRARIES_DYNAMIC ${${PROJECT_NAME}_LIBRARIES_DYNAMIC} PARENT_SCOPE)

add_dependencies(resources glpk_download)

set(GLPK_FOUND TRUE PARENT_SCOPE)