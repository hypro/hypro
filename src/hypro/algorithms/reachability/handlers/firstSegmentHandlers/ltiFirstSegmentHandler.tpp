#include "ltiFirstSegmentHandler.h"

namespace hypro {
template <typename State>
void ltiFirstSegmentHandler<State>::handle() {
	assert( !mState->getTimestamp().isEmpty() );
	// check if initial Valuation fulfills Invariant
	assert( mState->getLocation() != nullptr );

	std::size_t dim = mState->getLocation()->getLinearFlow( mIndex ).dimension();

	// if the location has no flow, stop computation and exit.
	if ( mState->getLocation()->getLinearFlow( mIndex ).isDiscrete() ) {
		// TRACE("Avoid further computation as the flow is zero." << std::endl);
		mTrafo = matrix_t<Number>::Identity( dim - 1, dim - 1 );
		mTranslation = vector_t<Number>::Zero( dim - 1 );
		mFlow = affineFlow<Number>{mTrafo, mTranslation};
		return;
	}

	// approximate R_[0,delta](X0)
	// R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is unit matrix.
	matrix_t<Number> trafoMatrix = computeTrafoMatrix( mState->getLocation() );

	TRACE( "hypro.worker", "e^(deltaMatrix): " << std::endl );
	TRACE( "hypro.worker", trafoMatrix << std::endl );
	TRACE( "hypro.worker", "------" << std::endl );

	// e^(At)*X0 = polytope at t=delta
	unsigned rows = trafoMatrix.rows();
	unsigned cols = trafoMatrix.cols();
	vector_t<Number> translation = trafoMatrix.col( cols - 1 );
	matrix_t<Number> trafoMatrixResized = matrix_t<Number>( rows - 1, cols - 1 );
	trafoMatrixResized = trafoMatrix.block( 0, 0, rows - 1, cols - 1 );
	translation.conservativeResize( rows - 1 );

	// update flow type
	mFlow = affineFlow<Number>{trafoMatrixResized, translation};
	//mState->rGetLocation()->setFlow(mIndex,affineFlow<Number>(mTrafo,mTranslation));

	State deltaValuation = mState->partiallyApplyTimeStep( ConstraintSet<Number>( trafoMatrixResized, translation ), mTimeStep, mIndex );

#ifdef HYDRA_USE_LOGGING
	TRACE( "hypro.worker", "Polytope at t=delta: " << deltaValuation );
#endif

	State firstSegment{mState->getLocation()};
	unsigned dimension = mState->getDimension( mIndex );
	Box<Number> externalInput( std::make_pair( Point<Number>( vector_t<Number>::Zero( dimension ) ),
											   Point<Number>( vector_t<Number>::Zero( dimension ) ) ) );

	std::vector<Box<Number>> errorBoxVector =
		  errorBoxes( carl::convert<tNumber, Number>( mTimeStep ), mState->getLocation()->getLinearFlow( mIndex ), *mState, trafoMatrix, externalInput );

	firstSegment = deltaValuation.unite( *( mState ) );

	TRACE( "hypro.worker", "Union of initial set and set after first step: " << firstSegment );

	TRACE( "hypro.worker", "Errorbox X_0: " << errorBoxVector[0] << " with dimension " << errorBoxVector[0].dimension() << " and d: " << dimension );
	TRACE( "hypro.worker", "Errorbox for bloating: " << errorBoxVector[2] << " with dimension " << errorBoxVector[2].dimension() << " and d: " << dimension );

	firstSegment = bloatBox( firstSegment, Number( Number( 1 ) / Number( 4 ) ) * errorBoxVector[2], mIndex );

	TRACE( "hypro.worker", "Epsilon errorbox: " << errorBoxVector[2] );

	TRACE( "hypro.worker", "first Flowpipe Segment (after minkowski Sum): " << firstSegment );

	firstSegment.partiallyRemoveRedundancy( mIndex );
	mState->setSet( firstSegment.getSet( mIndex ), mIndex );
}

template <typename State>
State ltiFirstSegmentHandler<State>::operator()( State initialStateSet, tNumber timeStep ) {
	assert( !initialStateSet.getTimestamp().isEmpty() );
	// check if initial Valuation fulfills Invariant
	assert( initialStateSet.getLocation() != nullptr );

	mTimeStep = timeStep;

	std::size_t dim = initialStateSet.getLocation()->getLinearFlow().dimension();

	// if the location has no flow, stop computation and exit.
	if ( initialStateSet.getLocation()->getLinearFlow( 0 ).isDiscrete() ) {
		// TRACE("Avoid further computation as the flow is zero." << std::endl);
		mTrafo = matrix_t<Number>::Identity( dim, dim );
		mTranslation = vector_t<Number>::Zero( dim );
		return initialStateSet;
	}

	// approximate R_[0,delta](X0)
	// R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is unit matrix.
	matrix_t<Number> trafoMatrix = computeTrafoMatrix( initialStateSet.getLocation() );

	TRACE( "hypro.worker", "e^(deltaMatrix): " << std::endl );
	TRACE( "hypro.worker", trafoMatrix << std::endl );
	TRACE( "hypro.worker", "------" << std::endl );

	// e^(At)*X0 = polytope at t=delta
	Eigen::Index rows = trafoMatrix.rows();
	Eigen::Index cols = trafoMatrix.cols();
	vector_t<Number> translation = trafoMatrix.col( cols - 1 );
	matrix_t<Number> trafoMatrixResized = matrix_t<Number>( rows - 1, cols - 1 );
	trafoMatrixResized = trafoMatrix.block( 0, 0, rows - 1, cols - 1 );
	translation.conservativeResize( rows - 1 );

	// update flow type
	mTrafo = trafoMatrixResized;
	mTranslation = translation;

	State deltaValuation = initialStateSet.partiallyApplyTimeStep( ConstraintSet<Number>( trafoMatrixResized, translation ), mTimeStep, 0 );

#ifdef HYDRA_USE_LOGGING
	TRACE( "hypro.worker", "Polytope at t=delta: " << deltaValuation );
#endif

	State firstSegment{initialStateSet.getLocation()};
	Box<Number> externalInput( std::make_pair( Point<Number>( vector_t<Number>::Zero( dim ) ),
											   Point<Number>( vector_t<Number>::Zero( dim ) ) ) );

	std::vector<Box<Number>> errorBoxVector =
		  errorBoxes( carl::convert<tNumber, Number>( mTimeStep ), initialStateSet.getLocation()->getLinearFlow( 0 ), initialStateSet, trafoMatrix, externalInput );

	firstSegment = deltaValuation.unite( initialStateSet );

	if(!errorBoxVector.empty()){
		TRACE( "hypro.worker", "Union of initial set and set after first step: " << firstSegment );
		TRACE( "hypro.worker", "Errorbox X_0: " << errorBoxVector[0] << " with dimension " << errorBoxVector[0].dimension() << " and d: " << initialStateSet.getDimension( 0 ) );
		TRACE( "hypro.worker", "Errorbox for bloating: " << errorBoxVector[2] << " with dimension " << errorBoxVector[2].dimension() << " and d: " << initialStateSet.getDimension( 0 ) );
	}
	
	firstSegment = bloatBox( firstSegment, Number( Number( 1 ) / Number( 4 ) ) * errorBoxVector[2], 0 );

	TRACE( "hypro.worker", "Epsilon errorbox: " << errorBoxVector[2] );

	TRACE( "hypro.worker", "first Flowpipe Segment (after minkowski Sum): " << firstSegment );

	firstSegment.partiallyRemoveRedundancy( 0 );
	initialStateSet.setSet( firstSegment.getSet( 0 ), 0 );

	return initialStateSet;
}

template <typename State>
matrix_t<typename State::NumberType> ltiFirstSegmentHandler<State>::computeTrafoMatrix( const Location<Number>* _loc ) const {
	matrix_t<Number> deltaMatrix( _loc->getLinearFlow().dimension(), _loc->getLinearFlow().dimension() );
	deltaMatrix = _loc->getLinearFlow( 0 ).getFlowMatrix() * carl::convert<tNumber, Number>( mTimeStep );
	TRACE( "hypro.worker", "Flowmatrix:\n"
								 << _loc->getLinearFlow( 0 ) << "\nmultiplied with time step: " << mTimeStep );
	TRACE( "hypro.worker", "delta matrix_t<Number>: " << std::endl );
	TRACE( "hypro.worker", deltaMatrix << std::endl );
	TRACE( "hypro.worker", "------" << std::endl );

	// e^(At) = resultMatrix
	matrix_t<Number> resultMatrix( deltaMatrix.rows(), deltaMatrix.cols() );

	//---
	// Workaround for:
	// resultMatrix = deltaMatrix.exp();
	//-> convert FLOAT_T to double, compute .exp(), then convert back to FLOAT_T
	matrix_t<double> doubleMatrix( deltaMatrix.rows(), deltaMatrix.cols() );
	matrix_t<double> expMatrix( deltaMatrix.rows(), deltaMatrix.cols() );
	doubleMatrix = convert<Number, double>( deltaMatrix );

	TRACE( "hypro.worker", "transformed matrix: " << doubleMatrix );

	expMatrix = doubleMatrix.exp();

	TRACE( "hypro.worker", "exp matrix: " << expMatrix );

	resultMatrix = convert<double, Number>( expMatrix );

	TRACE( "hypro.worker", "transformed matrix: " << resultMatrix );

	return resultMatrix;
}
}  // namespace hypro
