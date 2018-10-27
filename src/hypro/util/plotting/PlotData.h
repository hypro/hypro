#pragma once
#include "../../datastructures/HybridAutomaton/State.h"
#include "../../representations/types.h"

namespace hypro {

/**
 * @brief Class that contains a raw segment for plotting. Note that a segment can be composed of several sub-segments, in case subspace decomposition is used.
 * 
 * @tparam Number 
 */
template<typename Number>
struct PlotData {
	std::vector<typename State_t<Number>::repVariant> segments;		// contains raw segments - one segment per subspace
	std::size_t threadId;											// thread-id for color coding
	std::size_t refinementLevel;									// refinement level for color coding

	PlotData(const typename State_t<Number>::repVariant& s, std::size_t l) :
		threadId(),
		refinementLevel(l)
	{
		segments.push_back(s);
	}

	PlotData(const std::vector<typename State_t<Number>::repVariant>& s, std::size_t l) :
		segments(s),
		threadId(),
		refinementLevel(l)
	{}

};

} // hypro

