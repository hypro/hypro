#include "Flowpipe.h"

namespace hypro {
template <typename State>
Flowpipe<State>::Flowpipe( /* args */ ) {
}

template <typename State>
Flowpipe<State>::~Flowpipe() {
}

template <typename State>
std::vector<PlotData<State>> Flowpipe<State>::getPlotData( std::size_t refinementLevel, std::size_t threadId ) const {
	std::vector<PlotData<State>> res;
	for ( const auto& state : mStates ) {
		res.emplace_back( state, refinementLevel, threadId );
	}
	return res;
}

}  // namespace hypro
