add_subdirectory(Box)


set(lib_hypro_representations_sources
	${hypro_box_sources}
)

set(lib_hypro_representations_headers
        ${hypro_box_headers}
	GeometricObject.h
)

#add_library(representations OBJECT ${lib_hypro_representations_sources})
