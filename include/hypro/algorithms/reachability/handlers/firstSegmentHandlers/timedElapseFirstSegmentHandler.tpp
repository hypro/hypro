#include "timedElapseFirstSegmentHandler.h"

namespace hypro {
template <typename State>
void timedElapseFirstSegmentHandler<State>::handle() {
	assert( !this->mState->getTimestamp().isEmpty() );
	// check if initial Valuation fulfills Invariant
	assert( this->mState->getLocation() != nullptr );

	// set trafo and translation
	int rows = this->mState->getLocation()->getLinearFlow( this->mIndex ).dimension();
	this->mTrafo = matrix_t<Number>::Identity( rows - 1, rows - 1 );
	this->mTranslation = vector_t<Number>::Ones( rows - 1 ) * carl::convert<tNumber, Number>( this->mTimeStep );
}
}  // namespace hypro
