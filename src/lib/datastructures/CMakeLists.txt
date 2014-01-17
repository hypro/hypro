set(lib_hypro_datastructure_sources
	${hypro_box_sources}
	VertexContainer.cpp
)

set(lib_hypro_datastructure_headers
	${hypro_box_headers}
        Point.h
        Vertex.h
		VertexContainer.h
)

#add_library(datastructures OBJECT ${lib_hypro_datastructure_sources})
