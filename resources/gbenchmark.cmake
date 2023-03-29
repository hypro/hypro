# Add google-benchmark (local build)
ExternalProject_Add(
        google-benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_SHALLOW 1
        GIT_TAG "v1.6.0"
        DOWNLOAD_NO_PROGRESS 1
        CONFIGURE_COMMAND ${CMAKE_COMMAND} ../google-benchmark -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_TESTING=OFF
        -DBENCHMARK_ENABLE_INSTALL=OFF -DBENCHMARK_ENABLE_GTEST_TESTS=OFF
        BUILD_COMMAND cmake --build . --config Release --target benchmark
        COMMAND cmake --build . --config Release --target benchmark_main
        LOG_CONFIGURE ON
        LOG_BUILD ON
        INSTALL_COMMAND "")

# Specify include dir
ExternalProject_Get_Property(google-benchmark source_dir)
ExternalProject_Get_Property(google-benchmark binary_dir)

add_imported_library(HYPRO_GBENCHMARK STATIC
        "${binary_dir}/src/${CMAKE_FIND_LIBRARY_PREFIXES}benchmark${CMAKE_STATIC_LIBRARY_SUFFIX}"
        "${source_dir}/include")
add_imported_library(HYPRO_GBENCHMARKMAIN STATIC
        "${binary_dir}/src/${CMAKE_FIND_LIBRARY_PREFIXES}benchmark_main${CMAKE_STATIC_LIBRARY_SUFFIX}"
        "${source_dir}/include")

# required for testing.
set(GBENCHMARK_INCLUDE_DIR "${source_dir}/include" PARENT_SCOPE)
set(GBENCHMARK_LIBRARIES "${binary_dir}/src/${CMAKE_FIND_LIBRARY_PREFIXES}benchmark${CMAKE_STATIC_LIBRARY_SUFFIX}"
        "${binary_dir}/src/${CMAKE_FIND_LIBRARY_PREFIXES}benchmark_main${CMAKE_STATIC_LIBRARY_SUFFIX}"
        PARENT_SCOPE)

add_dependencies(hypro_resources google-benchmark)
