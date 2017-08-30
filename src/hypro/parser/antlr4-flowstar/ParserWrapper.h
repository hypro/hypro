#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HyproHAVisitor.h"
#include <boost/tuple/tuple.hpp>

//#include <unistd.h>		//getcwd()

namespace hypro {

	template<typename Number>
	boost::tuple<HybridAutomaton<Number>, ReachabilitySettings<Number>> parseFlowstarFile(const std::string& filename);

} // namespace
