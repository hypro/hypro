#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HyproHAVisitor.h"
#include "ErrorListener.h"
#include <boost/tuple/tuple.hpp>
#include "../../types.h"


//#include <unistd.h>		//getcwd()

namespace hypro {

	template<typename Number>
	boost::tuple<HybridAutomaton<Number,State_t<Number,Number>>, ReachabilitySettings<Number>> parseFlowstarFile(const std::string& filename);

	template<typename Number>
	boost::tuple<HybridAutomatonComp<Number,State_t<Number,Number>>, ReachabilitySettings<Number>> parseFlowstarCompFile(const std::string& filename);
} // namespace
