#pragma once
#include "../../datastructures/HybridAutomaton/State.h"
#include "../../representations/types.h"

namespace hypro {

/**
 * @brief Class that contains a raw segment for plotting. Note that a segment can be composed of several sub-segments, in case subspace decomposition is used.
 *
 * @tparam Number
 */
template <typename State>
struct PlotData {
	State sets;					  // contains sets - one segment per subspace
	std::size_t threadId;		  // thread-id for color coding
	std::size_t refinementLevel;  // refinement level for color coding

	PlotData( const State& s, std::size_t l )
		: sets( s )
		, threadId()
		, refinementLevel( l ) {}

	PlotData( const State& s, std::size_t l, std::size_t t )
		: sets( s )
		, threadId( t )
		, refinementLevel( l ) {}
};

}  // namespace hypro
