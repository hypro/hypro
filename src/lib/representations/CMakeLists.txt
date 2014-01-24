add_subdirectory(Box)


set(lib_hypro_representation_sources
	${hypro_box_sources}
	PARENT_SCOPE
)

set(lib_hypro_representation_headers
	${hypro_box_headers}
	GeometricObject.h
	PARENT_SCOPE
)

#add_library(representations OBJECT ${lib_hypro_representation_sources})
