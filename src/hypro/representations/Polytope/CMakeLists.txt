if(USE_PPL)
set(hypro_polytope_sources
	Polytope/util.cpp
	PARENT_SCOPE
)

set(hypro_polytope_headers
	Polytope/Polytope.h
	Polytope/Polytope.tpp
    Polytope/util.h
	PARENT_SCOPE
)
endif()
