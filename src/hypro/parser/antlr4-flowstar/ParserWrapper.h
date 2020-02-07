#pragma once
#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../datastructures/reachability/Settings.h"
#include <utility>

namespace hypro {

	template<typename Number>
	std::pair<HybridAutomaton<Number>, ReachabilitySettings> parseFlowstarFile(const std::string& filename);

} // namespace
