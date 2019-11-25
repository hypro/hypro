#include "timedResetHandler.h"

namespace hypro {
template <typename State>
void timedResetHandler<State>::handle() {
	TRACE( "hydra.worker", "Applying Reset trafo: \n"
								 << this->mTrafo << "\n Reset translation: \n"
								 << this->mTranslation << "to" << this->mIndex );
	hypro::DifferenceBounds<Number> dbm = std::get<hypro::DifferenceBounds<Number>>( this->mState->getSet( this->mIndex ) );
	for ( int i = 0; i < this->mTrafo.rows(); i++ ) {
		// if the diagonal entry of a clock is 0.0, reset that clock
		if ( this->mTrafo( i, i ) + 0.0 == 0.0 ) {
			dbm = dbm.reset( i + 1, 0.0 );
		}
	}
	this->mState->setSetDirect( dbm, this->mIndex );
}
}  // namespace hypro