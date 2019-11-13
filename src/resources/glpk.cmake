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
add_dependencies(resources GLPK_STATIC)

#ExternalProject_Get_Property(glpk source_dir)
#ExternalProject_Get_Property(glpk binary_dir)
#
##add_imported_library(GLPK SHARED "${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}#glpk${CMAKE_SHARED_LIBRARY_SUFFIX}" "${CMAKE_BINARY_DIR}/resources/glpk-${glpk_version}/include")
#
#set( GLPK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/resources/glpk-${glpk_version}/build/include" )
#set( GLPK_LIBRARIES "${CMAKE_SOURCE_DIR}/src/resources/glpk-${glpk_version}/build/lib/${CMAKE_FIND_LIBRARY_PREFIXES}#glpk${CMAKE_STATIC_LIBRARY_SUFFIX}" )
#set( GLPK_LIBRARIES ${GLPK_LIBRARIES})
#
#add_imported_library(GLPK STATIC "${GLPK_LIBRARIES}" "${GLPK_INCLUDE_DIR}")
#list(APPEND ${PROJECT_NAME}_LIBRARIES_STATIC ${GLPK_LIBRARIES})
#list(APPEND ${PROJECT_NAME}_LIBRARIES_DYNAMIC ${GLPK_LIBRARIES})
#list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${GLPK_INCLUDE_DIR})
#set(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_INCLUDE_DIRS} PARENT_SCOPE)
#set(${PROJECT_NAME}_LIBRARIES_STATIC ${${PROJECT_NAME}_LIBRARIES_STATIC} PARENT_SCOPE)
#set(${PROJECT_NAME}_LIBRARIES_DYNAMIC ${${PROJECT_NAME}_LIBRARIES_DYNAMIC} PARENT_SCOPE)
#
##add_dependencies(GLPK glpk)
#
#add_dependencies(resources GLPK_STATIC)
