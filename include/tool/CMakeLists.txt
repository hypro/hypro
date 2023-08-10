# collect sources
file(GLOB_RECURSE tool_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# create target
add_executable(hydra EXCLUDE_FROM_ALL ${tool_sources})

# find hypro
find_package(${PROJECT_NAME} REQUIRED)

if (TARGET Boost_program_options_SHARED)
    message(STATUS "program_options already exists")
    target_link_libraries(hydra ${PROJECT_NAME}-shared ${PROJECT_NAME}-parser Boost_program_options_SHARED)
else ()
    message(STATUS "program_options does not exist")
    find_package(Boost COMPONENTS program_options REQUIRED)
    target_link_libraries(hydra ${PROJECT_NAME}-shared ${PROJECT_NAME}-parser Boost::program_options)
endif ()
