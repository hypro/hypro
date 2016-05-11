#include "ParserWrapper.h"

#include "flowstarParser.h"

namespace hypro {

	#ifdef USE_CLN_NUMBERS
	template<>
	HybridAutomaton<cln::cl_RA> parseFlowstarFile<cln::cl_RA>(const std::string& filename) {
		parser::flowstarParser<cln::cl_RA> parser;
		return parser.parseInput(filename);
	}
	#endif

	template<>
	HybridAutomaton<mpq_class> parseFlowstarFile<mpq_class>(const std::string& filename) {
		parser::flowstarParser<mpq_class> parser;
		return parser.parseInput(filename);
	}
}


