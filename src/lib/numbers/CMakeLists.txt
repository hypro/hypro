set(lib_hypro_number_sources
	double_wrapper_t.cpp
	mpfr_wrapper_t.cpp
)

set(lib_hypro_number_headers
	double_wrapper_t.h
	HYPRO_FLOAT_T.h
	HYPRO_INT_T.h
	mpfr_wrapper_t.h
	number_t.h
PARENT_SCOPE)

add_library(numbers OBJECT ${lib_hypro_number_sources})