#include "ltiTimeEvolutionHandler.h"

namespace hypro {
template <typename State>
void ltiTimeEvolutionHandler<State>::handle() {
	TRACE( "hydra.worker", "Applying timestep to " << mState );
	TRACE( "hydra.worker", "Flow trafo: \n"
								 << mTrafo << "\n Flow translation: \n"
								 << mTranslation );
	State res = mState->partiallyApplyTimeStep( hypro::ConstraintSet<Number>( mTrafo, mTranslation ), mTimeStep, mIndex );
	mState->setSetDirect( res.getSet( mIndex ), mIndex );
	mState->setSetType( res.getSetType( mIndex ), mIndex );
}
}  // namespace hypro
