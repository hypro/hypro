#include "flowstarParser.tpp"


namespace hypro{
namespace parser{
	// explicit instantiation

	template flowstarParser<mpq_class>::flowstarParser();

	#ifdef USE_CLN_NUMBERS
	template flowstarParser<cln::cl_RA>::flowstarParser();
	#endif
}
}
