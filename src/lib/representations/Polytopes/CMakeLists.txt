add_subdirectory(VPolytope)
add_subdirectory(HPolytope)


set(lib_hypro_representation_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/${hypro_vpolytope_sources}
        ${CMAKE_CURRENT_SOURCE_DIR}/${hypro_hpolytope_sources}
	PARENT_SCOPE
)

set(lib_hypro_representation_headers
        util.h
        ${hypro_vpolytope_headers}
        ${hypro_hpolytope_headers}
	PARENT_SCOPE
)