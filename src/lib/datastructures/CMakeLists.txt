add_subdirectory(hybridAutomata)

set(lib_hypro_datastructure_sources
        PARENT_SCOPE
)

set(lib_hypro_datastructure_headers
        Facet.h
        Point.h
        Vertex.h
        VertexContainer.h
        ${hybrid_automata_headers}
        PARENT_SCOPE
)