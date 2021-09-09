#include "timedInvariantHandler.h"

namespace hypro {
template <typename State>
void timedInvariantHandler<State>::handle() {
	// check if initial Valuation fulfills Invariant
	DEBUG( "hydra.worker", "Check invariant: " << this->mState->getLocation()->getInvariant() );
	// DEBUG( "hydra.worker", "Set before intersection with invariant:\n: " << this->mState->getSet( this->mIndex ) );

	Condition<Number> invariant = this->mState->getLocation()->getInvariant();

	matrix_t<Number> constraints = this->mState->getLocation()->getInvariant().getMatrix( this->mIndex );
	vector_t<Number> constants = this->mState->getLocation()->getInvariant().getVector( this->mIndex );

	std::pair<CONTAINMENT, DifferenceBounds<Number>> res = std::get<DifferenceBounds<Number>>( this->mState->getSet( this->mIndex ) ).intersectConstraints( this->mState->getLocation()->getInvariant().getMatrix( this->mIndex ), this->mState->getLocation()->getInvariant().getVector( this->mIndex ), CONTAINMENT::FULL );
	DEBUG( "hydra.worker", "Set after intersection with invariant:\n"
								 << res.second );
	if ( res.first != CONTAINMENT::NO ) {
#ifdef HYDRA_USE_LOGGING
		// DBG
		DEBUG( "hydra.worker", "Invariant satisfying segment: " << res.second );
		Box<Number> tmp = Converter<Number>::toBox( res.second );
		DEBUG( "hydra.worker", "Invariant satisfying segment (box): " << tmp );
#endif

		this->mContainment = res.first;
		this->mState->setSetDirect( res.second, this->mIndex );
		return;
	}  // if set does not satisfy the invariant, return false
	else {
		this->mContainment = CONTAINMENT::NO;
		return;
	}
}
}  // namespace hypro
