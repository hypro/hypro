add_subdirectory(Box)
add_subdirectory(Polytopes)
add_subdirectory(Polytope)


set(lib_hypro_representation_sources
	${CMAKE_CURRENT_SOURCE_DIR}/${hypro_box_sources}
        ${CMAKE_CURRENT_SOURCE_DIR}/${hypro_polytopes_sources}
        ${CMAKE_CURRENT_SOURCE_DIR}/${hypro_polytope_sources}
        #${CMAKE_CURRENT_SOURCE_DIR}/${hypro_orthogonalpolyhedron_sources}
	PARENT_SCOPE
)

set(lib_hypro_representation_headers
	GeometricObject.h
        ${hypro_box_headers}
        ${hypro_polytopes_headers}
        ${hypro_polytope_headers}
        ${hypro_orthogonalpolyhedron_headers}
	PARENT_SCOPE
)