/*
#include "ParserWrapper.h"

#include "flowstarParser.h"

namespace hypro {

	#ifdef USE_CLN_NUMBERS
	template<>
	boost::tuple<HybridAutomaton<cln::cl_RA>, ReachabilitySettings> parseFlowstarFile<cln::cl_RA>(const std::string& filename) {
		parser::flowstarParser<cln::cl_RA> parser;
		return boost::tuple<HybridAutomaton<cln::cl_RA>, ReachabilitySettings>(parser.parseInput(filename), parser.mSettings);
	}
	#endif

	template<>
	boost::tuple<HybridAutomaton<mpq_class>, ReachabilitySettings> parseFlowstarFile<mpq_class>(const std::string& filename) {
		parser::flowstarParser<mpq_class> parser;
		return boost::tuple<HybridAutomaton<mpq_class>, ReachabilitySettings>(parser.parseInput(filename), parser.mSettings);
	}

	template<>
	boost::tuple<HybridAutomaton<double>, ReachabilitySettings> parseFlowstarFile<double>(const std::string& filename) {
		parser::flowstarParser<double> parser;
		return boost::tuple<HybridAutomaton<double>, ReachabilitySettings>(parser.parseInput(filename), parser.mSettings);
	}
} // namespace hypro
*/

