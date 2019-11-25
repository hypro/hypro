#pragma once
#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../IHandler.h"

namespace hypro {
template <typename State>
class ltiTimeEvolutionHandler : public ITimeEvolutionHandler {
	using Number = typename State::NumberType;

  protected:
	State* mState;  // A state containing the first segment for each subspace
	matrix_t<Number> mTrafo;
	vector_t<Number> mTranslation;

	size_t mIndex;
	tNumber mTimeStep;

  public:
	ltiTimeEvolutionHandler() = delete;
	ltiTimeEvolutionHandler( State* state, size_t index, tNumber timeStep, matrix_t<Number> trafo, vector_t<Number> translation ) {
		mState = state;
		mIndex = index;
		mTimeStep = timeStep;
		mTrafo = trafo;
		mTranslation = translation;
	}

	void handle();
	const char* handlerName() { return "ltiTimeEvolutionHandler"; }
	bool getMarkedForDelete() { return false; };
	void setMarkedForDelete( bool ){/*no op*/};
};
}  // namespace hypro

#include "ltiTimeEvolutionHandler.tpp"
