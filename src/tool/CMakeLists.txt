
# collect sources
file(GLOB_RECURSE tool_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
#message(STATUS "Hydra sources: ${tool_sources}")

# create target
add_executable(hydra EXCLUDE_FROM_ALL ${tool_sources} )

# find hypro
find_package(${PROJECT_NAME} REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)

# add dependency to ensure hypro is built before
add_dependencies(hydra ${PROJECT_NAME}-shared )

target_link_libraries(hydra ${PROJECT_NAME}-shared Boost::program_options)
target_include_directories(hydra PUBLIC ${${PROJECT_NAME}_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
