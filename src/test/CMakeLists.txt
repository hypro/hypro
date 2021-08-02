add_custom_target(allTests
        DEPENDS ${PROJECT_NAME}
)


add_subdirectory(algorithms)
add_subdirectory(case_studies)
add_subdirectory(core)
add_subdirectory(benchmark EXCLUDE_FROM_ALL)
add_subdirectory(datastructure)
add_subdirectory(representations)