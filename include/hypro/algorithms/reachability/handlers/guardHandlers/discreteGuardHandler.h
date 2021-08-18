#pragma once
#include "../IHandler.h"
#include "ltiGuardHandler.h"

namespace hypro {
template <typename State>
class discreteGuardHandler : public ltiGuardHandler<State> {
	using Number = typename State::NumberType;

  protected:
	bool mComputed = false;

  public:
	discreteGuardHandler() = delete;
	discreteGuardHandler( std::shared_ptr<State> state, size_t index, hypro::Transition<Number>* transition )
		: ltiGuardHandler<State>( state, index, transition ) {
		this->mSortIndex = 0;
	}

	void handle();
	void reinitialize();
	const char* handlerName() { return "discreteGuardHandler"; }
	double getSortIndex() { return this->mSortIndex; }
	void setSortIndex( double sortIndex ) { this->mSortIndex = sortIndex; }
};
}  // namespace hypro

#include "discreteGuardHandler.tpp"
