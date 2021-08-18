
ExternalProject_Add(
        mimalloc
        GIT_REPOSITORY https://github.com/microsoft/mimalloc.git
        GIT_SHALLOW ON
        GIT_TAG "v1.6.7"
        DOWNLOAD_NO_PROGRESS 1
        BUILD_COMMAND cmake --build . --config ${CMAKE_BUILD_TYPE}
        INSTALL_COMMAND ""
        LOG_CONFIGURE ON
        LOG_BUILD ON
)

# Specify include dir
ExternalProject_Get_Property(mimalloc source_dir)
ExternalProject_Get_Property(mimalloc binary_dir)

add_imported_library(mimalloc SHARED "${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}mimalloc${CMAKE_SHARED_LIBRARY_SUFFIX}" "${source_dir}/include")
add_imported_library(mimalloc STATIC "${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}mimalloc${CMAKE_STATIC_LIBRARY_SUFFIX}" "${source_dir}/include")

# required for testing.
set(MIMALLOC_INCLUDE_DIR "${source_dir}/include" PARENT_SCOPE)
set(MIMALLOC_LIBRARIES "${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}mimalloc${CMAKE_SHARED_LIBRARY_SUFFIX}" PARENT_SCOPE)

add_dependencies(hypro_resources mimalloc)