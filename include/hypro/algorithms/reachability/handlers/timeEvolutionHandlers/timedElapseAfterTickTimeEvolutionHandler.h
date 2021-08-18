#pragma once
#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../IHandler.h"
#include "ltiTimeEvolutionHandler.h"

namespace hypro {
/**
 * used when a timedFirstSegmentHandler was used. It does a tick on first segment and is used if the automaton
 * is not full timed
 */
template <typename State>
class timedElapseAfterTickTimeEvolutionHandler : public ltiTimeEvolutionHandler<State> {
	using Number = typename State::NumberType;

  protected:
	bool mComputed;
	tNumber mTimeBound;

  public:
	timedElapseAfterTickTimeEvolutionHandler() = delete;
	timedElapseAfterTickTimeEvolutionHandler( State* state, size_t index, tNumber timeStep, tNumber timeBound, hypro::matrix_t<Number> trafo, hypro::vector_t<Number> translation )
		: ltiTimeEvolutionHandler<State>( state, index, timeStep, trafo, translation ) {
		mComputed = false;
		mTimeBound = timeBound;
	}

	void handle();
	const char* handlerName() { return "timedElapseContinuousEvolutionHandler"; }
	bool getMarkedForDelete() { return false; };
	void setMarkedForDelete( bool ){ /*no op*/ };
};
}  // namespace hypro

#include "timedElapseAfterTickTimeEvolutionHandler.tpp"
