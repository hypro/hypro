#pragma once
#include "../IHandler.h"

namespace hypro {
template <typename State>
class ltiResetHandler : public IResetHandler {
	using Number = typename State::NumberType;

  protected:
	State* mState;	// A state containing the first segment for each subspace
	matrix_t<Number> mTrafo;
	vector_t<Number> mTranslation;

	size_t mIndex;

  public:
	ltiResetHandler() = delete;
	ltiResetHandler( State* state, size_t index, matrix_t<Number> trafo, vector_t<Number> translation ) {
		mState = state;
		mIndex = index;
		mTrafo = trafo;
		mTranslation = translation;
	}

	void handle();
	const char* handlerName() { return "ltiResetHandler"; }
};
}  // namespace hypro

#include "ltiResetHandler.tpp"
