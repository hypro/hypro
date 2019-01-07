#pragma once
#include "../IHandler.h"

namespace hypro
{
    template<typename State>
	class rectangularResetHandler : public IResetHandler {
		using Number = typename State::NumberType;
	protected:
		State*  mState; // A state containing the first segment for each subspace
		std::vector<carl::Interval<Number>> mIntervalResets;

		size_t mIndex;
	public:

		rectangularResetHandler() = delete;
		rectangularResetHandler(State* state, size_t index, const std::vector<carl::Interval<Number>>& intervalResets)
			: mState(state)
			, mIntervalResets(intervalResets)
			, mIndex(index)
		{}

		void handle();
		const char* handlerName() {return "rectangularResetHandler";}

	};
} // hypro

#include "rectangularResetHandler.tpp"
