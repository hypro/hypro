# collect sources
file(GLOB_RECURSE tool_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# create target
add_executable(hydra EXCLUDE_FROM_ALL ${tool_sources})
target_include_directories(hydra PRIVATE ${CMAKE_SOURCE_DIR}/include/tool)

# find hypro
find_package(${PROJECT_NAME} REQUIRED)

if (TARGET Boost_program_options_SHARED)
    target_link_libraries(hydra ${PROJECT_NAME}-shared ${PROJECT_NAME}-parser Boost_program_options_SHARED)
else ()
    find_package(Boost COMPONENTS program_options REQUIRED)
    target_link_libraries(hydra ${PROJECT_NAME}-shared ${PROJECT_NAME}-parser Boost::program_options)
endif ()
