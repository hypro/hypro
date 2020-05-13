
# collect sources
file(GLOB_RECURSE tool_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
message(STATUS "Hydra sources: ${tool_sources}")

# create target
add_executable(hydra EXCLUDE_FROM_ALL ${tool_sources} )

target_link_libraries(hydra ${PROJECT_NAME}-shared)