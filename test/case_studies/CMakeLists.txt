
if (HYPRO_BENCHMARK)

    add_executable(cs_bouncing_ball cs_bouncing_ball.cpp)
    target_link_libraries(cs_bouncing_ball ${PROJECT_NAME}-shared
            ${GBENCHMARK_LIBRARIES})
    target_include_directories(cs_bouncing_ball PRIVATE ${GBENCHMARK_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test/include/)
    add_dependencies(cs_bouncing_ball ${PROJECT_NAME}_resources)

    find_package(Boost COMPONENTS program_options REQUIRED)
    add_executable(cs_hypro_decomposition_benchmark cs_hypro_decomposition_benchmark.cpp
            ${CMAKE_SOURCE_DIR}/src/hydra/cli/cli.cpp ${CMAKE_SOURCE_DIR}/src/hydra/cli/settingsProcessing.cpp
            ${CMAKE_SOURCE_DIR}/src/hydra/cli/DynamicStrategyBuilder.cc
            ${CMAKE_SOURCE_DIR}/src/hydra/reachability/analysis.cpp
            ${CMAKE_SOURCE_DIR}/src/hydra/preprocessing/preprocessing.cpp)
    target_link_libraries(cs_hypro_decomposition_benchmark ${PROJECT_NAME}-shared
            ${GBENCHMARK_LIBRARIES} Boost::program_options)
    target_include_directories(cs_hypro_decomposition_benchmark PRIVATE ${GBENCHMARK_INCLUDE_DIR}
            ${CMAKE_SOURCE_DIR}/test/include/ ${CMAKE_SOURCE_DIR}/include/hydra/)
    add_dependencies(cs_hypro_decomposition_benchmark ${PROJECT_NAME}_resources)

    add_executable(cs_simplex_watertanks_benchmark cs_simplex_architecture_watertanks_benchmark.cpp)
    target_link_libraries(cs_simplex_watertanks_benchmark ${PROJECT_NAME}-shared
            ${GBENCHMARK_LIBRARIES})
    target_include_directories(cs_simplex_watertanks_benchmark PRIVATE ${GBENCHMARK_INCLUDE_DIR}
            ${CMAKE_SOURCE_DIR}/test/include/)
    add_dependencies(cs_simplex_watertanks_benchmark ${PROJECT_NAME}_resources)

    add_executable(cs_simplex_watertanks_interactive cs_simplex_architecture_watertanks_interactive.cpp)
    target_link_libraries(cs_simplex_watertanks_interactive ${PROJECT_NAME}-shared)
    target_include_directories(cs_simplex_watertanks_interactive PRIVATE ${CMAKE_SOURCE_DIR}/test/include/)
    add_dependencies(cs_simplex_watertanks_interactive ${PROJECT_NAME}_resources)

    add_executable(cs_rectangular_sha_car_benchmark cs_rectangular_sha_car_benchmark.cpp)
    target_link_libraries(cs_rectangular_sha_car_benchmark ${PROJECT_NAME}-shared)
    target_include_directories(cs_rectangular_sha_car_benchmark PRIVATE ${CMAKE_SOURCE_DIR}/test/include/)
    add_dependencies(cs_rectangular_sha_car_benchmark ${PROJECT_NAME}_resources)

    add_executable(cs_lawn_mower cs_lawn_mower.cpp)
    target_link_libraries(cs_lawn_mower ${PROJECT_NAME}-shared
            ${GBENCHMARK_LIBRARIES})
    target_include_directories(cs_lawn_mower PRIVATE ${GBENCHMARK_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test/include/)
    add_dependencies(cs_lawn_mower ${PROJECT_NAME}_resources)

endif ()