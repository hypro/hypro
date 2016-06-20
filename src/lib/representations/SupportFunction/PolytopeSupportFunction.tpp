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

namespace hypro {

template <typename Number>
PolytopeSupportFunction<Number>::PolytopeSupportFunction( matrix_t<Number> constraints,
														  vector_t<Number> constraintConstants )
	: mConstraints( constraints ), mConstraintConstants( constraintConstants ), mDimension(mConstraints.cols()) {
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
}

template<typename Number>
PolytopeSupportFunction<Number>::PolytopeSupportFunction( const std::vector<Point<Number>>& _points ) {
	if ( !_points.empty() ) {
		mDimension = _points.begin()->dimension();
		// check affine independence - verify object dimension.
		std::vector<vector_t<Number>> coordinates;
		for(const auto& vertex : _points){
			coordinates.emplace_back(vertex.rawCoordinates());
		}
		int effectiveDim = effectiveDimension(coordinates);
		assert(effectiveDim >= 0);

		if ( unsigned(effectiveDim) < mDimension ) {
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
			std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( _points ).first;
			unsigned rowCnt = 0;
			for ( auto &facet : facets ) {
				assert(facet->halfspace().contains(points));
				mConstraints.row(rowCnt) = facet->halfspace().normal();
				mConstraintConstants(rowCnt) = facet->halfspace().offset();
				++rowCnt;
			}
			facets.clear();
		}
	}
}

template <typename Number>
PolytopeSupportFunction<Number>::PolytopeSupportFunction( const PolytopeSupportFunction<Number> &_origin )
	: mConstraints( _origin.constraints() ), mConstraintConstants( _origin.constants()), mDimension(mConstraints.cols() ) {
}

template <typename Number>
PolytopeSupportFunction<Number>::~PolytopeSupportFunction() {
}

template <typename Number>
PolytopeSupportFunction<Number>& PolytopeSupportFunction<Number>::operator=(const PolytopeSupportFunction<Number>& _orig){
    this->mConstraints = _orig.mConstraints;
    this->mConstraintConstants = _orig.mConstraintConstants;
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

template <typename Number>
EvaluationResult<Number> PolytopeSupportFunction<Number>::evaluate( const vector_t<Number> &l ) const {
	EvaluationResult<Number> result;
	if(mConstraints.rows() > 0) {
		Optimizer<Number>& opt = Optimizer<Number>::getInstance();
		opt.setMatrix(mConstraints);
		opt.setVector(mConstraintConstants);
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << "Call to optimizer." << std::endl;
#endif
		result = opt.evaluate(l);
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << __func__ << ": " << *this << " evaluated in direction " << convert<Number,double>(l) << " results in " << carl::toDouble(result.supportValue) << std::endl;
#endif
		assert(result.errorCode != SOLUTION::FEAS || this->contains(result.optimumValue));
		assert( l.rows() == mDimension );
	} else {
		result.errorCode = SOLUTION::INFTY;
	}
	return result;
}

template <typename Number>
std::vector<EvaluationResult<Number>> PolytopeSupportFunction<Number>::multiEvaluate( const matrix_t<Number> &_A ) const {
	assert( _A.cols() == mDimension );
	std::vector<EvaluationResult<Number>> res;
	std::cout << "POLY SF, evaluate in directions " << convert<Number,double>(_A) << std::endl << "POLY SF IS " << *this << std::endl;
	for ( unsigned index = 0; index < _A.rows(); ++index ) {
		res.push_back(evaluate( _A.row( index ) ));
		assert(res.back().errorCode != SOLUTION::FEAS || this->contains(res.back().optimumValue));
		//assert(this->contains(res.back().optimumValue));
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
	Optimizer<Number>& opt = Optimizer<Number>::getInstance();
	opt.setMatrix(mConstraints);
	opt.setVector(mConstraintConstants);
	return !opt.checkConsistency();
}

template <typename Number>
void PolytopeSupportFunction<Number>::print() const{
    std::cout << convert<Number,double>(mConstraints) << std::endl;
    std::cout << convert<Number,double>(mConstraintConstants) << std::endl;
}
}  // namespace
