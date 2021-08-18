#include "timedFirstSegmentHandler.h"

namespace hypro {
template <typename State>
void timedFirstSegmentHandler<State>::handle() {
	assert( !this->mState->getTimestamp().isEmpty() );
	// check if initial Valuation fulfills Invariant
	assert( this->mState->getLocation() != nullptr );

	DifferenceBounds<Number> dbmBeforeElapse = std::get<DifferenceBounds<Number>>( this->mState->getSet( this->mIndex ) );
	// elapse the zone, then cut it by its old value + timestep in each clock direction
	if ( dbmBeforeElapse.dimension() > 0 ) {
		// elapse the dbm
		this->mState->setSet( std::get<DifferenceBounds<Number>>( this->mState->getSet( this->mIndex ) ).elapse(), this->mIndex );

		// cut it
		DifferenceBounds<Number> dbm = std::get<DifferenceBounds<Number>>( this->mState->getSet( this->mIndex ) );
		size_t numclocks = dbm.dimension();
		for ( size_t i = 1; i <= numclocks; i++ ) {
			// shift all clocks by timestep
			dbm = dbm.intersectConstraint( i, 0, typename DifferenceBounds<Number>::DBMEntry( dbmBeforeElapse.getDBM()( i, 0 ).first + carl::convert<tNumber, Number>( this->mTimeStep ), DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ) );
		}
#ifdef HYDRA_USE_LOGGING
		TRACE( "hydra.worker", "First Flowpipe Segment: " << dbm );
#endif

		// set dbm
		this->mState->setSet( dbm, this->mIndex );
		// set trafo and translation
		int rows = this->mState->getLocation()->getLinearFlow( this->mIndex ).dimension();
		this->mTrafo = matrix_t<Number>::Identity( rows - 1, rows - 1 );
		this->mTranslation = vector_t<Number>::Ones( rows - 1 ) * carl::convert<tNumber, Number>( this->mTimeStep );
		this->mFlow = affineFlow<Number>{ this->mTrafo, this->mTranslation };
	}
}
}  // namespace hypro
