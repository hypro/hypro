#include "discreteGuardHandler.h"

namespace hypro {
template <typename State>
void discreteGuardHandler<State>::reinitialize() {
	// only reinitialize on the first time we come here
	if ( mComputed ) {
		return;
	}
	ltiGuardHandler<State>::reinitialize();
}

template <typename State>
void discreteGuardHandler<State>::handle() {
	if ( mComputed ) {
		TRACE( "hydra.worker.discrete", "No flow invariant handler already computed" );
		return;
	}
	TRACE( "hydra.worker.discrete", "Applying handler " << this->handlerName() );
	ltiGuardHandler<State>::handle();
	mComputed = true;
}
}  // namespace hypro