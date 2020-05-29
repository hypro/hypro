#pragma once
#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../../../../datastructures/HybridAutomaton/flow/rectangular.h"
#include "../../../../datastructures/HybridAutomaton/flow/rectangularOperations.h"
#include "../IHandler.h"

#include <sstream>
#include <string>

namespace hypro {
template <typename State>
class rectangularTimeEvolutionHandler {
	using Number = typename State::NumberType;

  protected:
	State& mState;	// A state containing the first segment for each subspace
	rectangularFlow<Number> mFlow;
	std::size_t mIndex = 0;	 /// relict from multiset-computations after decomposition. Might be handy at some point.
	bool mComputed = false;

  public:
	rectangularTimeEvolutionHandler() = delete;
	rectangularTimeEvolutionHandler( State& state, const rectangularFlow<Number>& flow )
		: mState( state )
		, mFlow( flow )
		, mIndex( index ) {}

	void operator()();
};
}  // namespace hypro

#include "rectangularTimeEvolutionHandler.tpp"
