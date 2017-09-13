#pragma once
#include "../../flags.h"
#include <string>
#include <boost/tuple/tuple.hpp>

namespace hypro {

	template<typename Number>
	class HybridAutomaton;

	template<typename Number>
	struct ReachabilitySettings;

	template<typename Number>
	boost::tuple<HybridAutomaton<Number>, ReachabilitySettings<Number>> parseFlowstarFile(const std::string& filename);
} // namespace hypro
