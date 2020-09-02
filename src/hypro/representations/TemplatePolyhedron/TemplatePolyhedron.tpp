#include "TemplatePolyhedron.h"

namespace hypro {

//////// Constructors & Destructors ////////

//Empty constructor
template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting>::TemplatePolyhedronT()
	: mMatrixPtr( nullptr )
	, mVector( vector_t<Number>::Zero( 0 ) )
	, mOptimizer( Optimizer<Number>() ) {}

//Regular template polyhedron constructor
template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting>::TemplatePolyhedronT( const std::size_t dimension, const std::size_t noOfSides, const vector_t<Number>& vec ) {
	//Check if coeff vector has the right length
	//if(noOfSides != std::size_t(vec.rows())){
	//	throw std::invalid_argument("Template polyhedron offset vector length not fitting.");
	//}

	//compute template matrix and set it as new mMatrixPtr
	auto templateDirs = computeTemplate<Number>( dimension, noOfSides );
	mMatrixPtr = std::make_shared<matrix_t<Number>>( combineRows( templateDirs ) );
	if ( vec != vector_t<Number>::Zero( vec.rows() ) ) {
		mVector = vec;
	} else {
		mVector = vector_t<Number>::Zero( dimension );
	}
	mOptimizer = Optimizer<Number>( *mMatrixPtr, mVector );
}

//Matrix-Vector-constructor
template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting>::TemplatePolyhedronT( const matrix_t<Number>& mat, const vector_t<Number>& vec )
	: mMatrixPtr( std::make_shared<matrix_t<Number>>( mat ) )
	, mVector( vec )
	, mOptimizer( Optimizer<Number>( mat, vec ) ) {
	//reduceRepresentation();
	assert( mOptimizer.matrix() == mat );
	assert( mOptimizer.vector() == vec );
	assert( vec.rows() == mMatrixPtr->rows() );
}

//Vector of matrix and vector ctor
template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting>::TemplatePolyhedronT( const std::vector<std::pair<matrix_t<Number>, vector_t<Number>>>& matVecPairs ) {
	if ( matVecPairs.empty() ) {
		mMatrixPtr = std::make_shared<matrix_t<Number>>( matrix_t<Number>::Zero( 1, 1 ) );
		mVector = vector_t<Number>::Zero( 1 );
		mOptimizer = Optimizer<Number>( *mMatrixPtr, mVector );

	} else {
		//Template size is the amount of all rows combined
		std::size_t templateRows = 0;
		for ( const auto pair : matVecPairs ) {
			templateRows += pair.first.rows();
		}

		matrix_t<Number> mat = matrix_t<Number>::Zero( templateRows, matVecPairs.front().first.cols() );
		vector_t<Number> vec = vector_t<Number>::Zero( templateRows );
		Eigen::Index currentRow = 0;
		for ( const auto& pair : matVecPairs ) {
			assert( pair.first.rows() == pair.second.rows() );
			mat.block( currentRow, 0, pair.first.rows(), pair.first.cols() ) = pair.first;
			vec.block( currentRow, 0, pair.second.rows(), 1 ) = pair.second;
			currentRow += pair.first.rows();
		}

		mMatrixPtr = std::make_shared<matrix_t<Number>>( std::move( mat ) );
		mVector = std::move( vec );
		mOptimizer = Optimizer<Number>( *mMatrixPtr, mVector );

		assert( mOptimizer.matrix() == *mMatrixPtr );
		assert( mOptimizer.vector() == mVector );
		assert( mVector.rows() == mMatrixPtr->rows() );
		assert( mMatrixPtr->cols() == matVecPairs.front().first.cols() );
	}
}

//Shared-ptr-constructor
template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting>::TemplatePolyhedronT( const std::shared_ptr<const matrix_t<Number>>& matPtr, const vector_t<Number>& vec, const bool isNonRedundant )
	: mMatrixPtr( std::shared_ptr<const matrix_t<Number>>( matPtr ) )
	, mVector( vec )
	, mOptimizer( Optimizer<Number>( *matPtr, vec ) )
	, mNonRedundant( isNonRedundant ) {
	//TODO: get redundancy status somehow else
	//reduceRepresentation();
	//assert(this->rGetMatrixPtr() == matPtr);
	assert( mOptimizer.matrix() == *matPtr );
	assert( mOptimizer.vector() == vec );
	assert( vec.rows() == mMatrixPtr->rows() );
}

//Copy constructor
template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting>::TemplatePolyhedronT( const TemplatePolyhedronT<Number, Converter, Setting>& orig )
	: GeometricObjectBase( orig.getEmptyFlag() )
	, mMatrixPtr( orig.rGetMatrixPtr() )
	, mVector( orig.vector() )
	, mNonRedundant( orig.getNonRedundant() ) {
	if ( orig.rGetMatrixPtr() == nullptr ) {
		mOptimizer = Optimizer<Number>();
		mOptimizer.setVector( orig.vector() );
	} else {
		mOptimizer = Optimizer<Number>( *orig.rGetMatrixPtr(), orig.vector() );
		assert( mVector.rows() == mMatrixPtr->rows() );
	}
	assert( mMatrixPtr == orig.rGetMatrixPtr() );
}

//Move constructor
template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting>::TemplatePolyhedronT( TemplatePolyhedronT<Number, Converter, Setting>&& orig )
	: GeometricObjectBase( orig.getEmptyFlag() )
	, mMatrixPtr( std::move( orig.rGetMatrixPtr() ) )
	, mVector( std::move( orig.vector() ) )
	, mNonRedundant( std::move( orig.getNonRedundant() ) ) {
	if ( orig.rGetMatrixPtr() == nullptr ) {
		mOptimizer = Optimizer<Number>();
		mOptimizer.setVector( orig.vector() );
	} else {
		mOptimizer = Optimizer<Number>( *orig.rGetMatrixPtr(), orig.vector() );
		assert( mVector.rows() == mMatrixPtr->rows() );
	}
	orig.clear();
	//assert(mVector.rows() == mMatrixPtr->rows());
	assert( orig.rGetMatrixPtr() == nullptr );
}

//Settings constructor
template <typename Number, typename Converter, typename Setting>
template <typename SettingRhs, carl::DisableIf<std::is_same<Setting, SettingRhs>>>
TemplatePolyhedronT<Number, Converter, Setting>::TemplatePolyhedronT( const TemplatePolyhedronT<Number, Converter, SettingRhs>& orig )
	: GeometricObjectBase( orig.getEmptyFlag() )
	, mMatrixPtr( orig.rGetMatrixPtr() )
	, mVector( orig.vector() )
	, mNonRedundant( orig.getNonRedundant() ) {
	if ( orig.rGetMatrixPtr() == nullptr ) {
		mOptimizer = Optimizer<Number>();
		mOptimizer.setVector( orig.vector() );
	} else {
		mOptimizer = Optimizer<Number>( *orig.rGetMatrixPtr(), orig.vector() );
		assert( mVector.rows() == mMatrixPtr->rows() );
	}
	//assert(mVector.rows() == mMatrixPtr->rows());
	assert( mMatrixPtr == orig.rGetMatrixPtr() );
}

//////// GeometricObject Interface ////////

template <typename Number, typename Converter, typename Setting>
bool TemplatePolyhedronT<Number, Converter, Setting>::empty() const {
	//Quick checks
	if ( mMatrixPtr == nullptr ) return true;

	//Check emptiness cache
	if ( mEmptyState != SETSTATE::UNKNOWN ) return ( mEmptyState == SETSTATE::EMPTY );

	//Linear time quick checks:
	//If all coeffs negative -> all directions point towards origin -> unbounded polyhedron infeasible therefore empty
	//If all coeffs positive -> all directions point away from origin -> bounded polyhedron not empty
	bool allNegative = true;
	bool allPositive = true;
	for ( int i = 0; i < mVector.rows(); i++ ) {
		if ( mVector( i ) < 0 ) {
			allPositive = false;
		} else if ( mVector( i ) > 0 ) {
			allNegative = false;
		}
	}
	if ( allPositive ) return false;
	if ( allNegative ) return true;

	//If no quick check triggered: Solve LP and cache result
	//std::cout << "TemplatePolyhedron::empty, mOptimizer mat: \n" << mOptimizer.matrix() << "mOptimizer vec: \n" << mOptimizer.vector() << std::endl;
	mEmptyState = !mOptimizer.checkConsistency() ? SETSTATE::EMPTY : SETSTATE::NONEMPTY;
	//std::cout << "TemplatePolyhedron::empty, is empty? " << (mEmptyState == SETSTATE::EMPTY) << std::endl;
	TRACE( "hypro.representations.TPolytope", "Optimizer result: " << mEmptyState );
	return ( mEmptyState == SETSTATE::EMPTY );
}

//Copy from HPoly - is also obsolete
template <typename Number, typename Converter, typename Setting>
Number TemplatePolyhedronT<Number, Converter, Setting>::supremum() const {
	Number max = 0;
	if ( this->empty() ) return max;
	auto tmp = this->vertices();
	//assert(!this->empty());
	//assert(!this->vertices().empty());
	for ( const auto& point : this->vertices() ) {
		Number inftyNorm = Point<Number>::inftyNorm( point );
		max = max > inftyNorm ? max : inftyNorm;
	}
	return max;
}

//The (slow) HPoly way
template <typename Number, typename Converter, typename Setting>
std::vector<Point<Number>> TemplatePolyhedronT<Number, Converter, Setting>::vertices( const matrix_t<Number>& ) const {
	//std::cout << "TPoly:vertices!" << std::endl;
	if ( this->empty() ) {
		//std::cout << "TPoly:vertices, this was empty!" << std::endl;
		return std::vector<Point<Number>>();
	}
	typename Converter::HPolytope tmp( this->matrix(), this->vector() );
	//std::cout << "TPoly:vertices, vertices: " << tmp << std::endl;
	return tmp.vertices();
}

template <typename Number, typename Converter, typename Setting>
EvaluationResult<Number> TemplatePolyhedronT<Number, Converter, Setting>::evaluate( const vector_t<Number>& _direction, bool useExact ) const {
	if ( this->empty() ) return EvaluationResult<Number>( Number( 0 ), SOLUTION::INFEAS );
	assert( _direction.rows() == mMatrixPtr->cols() );
	//Quick check: If direction is a part of the template, then just return offset
	if ( mNonRedundant ) {
		for ( int i = 0; i < mMatrixPtr->rows(); ++i ) {
			//TODO: linear dependent better
			//if(vector_t<Number>(mMatrixPtr->row(i)) == _direction){
			if ( mMatrixPtr->row( i ).transpose().isApprox( _direction ) ) {
				COUNT( "Evaluate: Single Evaluation avoided" );
				return EvaluationResult<Number>( mVector( i ), SOLUTION::FEAS );
			}
		}
	}
	COUNT( "Evaluate: Evaluate calls" );
	return mOptimizer.evaluate( _direction, useExact );
}

template <typename Number, typename Converter, typename Setting>
std::vector<EvaluationResult<Number>> TemplatePolyhedronT<Number, Converter, Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
	//std::cout << "TPoly::multiEvaluate, this: \n" << *mMatrixPtr << " vec: \n" << mVector << " directions: \n" << _directions << std::endl;
	if ( this->empty() ) return std::vector<EvaluationResult<Number>>();
	assert( _directions.cols() == mMatrixPtr->cols() );
	std::vector<EvaluationResult<Number>> res;
	if ( mNonRedundant ) {
		//std::cout << "TPoly::multiEvaluate, non redundant" << std::endl;
		for ( int i = 0; i < _directions.rows(); ++i ) {
			//Quick check: If direction is a part of the template, then just return offset
			bool found = false;
			for ( int j = 0; j < mMatrixPtr->rows(); ++j ) {
				//TODO: linear dependent better
				if ( !found && mMatrixPtr->row( j ).isApprox( _directions.row( i ) ) ) {
					COUNT( "MultiEvaluate: Single Evaluation avoided" );
					res.emplace_back( EvaluationResult<Number>( mVector( j ), SOLUTION::FEAS ) );
					found = true;
					break;
				}
			}
			if ( !found ) {
				COUNT( "MultiEvaluate: Evaluate calls" );
				res.emplace_back( mOptimizer.evaluate( _directions.row( i ), useExact ) );
			}
		}
	} else {
		//std::cout << "TPoly::multiEvaluate, redundant" << std::endl;
		for ( int i = 0; i < _directions.rows(); ++i ) {
			COUNT( "MultiEvaluate: Evaluate calls" );
			res.emplace_back( mOptimizer.evaluate( _directions.row( i ), useExact ) );
		}
	}
	//std::cout << "TPoly::multiEvaluate, res: {" << std::endl;
	//for(auto& r : res){
	//	std::cout << r << ",";
	//}
	//std::cout << "}" << std::endl;
	return res;
}

template <typename Number, typename Converter, typename Setting>
std::size_t TemplatePolyhedronT<Number, Converter, Setting>::dimension() const {
	if ( mMatrixPtr == nullptr ) return std::size_t( 0 );
	return mMatrixPtr->cols();
}

template <typename Number, typename Converter, typename Setting>
void TemplatePolyhedronT<Number, Converter, Setting>::removeRedundancy() {
	//HPoly method: optimize, then get redundant constraints, then remove the redundant constraints
	//Time: LP + LP + linear
	//std::cout << "TemplatePolyhedron::removeRedundancy, mNonRedundant? " << mNonRedundant << std::endl;
	if ( !mNonRedundant && !empty() ) {
		std::vector<std::size_t> redundant = mOptimizer.redundantConstraints();
		std::sort( redundant.begin(), redundant.end() );
		//std::cout << "TemplatePolyhedron::removeRedundancy, redundant indices: {";
		//for(const auto& r : redundant){
		//	//std::cout << r << ",";
		//}
		//std::cout << "}" << std::endl;
		if ( !redundant.empty() ) {
			matrix_t<Number> nonRedundantMatrix = matrix_t<Number>::Zero( mMatrixPtr->rows() - redundant.size(), mMatrixPtr->cols() );
			vector_t<Number> nonRedundantVector = vector_t<Number>::Zero( mMatrixPtr->rows() - redundant.size() );
			int topUnfilledRow = 0;
			auto it = redundant.begin();
			for ( int i = 0; i < mMatrixPtr->rows(); ++i ) {
				//std::cout << "TemplatePolyhedron::removeRedundancy, currentRow: " << i << " redundant.s: " << redundant.size() << " lastUnfilledRow: " << topUnfilledRow << std::endl;
				//std::cout << "TemplatePolyhedron::removeRedundancy, nonRedundantMatrix: \n " << nonRedundantMatrix << "nonRedundantVector: \n" << nonRedundantVector << std::endl;
				if ( it == redundant.end() || std::size_t( i ) != *it ) {
					//std::cout << "TemplatePolyhedron::removeRedundancy, i: " << i << " != it: " << *it << ", add row!" << std::endl;
					nonRedundantMatrix.row( topUnfilledRow ) = mMatrixPtr->row( i );
					nonRedundantVector( topUnfilledRow ) = mVector( i );
					topUnfilledRow++;
				} else {
					//std::cout << "TemplatePolyhedron::removeRedundancy, i: " << i << " == it: " << *it << ", pop back!" << std::endl;
					++it;
				}
			}
			assert( it == redundant.end() );
			mMatrixPtr = std::move( std::make_shared<matrix_t<Number>>( nonRedundantMatrix ) );
			mVector = std::move( nonRedundantVector );
			mOptimizer.setMatrix( *mMatrixPtr );
			mOptimizer.setVector( mVector );
		}
		mNonRedundant = true;
		//Emptiness should stay the same
	}
	//If a plane has the same offset as another plane & normal is linearly dependent -> plane redundant
	//Time:
	//If a plane is only a tangent plane to a point, then it is redundant either
	//Assume polytope is convex and bounded: For each plane, shift it only a bit away, if point defined by intersection of three planes still inside, then plane redundant
	//But there are still redundant planes left
}

template <typename Number, typename Converter, typename Setting>
std::size_t TemplatePolyhedronT<Number, Converter, Setting>::size() const {
	return sizeof( *mMatrixPtr ) + sizeof( mVector );
}

template <typename Number, typename Converter, typename Setting>
const TemplatePolyhedronT<Number, Converter, Setting>& TemplatePolyhedronT<Number, Converter, Setting>::reduceNumberRepresentation() {
	return this;
}

template <typename Number, typename Converter, typename Setting>
std::pair<bool, bool> TemplatePolyhedronT<Number, Converter, Setting>::checkFullInsideFullOutside( const vector_t<Number>& normal, const Number& offset ) const {
	//Quick check:
	//If all coefficients of directions similar to hspace normal smaller than hspace offset, then current obj completely in hspace
	//If all coefficients of directions not similar to hspace normal bigger than hspace offset, then current obj completely not in hspace
	bool fullyInside = true;
	bool fullyOutside = true;
	for ( int i = 0; i < mMatrixPtr->rows(); ++i ) {
		if ( normal.dot( mMatrixPtr->row( i ) ) > 0 ) {
			if ( mVector( i ) > offset ) {
				fullyInside = false;
			}
		} else {
			if ( -mVector( i ) <= offset ) {
				fullyOutside = false;
			}
		}
		if ( !fullyInside && !fullyOutside ) break;
	}
	assert( !( fullyInside && fullyOutside ) );
	return std::make_pair( fullyInside, fullyOutside );
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, TemplatePolyhedronT<Number, Converter, Setting>> TemplatePolyhedronT<Number, Converter, Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
	if ( empty() ) {
		return std::make_pair( CONTAINMENT::NO, *this );
	}

	//Quick check NOTE: only sound on bounded tpoly
	auto fullInfullOut = checkFullInsideFullOutside( rhs.normal(), rhs.offset() );
	if ( fullInfullOut.first )
		return std::make_pair( CONTAINMENT::FULL, *this );
	if ( fullInfullOut.second )
		return std::make_pair( CONTAINMENT::NO, *this );

	//Expensive part
	auto tmp = this->intersectHalfspace( rhs );
	if ( tmp.empty() ) {
		return std::make_pair( CONTAINMENT::NO, std::move( tmp ) );
	} else {
		return std::make_pair( CONTAINMENT::PARTIAL, std::move( tmp ) );
	}
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, TemplatePolyhedronT<Number, Converter, Setting>> TemplatePolyhedronT<Number, Converter, Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	//std::cout << "TemplatePolyhedron::satisfiesHalfspaces, mEmptyState: " << mEmptyState << std::endl;
	//std::cout << "TemplatePolyhedron::satisfiesHalfspaces, this: \n" << *mMatrixPtr << "this vec: \n" << mVector << "_mat: \n" << _mat << "_vec: \n" << _vec << std::endl;

	if ( this->empty() ) {
		//std::cout << "TemplatePolyhedron::satisfiesHalfspaces, empty" << std::endl;
		return std::make_pair( CONTAINMENT::NO, *this );
	}
	if ( _mat.rows() == 0 ) {
		//std::cout << "TemplatePolyhedron::satisfiesHalfspaces, no mat" << std::endl;
		return std::make_pair( CONTAINMENT::FULL, *this );
	}

	//Not so quick check:
	bool fullyInside = true;
	bool fullyOutside = true;
	for ( int i = 0; i < _mat.rows(); ++i ) {
		auto fullInfullOut = checkFullInsideFullOutside( _mat.row( i ), _vec( i ) );
		if ( !fullInfullOut.first ) {
			//std::cout << "TemplatePolyhedron::satisfiesHalfspaces, row " << i << " not full in" << std::endl;
			fullyInside = false;
		}
		if ( !fullInfullOut.second ) {
			//std::cout << "TemplatePolyhedron::satisfiesHalfspaces, row " << i << " not full out" << std::endl;
			fullyOutside = false;
		}
		if ( !fullyInside && !fullyOutside ) {
			break;
		}
	}

	assert( !( fullyInside && fullyOutside ) );
	if ( fullyInside ) {
		//std::cout << "TemplatePolyhedron::satisfiesHalfspaces, fullyInside" << std::endl;
		return std::make_pair( CONTAINMENT::FULL, *this );
	}
	if ( fullyOutside ) {
		//std::cout << "TemplatePolyhedron::satisfiesHalfspaces, fullyOutside" << std::endl;
		return std::make_pair( CONTAINMENT::NO, *this );
	}

	//Even more expensive part
	//return std::make_pair(CONTAINMENT::PARTIAL, this->intersectHalfspaces(_mat,_vec));
	//std::cout << "TemplatePolyhedron::satisfiesHalfspaces, intersectHalfspaces" << std::endl;
	auto tmp = this->intersectHalfspaces( _mat, _vec );
	if ( tmp.empty() ) {
		//std::cout << "TemplatePolyhedron::satisfiesHalfspaces, tmp empty" << std::endl;
		return std::make_pair( CONTAINMENT::NO, std::move( tmp ) );
	} else {
		//std::cout << "TemplatePolyhedron::satisfiesHalfspaces, tmp partial" << std::endl;
		return std::make_pair( CONTAINMENT::PARTIAL, std::move( tmp ) );
	}
}

//NOTE: This returns a different tpoly with different constraints
template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting> TemplatePolyhedronT<Number, Converter, Setting>::projectOn( const std::vector<std::size_t>& dimensions ) const {
	//std::cout << "TPoly::project, dimensions: " << dimensions[0] << ", " << dimensions[1] << std::endl;

	if ( dimensions.empty() ) {
		//std::cout << "TPoly::project, dimensions empty" << std::endl;
		return Empty();
	}
	if ( empty() ) {
		//std::cout << "TPoly::project, this empty" << *this << std::endl;
		return *this;
	}
	if ( dimensions.size() > this->dimension() ) {
		throw( std::invalid_argument( "TPoly::project, too many dimensions given" ) );
	}

	//NOTE: very costly as we convert to a VPoly, then back to a HPoly
	typename Converter::VPolytope tmp( this->matrix(), this->vector() );
	tmp = tmp.projectOn( dimensions );
	auto tmpTPoly = Converter::toTemplatePolyhedron( tmp );
	//std::cout << "TPoly::project, tmpTPoly is: " << tmpTPoly << std::endl;
	return tmpTPoly;
}

template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting> TemplatePolyhedronT<Number, Converter, Setting>::linearTransformation( const matrix_t<Number>& A ) const {
	//Other Idea: Effectively, a linear transformation is only a scaling of the coeff vector, but how to find scaling factors?

	//std::cout << "TemplatePolyhedron::linearTransformation, this: " << *this << std::endl;
	//std::cout << "TemplatePolyhedron::linearTransformation, A: \n" << A << std::endl;

	assert( mMatrixPtr != nullptr );
	assert( A.cols() == (int)dimension() );
	assert( A.cols() == mMatrixPtr->cols() );
	assert( A.rows() == mMatrixPtr->cols() );
	if ( A.isApprox( matrix_t<Number>::Identity( dimension(), dimension() ) ) ) {
		return *this;
	}

	//Evaluate in the transformed directions
	matrix_t<Number> dirsRotatedInverse = ( *mMatrixPtr ) * A;
	//std::cout << "TemplatePolyhedron::linearTransformation, dirsRotatedInverse: \n" << dirsRotatedInverse << std::endl;
	assert( dirsRotatedInverse.rows() == mMatrixPtr->rows() );
	assert( dirsRotatedInverse.cols() == mMatrixPtr->cols() );
	for ( int i = 0; i < dirsRotatedInverse.rows(); i++ ) {
		COUNT( "Affine Transformation Evaluate" );
	}
	std::vector<EvaluationResult<Number>> evalInInvRotatedDirs = multiEvaluate( dirsRotatedInverse, false );
	//std::vector<EvaluationResult<Number>> evalInInvRotatedDirs = multiEvaluate(dirsRotatedInverse, true);
	//std::cout << "TemplatePolyhedron::linearTransformation, evalInInvRotatedDirs: {";
	//for(auto& e : evalInInvRotatedDirs){
	//	//std::cout << e << ", ";
	//}
	//std::cout << "}" << std::endl;
	vector_t<Number> newVector = vector_t<Number>::Zero( mVector.rows() );
	//std::cout << "TemplatePolyhedron::linearTransformation, newVector before filling: \n" << newVector << std::endl;
	assert( evalInInvRotatedDirs.size() == std::size_t( newVector.rows() ) );
	assert( evalInInvRotatedDirs.size() == std::size_t( mVector.rows() ) );
	for ( std::size_t i = 0; i < evalInInvRotatedDirs.size(); ++i ) {
		assert( evalInInvRotatedDirs.at( i ).errorCode == SOLUTION::FEAS );
		newVector( i ) = evalInInvRotatedDirs.at( i ).supportValue;
	}
	//std::cout << "TemplatePolyhedron::linearTransformation, newVector after filling: \n" << newVector << std::endl;
	return TemplatePolyhedronT<Number, Converter, Setting>( mMatrixPtr, newVector, getNonRedundant() );
}

template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting> TemplatePolyhedronT<Number, Converter, Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
	//std::cout << "TemplatePolyhedron::affineTransformation, this:" << *this << std::endl;
	//std::cout << "TemplatePolyhedron::affineTransformation, A: \n" << A << "b: \n" << b << std::endl;

	if ( empty() ) {
		return TemplatePolyhedronT<Number, Converter, Setting>::Empty( dimension() );
	}
	assert( A.rows() == b.rows() );
	assert( A.cols() == (int)dimension() );

	//std::cout << "TemplatePolyhedron::affineTransformation, use linearTransformation" << std::endl;
	TemplatePolyhedronT<Number, Converter, Setting> res = linearTransformation( A );

	//Translate res
	res.setVector( res.vector() + vector_t<Number>( ( *(mMatrixPtr)*b ) ) );

	return res;
}

template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting> TemplatePolyhedronT<Number, Converter, Setting>::minkowskiSum( const TemplatePolyhedronT<Number, Converter, Setting>& rhs ) const {
	//Emptiness check is very costly and usually does not happen during reachability computation
	if ( empty() ) return rhs;
	if ( rhs.empty() ) return *this;

	//In case rhs has a different matrix than this, overapproximate the minkowskisum of both via template directions
	//Costly, but shouldn't happen too often
	assert( mMatrixPtr->cols() == rhs.matrix().cols() );
	if ( mMatrixPtr->rows() != rhs.matrix().rows() || !mMatrixPtr->isApprox( rhs.matrix() ) ) {
		auto rhsHPoly = typename Converter::HPolytope( rhs.matrix(), rhs.vector() );
		auto thisHPoly = typename Converter::HPolytope( this->matrix(), this->vector() );
		auto summed = thisHPoly.minkowskiSum( rhsHPoly );
		//auto evalInDirs = summed.multiEvaluate(combineRows(computeTemplate<Number>(dimension(), 8)));
		for ( int i = 0; i < mMatrixPtr->rows(); i++ ) {
			COUNT( "Minkowski Sum Evaluate" );
		}
		auto evalInDirs = summed.multiEvaluate( *mMatrixPtr, false );
		vector_t<Number> newVector = vector_t<Number>::Zero( evalInDirs.size() );
		for ( std::size_t i = 0; i < evalInDirs.size(); ++i ) {
			if ( evalInDirs.at( i ).errorCode == SOLUTION::FEAS ) {
				newVector( i ) = evalInDirs.at( i ).supportValue;
			} else {
				//INFTY should not be possible since minkowskiSum of convex objects is also convex and therefore evaluable in all directions.
				//An infeasible set could occur from minkowskiSum when both sets are empty, in which case we just return Empty()
				assert( evalInDirs.at( i ).errorCode == SOLUTION::INFEAS );
				return TemplatePolyhedronT<Number, Converter, Setting>::Empty( dimension() );
			}
		}
		return TemplatePolyhedronT<Number, Converter, Setting>( mMatrixPtr, newVector, getNonRedundant() );
	}

	//This only works if both TPolys have the same; if MinkowskiSum with a box, use smth else
	vector_t<Number> newVector = vector_t<Number>::Zero( mMatrixPtr->rows() );
	for ( int i = 0; i < mMatrixPtr->rows(); i++ ) {
		newVector( i ) = this->vector()( i ) + rhs.vector()( i );
	}
	return TemplatePolyhedronT<Number, Converter, Setting>( mMatrixPtr, newVector, getNonRedundant() );
}

template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting> TemplatePolyhedronT<Number, Converter, Setting>::intersect( const TemplatePolyhedronT<Number, Converter, Setting>& rhs ) const {
	//assert(this->matrix() == rhs.matrix());
	if ( rhs.empty() ) {
		return *this;
	}
	if ( this->empty() ) return rhs;
	vector_t<Number> res = mVector;
	for ( int i = 0; i < mMatrixPtr->rows(); ++i ) {
		if ( rhs.vector()( i ) < res( i ) ) {
			res( i ) = rhs.vector()( i );
		}
	}
	return TemplatePolyhedronT<Number, Converter, Setting>( mMatrixPtr, res, getNonRedundant() );
	//Since intersecting with an empty / unfeasible Tpoly always results in smth unfeasible,
	//check emptiness only once after the computation instead of two times before the computation
	//auto tmp = TemplatePolyhedronT<Number,Converter,Setting>(*mMatrixPtr, res);
	//if(tmp.empty()){
	//	if(this->empty()) //		tmp = TemplatePolyhedronT<Number,Converter,Setting>();
	//		tmp = *this;
	//	}
	//}
	//return tmp;
}

//TODO: Is there a cheaper way?
template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting> TemplatePolyhedronT<Number, Converter, Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {
	//Quick check whether fully inside halfspace or fully outside
	auto fullInfullOut = checkFullInsideFullOutside( hspace.normal(), hspace.offset() );
	assert( !( fullInfullOut.first && fullInfullOut.second ) );
	if ( fullInfullOut.first ) return *this;

	//Check whether halfspace is not already in template, if it is, take the smaller of both values
	for ( int i = 0; i < mMatrixPtr->rows(); ++i ) {
		if ( mMatrixPtr->row( i ).transpose() == hspace.normal() ) {
			if ( mVector( i ) <= hspace.offset() ) {
				return *this;
			} else {
				vector_t<Number> newVec = mVector;
				newVec( i ) = hspace.offset();
				return TemplatePolyhedronT<Number, Converter, Setting>( mMatrixPtr, newVec, getNonRedundant() );
			}
		}
	}

	//If partially inside halfspace - costly
	assert( hspace.normal().rows() == mMatrixPtr->cols() );
	matrix_t<Number> mat = hspace.normal().transpose();
	vector_t<Number> vec = vector_t<Number>::Zero( 1 );
	vec( 0 ) = hspace.offset();
	return intersectHalfspaces( mat, vec );
}

template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting> TemplatePolyhedronT<Number, Converter, Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	//std::cout << "TemplatePolyhedron::intersectHalfspaces, this: " << *this << "_mat: \n" << _mat << "_vec: \n" << _vec << std::endl;
	COUNT( "IntersectHalfspaces" );

	//Emptiness check
	if ( this->empty() ) return *this;

	//Assume that this is currently non redundant (which should be the case since removeRedundancy() is used in most settings)
	bool foundAll = true;
	matrix_t<Number> extendedMatrix = *mMatrixPtr;
	vector_t<Number> extendedVector = mVector;
	//vector_t<Number> resultVec = vector_t<Number>::Zero(mVector.rows());
	vector_t<Number> resultVec = mVector;
	std::vector<int> alreadyDone;
	for ( int i = 0; i < _mat.rows(); ++i ) {
		bool found = false;
		for ( int j = 0; j < mMatrixPtr->rows(); ++j ) {
			if ( _mat.row( i ) == mMatrixPtr->row( j ) ) {
				//If constraint is already in template, take the smaller offset value
				//std::cout << "TemplatePolyhedron::intersectHalfspaces, _vec(i): " << _vec(i) << " < " << mVector(j) << "? " << (_vec(i) < mVector(j)) << std::endl;
				COUNT( "IntersectHalfspaces: Single evaluation avoided" );
				resultVec( j ) = _vec( i ) < mVector( j ) ? _vec( i ) : mVector( j );
				alreadyDone.emplace_back( j );
				found = true;
				break;
			}
		}
		if ( !found ) {
			//If constraint was not already in template, put it into extendedMatrix
			foundAll = false;
			extendedMatrix.conservativeResize( extendedMatrix.rows() + 1, extendedMatrix.cols() );
			extendedMatrix.row( extendedMatrix.rows() - 1 ) = _mat.row( i );
			extendedVector.conservativeResize( extendedVector.rows() + 1 );
			extendedVector( extendedVector.rows() - 1 ) = _vec( i );
			//std::cout << "TemplatePolyhedron::intersectHalfspaces, row has not been found, add row! extendedMatrix: \n" << extendedMatrix << " extendedVector: \n" << extendedVector << std::endl;
		}
	}
	//std::cout << "TemplatePolyhedron::intersectHalfspaces, foundAll: " << foundAll << std::endl; //" _mat: \n" << _mat << "_vec: \n" << _vec << std::endl;
	if ( foundAll && alreadyDone.size() > 0 ) {
		//If all constraints in _mat were found, we can safely return the result
		COUNT( "IntersectHalfspaces: found all" );
		return TemplatePolyhedronT<Number, Converter, Setting>( mMatrixPtr, resultVec, getNonRedundant() );
		//auto tmp = TemplatePolyhedronT<Number,Converter,Setting>(mMatrixPtr,resultVec);
		//std::cout << "TemplatePolyhedron::intersectHalfspaces, foundAll was true! returning: " << tmp << std::endl;
		//return tmp;
	}

	//Else, make a new TPoly and evaluate into all non found directions and put into resultVec
	auto itDone = alreadyDone.begin();
	//std::cout << "TemplatePolyhedron::intersectHalfspaces, alreadyDone: {";
	//for(auto d : alreadyDone){
	//	//std::cout << d << ",";
	//}
	//std::cout << "}" << std::endl;
	assert( extendedMatrix.cols() == mMatrixPtr->cols() );
	assert( extendedMatrix.rows() == extendedVector.rows() );
	TemplatePolyhedronT<Number, Converter, Setting> extendedTPoly( extendedMatrix, extendedVector );
	//std::cout << "TemplatePolyhedron::intersectHalfspaces, extendedTPoly before: " << extendedTPoly << std::endl;
	extendedTPoly.removeRedundancy();
	//std::cout << "TemplatePolyhedron::intersectHalfspaces, extendedTPoly after: " << extendedTPoly << std::endl;
	for ( int j = 0; j < mMatrixPtr->rows(); ++j ) {
		if ( itDone == alreadyDone.end() || j != *itDone ) {
			COUNT( "Intersect Halfspaces Evaluate" );
			auto res = extendedTPoly.evaluate( mMatrixPtr->row( j ), false );
			if ( res.errorCode == SOLUTION::FEAS ) {
				resultVec( j ) = res.supportValue;
			} else {
				assert( res.errorCode == SOLUTION::INFEAS );
				return TemplatePolyhedronT<Number, Converter, Setting>::Empty( dimension() );
			}
			if ( itDone != alreadyDone.end() ) {
				++itDone;
			}
		}
	}
	COUNT( "IntersectHalfspaces: Needed evaluation" );
	return TemplatePolyhedronT<Number, Converter, Setting>( mMatrixPtr, resultVec, getNonRedundant() );
}

template <typename Number, typename Converter, typename Setting>
bool TemplatePolyhedronT<Number, Converter, Setting>::contains( const Point<Number>& point ) const {
	if ( this->empty() ) return false;
	if ( point.dimension() != mMatrixPtr->cols() ) {
		throw std::invalid_argument( "Template polyhedron cannot contain point of different dimension." );
	}
	for ( int i = 0; i < mMatrixPtr->rows(); ++i ) {
		if ( !carl::AlmostEqual2sComplement( mMatrixPtr->row( i ).dot( point.rawCoordinates() ), mVector( i ), 128 ) && mMatrixPtr->row( i ).dot( point.rawCoordinates() ) > mVector( i ) ) {
			return false;
		}
	}
	return true;
}

template <typename Number, typename Converter, typename Setting>
bool TemplatePolyhedronT<Number, Converter, Setting>::contains( const TemplatePolyhedronT<Number, Converter, Setting>& rhs ) const {
	if ( rhs.dimension() != std::size_t( mMatrixPtr->cols() ) ) {
		throw std::invalid_argument( "Template polyhedron cannot contain another template polyhedron of different dimension." );
	}
	if ( this->empty() ) return false;
	if ( rhs.empty() ) return true;
	if ( !mMatrixPtr->isApprox( rhs.matrix() ) ) {
		COUNT( "Containment overapprox" );
		//std::cout << "this matrix: \n" << this->matrix() << "rhs matrix: \n" << rhs.matrix() << std::endl;
		auto overapproxedRhs = this->overapproximate( rhs.matrix() );
		for ( int i = 0; i < mVector.rows(); i++ ) {
			if ( mVector( i ) < overapproxedRhs.vector()( i ) ) return false;
		}
	} else {
		for ( int i = 0; i < mVector.rows(); i++ ) {
			if ( mVector( i ) < rhs.vector()( i ) ) return false;
		}
	}
	return true;
}

template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting> TemplatePolyhedronT<Number, Converter, Setting>::unite( const TemplatePolyhedronT<Number, Converter, Setting>& rhs ) const {
	//Since uniting with a empty / unfeasible TPoly can result in a feasible TPoly, check beforehand whether one of the arguments is empty.
	//TODO: What about union of two not connected sets?
	if ( this->empty() ) return rhs;
	if ( rhs.empty() ) return *this;
	assert( *mMatrixPtr == rhs.matrix() );
	vector_t<Number> res = mVector;
	for ( int i = 0; i < mMatrixPtr->rows(); ++i ) {
		if ( rhs.vector()( i ) > res( i ) ) {
			res( i ) = rhs.vector()( i );
		}
	}
	return TemplatePolyhedronT<Number, Converter, Setting>( mMatrixPtr, res, getNonRedundant() );
}

template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting> TemplatePolyhedronT<Number, Converter, Setting>::unite( const std::vector<TemplatePolyhedronT<Number, Converter, Setting>>& templatePolyhedrones ) {
#ifndef NDEBUG
	//All tpolys we unite with must have the same matrices
	for ( const auto& elem : templatePolyhedrones ) {
		assert( this->matrix().isApprox( elem.matrix() ) );
	}
#endif
	//Since uniting with a empty / unfeasible TPoly can result in a feasible TPoly, check for each TPoly beforehand whether it is empty, and if it is, ignore it.
	vector_t<Number> res( mMatrixPtr->rows() );
	if ( this->empty() ) {
		res = -10000000 * vector_t<Number>::Ones( mMatrixPtr->rows() );
	} else {
		res = mVector;
	}
	for ( int i = 0; i < mMatrixPtr->rows(); ++i ) {
		for ( const auto& tpoly : templatePolyhedrones ) {
			if ( !tpoly.empty() ) {
				if ( tpoly.vector()( i ) > res( i ) ) {
					res( i ) = tpoly.vector()( i );
				}
			}
		}
	}
	return TemplatePolyhedronT<Number, Converter, Setting>( mMatrixPtr, res, getNonRedundant() );
}

template <typename Number, typename Converter, typename Setting>
void TemplatePolyhedronT<Number, Converter, Setting>::reduceRepresentation() {
	//Check if doubles already removed
	if ( mNonRedundant ) return;

	//Make a vector of all row indices
	std::vector<int> importantRows;
	for ( int i = 0; i < mMatrixPtr->rows(); ++i ) {
		importantRows.push_back( i );
	}

	//Remove all doubled normal vectors
	for ( unsigned rowI = 0; rowI < importantRows.size(); ++rowI ) {
		for ( unsigned toCheck = 0; toCheck < importantRows.size(); ++toCheck ) {
			if ( rowI != toCheck && mMatrixPtr->row( rowI ).isApprox( mMatrixPtr->row( toCheck ) ) ) {
				importantRows[toCheck] = importantRows[rowI];
			}
		}
	}
	std::set<int> importantRowsWithoutDoubles( importantRows.begin(), importantRows.end() );
	importantRows.clear();
	importantRows = std::vector<int>( importantRowsWithoutDoubles.begin(), importantRowsWithoutDoubles.end() );

	//Create reduced matrix from the rest
	matrix_t<Number> reducedMat = matrix_t<Number>::Zero( importantRows.size(), dimension() );
	for ( int i = 0; i < (int)importantRows.size(); ++i ) {
		reducedMat.row( i ) = mMatrixPtr->row( importantRows[i] );
	}

	//Evaluate into only the needed directions
	//TODO: instead of overapprox, use checkFullInFullOut to find out which of the offset of the doubled vector should be used
	COUNT( "Reduce representation overapprox" );
	auto resPoly = overapproximate( reducedMat );
	mMatrixPtr = std::make_shared<matrix_t<Number>>( std::move( resPoly.matrix() ) );
	mVector = std::move( resPoly.vector() );
	mOptimizer.setMatrix( *mMatrixPtr );
	mOptimizer.setVector( mVector );
	//mEmptyState = SETSTATE::UNKNOWN;
	mNonRedundant = true;
}

template <typename Number, typename Converter, typename Setting>
void TemplatePolyhedronT<Number, Converter, Setting>::clear() {
	mMatrixPtr = nullptr;
	mVector = vector_t<Number>::Zero( 0 );
	mOptimizer.setMatrix( matrix_t<Number>::Zero( 1, 1 ) );
	mOptimizer.setVector( vector_t<Number>::Zero( 1 ) );
	mEmptyState = SETSTATE::UNKNOWN;
	mNonRedundant = false;
}

template <typename Number, typename Converter, typename Setting>
TemplatePolyhedronT<Number, Converter, Setting> TemplatePolyhedronT<Number, Converter, Setting>::overapproximate( const matrix_t<Number>& dirs ) const {
	if ( empty() ) return *this;
	//assert(isBounded());
	assert( dirs.cols() == mMatrixPtr->cols() );
	if ( dirs.rows() == mMatrixPtr->rows() && mMatrixPtr->isApprox( dirs ) ) {
		return *this;
	}
	for ( int i = 0; i < dirs.rows(); i++ ) {
		COUNT( "Overapprox Evaluate" );
	}
	auto evalRes = multiEvaluate( dirs, false );
	vector_t<Number> evalOffsets = vector_t<Number>::Zero( dirs.rows() );
	for ( std::size_t i = 0; i < evalRes.size(); ++i ) {
		//assert(evalRes[i].errorCode == SOLUTION::FEAS);
		//evalOffsets(i) = evalRes[i].supportValue;
		if ( evalRes[i].errorCode == SOLUTION::FEAS ) {
			evalOffsets( i ) = evalRes[i].supportValue;
		} else if ( evalRes[i].errorCode == SOLUTION::INFTY ) {
			//We bound unbounded template polyhedra with a high value
			//NOTE: is needed for Sankaranarayanan method
			evalOffsets( i ) = Setting::BOUNDING_VALUE;
		} else {
			std::cerr << "TPoly::overapproximate, evalRes was INFEAS" << std::endl;
			exit( 1 );
		}
	}
	return TemplatePolyhedronT<Number, Converter, Setting>( dirs, evalOffsets );
}

template <typename Number, typename Converter, typename Setting>
bool TemplatePolyhedronT<Number, Converter, Setting>::isBounded() const {
	//The empty set is bounded
	if ( empty() ) return true;
	//If less than dimension + 1 constraints, then unbounded
	if ( (unsigned)mMatrixPtr->rows() < dimension() + 1 ) return false;
	//std::cout << "TPoly::isBounded, expensive part" << std::endl;
	auto templateDirs = computeTemplate<Number>( mMatrixPtr->cols(), 4 );
	for ( std::size_t i = 0; i < templateDirs.size(); ++i ) {
		COUNT( "isBounded evaluate" );
		if ( evaluate( templateDirs.at( i ), false ).errorCode == SOLUTION::INFTY ) {
			return false;
		}
	}
	return true;
}

}  // namespace hypro
