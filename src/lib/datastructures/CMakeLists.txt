add_subdirectory(hybridAutomata)

set(lib_hypro_datastructure_sources
    PARENT_SCOPE
)

set(lib_hypro_datastructure_headers
        datastructures/Point.h
        datastructures/Facet.h
        datastructures/Ridge.h
        datastructures/Vertex.h
        datastructures/VertexContainer.h
        datastructures/${hybrid_automata_headers}
        PARENT_SCOPE
)