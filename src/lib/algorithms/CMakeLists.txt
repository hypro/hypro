add_subdirectory(reachability)

set(lib_hypro_algorithms_sources
        PARENT_SCOPE
)

set(lib_hypro_algorithms_headers
        ${reachability_headers}
        PARENT_SCOPE
)