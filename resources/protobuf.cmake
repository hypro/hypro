ExternalProject_Add(
        protobuf
        GIT_REPOSITORY git@github.com:protocolbuffers/protobuf.git
        CMAKE_ARGS -DBUILD_TESTING=OFF -Dprotobuf_BUILD_TESTS=OFF -Dprotobuf_INSTALL=OFF
        -Dprotobuf_MSVC_STATIC_RUNTIME=OFF
        INSTALL_COMMAND ""
        DOWNLOAD_NO_PROGRESS 1
        LOG_CONFIGURE ON
        LOG_BUILD ON
        GIT_TAG v22.2
)

ExternalProject_Get_Property(protobuf source_dir)
ExternalProject_Get_Property(protobuf binary_dir)

if (NOT EXISTS ${source_dir}/src/google)
    file(MAKE_DIRECTORY ${source_dir}/src/google)
endif ()

#message(STATUS "PROTOBUF INCLUDE DIR: ${source_dir}")
#message(STATUS "PROTOBUF LIBRARIES: ${binary_dir}")

add_imported_library(PROTOBUF STATIC "${binary_dir}/libprotobuf.a" "${source_dir}/src/google")

target_link_libraries(${PROJECT_NAME}-objects INTERFACE PROTOBUF_STATIC)
target_link_libraries(${PROJECT_NAME}-shared PRIVATE $<BUILD_INTERFACE:PROTOBUF_STATIC>)
target_link_libraries(${PROJECT_NAME}-static PRIVATE $<BUILD_INTERFACE:PROTOBUF_STATIC>)

add_dependencies(hypro_resources protobuf)
