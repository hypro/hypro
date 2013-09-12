add_subdirectory(Box)


set(lib_hypro_representation_sources
	${hypro_box_sources}
)

set(lib_hypro_representation_headers
	double_wrapper_t.h
	HYPRO_FLOAT_T.h
	HYPRO_INT_T.h
	mpfr_wrapper_t.h
	number_t.h
)
