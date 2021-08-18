#include "timedGuardHandler.h"

namespace hypro {
template <typename State>
void timedGuardHandler<State>::handle() {
	TRACE( "hydra.worker.discrete", "Check guard for transition " << this->mTransition->getSource()->getName() << "(" << this->mTransition->getSource()->hash() << ")"
																  << " -> " << this->mTransition->getTarget()->getName() << "(" << this->mTransition->getTarget()->hash() << ")" );
	TRACE( "hydra.worker.discrete", "Check guard constraint :" << this->mTransition->getGuard().getMatrix( this->mIndex ) << "\n Transition: " << this->mTransition->getGuard().getVector( this->mIndex ) );

	std::pair<CONTAINMENT, hypro::DifferenceBounds<Number>> res = std::get<hypro::DifferenceBounds<Number>>( this->mGuardSatisfyingState->getSet( this->mIndex ) ).intersectConstraints( this->mTransition->getGuard().getMatrix( this->mIndex ), this->mTransition->getGuard().getVector( this->mIndex ), hypro::CONTAINMENT::FULL );

	if ( res.first == CONTAINMENT::NO ) {
		TRACE( "hydra.worker.discrete", "Guard violating dbm: " << res.second );
		this->mSatisfies = false;
		return;
	}

	TRACE( "hydra.worker.discrete", "Guard satisfying DBM: \n"
										  << res.second );
	this->mGuardSatisfyingState->setSetDirect( res.second, this->mIndex );
	this->mSatisfies = true;
}
}  // namespace hypro
