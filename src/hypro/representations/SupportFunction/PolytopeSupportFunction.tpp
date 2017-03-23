/*
 * This file contains the basic implementation of support functions of polyhedra
 *(template polyhedra) and their
 *evaluation.
 * @file PolytopeSupportFunction.tpp
 *
 * @author Norman Hansen
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @version	2015-02-27
 */

#include "PolytopeSupportFunction.h"
//#define PPOLYTOPESUPPORTFUNCTION_VERBOSE

namespace hypro {

template <typename Number>
PolytopeSupportFunction<Number>::PolytopeSupportFunction( matrix_t<Number> constraints,
														  vector_t<Number> constraintConstants )
	: mConstraints( constraints ), mConstraintConstants( constraintConstants ), mOpt(constraints,constraintConstants), mDimension(mConstraints.cols()) {
	//this->removeRedundancy();
}

template <typename Number>
PolytopeSupportFunction<Number>::PolytopeSupportFunction( const std::vector<Halfspace<Number>> &_planes ) {
	assert( !_planes.empty() );
	mConstraints = matrix_t<Number>( _planes.size(), _planes[0].dimension() );
	mConstraintConstants = vector_t<Number>( _planes.size() );
	mDimension = _planes[0].dimension();

	unsigned pos = 0;
	for ( const auto &plane : _planes ) {
		mConstraints.row( pos ) = plane.normal().transpose();
		mConstraintConstants( pos ) = plane.offset();
		++pos;
	}
	mOpt = Optimizer<Number>(mConstraints,mConstraintConstants);
	//this->removeRedundancy();
}

template<typename Number>
PolytopeSupportFunction<Number>::PolytopeSupportFunction( const std::vector<Point<Number>>& _points ) {
	//std::cout << __func__ << std::endl;
	if ( !_points.empty() ) {
		//std::cout << "Points not empty" << std::endl;
		mDimension = _points.begin()->dimension();
		//std::cout << "Space dimension is " << mDimension << std::endl;
		// check affine independence - verify object dimension.
		std::vector<vector_t<Number>> coordinates;
		for(const auto& vertex : _points){
			coordinates.emplace_back(vertex.rawCoordinates());
		}
		int effectiveDim = effectiveDimension(coordinates);
		//std::cout << "Effective dimension of the pointset: " << effectiveDim << std::endl;
		assert(effectiveDim >= 0);

		if ( unsigned(effectiveDim) < mDimension ) {
			//std::cout << "Compute oriented box." << std::endl;
			std::vector<Halfspace<Number>> boxConstraints = computeOrientedBox(_points);

			mConstraints = matrix_t<Number>(boxConstraints.size(), mDimension);
			mConstraintConstants = vector_t<Number>(boxConstraints.size());

			unsigned rowCnt = 0;
			for(const auto& constraint : boxConstraints){
				mConstraints.row(rowCnt) = constraint.normal();
				mConstraintConstants(rowCnt) = constraint.offset();
				++rowCnt;
			}
		} else {
			//std::cout << "Use convex hull algorithm." << std::endl;
			std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( _points ).first;

			mConstraints = matrix_t<Number>(facets.size(), mDimension);
			mConstraintConstants = vector_t<Number>(facets.size());

			unsigned rowCnt = 0;
			for ( auto &facet : facets ) {
				assert(facet->halfspace().contains(_points));
				mConstraints.row(rowCnt) = facet->halfspace().normal();
				mConstraintConstants(rowCnt) = facet->halfspace().offset();
				++rowCnt;
			}
			facets.clear();
		}
	}
	mOpt = Optimizer<Number>(mConstraints,mConstraintConstants);
}

template <typename Number>
PolytopeSupportFunction<Number>::PolytopeSupportFunction( const PolytopeSupportFunction<Number> &_origin )
	: mConstraints( _origin.constraints() ), mConstraintConstants( _origin.constants()), mOpt(mConstraints,mConstraintConstants), mDimension(mConstraints.cols() ) {
}

template <typename Number>
PolytopeSupportFunction<Number>::~PolytopeSupportFunction() {
}

template <typename Number>
PolytopeSupportFunction<Number>& PolytopeSupportFunction<Number>::operator=(const PolytopeSupportFunction<Number>& _orig){
	std::cout << __func__ << std::endl;
    this->mConstraints = _orig.mConstraints;
    this->mConstraintConstants = _orig.mConstraintConstants;
    this->mOpt = Optimizer<Number>(mConstraints,mConstraintConstants);
    this->mDimension = _orig.mDimension;
}

template <typename Number>
unsigned PolytopeSupportFunction<Number>::dimension() const {
	return mDimension;
}

template <typename Number>
SF_TYPE PolytopeSupportFunction<Number>::type() const {
	return SF_TYPE::POLY;
}

template <typename Number>
matrix_t<Number> PolytopeSupportFunction<Number>::constraints() const {
	return mConstraints;
}

template <typename Number>
vector_t<Number> PolytopeSupportFunction<Number>::constants() const {
	return mConstraintConstants;
}

template<typename Number>
std::vector<Point<Number>> PolytopeSupportFunction<Number>::vertices() const {
	typename std::vector<Point<Number>> vertices;
	if(mConstraints.rows() != 0) {
		unsigned dim = this->dimension();

		Permutator permutator(mConstraints.rows(), dim);
		std::vector<unsigned> permutation;
		while(!permutator.end()) {
			permutation = permutator();

			matrix_t<Number> A( dim, dim );
			vector_t<Number> b( dim );

			// set up linear problem
			unsigned pos = 0;
			for(auto planeIt = permutation.begin(); planeIt != permutation.end(); ++planeIt) {
				A.row(pos) = mConstraints.row(*planeIt);
				b(pos) = mConstraintConstants(*planeIt);
				++pos;
			}

			// solve
			Eigen::FullPivLU<matrix_t<Number>> lu_decomp( A );
			if ( lu_decomp.rank() < A.rows() ) {
				continue;
			}

			vector_t<Number> res = lu_decomp.solve( b );

			// Check if the computed vertex is a real vertex
			bool outside = false;
			for(unsigned planePos = 0; planePos < mConstraints.rows(); ++planePos) {
				bool skip = false;
				for(unsigned permPos = 0; permPos < permutation.size(); ++permPos) {
					// naturally the computed vertex satisfies the planes we used for its computation -> skip the plane
					if(planePos == permutation.at(permPos)) {
						skip = true;
						break;
					}
				}

				if(!skip) {
					// verify if the vertex is outside the current plane
					if( mConstraintConstants(planePos) - mConstraints.row(planePos).dot(res) < 0 ) {
						outside = true;
						break;
					}
				}
			}
			if(!outside) {
				// insert, if no duplicate
				Point<Number> tmp(res);
				if(std::find(vertices.begin(), vertices.end(), tmp) == vertices.end()) {
					vertices.push_back(tmp);
				}
			}
		}
	}
	return vertices;
}

template<typename Number>
Point<Number> PolytopeSupportFunction<Number>::supremumPoint() const {
	assert(!this->empty());
	EvaluationResult<Number> sup;
	sup.errorCode = SOLUTION::UNKNOWN;

	for(unsigned d = 0; d < mDimension; ++d){
		// evaluate in each main direction, positive and negative
		vector_t<Number> posDir = vector_t<Number>::Zero(mDimension);
		posDir(d) = 1;
		vector_t<Number> negDir = vector_t<Number>::Zero(mDimension);
		negDir(d) = -1;

		EvaluationResult<Number> positive = this->evaluate(posDir, false);
		EvaluationResult<Number> negative = this->evaluate(negDir, false);
		assert(positive.errorCode != SOLUTION::UNKNOWN);
		assert(negative.errorCode != SOLUTION::UNKNOWN);

		// empty object
		if(positive.errorCode == SOLUTION::INFEAS) {
			return Point<Number>::Zero(mDimension);
		}

		// init once
		if(sup.errorCode == SOLUTION::UNKNOWN){
			sup = positive;
		}

		if(positive.supportValue > negative.supportValue) {
			sup = sup.supportValue > positive.supportValue ? sup : positive;
		} else {
			sup = sup.supportValue > negative.supportValue ? sup : negative;
		}
	}
	return Point<Number>(sup.optimumValue);
}

template <typename Number>
EvaluationResult<Number> PolytopeSupportFunction<Number>::evaluate( const vector_t<Number> &l, bool useExact ) const {
	// catch half-space
	if(mConstraints.rows() == 1) {
		//std::cout << "only one constraint! -> we evaluate against a plane!" << std::endl;
		// TODO: extend check to linear dependence. Here temporarily sufficient as we will initialize and evaluate with the plane normals, which should be the same vectors.
		if(l == vector_t<Number>(mConstraints.row(0))){
			//std::cout << "Managed to optimize into correct direction! which is: " << convert<Number,double>(mConstraints.row(0)).transpose() << std::endl;
			// The vectors are EXACTLY the same -> to find point on plane and to avoid squareroot computations, return vector
			// which contains zeroes except of the position with the first non-zero coeff, which is set to the stored distance.
			vector_t<Number> pointOnPlane = vector_t<Number>::Zero(l.rows());
			unsigned i = 0;
			while(i<l.rows() && l(i) == 0) {
				++i;
			}
			if(l(i) == 0) {
				return EvaluationResult<Number>(); // TODO: Check if this is correct -> we evaluated something weird with a weird direction (both zero vertors).
			}
			pointOnPlane(i) = mConstraintConstants(0);
			return EvaluationResult<Number>(mConstraintConstants(0),pointOnPlane,SOLUTION::FEAS);
		} else {
			//std::cout << "Eval to infty." << std::endl;
			return EvaluationResult<Number>(0,SOLUTION::INFTY);
		}
	}

	EvaluationResult<Number> res(mOpt.evaluate(l, useExact));
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
	std::cout << __func__ << ": " << *this << " evaluated in direction " << convert<Number,double>(l) << " results in " << res << std::endl;
#endif
#if defined(HYPRO_USE_SMTRAT) || defined(HYPRO_USE_Z3) || defined(HYPRO_USE_SOPLEX)
	assert(res.errorCode != SOLUTION::FEAS || this->contains(res.optimumValue));
#endif
	assert( l.rows() == mDimension );
	return res;
}

template <typename Number>
std::vector<EvaluationResult<Number>> PolytopeSupportFunction<Number>::multiEvaluate( const matrix_t<Number> &_A, bool useExact, bool setTemplate ) const {
	assert( _A.cols() == mDimension );
	std::vector<EvaluationResult<Number>> res;
	//std::cout << "POLY SF, evaluate in directions " << convert<Number,double>(_A) << std::endl << "POLY SF IS " << *this << std::endl;

	// catch half-space
	if(mConstraints.rows() == 1) {
		vector_t<Number> pointOnPlane = vector_t<Number>::Zero(mDimension);
		assert(mConstraints.row(0).nonZeros() != 0 );
		unsigned nonZeroPos = 0;
		while(mConstraints(0,nonZeroPos) == 0) { ++nonZeroPos; }
		pointOnPlane(nonZeroPos) = mConstraintConstants(0);
		for ( unsigned index = 0; index < _A.rows(); ++index ) {
			std::pair<bool,Number> dependent = linearDependent(vector_t<Number>(mConstraints.row(0)), vector_t<Number>(_A.row(index)));
			if( dependent.first ) {
				if( dependent.second > 0 ) {
					//std::cout << "Vectors " << convert<Number,double>(vector_t<Number>(mConstraints.row(0))).transpose() << " and " << convert<Number,double>(vector_t<Number>(_A.row(index))).transpose() << " are dependent!" << std::endl;
					//std::cout << "Factor: " << dependent.second << std::endl;
					res.emplace_back(mConstraintConstants(0)*dependent.second, pointOnPlane, SOLUTION::FEAS);
				} else {
					res.emplace_back(1, pointOnPlane, SOLUTION::INFTY);
				}
			} else {
				res.emplace_back(1, pointOnPlane, SOLUTION::INFTY);
			}
		}
		return res;
	}

	for ( unsigned index = 0; index < _A.rows(); ++index ) {
		res.emplace_back(mOpt.evaluate( _A.row( index ), useExact ));
	}
	assert(res.size() == std::size_t(_A.rows()));
	return res;
}

template <typename Number>
bool PolytopeSupportFunction<Number>::contains( const Point<Number> &_point ) const {
	return this->contains( _point.rawCoordinates() );
}

template <typename Number>
bool PolytopeSupportFunction<Number>::contains( const vector_t<Number> &_point ) const {
	assert(mConstraints.rows() == mConstraintConstants.rows());
	assert(mConstraints.cols() == _point.rows());
	//std::cout << "Matrix " << mConstraints << " contains " << _point << std::endl;
	for ( unsigned rowIt = 0; rowIt < mConstraints.rows(); ++rowIt ) {
		if( mConstraints.row(rowIt).dot(_point) > mConstraintConstants(rowIt) ){
			//std::cout << __func__ << ": Value is " <<  mConstraints.row(rowIt).dot(_point) << " but has to be <= " << mConstraintConstants(rowIt) << std::endl;
			return false;
		}
	}
	return true;
}

template <typename Number>
bool PolytopeSupportFunction<Number>::empty() const {
	return !mOpt.checkConsistency();
}

template <typename Number>
void PolytopeSupportFunction<Number>::print() const{
    std::cout << convert<Number,double>(mConstraints) << std::endl;
    std::cout << convert<Number,double>(mConstraintConstants) << std::endl;
}

template<typename Number>
std::string PolytopeSupportFunction<Number>::createCode(unsigned index) const {
	std::stringstream res;
	std::string tmp = createCode(mConstraints);
	std::string tmp2 = createCode(mConstraintConstants, index);
	res << tmp << tmp2;
	res << "PolytopeSupportFunction<TypeParam> psf" << index << " = PolytopeSupportFunction<TypeParam>(matrix" << index << ", vector" << index << ");\n";
	return res.str();

}

template<typename Number>
void PolytopeSupportFunction<Number>::removeRedundancy() {
	if(mConstraints.rows() > 1){

		std::vector<std::size_t> redundant = mOpt.redundantConstraints();
		//std::cout << __func__ << ": found " << redundant.size() << " redundant constraints." << std::endl;

		if(!redundant.empty()){
			matrix_t<Number> newConstraints = matrix_t<Number>(mConstraints.rows()-redundant.size(), mConstraints.cols());
			vector_t<Number> newConstants = vector_t<Number>(mConstraints.rows()-redundant.size());
			int insertionIndex = newConstants.rows()-1;
			for(int rowIndex = mConstraints.rows()-1; rowIndex >=0; --rowIndex) {
				if(redundant.empty() || unsigned(rowIndex) != redundant.back()){
					newConstraints.row(insertionIndex) = mConstraints.row(rowIndex);
					newConstants(insertionIndex) = mConstraintConstants(rowIndex);
					--insertionIndex;
				} else {
					redundant.pop_back();
				}
			}
			assert(insertionIndex == -1);
			mConstraints = newConstraints;
			mConstraintConstants = newConstants;
			mOpt = Optimizer<Number>(mConstraints,mConstraintConstants);
		}
		assert(redundant.empty());
	}
}

}  // namespace hypro
