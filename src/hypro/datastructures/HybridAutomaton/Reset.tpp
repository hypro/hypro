#include "Reset.h"

namespace hypro {

template <typename Number>
Reset<Number>::Reset( const matrix_t<Number>& mat, const vector_t<Number>& vec ) {
	assert( mat.rows() == mat.cols() );
	mAffineResets.emplace_back( mat, vec );
	mIntervalResets.emplace_back( std::vector<carl::Interval<Number>>( mat.rows(), carl::Interval<Number>::emptyInterval() ) );
}

template <typename Number>
Reset<Number>::Reset( const std::vector<carl::Interval<Number>>& intervals ) {
	mAffineResets.emplace_back( matrix_t<Number>::Identity( intervals.size(), intervals.size() ), vector_t<Number>::Zero( intervals.size() ) );
	mIntervalResets.emplace_back( intervals );
}

template <typename Number>
const vector_t<Number>& Reset<Number>::getVector( std::size_t I ) const {
	return mAffineResets[I].mTransformation.vector();
}

template <typename Number>
const matrix_t<Number>& Reset<Number>::getMatrix( std::size_t I ) const {
	return mAffineResets[I].mTransformation.matrix();
}

template <typename Number>
matrix_t<Number>& Reset<Number>::rGetMatrix( std::size_t I ) {
	return mAffineResets[I].mTransformation.rMatrix();
}

template <typename Number>
vector_t<Number>& Reset<Number>::rGetVector( std::size_t I ) {
	return mAffineResets[I].mTransformation.rVector();
}

template <typename Number>
const std::vector<carl::Interval<Number>>& Reset<Number>::getIntervals( std::size_t I ) const {
	return mIntervalResets[I].mIntervals;
}

template <typename Number>
std::vector<carl::Interval<Number>>& Reset<Number>::rGetIntervals( std::size_t I ) {
	return mIntervalResets[I].mIntervals;
}

template <typename Number>
void Reset<Number>::setVector( const vector_t<Number>& in, std::size_t I ) {
	assert( mAffineResets.size() == mIntervalResets.size() );
	while ( mAffineResets.size() < I + 1 ) {
		mAffineResets.emplace_back( AffineTransformation<Number>() );
		mIntervalResets.emplace_back( IntervalAssignment<Number>() );
	}
	assert( mAffineResets.size() == mIntervalResets.size() );
	mAffineResets[I].mTransformation.rVector() = in;
	mHash = 0;
}

template <typename Number>
void Reset<Number>::setMatrix( const matrix_t<Number>& in, std::size_t I ) {
	assert( mAffineResets.size() == mIntervalResets.size() );
	assert( in.rows() == in.cols() );
	while ( mAffineResets.size() < I + 1 ) {
		mAffineResets.emplace_back( AffineTransformation<Number>() );
		mIntervalResets.emplace_back( IntervalAssignment<Number>() );
	}
	assert( mAffineResets.size() == mIntervalResets.size() );
	mAffineResets[I].mTransformation.setMatrix( in );
	mHash = 0;
}

template <typename Number>
void Reset<Number>::setIntervals( const std::vector<carl::Interval<Number>>& intervals, std::size_t I ) {
	assert( mAffineResets.size() == mIntervalResets.size() );
	while ( mIntervalResets.size() < I + 1 ) {
		mAffineResets.emplace_back( AffineTransformation<Number>() );
		mIntervalResets.emplace_back( IntervalAssignment<Number>() );
	}
	assert( mAffineResets.size() == mIntervalResets.size() );
	mIntervalResets[I].mIntervals = intervals;
	mHash = 0;
}

template <typename Number>
bool Reset<Number>::isIdentity() const {
	return std::all_of( mAffineResets.begin(), mAffineResets.end(), []( const auto& affineReset ) { return affineReset.isIdentity(); } ) && ( mIntervalResets.empty() || std::all_of( mIntervalResets.begin(), mIntervalResets.end(), []( const auto& intervals ) { return intervals.isIdentity(); } ) );
}

template <typename Number>
std::size_t Reset<Number>::hash() const {
	if ( mHash == 0 ) {
		mHash = std::hash<Reset<Number>>()( *this );
	}
	return mHash;
}

template <typename Number>
Reset<Number> combine(
	  const Reset<Number>& lhs, const Reset<Number>& rhs,
	  const std::vector<std::string> haVar, const std::vector<std::string> lhsVar, const std::vector<std::string> rhsVar ) {
	matrix_t<Number> newMat;
	vector_t<Number> newVec;

	if ( lhs.size() == 0 && rhs.size() != 0 ) {
		//std::cout << "take rhs" << std::endl;
		newMat = combine( matrix_t<Number>( 0, 0 ), rhs.getMatrix(), haVar, lhsVar, rhsVar );
		newVec = combine( vector_t<Number>( 0 ), rhs.getVector() );
	} else if ( lhs.size() != 0 && rhs.size() == 0 ) {
		//std::cout << "take lhs" << std::endl;
		newMat = combine( lhs.getMatrix(), matrix_t<Number>( 0, 0 ), haVar, lhsVar, rhsVar );
		newVec = combine( lhs.getVector(), vector_t<Number>( 0 ) );
	} else if ( lhs.size() == 0 && rhs.size() == 0 ) {
		//std::cout << "both empty" << std::endl;
		return Reset<Number>();
	} else {
		assert( lhs.size() != 0 );
		assert( rhs.size() != 0 );
		//std::cout << "Default." << std::endl;
		//std::cout << "Combine: " << lhs.getMatrix() << " and " << rhs.getMatrix() << std::endl;
		//std::cout << "LhsVAR:";
		//for(const auto& v : lhsVar) std::cout << v << " ";
		//std::cout << std::endl;
		//std::cout << "RhsVAR:";
		//for(const auto& v : rhsVar) std::cout << v << " ";
		//std::cout << std::endl;

		// Todo: This is a corrected, yet ineffective method. Improve!
		newMat = matrix_t<Number>::Zero( haVar.size(), haVar.size() );
		newVec = vector_t<Number>::Zero( haVar.size() );
		std::size_t lhsIR = 0;
		std::size_t lhsIC = 0;
		std::size_t rhsIR = 0;
		std::size_t rhsIC = 0;
		bool admissible = true;	 // flag used to denote a non-admissible flow, i.e. shared variables with different flow.
		// iterate over all rows
		for ( std::size_t rowI = 0; rowI != haVar.size(); ++rowI ) {
			//std::cout << "Consider composed row " << rowI << " for var " << haVar[rowI] << std::endl;
			//std::cout << "lhsIR: " << lhsIR << std::endl;
			//std::cout << "rhsIR: " << rhsIR << std::endl;
			//std::cout << "Now left hand side." << std::endl;
			if ( lhsIR < lhsVar.size() && lhsVar[lhsIR] == haVar[rowI] ) {
				newVec( rowI ) = lhs.getVector()( lhsIR );
				// iterate over all columns
				lhsIC = 0;
				for ( std::size_t colI = 0; colI != haVar.size(); ++colI ) {
					//std::cout << "Consider composed col " << colI << " for var " << haVar[colI] << std::endl;
					//std::cout << "lhsIC: " << lhsIC << std::endl;
					//std::cout << "rhsIC: " << rhsIC << std::endl;
					assert( lhsIC < lhsVar.size() );
					if ( lhsVar[lhsIC] == haVar[colI] ) {
						//std::cout << "rowI " << rowI << ", colI " << colI << ", lhsIR " << lhsIR << ", lhsIC " << lhsIC << std::endl;
						newMat( rowI, colI ) = lhs.getMatrix()( lhsIR, lhsIC );
						++lhsIC;
						if ( lhsIC == lhsVar.size() ) {
							break;
						}
					}
				}
				++lhsIR;
			}
			//std::cout << "lhsIR: " << lhsIR << std::endl;
			//std::cout << "intermediate result: " << newMat << std::endl;
			//std::cout << "Now right hand side." << std::endl;
			if ( rhsIR < rhsVar.size() && rhsVar[rhsIR] == haVar[rowI] ) {
				newVec( rowI ) = rhs.getVector()( rhsIR );
				// iterate over all columns
				rhsIC = 0;
				for ( std::size_t colI = 0; colI != haVar.size(); ++colI ) {
					//std::cout << "Consider composed col " << colI << " for var " << haVar[colI] << std::endl;
					//std::cout << "lhsIC: " << lhsIC << std::endl;
					//std::cout << "rhsIC: " << rhsIC << std::endl;
					if ( rhsVar[rhsIC] == haVar[colI] ) {
						// TODO: the check is not entirely correct, since the flow can be non-admissible but set to 0 in lhs and something != 0 in rhs.
						if ( newMat( rowI, colI ) != 0 && rhs.getMatrix()( rhsIR, rhsIC ) != newMat( rowI, colI ) ) {
							//std::cout << "Attention, try to set " << rowI << "," << colI << " to " << rhs.getMatrix()(rhsIR,rhsIC) << " which already is set to " << newMat(rowI,colI);
							admissible = false;
							break;
						}
						newMat( rowI, colI ) = rhs.getMatrix()( rhsIR, rhsIC );
						++rhsIC;
						if ( rhsIC == rhsVar.size() ) {
							break;
						}
					}
				}
				++rhsIR;
			}
			//std::cout << "rhsIR: " << rhsIR << std::endl;
			if ( !admissible )
				break;
		}
		assert( admissible );
		// newMat = combine(lhs.getMatrix(), rhs.getMatrix(), haVar, lhsVar, rhsVar);
		// newVec = combine(lhs.getVector(), rhs.getVector());
	}

	Reset<Number> re;
	re.setMatrix( newMat );
	re.setVector( newVec );

	return re;
}

template <typename Number>
void Reset<Number>::decompose( const Decomposition& decomposition ) {
	if ( mAffineResets.size() == 0 || mDecomposed ) {
		//empty constraints
		return;
	}

	INFO( "hypro.datastructures", "In the current state we assume that rectangular subspaces will not be decomposed." );
	assert( mAffineResets.size() == 1 );

	// traverse reset variants to collect all assignments per proposed subspace
	ConstraintSetT<Number> cset = mAffineResets[0].mTransformation;
	DEBUG( "hypro.datastructures", "Constraint Set before: \n " << cset );

	matrix_t<Number> constraintsOld( cset.matrix() );
	vector_t<Number> constantsOld( cset.vector() );
	auto oldIntervalAssignments = mIntervalResets[0].mIntervals;

	mAffineResets.clear();
	mIntervalResets.clear();

	// select constrains i,j,k into new constraint vector
	for ( auto set : decomposition.subspaces ) {
#ifdef HYPRO_LOGGING
		DEBUG( "hypro.datastructures", "decompose constraint for set: {" );
		for ( auto entry : set ) {
			DEBUG( "hypro.datastructures", "" << entry << ", " );
		}
		DEBUG( "hypro.datastructures", "}" );
#endif

		// new interval assignments are just copied, as we do not store the variable
		//std::vector<carl::Interval<Number>> newIntervals;
		std::vector<carl::Interval<Number>> newIntervals = oldIntervalAssignments;

		// for each row of the constraints check if it contains an entry for one of the variables of the set
		// and add the corresponding rows to a list of indices that are later added to a matrix
		std::vector<Eigen::Index> indicesToAdd;
		for ( auto entry : set ) {
			indicesToAdd.emplace_back( Eigen::Index( entry ) );
			//newIntervals.emplace_back(oldIntervalAssignments[entry]);
		}

		// create a row matrix with numIndicesToAdd many rows
		matrix_t<Number> newMatrix = selectRows( constraintsOld, indicesToAdd );
		newMatrix = selectCols( newMatrix, set );

		// create final constant vector
		vector_t<Number> newVec = selectRows( constantsOld, indicesToAdd );

		ConstraintSetT<Number> newConstraintSet( newMatrix, newVec );
		mAffineResets.emplace_back( std::move( newConstraintSet ) );
		mIntervalResets.emplace_back( std::move( newIntervals ) );
	}

	mDecomposed = true;
	mHash = 0;
}
}  // namespace hypro
