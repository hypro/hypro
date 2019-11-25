#include "ltiResetHandler.h"

namespace hypro {
template <typename State>
void ltiResetHandler<State>::handle() {
	TRACE( "hydra.worker", "Applying Reset trafo: \n"
								 << mTrafo << "\n Reset translation: \n"
								 << mTranslation << "to" << mIndex );
	State res = mState->partiallyApplyTransformation( hypro::ConstraintSet<Number>( mTrafo, mTranslation ), mIndex );
	mState->setSetDirect( res.getSet( mIndex ), mIndex );
	mState->setSetType( res.getSetType( mIndex ), mIndex );
}
}  // namespace hypro