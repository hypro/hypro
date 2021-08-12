
if (HYPRO_BENCHMARK)

    add_executable(bouncing_ball bouncing_ball.cpp)
    target_link_libraries(bouncing_ball ${PROJECT_NAME}-shared
            ${GBENCHMARK_LIBRARIES})
    target_include_directories(bouncing_ball PRIVATE ${GBENCHMARK_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test/include/)
    add_dependencies(bouncing_ball hypro_resources)

    add_executable(simplex_watertanks simplex_architecture_watertanks.cpp)
    target_link_libraries(simplex_watertanks ${PROJECT_NAME}-shared
            ${GBENCHMARK_LIBRARIES})
    target_include_directories(simplex_watertanks PRIVATE ${GBENCHMARK_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test/include/)
    add_dependencies(simplex_watertanks hypro_resources)

endif ()