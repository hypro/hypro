set(lib_hypro_datastructure_sources
	${hypro_box_sources}
)

set(lib_hypro_datastructure_headers
	${hypro_box_headers}
)

add_library(datastructures OBJECT ${lib_hypro_datastructure_sources})
