add_subdirectory(Box)


set(lib_hypro_representations_sources
	${hypro_box_sources}
)

set(lib_hypro_representations_headers
	double_wrapper_t.h
	HYPRO_FLOAT_T.h
	HYPRO_INT_T.h
	mpfr_wrapper_t.h
	number_t.h
)

add_library(representations OBJECT ${lib_hypro_representations_sources})
