# only JRE required
#FIND_PACKAGE(Java COMPONENTS Runtime REQUIRED)

#set(ANTLR4CPP_LOCAL_REPO ${CMAKE_CURRENT_SOURCE_DIR}/antlr4-cpp-runtime-4.7.1-source)

set(ANTLR4_ROOT ${EP_PREFIX_DIR}/src/antlrcpp)
set(ANTLR4_INCLUDE_DIRS ${ANTLR4_ROOT}/runtime/src)

if (${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
    set(ANTLR4_OUTPUT_DIR ${ANTLR4_ROOT}/dist/$(Configuration))
elseif (${CMAKE_GENERATOR} MATCHES "Xcode.*")
    set(ANTLR4_OUTPUT_DIR ${ANTLR4_ROOT}/dist/$(CONFIGURATION))
else ()
    set(ANTLR4_OUTPUT_DIR ${ANTLR4_ROOT}/dist)
endif ()

if (MSVC)
    set(ANTLR4_STATIC_LIBRARIES
            ${ANTLR4_OUTPUT_DIR}/antlr4-runtime-static.lib)
    set(ANTLR4_SHARED_LIBRARIES
            ${ANTLR4_OUTPUT_DIR}/antlr4-runtime.lib)
    set(ANTLR4_RUNTIME_LIBRARIES
            ${ANTLR4_OUTPUT_DIR}/antlr4-runtime.dll)
else ()
    set(ANTLR4_STATIC_LIBRARIES
            ${ANTLR4_OUTPUT_DIR}/libantlr4-runtime.a)
    if (MINGW)
        set(ANTLR4_SHARED_LIBRARIES
                ${ANTLR4_OUTPUT_DIR}/libantlr4-runtime.dll.a)
        set(ANTLR4_RUNTIME_LIBRARIES
                ${ANTLR4_OUTPUT_DIR}/libantlr4-runtime.dll)
    elseif (CYGWIN)
        set(ANTLR4_SHARED_LIBRARIES
                ${ANTLR4_OUTPUT_DIR}/libantlr4-runtime.dll.a)
        set(ANTLR4_RUNTIME_LIBRARIES
                ${ANTLR4_OUTPUT_DIR}/cygantlr4-runtime-4.9.3.dll)
    elseif (APPLE)
        set(ANTLR4_RUNTIME_LIBRARIES
                ${ANTLR4_OUTPUT_DIR}/libantlr4-runtime.dylib)
    else ()
        set(ANTLR4_RUNTIME_LIBRARIES
                ${ANTLR4_OUTPUT_DIR}/libantlr4-runtime.so)
    endif ()
endif ()


# download runtime environment
ExternalProject_ADD(
        antlr4cpp
        URL https://www.antlr.org/download/antlr4-cpp-runtime-4.9.3-source.zip
        URL_HASH MD5=eafa4fef583e12e963062882773461be
        SOURCE_DIR ${ANTLR4_ROOT}
        SOURCE_SUBDIR runtime/Cpp
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        #BINARY_DIR ${EP_PREFIX_DIR}/src/antlr4cpp-build
        #INSTALL_DIR ${EP_PREFIX_DIR}/src/antlr4cpp-build
        CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX:PATH=${EP_PREFIX_DIR}/src/antlr4cpp-build -DCMAKE_CXX_FLAGS=${RESSOURCES_FLAGS} -DBUILD_SHARED_LIBS=ON -DBUILD_TESTS=OFF -DWITH_DEMO=False -DWITH_LIBCXX=False ${ANTLR4_ROOT}
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
        LOG_MERGED_STDOUTERR ON
        LOG_OUTPUT_ON_FAILURE ON
        #INSTALL_COMMAND ""
)


#ExternalProject_Get_Property(antlr4cpp INSTALL_DIR)
#file(MAKE_DIRECTORY ${INSTALL_DIR}/include/antlr4-runtime)
#list(APPEND ANTLR4CPP_INCLUDE_DIRS ${INSTALL_DIR}/include/antlr4-runtime)

#message(STATUS "Antlr library dir: ${ANTLR4_OUTPUT_DIR}")
#message(STATUS "Antlr include dir: ${ANTLR4_INCLUDE_DIRS}")

if (NOT EXISTS ${ANTLR4_INCLUDE_DIRS})
    file(MAKE_DIRECTORY ${ANTLR4_INCLUDE_DIRS})
endif ()

set(ANTLR4CPP_STATIC_LIBS "${ANTLR4_OUTPUT_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}antlr4-runtime${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(ANTLR4CPP_SHARED_LIBS "${ANTLR4_OUTPUT_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}antlr4-runtime${CMAKE_SHARED_LIBRARY_SUFFIX}")

add_imported_library(ANTLR4 STATIC ${ANTLR4CPP_STATIC_LIBS} ${ANTLR4_INCLUDE_DIRS})
add_imported_library(ANTLR4 SHARED ${ANTLR4CPP_SHARED_LIBS} ${ANTLR4_INCLUDE_DIRS})

add_dependencies(ANTLR4_STATIC antlr4cpp)
add_dependencies(ANTLR4_SHARED antlr4cpp)
add_dependencies(hypro_resources ANTLR4_STATIC ANTLR4_SHARED)

target_link_libraries(${PROJECT_NAME}-shared PUBLIC ANTLR4_SHARED)
target_link_libraries(${PROJECT_NAME}-static PUBLIC ANTLR4_STATIC)

target_include_directories(${PROJECT_NAME}-objects
        PRIVATE ${ANTLR4_INCLUDE_DIRS}
        )
target_include_directories(${PROJECT_NAME}-static
        PRIVATE ${ANTLR4_INCLUDE_DIRS}
        )
target_include_directories(${PROJECT_NAME}-shared
        PRIVATE ${ANTLR4_INCLUDE_DIRS}
        )

list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${ANTLR4_INCLUDE_DIRS})
