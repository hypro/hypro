
if (HYPRO_BENCHMARK)

    add_executable(bouncing_ball bouncing_ball.cpp)
    target_link_libraries(bouncing_ball ${PROJECT_NAME}-shared
            ${GBENCHMARK_LIBRARIES})
    target_include_directories(bouncing_ball PRIVATE ${GBENCHMARK_INCLUDE_DIR})
    add_dependencies(bouncing_ball hypro_resources)

endif ()