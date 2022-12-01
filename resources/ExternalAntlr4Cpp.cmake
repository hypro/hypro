# only JRE required
#FIND_PACKAGE(Java COMPONENTS Runtime REQUIRED)

set(ANTLR4CPP_LOCAL_REPO ${CMAKE_CURRENT_SOURCE_DIR}/antlr4-cpp-runtime-4.7.1-source)

#if(NOT EXISTS "${ANTLR4CPP_JAR_LOCATION}")
#  message(FATAL_ERROR "Unable to find antlr tool. ANTLR4CPP_JAR_LOCATION:${ANTLR4CPP_JAR_LOCATION}")
#endif()

# download runtime environment
ExternalProject_ADD(
        antlr4cpp
        #--Depend-on-antrl-tool-----------
        # DEPENDS antlrtool
        #--Core-directories-----------
        #PREFIX             ${ANTLR4CPP_EXTERNAL_ROOT}
        #PREFIX             ${ANTLR4CPP_BUILD_INCLUDE_DIR}		#Added for local copy
        #--Download step--------------
        # GIT_REPOSITORY    ${ANTLR4CPP_EXTERNAL_REPO}
        # GIT_TAG           ${ANTLR4CPP_EXTERNAL_TAG}
        #SOURCE_DIR ${ANTLR4CPP_LOCAL_REPO}  #Added for local copy
        URL https://www.antlr.org/download/antlr4-cpp-runtime-4.9.3-source.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        #SOURCE_DIR ${EP_PREFIX_DIR}/src/antlr4cpp
        INSTALL_DIR ${EP_PREFIX_DIR}/src/antlr4cpp-build
        CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX:PATH=${EP_PREFIX_DIR}/src/antlr4cpp-build -DCMAKE_CXX_FLAGS=${RESSOURCES_FLAGS} -DBUILD_SHARED_LIBS=ON -DBUILD_TESTS=OFF -DWITH_DEMO=False -DWITH_LIBCXX=False ${EP_PREFIX_DIR}/src/antlr4cpp
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        #BUILD_COMMAND ${CMAKE_MAKE_PROGRAM}
        LOG_BUILD ON
        LOG_MERGED_STDOUTERR ON
        LOG_OUTPUT_ON_FAILURE ON
        #INSTALL_COMMAND ""
)

ExternalProject_Get_Property(antlr4cpp INSTALL_DIR)
file(MAKE_DIRECTORY ${INSTALL_DIR}/include/antlr4-runtime)
list(APPEND ANTLR4CPP_INCLUDE_DIRS ${INSTALL_DIR}/include/antlr4-runtime)

set(ANTLR4CPP_STATIC_LIBS "${INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}antlr4-runtime${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(ANTLR4CPP_SHARED_LIBS "${INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}antlr4-runtime${CMAKE_SHARED_LIBRARY_SUFFIX}")
set(ANTLR4CPP_INCLUDE_DIRS ${ANTLR4CPP_INCLUDE_DIRS})

add_imported_library(ANTLR4 STATIC ${ANTLR4CPP_STATIC_LIBS} ${ANTLR4CPP_INCLUDE_DIRS})
add_imported_library(ANTLR4 SHARED ${ANTLR4CPP_SHARED_LIBS} ${ANTLR4CPP_INCLUDE_DIRS})

add_dependencies(ANTLR4_STATIC antlr4cpp)
add_dependencies(ANTLR4_SHARED antlr4cpp)
add_dependencies(hypro_resources ANTLR4_STATIC ANTLR4_SHARED)

target_link_libraries(${PROJECT_NAME}-shared PUBLIC ANTLR4_SHARED)
target_link_libraries(${PROJECT_NAME}-static PUBLIC ANTLR4_STATIC)

target_include_directories(${PROJECT_NAME}-objects
        PRIVATE ${ANTLR4CPP_INCLUDE_DIRS}
        )
target_include_directories(${PROJECT_NAME}-static
        PRIVATE ${ANTLR4CPP_INCLUDE_DIRS}
        )
target_include_directories(${PROJECT_NAME}-shared
        PRIVATE ${ANTLR4CPP_INCLUDE_DIRS}
        )

list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${ANTLR4CPP_INCLUDE_DIRS})
