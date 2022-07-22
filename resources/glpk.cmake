set(glpk_version "5.0")

# create build folder to be able to use it as an include folder
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources/src/glpk-build/include)

ExternalProject_Add(
        glpk
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glpk-${glpk_version}"
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/glpk-${glpk_version}/configure --prefix=${CMAKE_BINARY_DIR}/resources/src/glpk-build --with-gmp --with-pic CPPFLAGS=-fPIC --disable-shared --disable-dl --enable-static
        # build in source is needed here, as configure moves all relevant files to glpk-build and then the make and make install need to know that it is
        # in-source (from this perspective on)
        BUILD_IN_SOURCE 1
        INSTALL_DIR ${CMAKE_BINARY_DIR}/resources/src/glpk-build
        INSTALL_COMMAND make install
        LOG_CONFIGURE ON
        LOG_BUILD ON
        LOG_MERGED_STDOUTERR ON
        LOG_OUTPUT_ON_FAILURE ON
)


set(GLPK_INCLUDE_DIR "${CMAKE_BINARY_DIR}/resources/src/glpk-build/include")
set(GLPK_LIBRARIES "${CMAKE_BINARY_DIR}/resources/src/glpk-build/lib/${CMAKE_FIND_LIBRARY_PREFIXES}glpk${CMAKE_STATIC_LIBRARY_SUFFIX}")

add_imported_library(GLPK STATIC "${GLPK_LIBRARIES}" "${GLPK_INCLUDE_DIR}")

add_dependencies(GLPK_STATIC glpk)
add_dependencies(hypro_resources GLPK_STATIC)

target_link_libraries(${PROJECT_NAME}-objects PUBLIC GLPK_STATIC)
target_link_libraries(${PROJECT_NAME}-shared PUBLIC GLPK_STATIC)
target_link_libraries(${PROJECT_NAME}-static PUBLIC GLPK_STATIC)

target_include_directories(${PROJECT_NAME}-objects
        PRIVATE ${GLPK_INCLUDE_DIR}
        )
target_include_directories(${PROJECT_NAME}-static
        PRIVATE ${GLPK_INCLUDE_DIR}
        )
target_include_directories(${PROJECT_NAME}-shared
        PRIVATE ${GLPK_INCLUDE_DIR}
        )

list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${GLPK_INCLUDE_DIR})
