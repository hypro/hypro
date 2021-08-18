
if (HYPRO_BENCHMARK)

    add_executable(cs_bouncing_ball cs_bouncing_ball.cpp)
    target_link_libraries(cs_bouncing_ball ${PROJECT_NAME}-shared
            ${GBENCHMARK_LIBRARIES})
    target_include_directories(cs_bouncing_ball PRIVATE ${GBENCHMARK_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test/include/)
    add_dependencies(cs_bouncing_ball ${PROJECT_NAME}_resources)

    add_executable(cs_simplex_watertanks cs_simplex_architecture_watertanks.cpp)
    target_link_libraries(cs_simplex_watertanks ${PROJECT_NAME}-shared
            ${GBENCHMARK_LIBRARIES})
    target_include_directories(cs_simplex_watertanks PRIVATE ${GBENCHMARK_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test/include/)
    add_dependencies(cs_simplex_watertanks ${PROJECT_NAME}_resources)

endif ()