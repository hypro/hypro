add_subdirectory(Box)
add_subdirectory(Polytopes)
add_subdirectory(Polytope)
add_subdirectory(Zonotope)
add_subdirectory(OrthogonalPolyhedron)

set(lib_hypro_representation_sources
	PARENT_SCOPE
)

set(lib_hypro_representation_headers
	GeometricObject.h
    ${hypro_box_headers}
    ${hypro_orthogonalpolyhedron_headers}
    ${hypro_polytope_headers}
    ${hypro_polytopes_headers}
	${hypro_zonotope_headers}
	PARENT_SCOPE
)
