#pragma once
#include "../IHandler.h"
#include "ltiGuardHandler.h"

namespace hypro {
template <typename State>
class timedGuardHandler : public ltiGuardHandler<State> {
	using Number = typename State::NumberType;

  public:
	timedGuardHandler() = delete;
	timedGuardHandler( std::shared_ptr<State> state, size_t index, Transition<Number>* transition )
		: ltiGuardHandler<State>( state, index, transition ) {
		// 0.1 because standard before timed of same dimension
		if ( SettingsProvider<State>::getInstance().decomposeAutomaton() ) {
			this->mSortIndex = 0.1 + SettingsProvider<State>::getInstance().getSubspaceDecomposition().at( this->mIndex ).size();
		} else {
			this->mSortIndex = 0;
		}
	}

	void handle();
	const char* handlerName() { return "timedGuardHandler"; }
	// 1+ because standard before timed of same dimension
	double getSortIndex() { return this->mSortIndex; }
	void setSortIndex( double sortIndex ) { this->mSortIndex = sortIndex; }
};
}  // namespace hypro

#include "timedGuardHandler.tpp"