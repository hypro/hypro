#include "State.h"

namespace hypro {

template <typename Number, typename Representation, typename... Rargs>
const std::variant<Representation, Rargs...>& State<Number, Representation, Rargs...>::getSet( std::size_t i ) const {
	DEBUG( "hypro.datastructures", "Attempt to get set at pos " << i << ", mSets.size() = " << mSets.size() << ", mTypes.size() = " << mTypes.size() );
	assert( mTypes.size() == mSets.size() );
	assert( i < mSets.size() );
	assert( checkConsistency() );
	return mSets.at( i );
}

template <typename Number, typename Representation, typename... Rargs>
std::variant<Representation, Rargs...>& State<Number, Representation, Rargs...>::rGetSet( std::size_t i ) {
	DEBUG( "hypro.datastructures", "Attempt to get set reference at pos " << i << ", mSets.size() = " << mSets.size() );
	assert( mTypes.size() == mSets.size() );
	assert( checkConsistency() );
	return mSets.at( i );
}

template <typename Number, typename Representation, typename... Rargs>
template <typename R>
void State<Number, Representation, Rargs...>::setSet( const R& s, std::size_t i ) {
	DEBUG( "hypro.datastructures", "Attempt to set set at pos " << i << ", mSets.size() = " << mSets.size() );
	assert( mSets.size() == mTypes.size() );
	assert( checkConsistency() );
	while ( i >= mSets.size() ) {
		mSets.emplace_back( Representation() );		 // some default set.
		mTypes.push_back( Representation::type() );	 // some default set type.
		mIsEmpty.push_back( TRIBOOL::NSET );
		TRACE( "hypro.datastructures", "Add empty dummy set of type " << mTypes.back() << " at index " << mSets.size() );
	}
	TRACE( "hypro.datastructures", "Set set to:" << s << ", type: " << R::type() );
	mSets[i] = s;
	mTypes[i] = R::type();
	DEBUG( "hypro.datastructures", "Set set at pos " << i << ", mSets.size() = " << mSets.size() );
	assert( mSets.size() > i );
	assert( checkConsistency() );
}

template <typename Number, typename Representation, typename... Rargs>
void State<Number, Representation, Rargs...>::setSet( const State<Number, Representation, Rargs...>::repVariant& s, std::size_t i ) {
	DEBUG( "hypro.datastructures", "Attempt to set set at pos " << i << ", mSets.size() = " << mSets.size() );
	assert( mSets.size() == mTypes.size() );
	assert( checkConsistency() );
	while ( i >= mSets.size() ) {
		mSets.emplace_back( Representation() );		 // some default set.
		mTypes.push_back( Representation::type() );	 // some default set type.
		mIsEmpty.push_back( TRIBOOL::NSET );
	}
	mSets[i] = s;
	mTypes[i] = std::visit( genericTypeVisitor(), s );
	DEBUG( "hypro.datastructures", "Set set at pos " << i << ", mSets.size() = " << mSets.size() );
	assert( mSets.size() > i );
	assert( checkConsistency() );
}

template <typename Number, typename Representation, typename... Rargs>
void State<Number, Representation, Rargs...>::addTimeToClocks( tNumber t ) {
	TRACE( "hypro.datastructures", "Add timestep of size " << t << " to clocks." );
	//if(mHasClocks) {
	//	matrix_t<Number> identity = matrix_t<Number>::Identity(mClockAssignment.dimension(), mClockAssignment.dimension());
	//	vector_t<Number> clockShift = vector_t<Number>::Ones(mClockAssignment.dimension());
	//	clockShift = clockShift * t;
	//	mClockAssignment = mClockAssignment.affineTransformation(identity,clockShift);
	//}
	assert( checkConsistency() );
	mTimestamp += t;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::unite( const State<Number, Representation, Rargs...>& in ) const {
	State<Number, Representation, Rargs...> res( *this );

	TRACE( "hypro.datastructures", "Union with " << mSets.size() << " sets." );

	// element-wise union.
	assert( mSets.size() == in.getSets().size() );
	assert( checkConsistency() );
	for ( std::size_t i = 0; i < mSets.size(); ++i ) {
		TRACE( "hypro.datastructures", "Apply unite visitor for set " << i );
		res.setSetDirect( std::visit( genericUniteVisitor<repVariant>(), mSets.at( i ), in.getSet( i ) ), i );
		if ( in.getEmptyStates()[i] == TRIBOOL::TRUE || this->getEmptyStates()[i] == TRIBOOL::TRUE ) {
			res.rGetEmptyStates()[i] = TRIBOOL::TRUE;
		}
	}

	TRACE( "hypro.datastructures", "Done union." );

	res.setTimestamp( mTimestamp.convexHull( in.getTimestamp() ) );
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::intersect( const State<Number, Representation, Rargs...>& in ) const {
	State<Number, Representation, Rargs...> res( *this );

	// intersection.
	assert( mSets.size() == in.getSets().size() );
	assert( checkConsistency() );
	for ( std::size_t i = 0; i < mSets.size(); ++i ) {
		TRACE( "hypro.datastructures", "Apply unite vistor for set " << i );
		if ( in.getEmptyStates()[i] == TRIBOOL::TRUE || this->getEmptyStates()[i] == TRIBOOL::TRUE ) {
			res.rGetEmptyStates()[i] = TRIBOOL::TRUE;
		} else {
			res.setSetDirect( std::visit( genericIntersectVisitor<repVariant>(), mSets.at( i ), in.getSet( i ) ), i );
			res.rGetEmptyStates()[i] = TRIBOOL::NSET;
		}
	}

	TRACE( "hypro.datastructures", "Done intersection." );

	res.setTimestamp( carl::set_intersection( mTimestamp, in.getTimestamp() ) );
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
std::pair<CONTAINMENT, State<Number, Representation, Rargs...>> State<Number, Representation, Rargs...>::satisfies( const Condition<Number>& in ) const {
	//DEBUG("hypro.datastructures","this rep name: " << mSetRepresentationName << " vs " << in.getSetRepresentation());
	//assert(mSetRepresentationName == in.getSetRepresentation());

	assert( checkConsistency() );

	if ( in.constraints().empty() ) {
		return std::make_pair( CONTAINMENT::FULL, *this );
	}

	DEBUG( "hypro.datastructures", "This size: " << mSets.size() << ", condition size: " << in.size() );
	DEBUG( "hypro.datastructures", "Condition matrix: " << std::endl
														<< in.getMatrix() << std::endl
														<< "Vector: " << std::endl
														<< in.getVector() );
	assert( in.size() == mSets.size() );

	State<Number, Representation, Rargs...> res( *this );

	CONTAINMENT strictestContainment = CONTAINMENT::FULL;

	for ( std::size_t i = 0; i < mSets.size(); ++i ) {
		// check each substateset agains its invariant subset
		//DEBUG("hypro.datastructures","Condition matrix: " << std::endl << in.getMatrix(i) << std::endl << "Vector: " << std::endl << in.getVector(i));
		//DEBUG("hypro.datastructures", "Before genericSatisfiesHalfspacesVisitor. mSets.at(" << i << ") is: "<< std::endl << mSets.at(i));
		auto resultPair = std::visit( genericSatisfiesHalfspacesVisitor<repVariant, Number>( in.getMatrix( i ), in.getVector( i ) ), mSets.at( i ) );
		//DEBUG("hypro.datastructures", "After genericSatisfiesHalfspacesVisitor.");

		res.setSetDirect( resultPair.second, i );
		//DEBUG("hypro.datastructures", "i is:" << i << "After setSetDirect.");

		if ( resultPair.first == CONTAINMENT::NO ) {
			DEBUG( "hypro.datastructures", "State set " << i << "(type " << mTypes.at( i ) << ") failed the condition - return empty." );
			strictestContainment = resultPair.first;
			res.rGetEmptyStates()[i] = TRIBOOL::TRUE;
			break;
		} else if ( resultPair.first == CONTAINMENT::PARTIAL ) {
			DEBUG( "hypro.datastructures", "State set " << i << "(type " << mTypes.at( i ) << ") succeeded the condition - return partial." );
			strictestContainment = CONTAINMENT::PARTIAL;
			res.rGetEmptyStates()[i] = TRIBOOL::FALSE;
		} else if ( resultPair.first == CONTAINMENT::YES ) {
			strictestContainment = CONTAINMENT::YES;
			res.rGetEmptyStates()[i] = TRIBOOL::FALSE;
		} else {
			res.rGetEmptyStates()[i] = TRIBOOL::FALSE;
		}
	}
	DEBUG( "hypro.datastructures", "State::satisfies: End of loop" );
	return std::make_pair( strictestContainment, res );
}

template <typename Number, typename Representation, typename... Rargs>
std::pair<CONTAINMENT, State<Number, Representation, Rargs...>> State<Number, Representation, Rargs...>::satisfiesHalfspaces( const matrix_t<Number>& constraints, const vector_t<Number>& constants ) const {
	if ( constraints.rows() == 0 ) {
		return std::make_pair( CONTAINMENT::FULL, *this );
	}
	assert( checkConsistency() );
	return partiallySatisfies( Condition<Number>( constraints, constants ), 0 );
}

template <typename Number, typename Representation, typename... Rargs>
std::pair<CONTAINMENT, State<Number, Representation, Rargs...>> State<Number, Representation, Rargs...>::partiallySatisfies( const Condition<Number>& in, std::size_t I ) const {
	TRACE( "hypro.datastructures", "Check Condition of size " << in.size() << " against set at pos " << I );
	assert( checkConsistency() );

	if ( in.size() == 0 || in.constraints().empty() ) {
		return std::make_pair( CONTAINMENT::FULL, *this );
	}
	assert( in.size() == mSets.size() );

	State<Number, Representation, Rargs...> res( *this );
	assert( res.getTimestamp() == this->getTimestamp() );

	TRACE( "hypro.datastructures", "Invoking satisfiesHalfspaces visitor." );
	assert( mSets.size() > I );
	auto resultPair = std::visit( genericSatisfiesHalfspacesVisitor<repVariant, Number>( in.getMatrix( I ), in.getVector( I ) ), mSets.at( I ) );
	TRACE( "hypro.datastructures", "Done satisfiesHalfspaces visitor, attempt to set result." );
	res.setSetDirect( resultPair.second, I );
	res.rGetEmptyStates()[I] = resultPair.first == CONTAINMENT::NO ? TRIBOOL::TRUE : TRIBOOL::FALSE;

	TRACE( "hypro.datastructures", "Result empty: " << resultPair.first );

	return std::make_pair( resultPair.first, res );
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::intersectHalfspaces( const matrix_t<Number>& constraints, const vector_t<Number>& constants, std::size_t I ) const {
	assert( checkConsistency() );

	State<Number, Representation, Rargs...> res( *this );
	assert( res.getTimestamp() == this->getTimestamp() );
	assert( mSets.size() > I );

	auto resultPair = std::visit( genericSatisfiesHalfspacesVisitor<repVariant, Number>( constraints, constants ), mSets.at( I ) );
	res.setSetDirect( resultPair.second, I );
	res.rGetEmptyStates()[I] = resultPair.first == CONTAINMENT::NO ? TRIBOOL::TRUE : TRIBOOL::FALSE;

	return res;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::applyTimeStep( const std::vector<std::pair<const matrix_t<Number>&, const vector_t<Number>&>>& flows, tNumber timeStepSize ) const {
	State<Number, Representation, Rargs...> res( *this );
	TRACE( "hypro.datastructures", "Apply timestep of size " << timeStepSize );
	//res.setSet(mSet.affineTransformation(trafoMatrix,trafoVector));
	assert( flows.size() == mSets.size() );
	assert( checkConsistency() );
	for ( std::size_t i = 0; i < mSets.size(); ++i ) {
		res.setSetDirect( std::visit( genericAffineTransformationVisitor<repVariant, Number>( flows.at( i ).first, flows.at( i ).second ), mSets.at( i ) ), i );
	}
	res.addTimeToClocks( timeStepSize );
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::partiallyApplyTimeStep( const ConstraintSet<Number>& flow, tNumber timeStepSize, std::size_t I ) const {
	State<Number, Representation, Rargs...> res( *this );
	assert( I < mSets.size() );
	assert( checkConsistency() );
	res.setSetDirect( std::visit( genericAffineTransformationVisitor<repVariant, Number>( flow.matrix(), flow.vector() ), mSets.at( I ) ), I );

	res.addTimeToClocks( timeStepSize );
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::computeAndApplyLinearTimeStep( const std::vector<const matrix_t<Number>&>& flows, tNumber timeStepSize ) const {
	assert( flows.size() <= mSets.size() );
	assert( checkConsistency() );

	State<Number, Representation, Rargs...> res( *this );
	// iterate over all sets
	for ( int i = 0; i < flows.size(); ++i ) {
		// compute matrix exponential e^{delta A}
		matrix_t<Number> deltaMatrix = carl::convert<tNumber, Number>( timeStepSize ) * flows[i];
		auto expMatrix = matrixExponential( deltaMatrix );

		// apply according transformation to subspace set
		assert( std::visit( genericDimensionVisitor(), mSets[i] ) == expMatrix.rows() );
		res.setSetDirect( std::visit( genericAffineTransformationVisitor<repVariant, Number>( expMatrix.matrix(), vector_t<Number>::Zero( flows[i].rows() ) ), mSets.at( i ) ), i );
	}
	// update internal clocks
	res.addTimeToClocks( timeStepSize );
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::partiallyComputeAndApplyLinearTimeStep( const matrix_t<Number>& flow, tNumber timeStepSize, std::size_t I ) const {
	// compute matrix exponential e^{delta A}
	matrix_t<Number> deltaMatrix = carl::convert<tNumber, Number>( timeStepSize ) * flow;
	auto expMatrix = matrixExponential( deltaMatrix );
	// apply according transformation
	return this->partiallyApplyTimeStep( ConstraintSet<Number>( expMatrix ), timeStepSize, I );
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::computeAndApplyAffineTimeStep( const std::vector<const matrix_t<Number>&>& flows, tNumber timeStepSize ) const {
	assert( flows.size() <= mSets.size() );
	assert( checkConsistency() );

	State<Number, Representation, Rargs...> res( *this );
	// iterate over all sets
	for ( int i = 0; i < flows.size(); ++i ) {
		// compute matrix exponential e^{delta A}
		matrix_t<Number> deltaMatrix = carl::convert<tNumber, Number>( timeStepSize ) * flows[i];
		auto expMatrix = matrixExponential( deltaMatrix );

		// assumption: the flow is affine, i.e. of the form \dot(x) = Ax + b. We cut off the last col/row
		unsigned rows = expMatrix.rows();
		unsigned cols = expMatrix.cols();
		vector_t<Number> translation = expMatrix.col( cols - 1 );
		matrix_t<Number> expMatrixResized = matrix_t<Number>( rows - 1, cols - 1 );
		expMatrixResized = expMatrix.block( 0, 0, rows - 1, cols - 1 );
		translation.conservativeResize( rows - 1 );

		// apply according transformation to subspace set
		assert( std::visit( genericDimensionVisitor(), mSets[i] ) == expMatrix.rows() );
		res.setSetDirect( std::visit( genericAffineTransformationVisitor<repVariant, Number>( expMatrixResized.matrix(), translation ), mSets.at( i ) ), i );
	}
	// update internal clocks
	res.addTimeToClocks( timeStepSize );
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::partiallyComputeAndApplyAffineTimeStep( const matrix_t<Number>& flow, tNumber timeStepSize, std::size_t I ) const {
	assert( I < mSets.size() );
	// compute matrix exponential e^{delta A}
	matrix_t<Number> deltaMatrix = carl::convert<tNumber, Number>( timeStepSize ) * flow;
	auto expMatrix = matrixExponential( deltaMatrix );

	// assumption: the flow is affine, i.e. of the form \dot(x) = Ax + b. We cut off the last col/row
	unsigned rows = expMatrix.rows();
	unsigned cols = expMatrix.cols();
	vector_t<Number> translation = expMatrix.col( cols - 1 );
	matrix_t<Number> expMatrixResized = matrix_t<Number>( rows - 1, cols - 1 );
	expMatrixResized = expMatrix.block( 0, 0, rows - 1, cols - 1 );
	translation.conservativeResize( rows - 1 );

	// apply transformation after resizing.
	return this->partiallyApplyTimeStep( ConstraintSet<Number>( expMatrixResized, translation ), timeStepSize, I );
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::applyTransformation( const std::vector<ConstraintSet<Number>>& trafos ) const {
	State<Number, Representation, Rargs...> res( *this );
	TRACE( "hypro.datastructures", "Apply transformation of " << mSets.size() << " sets (" << trafos.size() << " transformations)." );
	assert( trafos.size() == mSets.size() );
	assert( checkConsistency() );
	for ( std::size_t i = 0; i < mSets.size(); ++i ) {
		res.setSetDirect( std::visit( genericAffineTransformationVisitor<repVariant, Number>( trafos.at( i ).matrix(), trafos.at( i ).vector() ), mSets.at( i ) ), i );
	}
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::applyTransformation( const ConstraintSet<Number>& trafo, std::size_t I ) const {
	State<Number, Representation, Rargs...> res( *this );
	assert( I < mSets.size() );
	assert( checkConsistency() );
	INFO( "hypro.datastructures", "Apply transformation of set at pos " << I << ", using transformation " << trafo );
	res.setSet( std::visit( genericAffineTransformationVisitor<repVariant, Number>( trafo.matrix(), trafo.vector() ), mSets.at( I ) ), I );
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::applyTransformation( const ConstraintSet<Number>& trafo ) const {
	State<Number, Representation, Rargs...> res( *this );
	TRACE( "hypro.datastructures", "Apply transformation of " << mSets.size() << " sets (" << trafo.size() << " transformations)." );
	assert( mSets.size() == 1 );
	assert( checkConsistency() );
	for ( std::size_t i = 0; i < mSets.size(); ++i ) {
		res.setSetDirect( std::visit( genericAffineTransformationVisitor<repVariant, Number>( trafo.matrix(), trafo.vector() ), mSets.at( i ) ), i );
	}
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::linearTransformation( const matrix_t<Number>& matrix ) const {
	assert( checkConsistency() );
	return partiallyApplyTransformation( ConstraintSet<Number>( matrix, vector_t<Number>::Zero( matrix.rows() ) ), 0 );
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::affineTransformation( const matrix_t<Number>& matrix, const vector_t<Number>& vector ) const {
	assert( checkConsistency() );
	return partiallyApplyTransformation( ConstraintSet<Number>( matrix, vector ), 0 );
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::partialIntervalAssignment( const std::vector<carl::Interval<Number>>& assignments, std::size_t I ) const {
	assert( checkConsistency() );
	State<Number, Representation, Rargs...> res( *this );
	TRACE( "hypro.datastructures", "Apply interval assignment for subspace " << I << "." );
	// Note: We abuse empty intervals to indicate identity assignments -> change to a map later! (TODO)
	res.setSetDirect( std::visit( genericIntervalAssignmentVisitor<repVariant, Number>( assignments ), mSets.at( I ) ), I );
	for ( const auto& i : assignments ) {
		if ( i.isEmpty() ) {
			res.rGetEmptyStates()[I] = TRIBOOL::TRUE;
		}
	}
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::partiallyApplyTransformation( const std::vector<ConstraintSet<Number>>& trafos, const std::vector<std::size_t>& sets ) const {
	State<Number, Representation, Rargs...> res( *this );
	assert( trafos.size() == sets.size() );
	assert( checkConsistency() );
	for ( std::size_t i = 0; i < sets.size(); ++i ) {
		assert( sets.at( i ) < mSets.size() );
		res.setSetDirect( std::visit( genericAffineTransformationVisitor<repVariant, Number>( trafos.at( i ).matrix(), trafos.at( i ).vector() ), mSets.at( sets.at( i ) ) ), sets.at( i ) );
	}
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::partiallyApplyTransformation( const ConstraintSet<Number>& trafo, std::size_t I ) const {
	State<Number, Representation, Rargs...> res( *this );
	assert( I < mSets.size() );
	assert( checkConsistency() );
	res.setSetDirect( std::visit( genericAffineTransformationVisitor<repVariant, Number>( trafo.matrix(), trafo.vector() ), mSets.at( I ) ), I );
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::minkowskiSum( const State<Number, Representation, Rargs...>& rhs ) const {
	//If only one representation given: avoid visitor
	//if(mTypes.size() == 1){
	//	return std::get<Representation>(mSets.at(0)).minkowskiSum(rhs);
	//}
	//For more representations: use visitor
	State<Number, Representation, Rargs...> res( *this );
	assert( mSets.size() == rhs.getSets().size() );
	assert( checkConsistency() );
	for ( std::size_t i = 0; i < rhs.getSets().size(); i++ ) {
		res.setSetDirect( std::visit( genericMinkowskiSumVisitor<repVariant>(), mSets.at( i ), rhs.getSet( i ) ), i );
		if ( rhs.getEmptyState()[i] == TRIBOOL::TRUE || this->getEmptyState()[i] == TRIBOOL::TRUE ) {
			res.rGetEmptyStates()[i] = TRIBOOL::TRUE;
		}
	}
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::partiallyMinkowskiSum( const State<Number, Representation, Rargs...>& rhs, std::size_t I ) const {
	assert( I < mSets.size() );
	assert( I < rhs.getSets().size() );
	assert( checkConsistency() );
	//If only one representation given: avoid visitor
	//if(mTypes.size() == 1){
	//	return std::get<Representation>(mSets.at(0)).minkowskiSum(rhs);
	//}
	//For more representations avaiable: use visitor
	State<Number, Representation, Rargs...> res( *this );
	res.setSetDirect( std::visit( genericMinkowskiSumVisitor<repVariant>(), mSets.at( I ), rhs.getSet( I ) ), I );
	if ( rhs.getEmptyStates()[I] == TRIBOOL::TRUE || this->getEmptyStates()[I] == TRIBOOL::TRUE ) {
		res.rGetEmptyStates()[I] = TRIBOOL::TRUE;
	}
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
bool State<Number, Representation, Rargs...>::contains( const State<Number, Representation, Rargs...>& rhs ) const {
	assert( checkConsistency() );
	assert( rhs.getNumberSets() == this->getNumberSets() );
	for ( std::size_t i = 0; i < this->getNumberSets(); ++i ) {
		if ( !std::visit( genericSetContainsVisitor(), this->getSet( i ), rhs.getSet( i ) ) ) {
			return false;
		}
	}
	return true;
}

template <typename Number, typename Representation, typename... Rargs>
std::vector<Point<Number>> State<Number, Representation, Rargs...>::vertices( std::size_t I ) const {
	assert( checkConsistency() );
	return std::visit( genericVerticesVisitor<Number>(), mSets.at( I ) );
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::projectOn( const std::vector<std::size_t>& dimensions, std::size_t I ) const {
	assert( I < mSets.size() );
	assert( checkConsistency() );
	State res( *this );
	res.setSetDirect( std::visit( genericProjectionVisitor<repVariant>( dimensions ), mSets.at( I ) ) );
	if ( dimensions.size() == 0 ) {
		res.rGetEmptyStates()[I] = TRIBOOL::TRUE;
	}
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::projectOn( const std::pair<std::size_t, std::size_t>& dimensions, std::size_t I ) const {
	assert( I < mSets.size() );
	assert( checkConsistency() );
	std::vector<std::size_t> ds;
	ds.push_back( dimensions.first );
	ds.push_back( dimensions.second );
	return this->projectOn( ds, I );
}

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> State<Number, Representation, Rargs...>::assignIntervals( const std::map<std::size_t, carl::Interval<Number>>& assignments, std::size_t I ) const {
	assert( I < mSets.size() );
	assert( checkConsistency() );
	State res{ *this };
	res.setSetDirect( std::visit( genericAssignIntervalsVisitor<repVariant, Number>( assignments ), mSets.at( I ) ) );
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
std::size_t State<Number, Representation, Rargs...>::getDimension( std::size_t I ) const {
	assert( I < mSets.size() );
	assert( checkConsistency() );
	return std::visit( genericDimensionVisitor(), mSets.at( I ) );
}

template <typename Number, typename Representation, typename... Rargs>
std::size_t State<Number, Representation, Rargs...>::getDimensionOffset( std::size_t I ) const {
	assert( I < mSets.size() );
	assert( checkConsistency() );
	std::size_t res = 0;
	for ( std::size_t i = 0; i < I; ++i ) {
		res += this->getDimension( i );
	}
	return res;
}

template <typename Number, typename Representation, typename... Rargs>
Number State<Number, Representation, Rargs...>::getSupremum( std::size_t I ) const {
	assert( I < mSets.size() );
	assert( checkConsistency() );
	//If only one representation given: avoid visitor
	//if(mTypes.size() == 1){
	//	return std::get<Representation>(mSets.at(0)).supremum();
	//}
	//For more representations avaiable: use visitor
	return std::visit( genericSupremumVisitor<Number>(), mSets.at( I ) );
}

template <typename Number, typename Representation, typename... Rargs>
void State<Number, Representation, Rargs...>::removeRedundancy() {
	//If only one representation given: avoid visitor
	//if(mTypes.size() == 1){
	//	return std::get<Representation>(mSets.at(0)).removeRedundancy();
	//}
	//For more representations avaiable: use visitor
	assert( checkConsistency() );
	State<Number, Representation, Rargs...> res( *this );
	for ( std::size_t i = 0; i < mSets.size(); i++ ) {
		res.setSetDirect( std::visit( genericRedundancyVisitor<repVariant, Number>(), mSets.at( i ) ), i );
	}
}

template <typename Number, typename Representation, typename... Rargs>
void State<Number, Representation, Rargs...>::partiallyRemoveRedundancy( std::size_t I ) {
	assert( I < mSets.size() );
	assert( checkConsistency() );
	//If only one representation given: avoid visitor
	//if(mTypes.size() == 1){
	//	return std::get<Representation>(mSets.at(0)).removeRedundancy();
	//}
	//For more representations avaiable: use visitor
	mSets[I] = std::visit( genericRedundancyVisitor<repVariant, Number>(), mSets[I] );
}

template <typename Number, typename Representation, typename... Rargs>
void State<Number, Representation, Rargs...>::reduceRepresentation() {
	assert( checkConsistency() );
	for ( std::size_t i = 0; i < mSets.size(); i++ ) {
		this->setSetDirect( std::visit( genericReductionVisitor<repVariant, Number>(), mSets.at( i ) ), i );
	}
}

template <typename Number, typename Representation, typename... Rargs>
void State<Number, Representation, Rargs...>::partiallyReduceRepresentation( std::size_t I ) {
	assert( I < mSets.size() );
	assert( checkConsistency() );
	this->setSetDirect( std::visit( genericReductionVisitor<repVariant, Number>(), mSets.at( I ) ), I );
}

template <typename Number, typename Representation, typename... Rargs>
bool State<Number, Representation, Rargs...>::checkConsistency() const {
	if ( mSets.size() != mTypes.size() || mSets.size() != mIsEmpty.size() ) {
		std::cout << "Inconsistent size!" << std::endl;
		return false;
	}
	for ( std::size_t i = 0; i < mSets.size(); i++ ) {
		if ( mTypes.at( i ) != std::visit( genericTypeVisitor(), mSets.at( i ) ) ) {
			std::cout << "Types do not match (expected: " << mTypes.at( i ) << ", is: " << std::visit( genericTypeVisitor(), mSets.at( i ) ) << ")" << std::endl;
			return false;
			//} else {
			//std::cout << "Types matched, in mTypes: " << mTypes.at(i) << " actual type in mSets is:" << std::visit(genericTypeVisitor(), mSets.at(i)) << std::endl;
		}
	}
	return true;
}

template <typename Number, typename Representation, typename... Rargs>
bool State<Number, Representation, Rargs...>::isEmpty() const {
	for ( std::size_t i = 0; i < mSets.size(); ++i ) {
		// TODO: do not ignore cache!
		bool localEmpty = std::visit( genericEmptyVisitor(), mSets.at( i ) );
		mIsEmpty[i] = localEmpty == true ? TRIBOOL::TRUE : TRIBOOL::FALSE;
		if ( localEmpty ) {
			return true;
		}
	}
	return false;
}

template <typename Number, typename Representation, typename... Rargs>
void State<Number, Representation, Rargs...>::setSets( const std::vector<std::variant<Representation, Rargs...>>& sets ) {
	mSets = sets;
	mIsEmpty = std::vector<TRIBOOL>{ mSets.size(), TRIBOOL::NSET };
}

template <typename Number, typename Representation, typename... Rargs>
void State<Number, Representation, Rargs...>::setSetsSave( const std::vector<std::variant<Representation, Rargs...>>& sets ) {
	assert( checkConsistency() );
	//std::cout << "mSets.size(): " << mSets.size() << " mTypes.size(): " << mTypes.size() << " sets.size(): " << sets.size() << std::endl;
	for ( std::size_t i = 0; i < sets.size(); i++ ) {
		setSetType( std::visit( genericTypeVisitor(), sets.at( i ) ), i );
	}
	mSets = sets;
	mIsEmpty = std::vector<TRIBOOL>{ mSets.size(), TRIBOOL::NSET };
	assert( checkConsistency() );
}

template <typename Number, typename Representation, typename... Rargs>
void State<Number, Representation, Rargs...>::decompose( const Decomposition& decomposition ) {
	if ( decomposition.subspaces.size() == 1 || mSets.size() != 1 ) {
		// no decomposition/already decomposed
	}
	// initial set is a constraint set
	matrix_t<Number> constraintsOld( std::get<hypro::ConstraintSet<Number>>( mSets.at( 0 ) ).matrix() );
	vector_t<Number> constantsOld( std::get<hypro::ConstraintSet<Number>>( mSets.at( 0 ) ).vector() );
	int i = 0;
	for ( auto decomp : decomposition.subspaces ) {
#ifdef HYPRO_LOGGING
		DEBUG( "hypro.datastructures", "Trying to project set: \n " << mSets.at( 0 ) << "\n to dimensions: " );
		DEBUG( "hypro.datastructures", "{" );
		for ( auto entry : decomp ) {
			DEBUG( "hypro.datastructures", "" << entry << ", " );
		}
		DEBUG( "hypro.datastructures", "}" );
#endif

		// for each row of the constraints check if it contains an entry for one of the variables of the set
		// and add the corresponding rows to a list of indices that are later added to the result matrix
		std::vector<int> indicesToAdd;
		for ( int i = 0; i < constraintsOld.rows(); i++ ) {
			vector_t<Number> row = constraintsOld.row( i );
			bool containsVar = false;
			for ( int j = 0; j < row.rows(); j++ ) {
				if ( row( j, 0 ) != 0 ) {
					if ( std::find( decomp.begin(), decomp.end(), j ) != decomp.end() ) {
						//set contains variable j, which is also contained in this constraint
						containsVar = true;
						break;
					}
				}
			}
			if ( containsVar ) {
				// this row contains information for one of the variables of this decomposition
				indicesToAdd.push_back( i );
			}
		}

		// we found information for our decomposition
		if ( indicesToAdd.size() > 0 ) {
			// create a row matrix with numIndicesToAdd many rows
			matrix_t<Number> rowMat = matrix_t<Number>::Zero( indicesToAdd.size(), constraintsOld.cols() );
			for ( Eigen::Index index = 0; index < rowMat.rows(); index++ ) {
				// copy over preselected rows
				rowMat.row( index ) = constraintsOld.row( indicesToAdd[index] );
			}
			// create final matrix that does not contain columns not in this set
			matrix_t<Number> finMat = matrix_t<Number>::Zero( rowMat.rows(), decomp.size() );
			// -1 for constant column
			for ( Eigen::Index index = 0; index < finMat.cols(); index++ ) {
				finMat.col( index ) = rowMat.col( decomp[index] );
			}
			// create final constant vector
			vector_t<Number> finVec = vector_t<Number>::Zero( indicesToAdd.size() );
			for ( Eigen::Index index = 0; index < finVec.rows(); index++ ) {
				finVec( index ) = constantsOld( indicesToAdd[index] );
			}

			ConstraintSet<Number> res( finMat, finVec );
			DEBUG( "hypro.datastructures", "Final decomposed ConstraintSet: \n"
												 << res );
			setSetDirect( hypro::Converter<Number>::toConstraintSet( res ), i );
			setSetType( hypro::representation_name::constraint_set, i );
		} else {
			DEBUG( "hypro.datastructures", "No constraints for set found." );
			ConstraintSet<Number> res = ConstraintSet<Number>();
			setSetDirect( hypro::Converter<Number>::toConstraintSet( res ), i );
			setSetType( hypro::representation_name::constraint_set, i );
		}
		i++;
	}
	mIsEmpty = std::vector<TRIBOOL>{ mSets.size(), TRIBOOL::NSET };
	DEBUG( "hypro.datastructures", "State after decomposition: " << *this );
}

template <typename Number, typename Representation, typename... Rargs>
template <typename To>
void State<Number, Representation, Rargs...>::setAndConvertType( std::size_t I ) {
	assert( checkConsistency() );
	assert( I < mTypes.size() );

	// convert set to type

	//this->setSet( std::visit( genericInternalConversionVisitor<typename State::repVariant, To>( this->getSet( I ) ), this->getSet( I ) ), I );

	this->setSet( std::visit( genericConversionVisitor<typename State::repVariant, To>(),
							  this->getSet( I ) ),
				  I );

	assert( checkConsistency() );
}

}  // namespace hypro
