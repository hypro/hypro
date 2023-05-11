# Create configure command dependend on compiler
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(cmake_command -Dgtest_force_shared_crt=ON -DCXX=${CMAKE_CXX_COMPILER} -DCMAKE_CXX_FLAGS=-stdlib=libc++ -DCMAKE_CXX_FLAGS=-std=c++14 -DCMAKE_CXX_FLAGS=-DGTEST_USE_OWN_TR1_TUPLE=1)
else ()
    set(cmake_command -Dgtest_force_shared_crt=ON)
endif ()
# Add gtest (local build)
ExternalProject_Add(
        googletest
        GIT_REPOSITORY http://github.com/google/googletest.git
        GIT_TAG "v1.13.0"
        GIT_SHALLOW 1
        DOWNLOAD_NO_PROGRESS 1
        #CONFIGURE_COMMAND ${CMAKE_COMMAND} ../googletest-stamp -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
        BUILD_COMMAND cmake --build . --config ${CMAKE_BUILD_TYPE} --target gtest
        COMMAND cmake --build . --config ${CMAKE_BUILD_TYPE} --target gtest_main
        LOG_CONFIGURE ON
        LOG_BUILD ON
        # Force separate output paths for debug and release builds to allow easy
        # identification of correct lib in subsequent TARGET_LINK_LIBRARIES
        #CMAKE_ARGS ${cmake_command}
        INSTALL_COMMAND "")

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
ExternalProject_Get_Property(googletest binary_dir)

add_imported_library(HYPRO_GTESTCORE STATIC "${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}" "${source_dir}/googletest/include")
add_imported_library(HYPRO_GTESTMAIN STATIC "${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}" "${source_dir}/googletest/include")

# required for testing.
set(GTEST_INCLUDE_DIR "${source_dir}/googletest/include" PARENT_SCOPE)
set(GTEST_LIBRARIES "${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}" "${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}" pthread dl PARENT_SCOPE)

add_dependencies(${PROJECT_NAME}-resources googletest)
