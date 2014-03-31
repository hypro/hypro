add_subdirectory(Box)
add_subdirectory(VPolytope)
add_subdirectory(Polytope)


set(lib_hypro_representation_sources
	#${CMAKE_CURRENT_SOURCE_DIR}/${hypro_box_sources}
        #${CMAKE_CURRENT_SOURCE_DIR}/${hypro_vpolytope_sources}
        ${CMAKE_CURRENT_SOURCE_DIR}/${hypro_polytope_sources}
        #${CMAKE_CURRENT_SOURCE_DIR}/${hypro_orthogonalpolyhedron_sources}
	PARENT_SCOPE
)

set(lib_hypro_representation_headers
	${hypro_box_headers}
        ${hypro_vpolytope_headers}
        ${hypro_polytope_headers}
        ${hypro_orthogonalpolyhedron_headers}
	GeometricObject.h
	PARENT_SCOPE
)