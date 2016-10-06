add_subdirectory(VPolytope)
add_subdirectory(HPolytope)


set(lib_hypro_polytopes_sources
	PARENT_SCOPE
)

set(lib_hypro_polytopes_headers
        Polytopes/util.h
        Polytopes/${hypro_vpolytope_headers}
        Polytopes/${hypro_hpolytope_headers}
	PARENT_SCOPE
)